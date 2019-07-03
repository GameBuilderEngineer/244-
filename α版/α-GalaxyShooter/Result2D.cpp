//=============================================================================
// Title�̕`�揈�� [Title2D.cpp]
////=============================================================================
#include "Result2D.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 1280;						// ���T�C�Y
const static int		HEIGHT = 720;						// �c�T�C�Y					
const static float		POSITION_X_PLAYER1 = 0.0f;			// X���W
const static float		POSITION_X_PLAYER2 = 0.0f;
const static float		POSITION_Y = 0.0f;					// Y���W
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �o�[�̐F

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Result2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Result2D::buffTexture = NULL;	// �e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Result2D::Result2D()
{
	cntUI++;
}


Result2D::~Result2D()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Result2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (buffTexture == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "sTex.png", &buffTexture)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "sTex.png", MB_OK);
			return E_FAIL;
		}
	}

	Sprite::initialize(device,
		buffTexture,						// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Result2D::uninitialize(void)
{
	setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(buffTexture)
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Result2D::update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void Result2D::render(LPDIRECT3DDEVICE9 device)
{
	Sprite::render(device);
}
