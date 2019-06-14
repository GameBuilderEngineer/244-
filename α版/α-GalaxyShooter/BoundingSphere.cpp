#include "BoundingSphere.h"



BoundingSphere::BoundingSphere()
{
	ZeroMemory(this, sizeof(BoundingSphere));
}


BoundingSphere::~BoundingSphere()
{
}


void BoundingSphere::initialize(LPDIRECT3DDEVICE9 device,D3DXVECTOR3* _position, LPD3DXMESH ownerMesh)
{
	position = _position;

	// メッシュの頂点バッファをロックする
	LPVOID buffer;
	ownerMesh->LockVertexBuffer(D3DLOCK_READONLY, &buffer);

	// メッシュの境界球を求める
	D3DXComputeBoundingSphere(
		(D3DXVECTOR3 *)buffer,
		ownerMesh->GetNumVertices(),
		ownerMesh->GetNumBytesPerVertex(),
		&center, &radius);

	// ロックした頂点バッファをアンロック
	ownerMesh->UnlockVertexBuffer();

	//メッシュを作成
	D3DXCreateSphere(device, radius, 8, 8, &mesh, NULL);

}
void BoundingSphere::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX owner)
{
	// ライティングモードを設定
	device->SetRenderState(D3DRS_LIGHTING, true);
	// レンダリングモードの設定
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//ワイヤーフレーム表示
	// アルファ・ブレンディングを行う
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// 半透明処理を行う
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	D3DMATERIAL9 matDef;
	// 現在のマテリアルを取得
	device->GetMaterial(&matDef);

	//ワールドマトリックスの設定
	device->SetTransform(D3DTS_WORLD, &owner);

	// テクスチャの設定をNULLにする
	device->SetTexture(0, NULL);

	// マテリアル情報に対するポインタを取得
	D3DMATERIAL9 material;

	// マテリアル情報を緑色にし、少し透過
	material.Diffuse = D3DCOLORVALUE(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f));
	material.Ambient = D3DCOLORVALUE(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	material.Specular = D3DCOLORVALUE(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	material.Emissive = D3DCOLORVALUE(D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));
	material.Power = 120.0f;

	// マテリアルの設定
	device->SetMaterial(&material);

	//描画
	mesh->DrawSubset(0);

	//マテリアルをデフォルトに戻す
	device->SetMaterial(&matDef);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);//ワイヤーフレーム表示
}

bool BoundingSphere::collide(D3DXVECTOR3 targetCenter, float targetRadius)
{
	//２つの物体の中心間の距離を求める
	float length = D3DXVec3Length(&(targetCenter - center));
	// その距離が、２つの物体の半径を足したものより小さい場合、境界球同士が重なっている（衝突している）ということ
	if (length <= radius + targetRadius)
	{
		return true;
	}
	return false;
}