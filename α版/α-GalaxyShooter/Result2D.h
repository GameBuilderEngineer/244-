//=============================================================================
// Result�`�揈�� [Result2D.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Result2D :public Sprite
{

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 buffTexture;			// �e�N�X�`��

public:
	Result2D(void);
	~Result2D(void);

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);

};

