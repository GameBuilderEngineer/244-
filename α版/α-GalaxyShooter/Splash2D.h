//=============================================================================
// Splash�`�揈�� [Splash2D.h]
//
//=============================================================================
#pragma once
#include "AbstractScene.h"
#include "Sprite.h"

#define SPLASH2D_COLOR		(D3DCOLOR_RGBA(255, 255, 255,alphaColor))	// �X�v���b�V���̐F
#define SPLASH_ALPHA_MAX	(255)										// �X�v���b�V���ő�A���t�@�l
#define SPLASH_TIME			(200)										// �X�v���b�V�����Ŏ���
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Splash2D :public Sprite
{

private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	static int cntUI;								// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 textureSplash2D;		// �e�N�X�`��

public:
	Splash2D(void);
	~Splash2D(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber,TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void fade(void);								// �t�F�[�h����
	void fadein(void);								// �t�F�[�h�C��
	void fadeout(void);								// �t�F�[�h�A�E�g
	bool fadeon;									// �t�F�[�h�t���O
	bool gotitle;									// �^�C�g���J�ڃt���O
};

