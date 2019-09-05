//-----------------------------------------------------------------------------
// インスタンシングエフェクト処理 [InstancingEffect.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "InstancingEffect.h"
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InstancingEffect::initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture)
{
	InstancingBillboard::initialize(device, effect, texture);

	return S_OK;
}
//=============================================================================
// 描画処理
//=============================================================================
void InstancingEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	if (!onRender)return;
	if (renderNum <= 0)return;
	// 回転を打ち消す。
	D3DXMATRIX cancelRotation = view;
	cancelRotation._41 = cancelRotation._42 = cancelRotation._43 = 0;
	D3DXMatrixInverse(&cancelRotation, NULL, &cancelRotation);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//αテスト
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	device->SetRenderState(D3DRS_ALPHAREF, 0x00);

	// αブレンドを行う
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// αソースカラーの指定
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//加算合成
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);	// 結果 = 転送先(DEST) ＋ 転送元(SRC)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ラインティングを無効にする
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//インスタンス宣言
	device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | renderNum);
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

	//device->SetTexture(0, texture);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	////device->SetTexture(0, NULL);
	effect->EndPass();
	effect->End();

	//後始末
	device->SetStreamSourceFreq(0, 1);
	device->SetStreamSourceFreq(1, 1);
	// αブレンドを切る
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// ラインティングを有効にする
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
