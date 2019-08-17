//=============================================================================
// �L�����N�^�[�Z���N�g�o�[UI�w�b�_�[ [CharaSelectBarUI.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))				// �L�����Z���N�g�̐F
//=============================================================================
// ���O���
//=============================================================================
namespace charaSelectBarUINS
{
	// �v���C���[�l��
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};
}
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CharaSelectBarUI :public Sprite
{
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

	Sprite charaSelectBar;								// �Z���N�g�o�[���C�g�e�N�X�`��
	Sprite charaSelectBar2;								// �Z���N�g�o�[���C�g�e�N�X�`��2
	Sprite charaSelectNo;								// �Z���N�g�i���o�[�e�N�X�`��
	Sprite charaSelectNo2;								// �Z���N�g�i���o�[�e�N�X�`��2
	Sprite charaSelectCursor;							// �Z���N�g�J�[�\���e�N�X�`��
	Sprite charaSelectCursor2;							// �Z���N�g�J�[�\���e�N�X�`��2
	Sprite charaSelectLogo;								// �Z���N�g�v���C���[���S�e�N�X�`��
	Sprite nameEveEng;									// �C�����O�p��e�N�X�`��
	Sprite nameEveEng2;									// �C�����O�p��e�N�X�`��2
	Sprite nameAdamEng;									// �A�_�����O�p��e�N�X�`��
	Sprite nameAdamEng2;								// �A�_�����O�p��e�N�X�`��2
	Sprite nameEveJp;									// �C�����O���{��e�N�X�`��
	Sprite nameEveJp2;									// �C�����O���{��e�N�X�`��2
	Sprite nameAdamJp;									// �A�_�����O���{��e�N�X�`��
	Sprite nameAdamJp2;									// �A�_�����O���{��e�N�X�`��2

public:
	// Method
	CharaSelectBarUI(void);
	~CharaSelectBarUI(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No);
};
