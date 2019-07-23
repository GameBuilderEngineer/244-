//=============================================================================
// �^�C�g���I���ʒu�`�揈�� [TitleTransPos.cpp]
////=============================================================================
#include "TitleTransPos.h"
//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
#ifdef _DEBUG
const static int		WIDTH = 600;								// �^�C�g���I���ʒu�摜���T�C�Y
const static int		HEIGHT = 50;								// �^�C�g���I���ʒu�摜�c�T�C�Y

const static float		POSITION_X = 0.0f;							// �^�C�g���I���ʒu�摜X���W
static float			POSITION_Y = CNT_TITLE_START;				// �^�C�g���I���ʒu�摜Y���W
#else
const static int		WIDTH = 800;								// �^�C�g���I���ʒu�摜���T�C�Y
const static int		HEIGHT = 80;								// �^�C�g���I���ʒu�摜�c�T�C�Y

const static float		POSITION_X = 0.0f;							// �^�C�g���I���ʒu�摜X���W
static float			POSITION_Y = CNT_RELEASE_START;				// �^�C�g���I���ʒu�摜Y���W
#endif 

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int TitleTransPos::cntUI = -1;
LPDIRECT3DTEXTURE9 TitleTransPos::titleTransPosTex = NULL;			// �^�C�g���I���ʒu�摜�e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
TitleTransPos::TitleTransPos()
{
	cntUI++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
TitleTransPos::~TitleTransPos()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT TitleTransPos::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	titleTransPosTex = *textureLoader->getTexture(textureLoaderNS::TITLE_POS);

	Sprite::initialize(device,
		titleTransPosTex,								// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		TITLE_TRANSPOS_COLOR							// �F
	);

	cntTitle = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void TitleTransPos::uninitialize(void)
{
	setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(titleTransPosTex)
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void TitleTransPos::update(void)
{
	// �^�C�g���I���ʒu�摜�ړ�����
	titleTransPosMove();

	// �ʒu�ݒ�
	setVertex();
}


//=============================================================================
// �`�揈��
//=============================================================================
void TitleTransPos::render(LPDIRECT3DDEVICE9 device)
{
	Sprite::render(device);
}

//=============================================================================
// �^�C�g���I���ʒu�摜�ړ�����
//=============================================================================
void TitleTransPos::titleTransPosMove(void)
{
	switch (cntTitle)
	{
		// �Q�[���J�n
	case 0:
#ifdef _DEBUG
		setPosition2(D3DXVECTOR3(0, CNT_TITLE_START, 0));
#else
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_RELEASE_START, 0));
#endif 
		break;

		// �`���[�g���A��
	case 1:
#ifdef _DEBUG
		setPosition2(D3DXVECTOR3(0, CNT_TITLE_TUTORIAL, 0));
#else
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_RELEASE_TUTORIAL, 0));
#endif 
		break;

		// ������@
	case 2:
#ifdef _DEBUG
		setPosition2(D3DXVECTOR3(0, CNT_TITLE_OPERATION, 0));
#else
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_RELEASE_OPERATION, 0));
#endif 
		break;

		// �N���W�b�g
	case 3:
#ifdef _DEBUG
		setPosition2(D3DXVECTOR3(0, CNT_TITLE_CREDIT, 0));
#else
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_RELEASE_CREDIT, 0));
#endif 
		break;

		// �Q�[���I��
	case 4:
#ifdef _DEBUG
		setPosition2(D3DXVECTOR3(0, CNT_TITLE_END, 0));
#else
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_RELEASE_END, 0));
#endif 
		break;
	}
}