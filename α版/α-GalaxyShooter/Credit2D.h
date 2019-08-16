//=============================================================================
// �N���W�b�g�`��w�b�_�[ [Credit2D.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CREDIT2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// �N���W�b�g2D�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Credit2D :public Sprite
{
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureCredit2D;		// �e�N�X�`��

public:
	Credit2D(void);
	~Credit2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

