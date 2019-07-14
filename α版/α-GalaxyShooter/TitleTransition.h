//=============================================================================
// �^�C�g���J�ډ摜�`�揈�� [TitleTransition.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

#define TITLE_TRANS_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// �^�C�g���J�ډ摜�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TitleTransition :public Sprite
{
private:
	// Data
	int playerNumber;											// �v���C���[�ԍ�
	static int cntUI;											// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 titleTransTex;					// �^�C�g���J�ڃe�N�X�`��
public:
	TitleTransition(void);
	~TitleTransition(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

