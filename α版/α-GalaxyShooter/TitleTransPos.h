//=============================================================================
// �^�C�g���I���ʒu�`�揈�� [TitleTransPos.h]
//
//=============================================================================
#pragma once
#include "TitleTransition.h"
#include "Input.h"
#include "AbstractScene.h"

#define TITLE_TRANSPOS_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))	// �^�C�g���I���ʒu�̐F
#define CNT_TITLE_MAX			(4)											// �^�C�g���I���ʒu����l
#define CNT_TITLE_START			(235)										// �^�C�g���I���ʒu�X�^�[�g�l
#define CNT_TITLE_TUTORIAL		(285)										// �^�C�g���I���ʒu�`���[�g���A���l
#define CNT_TITLE_OPERATION		(335)										// �^�C�g���I���ʒu������@�l
#define CNT_TITLE_CREDIT		(385)										// �^�C�g���I���ʒu�N���W�b�g�l
#define CNT_TITLE_END			(435)										// �^�C�g���I���ʒu�I���l
#define CNT_RELEASE_START		(485)										// �����[�X���^�C�g���I���ʒu�X�^�[�g�l
#define CNT_RELEASE_TUTORIAL	(585)										// �����[�X���^�C�g���I���ʒu�`���[�g���A���l
#define CNT_RELEASE_OPERATION	(685)										// �����[�X���^�C�g���I���ʒu������@�l
#define CNT_RELEASE_CREDIT		(785)										// �����[�X���^�C�g���I���ʒu�N���W�b�g�l
#define CNT_RELEASE_END			(885)										// �����[�X���^�C�g���I���ʒu�I���l

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TitleTransPos :public TitleTransition
{
private:
	// Data
	int playerNumber;											// �v���C���[�ԍ�
	static int cntUI;											// �C���X�^���X�̐��𐔂���
	static LPDIRECT3DTEXTURE9 titleTransPosTex;					// �^�C�g���I���ʒu�摜
	Sprite titleTransPos;										// �^�C�g���I���ʒu
public:
	TitleTransPos(void);
	~TitleTransPos(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void titleTransPosMove(void);								// �^�C�g���I���ʒu�ړ�����
	int	cntTitle;												// �^�C�g���I���ʒu�ϐ�
};

