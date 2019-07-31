//=============================================================================
// �^�C�g���J�ډ摜�`�揈�� [TitleTransition.h]
//
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"

#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))			// �^�C�g���J�ڈʒu�̐F
#define TITLE_GAME_POS			(235)								// �Q�[���I���ʒu
#define TITLE_TUTORIAL_POS		(285)								// �`���[�g���A���I���ʒu
#define TITLE_OPERATION_POS		(335)								// �I�y���[�V�����I���ʒu
#define TITLE_CREDIT_POS		(385)								// �N���W�b�g�I���ʒu
#define TITLE_GAMEEND_POS		(435)								// �Q�[���G���h�I���ʒu
#define RELEASE_START_POS		(485)								// �����[�X���^�C�g���I���ʒu�X�^�[�g�l
#define RELEASE_TUTORIAL_POS	(585)								// �����[�X���^�C�g���I���ʒu�`���[�g���A���l
#define RELEASE_OPERATION_POS	(685)								// �����[�X���^�C�g���I���ʒu������@�l
#define RELEASE_CREDIT_POS		(785)								// �����[�X���^�C�g���I���ʒu�N���W�b�g�l
#define RELEASE_GAMEEND_POS		(885)								// �����[�X���^�C�g���I���ʒu�I���l
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TitleTransition :public Sprite
{
private:
	// Data
	int playerNumber;											// �v���C���[�ԍ�
	static int cntUI;											// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 titleGameTex;						// �Q�[���J�ڃe�N�X�`��
	static LPDIRECT3DTEXTURE9 titleTutorialTex;					// �`���[�g���A���J�ڃe�N�X�`��
	static LPDIRECT3DTEXTURE9 titleOperationTex;				// �I�y���[�V�����J�ڃe�N�X�`��
	static LPDIRECT3DTEXTURE9 titleCreditTex;					// �N���W�b�g�J�ڃe�N�X�`��
	static LPDIRECT3DTEXTURE9 titleGameendTex;					// �Q�[���G���h�J�ڃe�N�X�`��
	static LPDIRECT3DTEXTURE9 titleGameBTex;					// �Q�[���J�ڎ��e�N�X�`��
	static LPDIRECT3DTEXTURE9 titleTutorialBTex;				// �`���[�g���A���J�ڎ��e�N�X�`��
	static LPDIRECT3DTEXTURE9 titleOperationBTex;				// �I�y���[�V�����J�ڎ��e�N�X�`��
	static LPDIRECT3DTEXTURE9 titleCreditBTex;					// �N���W�b�g�J�ڎ��e�N�X�`��
	static LPDIRECT3DTEXTURE9 titleGameendBTex;					// �Q�[���G���h�J�ڎ��e�N�X�`��

	Sprite TitleGame;
	Sprite TitleTutorial;
	Sprite TitleOperation;
	Sprite TitleCredit;
	Sprite TitleGameend;
	Sprite TitleGameB;
	Sprite TitleTutorialB;
	Sprite TitleOperationB;
	Sprite TitleCreditB;
	Sprite TitleGameendB;
public:
	TitleTransition(void);
	~TitleTransition(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void titleTransBlack(LPDIRECT3DDEVICE9 device);
	int	cntTitle;											// �^�C�g���I���ʒu�ϐ�

};

