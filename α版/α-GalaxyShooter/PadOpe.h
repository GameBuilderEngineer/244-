//=============================================================================
// �p�b�h����������� [PadOpe.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"

#define PAD_OPE_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// �p�b�h��������̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PadOpe :public Sprite
{

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 texturePadOpe;		// �p�b�h��������e�N�X�`��
	Sprite padOpe;									// �p�b�h�������

public:
	PadOpe(void);
	~PadOpe(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

