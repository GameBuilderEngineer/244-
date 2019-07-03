//=============================================================================
// Title�̕`�揈�� [Title2D.cpp]
////=============================================================================
#include "Title2D.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 1280;								// �^�C�g�����T�C�Y
const static int		HEIGHT = 720;								// �^�C�g���c�T�C�Y
const static int		WIDTH2 = 600;								// �I���摜���T�C�Y
const static int		HEIGHT2 = 50;								// �I���摜�c�T�C�Y

const static float		POSITION_X = 0.0f;							// �^�C�g��X���W
const static float		POSITION_Y = 0.0f;							// �^�C�g��Y���W
const static float		POSITION_X_2 = 0.0f;						// �I���摜X���W
static float			POSITION_Y_2 = CNT_TITLE_START;				// �I���摜Y���W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Title2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Title2D::titleTexture2D = NULL;					// �^�C�g���e�N�X�`��
LPDIRECT3DTEXTURE9 Title2D::choiceTexture = NULL;					// �I���摜�e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Title2D::Title2D()
{
	cntUI++;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Title2D::~Title2D()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Title2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (titleTexture2D == NULL)
	{
		//if (FAILED(D3DXCreateTextureFromFile(device, "ColonyHitPointUI.jpg", &titleTexture2D)))
		if (FAILED(D3DXCreateTextureFromFile(device, "Title.png", &titleTexture2D)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "ColonyHitPointUI.jpg", MB_OK);
			return E_FAIL;
		}
	}
	if (choiceTexture == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "Title_Bar.png", &choiceTexture)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "nTex.png", MB_OK);
			return E_FAIL;
		}
	}

	title2D.initialize(device,
		titleTexture2D,									// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		TITLE2D_COLOR									// �F
	);

	choice.initialize(device,
		choiceTexture,									// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH2,											// ����
		HEIGHT2,										// ����
		D3DXVECTOR3(POSITION_X_2, POSITION_Y_2, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		TITLE2D_COLOR									// �F
	);

	cntTitle = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Title2D::uninitialize(void)
{
	title2D.setTexture(NULL);
	choice.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(titleTexture2D)
		SAFE_RELEASE(choiceTexture)
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Title2D::update(void)
{
	titleUImove();

	choice.setVertex();
}


//=============================================================================
// �`�揈��
//=============================================================================
void Title2D::render(LPDIRECT3DDEVICE9 device)
{
	choice.render(device);
	title2D.render(device);

}

//=============================================================================
// �I��UI�ړ�����
//=============================================================================
void Title2D::titleUImove(void)
{
	switch (cntTitle)
	{
		// �Q�[���J�n
	case 0:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_START, 0));
		break;

		// �`���[�g���A��
	case 1:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_TUTORIAL, 0));
		break;

		// ������@
	case 2:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_OPERATION, 0));
		break;

		// �N���W�b�g
	case 3:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_CREDIT, 0));
		break;

		// �Q�[���I��
	case 4:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_END, 0));
		break;
	}
}