//=============================================================================
// �^�C�g���I���ʒu�`�揈�� [TitleTransPos.cpp]
////=============================================================================
#include "TitleTransPos.h"
//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 600;								// �^�C�g���I���ʒu�摜���T�C�Y
const static int		HEIGHT = 50;								// �^�C�g���I���ʒu�摜�c�T�C�Y

const static float		POSITION_X = 0.0f;							// �^�C�g���I���ʒu�摜X���W
static float			POSITION_Y = CNT_TITLE_START;				// �^�C�g���I���ʒu�摜Y���W
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
HRESULT TitleTransPos::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (titleTransPosTex == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "Title_Bar.png", &titleTransPosTex)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "nTex.png", MB_OK);
			return E_FAIL;
		}
	}

	titleTransPos.initialize(device,
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
	titleTransPos.setTexture(NULL);

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
	titleTransPos.setVertex();
}


//=============================================================================
// �`�揈��
//=============================================================================
void TitleTransPos::render(LPDIRECT3DDEVICE9 device)
{
	titleTransPos.render(device);
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
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_TITLE_START, 0));
		break;

		// �`���[�g���A��
	case 1:
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_TITLE_TUTORIAL, 0));
		break;

		// ������@
	case 2:
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_TITLE_OPERATION, 0));
		break;

		// �N���W�b�g
	case 3:
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_TITLE_CREDIT, 0));
		break;

		// �Q�[���I��
	case 4:
		titleTransPos.setPosition2(D3DXVECTOR3(0, CNT_TITLE_END, 0));
		break;
	}
}