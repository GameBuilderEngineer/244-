//=============================================================================
// �^�C�g���I���ʒu�`��w�b�_�[ [TitleTransPos.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "TitleTransition.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TRANSPOS_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))			// �^�C�g���I���ʒu�̐F
#define CNT_TITLE_MAX			(4)											// �^�C�g���I���ʒu����l
#define CNT_TITLE_START			(235)										// �^�C�g���I���ʒu�X�^�[�g�l
#define CNT_TITLE_TUTORIAL		(285)										// �^�C�g���I���ʒu�`���[�g���A���l
#define CNT_TITLE_OPERATION		(335)										// �^�C�g���I���ʒu������@�l
#define CNT_TITLE_CREDIT		(385)										// �^�C�g���I���ʒu�N���W�b�g�l
#define CNT_TITLE_END			(435)										// �^�C�g���I���ʒu�I���l
#define CNT_RELEASE_START		(475)										// �����[�X���^�C�g���I���ʒu�X�^�[�g�l
#define CNT_RELEASE_TUTORIAL	(575)										// �����[�X���^�C�g���I���ʒu�`���[�g���A���l
#define CNT_RELEASE_OPERATION	(675)										// �����[�X���^�C�g���I���ʒu������@�l
#define CNT_RELEASE_CREDIT		(775)										// �����[�X���^�C�g���I���ʒu�N���W�b�g�l
#define CNT_RELEASE_END			(875)										// �����[�X���^�C�g���I���ʒu�I���l
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

public:
	TitleTransPos(void);
	~TitleTransPos(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	virtual void titleTransPosMove(void);						// �^�C�g���I���ʒu�ړ�����
};

