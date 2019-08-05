//-----------------------------------------------------------------------------
// チンギン処理 [Chingin.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/8/1
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingBillboard.h"


//------------------------------------
// チンギンインスタンシング描画クラス
//------------------------------------
class InstancingChingin :public InstancingBillboard
{
public:
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
};


