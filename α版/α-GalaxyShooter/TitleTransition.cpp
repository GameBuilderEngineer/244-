//=============================================================================
// �^�C�g���J�ډ摜�J�ډ摜�̕`�揈�� [TitleTransition.cpp]
////=============================================================================
#include "TitleTransition.h"
//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;								// �^�C�g���J�ډ摜���T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;								// �^�C�g���J�ډ摜�c�T�C�Y

const static float		POSITION_X = 0.0f;							// �^�C�g���J�ډ摜X���W
const static float		POSITION_Y = 0.0f;							// �^�C�g���J�ډ摜Y���W
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int TitleTransition::cntUI = -1;
LPDIRECT3DTEXTURE9 TitleTransition::titleTransTex = NULL;			// �^�C�g���J�ډ摜�e�N�X�`��
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
HRESULT TitleTransition::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (titleTransTex == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "Title.png", &titleTransTex)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "ColonyHitPointUI.jpg", MB_OK);
			return E_FAIL;
		}
	}

	titleTrans.initialize(device,
		titleTransTex,									// �e�N�X�`��
		spriteNS::TOP_LEFT,								// ���_
		WIDTH,											// ����
		HEIGHT,											// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),		// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// ��]
		TITLE_TRANS_COLOR								// �F
	);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void TitleTransition::uninitialize(void)
{
	titleTrans.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(titleTransTex)
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
	titleTrans.render(device);
}