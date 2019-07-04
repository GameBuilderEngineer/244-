//=============================================================================
// Credit�̕`�揈�� [Credit2D.cpp]
////=============================================================================
#include "Credit2D.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
//�}�N����`
const static int		WIDTH = WINDOW_WIDTH;						// �N���W�b�g2D���T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;						// �N���W�b�g2D�c�T�C�Y

const static float		POSITION_X = 0.0f;							// �N���W�b�g2DX���W
const static float		POSITION_Y = 0.0f;							// �N���W�b�g2DY���W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Credit2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Credit2D::textureCredit2D = NULL;			// �N���W�b�g2D�e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Credit2D::Credit2D()
{
	cntUI++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Credit2D::~Credit2D()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Credit2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (textureCredit2D == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "kurezitto.png", &textureCredit2D)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "kurezitto.png", MB_OK);
			return E_FAIL;
		}
	}

	textureCredit2D = *textureLoader->getTexture(textureLoaderNS::CREDIT);

	credit2D.initialize(device,
		textureCredit2D,							// �e�N�X�`��
		spriteNS::TOP_LEFT,							// ���_
		WIDTH,										// ����
		HEIGHT,										// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ��]
		CREDIT2D_COLOR
	);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Credit2D::uninitialize(void)
{
	credit2D.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(textureCredit2D)
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Credit2D::update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void Credit2D::render(LPDIRECT3DDEVICE9 device)
{
	credit2D.render(device);
}

