//=============================================================================
// �L�[�{�[�h����������� [KeyOpe.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

#define KEY_OPE_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// �L�[�{�[�h��������̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class KeyOpe :public Sprite
{

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureKeyOpe;		// �L�[�{�[�h��������e�N�X�`��
	Sprite keyOpe;									// �L�[�{�[�h�������

public:
	KeyOpe(void);
	~KeyOpe(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

