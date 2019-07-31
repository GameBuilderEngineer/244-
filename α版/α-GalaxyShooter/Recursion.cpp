#include "Recursion.h"

namespace recursionNS
{

}

Recursion::Recursion()
{
	weightCenter = D3DXVECTOR3(0, 0, 0);
}


Recursion::~Recursion()
{
}

HRESULT Recursion::initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3* _vertexArray, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect)
{
	//テクスチャをセット
	texture = _texture;

	//シェーダーをセット
	effect = _effect;

	//頂点を構成するメモリーパイル位置情報をセット
	vertexArray = new D3DXVECTOR3[5];
	for (int i = 0; i < 5; i++)
		vertexArray[i] = _vertexArray[i];

	//頂点座標の作成
	Vertex3D vertex[5];
	for (int i = 0; i < 5; i++)
	{
		vertex[i].coord = _vertexArray[i];
	}
	//UV座標の作成
	UV uv[5] = {
		D3DXVECTOR2(0.0f,0.5f),
		D3DXVECTOR2(0.375f,0.0f),
		D3DXVECTOR2(1.0f,0.1875f),
		D3DXVECTOR2(1.0f,0.8125f),
		D3DXVECTOR2(0.375f,1.0f),
	};

	//インデックスの作成
	WORD index[3 * 3] = {
		4,0,1,
		1,3,4,
		1,2,3
	};

	//頂点バッファの作成
	device->CreateVertexBuffer(sizeof(vertex), 0, 0, D3DPOOL_MANAGED, &vertexBuffer, 0);
	copyVertexBuffer(sizeof(vertex), &vertex, vertexBuffer);
	//UVバッファの作成
	device->CreateVertexBuffer(sizeof(uv), 0, 0, D3DPOOL_MANAGED, &uvBuffer, 0);
	copyVertexBuffer(sizeof(uv), &uv, uvBuffer);

	//インデックスバッファの作成
	device->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	void* p = 0;
	indexBuffer->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuffer->Unlock();

	//頂点宣言
	D3DVERTEXELEMENT9 vertexElement[] = {
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},//頂点座標
		{1,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},//UV
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(vertexElement, &declation);

	//重心を求める
	calculationCenter(vertexArray,5);

	//球コリジョンの半径を作成する
	float radius = D3DXVec3Length(&(vertexArray[0]-weightCenter));
	for (int i = 1; i < 5; i++)
	{
		radius = max(radius, D3DXVec3Length(&(vertexArray[i] - weightCenter)));
	}
	//球コリジョンを半径と中心位置で初期化
	boundingSphere.initialize(device, radius);

	onRender = true;

	return S_OK;
}


void Recursion::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	if (onRender == false)return;
	// αブレンドを行う
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// αソースカラーの指定
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// カリングはしない
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	//頂点宣言を追加
	device->SetVertexDeclaration(declation);

	//デバイスデータストリームにメッシュの頂点バッファをバインド
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex3D));
	device->SetStreamSource(1, uvBuffer, sizeof(Vertex3D), sizeof(UV));
	

	//インデックスバッファをセット
	device->SetIndices(indexBuffer);
	
	//シェーダー操作
	effect->SetTechnique("main");
	effect->SetMatrix("matrixProjection", &projection);
	effect->SetMatrix("matrixView", &view);
	effect->SetTexture("textureDecal", texture);

	effect->Begin(0, 0);
	effect->BeginPass(0);

	//描画
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 3);

	effect->EndPass();
	effect->End();

	//後始末
	// カリングを有効にする
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//重心位置＆衝突判定範囲描画
	worldMatrix = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		weightCenter.x,weightCenter.y,weightCenter.z,1.0f
	};
	boundingSphere.render(device, worldMatrix);

}


void Recursion::calculationCenter(D3DXVECTOR3* vertex, int vertexNum)
{
	//三角形の重心を求める。
	D3DXVECTOR3* eachWeightCenter = new D3DXVECTOR3[vertexNum-2];
	for (int i = 0; i < vertexNum-2;i++)
	{
		eachWeightCenter[i] = (vertex[vertexNum-1] + vertex[i] + vertex[i + 1])/3;
	}
	//加重平均に要する重み（面積）を外積により算出：三角形なので、本来は1/2するが省略
	float* eachWeight = new float[vertexNum-2];
	float sumWeight = 0;
	for (int i = 0; i < vertexNum - 2; i++)
	{
		D3DXVECTOR3 v1 = vertex[i] - vertex[vertexNum - 1];
		D3DXVECTOR3 v2 = vertex[i+1] - vertex[vertexNum - 1];
		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &v1, &v2);
		eachWeight[i] = D3DXVec3Length(&cross);
		sumWeight += eachWeight[i];
	}
	//加重平均により重心を求める。
	weightCenter = D3DXVECTOR3(0, 0, 0);
	for (int i = 0; i < vertexNum - 2; i++)
	{
		weightCenter += eachWeightCenter[i] * eachWeight[i];
	}
	weightCenter /= sumWeight;

	delete[] eachWeight;
	delete[] eachWeightCenter;
}

bool Recursion::collide(D3DXVECTOR3 targetPosition,D3DXVECTOR3 targetCenter, float targetRadius, D3DXMATRIX targetMatrix)
{
	//【判定1】
	//球との衝突判定：おおよその衝突検知
	if (boundingSphere.collide(targetCenter, targetRadius, worldMatrix, targetMatrix) == false)
		return false;

	//【判定2】
	//リカージョンのポリゴンと衝突しているか検知
	//重心をもとに構成される三角ポリゴン５枚との衝突検知を行う
	//ターゲットの位置情報を三角ポリゴンと同一平面上に補正したうえで、
	//三角ポリゴンとの内外判定を行う
	bool collide = false;
	for (int i = 0; i < 5; i++)
	{
		if (collide)continue;//いずれかで衝突が検知できている場合は判定しない
		int j;
		if( i+1 >= 5)j = 0;
		else j = i+1;
		//【辺ベクトル】三角ポリゴンを構成する辺ベクトルを作成
		D3DXVECTOR3 side[3];
		side[0] = vertexArray[i] - weightCenter;
		side[1] = vertexArray[j] - vertexArray[i];
		side[2] = weightCenter - vertexArray[j];

		//【法線ベクトル】三角ポリゴンの法線の作成
		D3DXVECTOR3 normal = D3DXVECTOR3(0,0,0);
		D3DXVec3Cross(&normal, &side[0],&side[1]);
		D3DXVec3Normalize(&normal, &normal);//正規化

		//【平面点】対象の位置情報を三角ポリゴンが属する平面上へ補正する
		D3DXVECTOR3 correctionVector = normal * D3DXVec3Dot(&normal,&(targetPosition-weightCenter));
		D3DXVECTOR3 pointOnPlane = targetPosition - correctionVector;

		//【対象ベクトル】三角ポリゴンの３頂点から内外判定を行う点（位置情報）へのベクトルを作成する
		D3DXVECTOR3 toTarget[3];
		toTarget[0] = pointOnPlane - vertexArray[i];
		toTarget[1] = pointOnPlane - vertexArray[j];
		toTarget[2] = pointOnPlane - weightCenter;

		//【外積ベクトル】辺ベクトルと対象ベクトルの外積を算出する
		D3DXVECTOR3 cross[3];
		for (int k = 0; k < 3; k++)
		{
			D3DXVec3Cross(&cross[k], &side[k], &toTarget[k]);
			D3DXVec3Normalize(&cross[k], &cross[k]);//内積による方向比較のため正規化
		}

		//【内積による方向比較】
		//TRUE：外積ベクトルがすべて同じ方向の場合(内積が１(誤差防止のため0.99fとの比較))
		//FALSE：外積ベクトルのいずれかが別の方向の場合(内積が－１（１以外の場合はすべて）)
		if (D3DXVec3Dot(&cross[0],&cross[1]) < 0.99f)
		{
			//別方向
		}
		else if (D3DXVec3Dot(&cross[1], &cross[2]) < 0.99f)
		{
			//別方向
		}
		else
		{
			//同一方向
			collide = true;
		}
	}

	return collide;

}