//=============================================================================
// Operation�`�揈�� [Operation2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"

#define OPERATION2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))			// ����m�F�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Operation2D :public Sprite
{

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureOperation2D;	// �e�N�X�`���P
	Sprite operation2D;								// ����m�F2D

public:
	Operation2D(void);
	~Operation2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

