//-----------------------------------------------------------------------------
// �`���M������ [Chingin.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/8/1
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingBillboard.h"


//------------------------------------
// �`���M���C���X�^���V���O�`��N���X
//------------------------------------
class InstancingChingin :public InstancingBillboard
{
public:
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
};


