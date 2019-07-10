#include "InstancingBillboard.h"



InstancingBillboard::InstancingBillboard()
{
}


InstancingBillboard::~InstancingBillboard()
{
	delete[] position;
}

HRESULT InstancingBillboard::initialize(LPDIRECT3DDEVICE9 device)
{
	InstancingBillboardVertex vertex[4] = {
		{D3DXVECTOR2( -1.0f,  1.0f),D3DXVECTOR2(0.0f,0.0f)},
		{D3DXVECTOR2(  1.0f,  1.0f),D3DXVECTOR2(1.0f,0.0f)},
		{D3DXVECTOR2( -1.0f, -1.0f),D3DXVECTOR2(0.0f,1.0f)},
		{D3DXVECTOR2(  1.0f, -1.0f),D3DXVECTOR2(1.0f,1.0f)},
	};
	//頂点バッファの作成
	device->CreateVertexBuffer(sizeof(vertex), 0, 0, D3DPOOL_MANAGED, &vertexBuffer, 0);//サイズ確保
	copyVertexBuffer(sizeof(vertex), &vertex, vertexBuffer);

	WORD index[6] = { 
		0,1,2,
		2,1,3 
	};

	//インデックスバッファの作成
	device->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	void *p = 0;
	indexBuffer->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuffer->Unlock();

	//位置情報バッファの作成
	device->CreateVertexBuffer(sizeof(D3DXVECTOR3)*num, 0, 0, D3DPOOL_MANAGED, &positionBuffer, 0);
	copyVertexBuffer(sizeof(D3DXVECTOR3)*num, position, positionBuffer);

	//頂点宣言
	D3DVERTEXELEMENT9 vertexElement[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//頂点座標
		{ 0, sizeof(D3DXVECTOR2), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },//UV
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD, 1 },	//位置
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(vertexElement, &declation);

	//シェーダーを読み込む
	setShaderDirectory();
	HRESULT hr;
	LPD3DXBUFFER err = NULL;
	if (FAILED(hr = D3DXCreateEffectFromFile(device, "InstancingBillboard.fx", NULL, NULL, 0, NULL, &effect, &err)))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "ERROR", MB_OK);
	}
	
	//テクスチャを読み込む
	setVisualDirectory();
	D3DXCreateTextureFromFileA(device, "ring.png", &texture);

	return S_OK;
}

void InstancingBillboard::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	//回転を打ち消す。
	//D3DXMATRIX cancelRotation = view;
	//cancelRotation._41 = cancelRotation._42 = cancelRotation._43 = 0;
	//D3DXMatrixInverse(&cancelRotation, NULL,&cancelRotation);

	// αブレンドを行う
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// αソースカラーの指定
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//インスタンス宣言
	device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | num);
	device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	// 頂点宣言を通知
	device->SetVertexDeclaration(declation);
	
	//デバイスデータストリームにメッシュの頂点バッファをバインド
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(InstancingBillboardVertex));
	device->SetStreamSource(1, positionBuffer, 0, sizeof(D3DXVECTOR3));

	//インデックスバッファをセット
	device->SetIndices(indexBuffer);

	effect->SetTechnique("mainTechnique");
	//effect->SetMatrix("cancelRotation", &cancelRotation);
	effect->SetMatrix("matrixProjection", &projection);
	effect->SetMatrix("matrixView", &view);
	effect->SetTexture("planeTexture", texture);
	effect->Begin(0, 0);
	effect->BeginPass(0);
		
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	effect->EndPass();
	effect->End();

	//後始末
	device->SetStreamSourceFreq(0, 1);
	device->SetStreamSourceFreq(1, 1);

}

void InstancingBillboard::createPositionSpherical(int _num ,float radius)
{
	num = _num;
	//位置バッファの作成
	position = new D3DXVECTOR3[num];
	for (int i = 0; i < num; i++)
	{
		D3DXVECTOR3 pos((float)(rand() % 100 - 50),(float)(rand() % 100 - 50),(float)(rand() % 100 - 50));
		D3DXVec3Normalize(&pos, &pos);
		pos *= radius;
		position[i] = pos;
	}
}