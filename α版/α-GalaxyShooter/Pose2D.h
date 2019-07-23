//=============================================================================
// Pose�`�揈�� [Pose2D.h]
//
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"

#define POSE2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// �|�[�Y�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Pose2D :public Sprite
{

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 texturePose2D;		// �e�N�X�`��

public:
	Pose2D(void);
	~Pose2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
};

