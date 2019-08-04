//=============================================================================
// �L�����N�^�[�Z���N�g�o�[UI���� [CharaSelectBarUI.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

namespace charaSelectBarUINS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CharaSelectBarUI :public Sprite {

private:
	// Data
	int playerNumber;									// �v���C���[�ԍ�
	static int cntUI;									// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 selectBarLightTexture;	// �Z���N�g�o�[���C�g�e�N�X�`��
	static LPDIRECT3DTEXTURE9 selectBarLightTexture2;	// �Z���N�g�o�[���C�g�e�N�X�`��2
	static LPDIRECT3DTEXTURE9 selectNoTexture;			// �Z���N�g�i���o�[�e�N�X�`��
	static LPDIRECT3DTEXTURE9 selectNoTexture2;			// �Z���N�g�i���o�[�e�N�X�`��2
	static LPDIRECT3DTEXTURE9 selectCursorTexture;		// �Z���N�g�J�[�\���e�N�X�`��
	static LPDIRECT3DTEXTURE9 selectCursorTexture2;		// �Z���N�g�J�[�\���e�N�X�`��2
	static LPDIRECT3DTEXTURE9 selectPlayerLogoTexture;	// �Z���N�g�v���C���[���S�e�N�X�`��
	static LPDIRECT3DTEXTURE9 nameEveEngTexture;		// �C�����O�p��e�N�X�`��
	static LPDIRECT3DTEXTURE9 nameEveEngTexture2;		// �C�����O�p��e�N�X�`��2
	static LPDIRECT3DTEXTURE9 nameAdamEngTexture;		// �A�_�����O�p��e�N�X�`��
	static LPDIRECT3DTEXTURE9 nameAdamEngTexture2;		// �A�_�����O�p��e�N�X�`��2
	static LPDIRECT3DTEXTURE9 nameEveJpTexture;			// �C�����O���{��e�N�X�`��
	static LPDIRECT3DTEXTURE9 nameEveJpTexture2;		// �C�����O���{��e�N�X�`��2
	static LPDIRECT3DTEXTURE9 nameAdamJpTexture;		// �A�_�����O���{��e�N�X�`��
	static LPDIRECT3DTEXTURE9 nameAdamJpTexture2;		// �A�_�����O���{��e�N�X�`��2

	Sprite charaSelectBar;
	Sprite charaSelectBar2;
	Sprite charaSelectNo;
	Sprite charaSelectNo2;
	Sprite charaSelectCursor;
	Sprite charaSelectCursor2;
	Sprite charaSelectLogo;
	Sprite nameEveEng;
	Sprite nameEveEng2;
	Sprite nameAdamEng;
	Sprite nameAdamEng2;
	Sprite nameEveJp;
	Sprite nameEveJp2;
	Sprite nameAdamJp;
	Sprite nameAdamJp2;

public:
	// Method
	CharaSelectBarUI(void);
	~CharaSelectBarUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No);
};
