#include "Recursion.h"

namespace recursionNS
{

}

Recursion::Recursion()
{
}


Recursion::~Recursion()
{
}

HRESULT Recursion::initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3* vertexArray, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect)
{
	//テクスチャをセット
	texture = _texture;

	//シェーダーをセット
	effect = _effect;

	//頂点座標の作成
	Vertex3D vertex[5];
	for (int i = 0; i < 5; i++)
	{
		vertex[i].coord = vertexArray[i];
	}
	//UV座標の作成
	UV uv[5] = {
		D3DXVECTOR2(0.0f,0.5f),
		D3DXVECTOR2(0.375f,0.0f),
		D3DXVECTOR2(1.0f,0.1875f),
		D3DXVECTOR2(1.0f,0.8125f),
		D3DXVECTOR2(0.375f,1.0f)
	};

	//インデックスの作成
	WORD index[3 * 3] = {
		1,2,5,
		2,4,5,
		2,3,4
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

}


void Recursion::calculationCenter()
{

}