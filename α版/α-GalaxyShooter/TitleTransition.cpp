//=============================================================================
// �^�C�g���J�ډ摜�J�ډ摜�̕`�揈�� [TitleTransition.cpp]
////=============================================================================
#include "TitleTransition.h"
//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH / 2;						// �^�C�g���J�ډ摜���T�C�Y
const static float		GAME_POSITION_X = 0.0f;						// �Q�[���J�ډ摜X���W
const static float		TUTORIAL_POSITION_X = 0.0f;					// �`���[�g���A���J�ډ摜X���W
const static float		OPERATION_POSITION_X = 0.0f;				// �I�y���[�V�����J�ډ摜X���W
const static float		CREDIT_POSITION_X = 0.0f;					// �N���W�b�g�J�ډ摜X���W
const static float		GAMEEND_POSITION_X = 0.0f;					// �Q�[���G���h�J�ډ摜X���W
#ifdef _DEBUG
const static int		HEIGHT = WINDOW_HEIGHT/9;					// �^�C�g���J�ډ摜�c�T�C�Y
const static float		GAME_POSITION_Y = TITLE_GAME_POS;			// �Q�[���J�ډ摜Y���W
const static float		TUTORIAL_POSITION_Y = TITLE_TUTORIAL_POS;	// �`���[�g���A���J�ډ摜Y���W
const static float		OPERATION_POSITION_Y = TITLE_OPERATION_POS;	// �I�y���[�V�����J�ډ摜Y���W
const static float		CREDIT_POSITION_Y = TITLE_CREDIT_POS;		// �N���W�b�g�J�ډ摜Y���W
const static float		GAMEEND_POSITION_Y = TITLE_GAMEEND_POS;		// �Q�[���G���h�J�ډ摜Y���W
#else
const static int		HEIGHT = WINDOW_HEIGHT / 7;						// �^�C�g���J�ډ摜�c�T�C�Y
const static float		GAME_POSITION_Y = RELEASE_START_POS;			// �Q�[���J�ډ摜Y���W
const static float		TUTORIAL_POSITION_Y = RELEASE_TUTORIAL_POS;		// �`���[�g���A���J�ډ摜Y���W
const static float		OPERATION_POSITION_Y = RELEASE_OPERATION_POS;	// �I�y���[�V�����J�ډ摜Y���W
const static float		CREDIT_POSITION_Y = RELEASE_CREDIT_POS;			// �N���W�b�g�J�ډ摜Y���W
const static float		GAMEEND_POSITION_Y = RELEASE_GAMEEND_POS;		// �Q�[���G���h�J�ډ摜Y���W
#endif 
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int TitleTransition::cntUI = -1;
LPDIRECT3DTEXTURE9 TitleTransition::titleGameTex = NULL;			// �Q�[���J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleTutorialTex = NULL;		// �`���[�g���A���J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleOperationTex = NULL;		// �I�y���[�V�����J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleCreditTex = NULL;			// �N���W�b�g�J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleGameendTex = NULL;			// �Q�[���G���h�J�ډ摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleGameBTex = NULL;			// �Q�[���J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleTutorialBTex = NULL;		// �`���[�g���A���J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleOperationBTex = NULL;		// �I�y���[�V�����J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleCreditBTex = NULL;			// �N���W�b�g�J�ڎ��摜�e�N�X�`��
LPDIRECT3DTEXTURE9 TitleTransition::titleGameendBTex = NULL;		// �Q�[���G���h�J�ڎ��摜�e�N�X�`��
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
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	titleGameTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAME);
	titleTutorialTex = *textureLoader->getTexture(textureLoaderNS::TITLE_TUTORIAL);
	titleOperationTex = *textureLoader->getTexture(textureLoaderNS::TITLE_OPERATION);
	titleCreditTex = *textureLoader->getTexture(textureLoaderNS::TITLE_CREDIT);
	titleGameendTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAMEEND);
	titleGameBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAME_B);
	titleTutorialBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_TUTORIAL_B);
	titleOperationBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_OPERATION_B);
	titleCreditBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_CREDIT_B);
	titleGameendBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAMEEND_B);

	TitleGame.initialize(device,
		titleGameTex,									// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(GAME_POSITION_X, GAME_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR								// �F
	);

	TitleTutorial.initialize(device,
		titleTutorialTex,								// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(TUTORIAL_POSITION_X, TUTORIAL_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR							// �F
	);

	TitleOperation.initialize(device,
		titleOperationTex,								// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(OPERATION_POSITION_X, OPERATION_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR							// �F
	);

	TitleCredit.initialize(device,
		titleCreditTex,									// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(CREDIT_POSITION_X, CREDIT_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR								// �F
	);

	TitleGameend.initialize(device,
		titleGameendTex,								// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(GAMEEND_POSITION_X, GAMEEND_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR								// �F
	);

	TitleGameB.initialize(device,
		titleGameBTex,									// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(GAME_POSITION_X, GAME_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR								// �F
	);

	TitleTutorialB.initialize(device,
		titleTutorialBTex,								// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(TUTORIAL_POSITION_X, TUTORIAL_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR							// �F
	);

	TitleOperationB.initialize(device,
		titleOperationBTex,								// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(OPERATION_POSITION_X, OPERATION_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR							// �F
	);

	TitleCreditB.initialize(device,
		titleCreditBTex,									// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(CREDIT_POSITION_X, CREDIT_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR								// �F
	);

	TitleGameendB.initialize(device,
		titleGameendBTex,								// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(GAMEEND_POSITION_X, GAMEEND_POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		DEFAULT_COLOR								// �F
	);

	cntTitle = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void TitleTransition::uninitialize(void)
{
	TitleGame.setTexture(NULL);
	TitleTutorial.setTexture(NULL);
	TitleOperation.setTexture(NULL);
	TitleCredit.setTexture(NULL);
	TitleGameend.setTexture(NULL);
	TitleGameB.setTexture(NULL);
	TitleTutorialB.setTexture(NULL);
	TitleOperationB.setTexture(NULL);
	TitleCreditB.setTexture(NULL);
	TitleGameendB.setTexture(NULL);

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
	TitleGame.render(device);
	TitleTutorial.render(device);
	TitleOperation.render(device);
	TitleCredit.render(device);
	TitleGameend.render(device);
	titleTransBlack(device);
}

//=============================================================================
// �^�C�g���I���ʒu�摜�ړ�����
//=============================================================================
void TitleTransition::titleTransBlack(LPDIRECT3DDEVICE9 device)
{
	switch (cntTitle)
	{
		// �Q�[���J�n
	case 0:
		TitleGameB.render(device);
		break;

		// �`���[�g���A��
	case 1:
		TitleTutorialB.render(device);
		break;

		// ������@
	case 2:
		TitleOperationB.render(device);
		break;

		// �N���W�b�g
	case 3:
		TitleCreditB.render(device);
		break;

		// �Q�[���I��
	case 4:
		TitleGameendB.render(device);
		break;
	}
}