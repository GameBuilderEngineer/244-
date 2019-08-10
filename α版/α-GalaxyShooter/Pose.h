//=============================================================================
// Pose�`��w�b�_�[ [Pose.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POSE_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// �|�[�Y�̐F
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Pose :public Sprite
{
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 texturePose;			// �e�N�X�`��

public:
	Pose(void);
	~Pose(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	bool poseon;									// �|�[�Y�t���O
};

