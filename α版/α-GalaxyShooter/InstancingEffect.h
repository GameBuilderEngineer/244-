//-----------------------------------------------------------------------------
// インスタンシングエフェクトヘッダー [InstancingEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingBillboard.h"
//------------------------------------
// エフェクトインスタンシング描画クラス
//------------------------------------
class InstancingEffect :public InstancingBillboard
{
public:
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
};
