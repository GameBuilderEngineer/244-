#include "Object.h"
using namespace ObjectNS;

Object::Object(){

}

Object::~Object(){

}

HRESULT Object::initialize(LPDIRECT3DDEVICE9 pDevice) {
	// Xファイルからメッシュをロードする	
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	if (FAILED(D3DXLoadMeshFromX("Box.x", D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &pD3DXMtrlBuffer, NULL,
		&dwNumMaterials, &pMesh)))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました", NULL, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pMeshMaterials = new D3DMATERIAL9[dwNumMaterials];
	pMeshTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];

	for (DWORD i = 0; i < dwNumMaterials; i++)
	{
		pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
		pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				d3dxMaterials[i].pTextureFilename,
				&pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
	pD3DXMtrlBuffer->Release();

	D3DXCreateEffectFromFile(pDevice, "Min.fx", NULL, NULL, 0, NULL, &g_pEffect, NULL);

	WorldPosXYZ* worldPos = new WorldPosXYZ[WIDTH_NUM*DEPTH_NUM]; //ワールド座標位置バッファ
	for (int w = 0; w < WIDTH_NUM; w++) {
		for (int d = 0; d < DEPTH_NUM; d++) {
			int e = d * WIDTH_NUM + w;
			worldPos[e].x = 50 * w;
			worldPos[e].z = 50 * d;
		}
	}

	//頂点バッファ作成
	pDevice->CreateVertexBuffer(sizeof(WorldPosXYZ)*WIDTH_NUM*DEPTH_NUM, 0, 0, D3DPOOL_MANAGED, &worldPosBuf, 0);
	copyBuf(sizeof(WorldPosXYZ)*WIDTH_NUM*DEPTH_NUM, worldPos, worldPosBuf);

	//頂点宣言作成
	D3DVERTEXELEMENT9 declElems[] = {
		{1,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,1},	//ワールド位置
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(declElems, &decl);


	pMesh->GetVertexBuffer(&vtxBuf);

	delete[] worldPos;

	return S_OK;
}

void Object::update() {

}

void Object::render(LPDIRECT3DDEVICE9 pDevice) {
	//ワールドトランスフォーム（絶対座標変換）
	D3DXMATRIX mWorld, mRotation;
	D3DXMatrixRotationY(&mWorld, timeGetTime() / 3000.0f);
	D3DXMatrixRotationX(&mRotation, 0.5f);
	D3DXMatrixMultiply(&mWorld, &mWorld, &mRotation);
	// ビュートランスフォーム（視点座標変換）
	D3DXVECTOR3 vEyePt(0.0f, 2.0f, -50.0f); //カメラ（視点）位置
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//注視位置
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置
	D3DXMATRIX mView;
	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);
	// プロジェクショントランスフォーム（射影変換）
	D3DXMATRIX mProj;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100000.0f);


	//インスタンス宣言
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | (WIDTH_NUM*DEPTH_NUM));
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//頂点とインデックスを設定
	pDevice->SetVertexDeclaration(decl);
	pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(Vtx));
	pDevice->SetStreamSource(1, worldPosBuf, 0, sizeof(WorldPosXYZ));



	g_pEffect->SetTechnique("texMinimum");
	D3DXMATRIX mAll = mWorld * mView * mProj;
	g_pEffect->SetMatrix("mWVP", &mAll);
	g_pEffect->Begin(NULL, 0);
	g_pEffect->BeginPass(0);
	for (DWORD i = 0; i < dwNumMaterials; i++)
	{
		g_pEffect->SetTexture("texMinimum", pMeshTextures[i]);
		pMesh->DrawSubset(i);
	}
	g_pEffect->EndPass();
	g_pEffect->End();
}

void Object::unInitialize()
{

}
