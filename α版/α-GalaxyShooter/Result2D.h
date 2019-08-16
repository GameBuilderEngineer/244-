//=============================================================================
// ���U���g�`��w�b�_�[ [Result2D.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT2D_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// ���U���g2D�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Result2D :public Sprite
{
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 result2DTexture;		// �e�N�X�`��

public:
	Result2D(void);
	~Result2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

