//=============================================================================
// �`���[�g���A���`��w�b�_�[ [Tutorial2D.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIAL2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// �`���[�g���A���̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Tutorial2D :public Sprite
{
private:

	Sprite tuto2;
	Sprite tuto3;
	Sprite tuto4;

	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureTutorial2D;	// �e�N�X�`��1
	static LPDIRECT3DTEXTURE9 textureTutorial2D2;	// �e�N�X�`��2
	static LPDIRECT3DTEXTURE9 textureTutorial2D3;	// �e�N�X�`��3
	static LPDIRECT3DTEXTURE9 textureTutorial2D4;	// �e�N�X�`��4

public:
	Tutorial2D(void);
	~Tutorial2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	int next;

};

