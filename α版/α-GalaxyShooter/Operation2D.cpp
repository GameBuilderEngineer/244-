//=============================================================================
// Operation�̕`�揈�� [Operation2D.cpp]
////=============================================================================
#include "Operation2D.h"
//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
//�}�N����`
const static int		WIDTH = 1280;								// ����m�F2D���T�C�Y
const static int		HEIGHT = 720;								// ����m�F2D�c�T�C�Y

const static float		POSITION_X = 0.0f;							// ����m�F2DX���W
const static float		POSITION_Y = 0.0f;							// ����m�F2DY���W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Operation2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Operation2D::textureOperation2D = NULL;			// ����m�F2D�e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Operation2D::Operation2D()
{
	cntUI++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Operation2D::~Operation2D()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Operation2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (textureOperation2D == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "MissileUI.jpg", &textureOperation2D)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "MissileUI.jpg", MB_OK);
			return E_FAIL;
		}
	}

	operation2D.initialize(device,
		textureOperation2D,							// �e�N�X�`��
		spriteNS::TOP_LEFT,							// ���_
		WIDTH,										// ����
		HEIGHT,										// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ��]
		OPERATION2D_COLOR
	);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Operation2D::uninitialize(void)
{
	operation2D.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(textureOperation2D)
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Operation2D::update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void Operation2D::render(LPDIRECT3DDEVICE9 device)
{
	operation2D.render(device);
}

