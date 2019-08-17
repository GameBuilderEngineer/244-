//=============================================================================
// �^�C�g���J�ډ摜�`�揈�� [TitleTransition.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "TitleTransition.h"
//*****************************************************************************
// �萔
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH / 2;						// �^�C�g���J�ډ摜���T�C�Y
const static float		GAME_POSITION_X = 0.0f;							// �Q�[���J�ډ摜X���W
const static float		TUTORIAL_POSITION_X = 0.0f;						// �`���[�g���A���J�ډ摜X���W
const static float		OPERATION_POSITION_X = 0.0f;					// �I�y���[�V�����J�ډ摜X���W
const static float		CREDIT_POSITION_X = 0.0f;						// �N���W�b�g�J�ډ摜X���W
const static float		GAMEEND_POSITION_X = 0.0f;						// �Q�[���G���h�J�ډ摜X���W
#ifdef _DEBUG
const static int		HEIGHT = WINDOW_HEIGHT/9;						// �^�C�g���J�ډ摜�c�T�C�Y
const static float		GAME_POSITION_Y = TITLE_GAME_POS;				// �Q�[���J�ډ摜Y���W
const static float		TUTORIAL_POSITION_Y = TITLE_TUTORIAL_POS;		// �`���[�g���A���J�ډ摜Y���W
const static float		OPERATION_POSITION_Y = TITLE_OPERATION_POS;		// �I�y���[�V�����J�ډ摜Y���W
const static float		CREDIT_POSITION_Y = TITLE_CREDIT_POS;			// �N���W�b�g�J�ډ摜Y���W
const static float		GAMEEND_POSITION_Y = TITLE_GAMEEND_POS;			// �Q�[���G���h�J�ډ摜Y���W
#else
const static int		HEIGHT = WINDOW_HEIGHT / 9;						// �����[�X���^�C�g���J�ډ摜�c�T�C�Y
const static float		GAME_POSITION_Y = RELEASE_START_POS;			// �����[�X���Q�[���J�ډ摜Y���W
const static float		TUTORIAL_POSITION_Y = RELEASE_TUTORIAL_POS;		// �����[�X���`���[�g���A���J�ډ摜Y���W
const static float		OPERATION_POSITION_Y = RELEASE_OPERATION_POS;	// �����[�X���I�y���[�V�����J�ډ摜Y���W
const static float		CREDIT_POSITION_Y = RELEASE_CREDIT_POS;			// �����[�X���N���W�b�g�J�ډ摜Y���W
const static float		GAMEEND_POSITION_Y = RELEASE_GAMEEND_POS;		// �����[�X���Q�[���G���h�J�ډ摜Y���W
#endif 
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int TitleTransition::cntUI = -1;
LPDIRECT3DTEXTURE9 TitleTransition::titleGameTex = NULL;				// �Q�[���J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleTutorialTex = NULL;			// �`���[�g���A���J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleOperationTex = NULL;			// �I�y���[�V�����J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleCreditTex = NULL;				// �N���W�b�g�J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleGameendTex = NULL;				// �Q�[���G���h�J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleGameBTex = NULL;				// �Q�[���J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleTutorialBTex = NULL;			// �`���[�g���A���J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleOperationBTex = NULL;			// �I�y���[�V�����J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleCreditBTex = NULL;				// �N���W�b�g�J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleGameendBTex = NULL;			// �Q�[���G���h�J�ڎ��摜�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
TitleTransition::TitleTransition()
{
	cntUI++;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
TitleTransition::~TitleTransition()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT TitleTransition::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	titleGameTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAME);					// �Q�[��
	titleTutorialTex = *textureLoader->getTexture(textureLoaderNS::TITLE_TUTORIAL);			// �`���[�g���A��
	titleOperationTex = *textureLoader->getTexture(textureLoaderNS::TITLE_OPERATION);		// �I�y���[�V����
	titleCreditTex = *textureLoader->getTexture(textureLoaderNS::TITLE_CREDIT);				// �N���W�b�g
	titleGameendTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAMEEND);			// �Q�[���G���h
	titleGameBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAME_B);				// �Q�[���J�ڎ�
	titleTutorialBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_TUTORIAL_B);		// �`���[�g���A���J�ڎ�
	titleOperationBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_OPERATION_B);	// �I�y���[�V�����J�ڎ�
	titleCreditBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_CREDIT_B);			// �N���W�b�g�J�ڎ�
	titleGameendBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAMEEND_B);		// �Q�[���G���h�J�ڎ�

	// �Q�[���J�ډ摜������
	TitleGame.initialize(device,
		titleGameTex,														// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(GAME_POSITION_X, GAME_POSITION_Y, 0.0f),				// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �`���[�g���A���J�ډ摜������
	TitleTutorial.initialize(device,
		titleTutorialTex,													// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(TUTORIAL_POSITION_X, TUTORIAL_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �I�y���[�V�����J�ډ摜������
	TitleOperation.initialize(device,
		titleOperationTex,													// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(OPERATION_POSITION_X, OPERATION_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �N���W�b�g�J�ډ摜������
	TitleCredit.initialize(device,
		titleCreditTex,														// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(CREDIT_POSITION_X, CREDIT_POSITION_Y, 0.0f),			// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �Q�[���G���h�J�ډ摜������
	TitleGameend.initialize(device,
		titleGameendTex,													// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(GAMEEND_POSITION_X, GAMEEND_POSITION_Y, 0.0f),			// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);


	// �Q�[���J�ڎ��摜������
	TitleGameB.initialize(device,
		titleGameBTex,														// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(GAME_POSITION_X, GAME_POSITION_Y, 0.0f),				// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �`���[�g���A���J�ڎ��摜������
	TitleTutorialB.initialize(device,
		titleTutorialBTex,													// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(TUTORIAL_POSITION_X, TUTORIAL_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �I�y���[�V�����J�ڎ��摜������
	TitleOperationB.initialize(device,
		titleOperationBTex,													// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(OPERATION_POSITION_X, OPERATION_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �N���W�b�g�J�ڎ��摜������
	TitleCreditB.initialize(device,
		titleCreditBTex,													// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(CREDIT_POSITION_X, CREDIT_POSITION_Y, 0.0f),			// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);
	// �Q�[���G���h�J�ڎ��摜������
	TitleGameendB.initialize(device,
		titleGameendBTex,													// �e�N�X�`��
		spriteNS::TOP_LEFT,													// ���_
		WIDTH,																// ����
		HEIGHT,																// ����
		D3DXVECTOR3(GAMEEND_POSITION_X, GAMEEND_POSITION_Y, 0.0f),			// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// ��]
		DEFAULT_COLOR														// �F
	);

	// �J�ڈʒu������
	cntTitle = NULL;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void TitleTransition::uninitialize(void)
{
	TitleGame.setTexture(NULL);				// �Q�[���J�ډ摜���
	TitleTutorial.setTexture(NULL);			// �`���[�g���A���J�ډ摜���
	TitleOperation.setTexture(NULL);		// �I�y���[�V�����J�ډ摜���
	TitleCredit.setTexture(NULL);			// �N���W�b�g�J�ډ摜���
	TitleGameend.setTexture(NULL);			// �Q�[���G���h�J�ډ摜���
	TitleGameB.setTexture(NULL);			// �Q�[���J�ڎ��摜���
	TitleTutorialB.setTexture(NULL);		// �`���[�g���A���J�ڎ��摜���
	TitleOperationB.setTexture(NULL);		// �I�y���[�V�����J�ڎ��摜���
	TitleCreditB.setTexture(NULL);			// �N���W�b�g�J�ڎ��摜���
	TitleGameendB.setTexture(NULL);			// �Q�[���G���h�J�ڎ��摜���

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(titleGameTex)
		SAFE_RELEASE(titleTutorialTex)
		SAFE_RELEASE(titleOperationTex)
		SAFE_RELEASE(titleCreditTex)
		SAFE_RELEASE(titleGameendTex)
		SAFE_RELEASE(titleGameBTex)
		SAFE_RELEASE(titleTutorialBTex)
		SAFE_RELEASE(titleOperationBTex)
		SAFE_RELEASE(titleCreditBTex)
		SAFE_RELEASE(titleGameendBTex)
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void TitleTransition::update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void TitleTransition::render(LPDIRECT3DDEVICE9 device)
{
	TitleGame.render(device);			// �Q�[���J�ډ摜�`��
	TitleTutorial.render(device);		// �`���[�g���A���J�ډ摜�`��
	TitleOperation.render(device);		// �I�y���[�V�����J�ډ摜�`��
	TitleCredit.render(device);			// �N���W�b�g�J�ډ摜�`��
	TitleGameend.render(device);		// �Q�[���G���h�J�ډ摜�`��
	titleTransBlack(device);			// �^�C�g���I���ʒu�摜�ړ�����
}
//=============================================================================
// �^�C�g���I���ʒu�摜�ړ�����
//=============================================================================
void TitleTransition::titleTransBlack(LPDIRECT3DDEVICE9 device)
{
	switch (cntTitle)
	{
		// �Z���N�g
	case 0:
		TitleGameB.render(device);			// �Q�[���J�ڎ��摜�`��
		break;

		// �`���[�g���A��
	case 1:
		TitleTutorialB.render(device);		// �`���[�g���A���J�ڎ��摜�`��
		break;

		// ������@
	case 2:
		TitleOperationB.render(device);		// �I�y���[�V�����J�ڎ��摜�`��
		break;

		// �N���W�b�g
	case 3:
		TitleCreditB.render(device);		// �N���W�b�g�J�ڎ��摜�`��
		break;

		// �Q�[���I��
	case 4:
		TitleGameendB.render(device);		// �Q�[���G���h�J�ڎ��摜�`��
		break;
	}
}