//-----------------------------------------------------------------------------
// �C���X�^���V���O�G�t�F�N�g�w�b�_�[ [InstancingEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingBillboard.h"
//------------------------------------
// �G�t�F�N�g�C���X�^���V���O�`��N���X
//------------------------------------
class InstancingEffect :public InstancingBillboard
{
public:
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
};
