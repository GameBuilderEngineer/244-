//=============================================================================
// Tutorial�`�揈�� [Tutorial2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"


#define TUTORIAL2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// �`���[�g���A���̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Tutorial2D :public Sprite
{

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureTutorial2D;	// �e�N�X�`���P
	Sprite tutorial2D;								// �`���[�g���A��2D

public:
	Tutorial2D(void);
	~Tutorial2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

