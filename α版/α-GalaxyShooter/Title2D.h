//=============================================================================
// �^�C�g���`��w�b�_�[ [Title2D.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255,255))	// �^�C�g���̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Title2D :public Sprite
{
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureTitle2D;		// �e�N�X�`��

public:
	Title2D(void);
	~Title2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

