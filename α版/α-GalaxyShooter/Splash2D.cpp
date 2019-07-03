//=============================================================================
// Splash�̕`�揈�� [Splash.cpp]
////=============================================================================
#include "Splash2D.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
//�}�N����`
const static int		WIDTH = 960;								// �X�v���b�V��2D���T�C�Y
const static int		HEIGHT = 540;								// �X�v���b�V��2D�c�T�C�Y
static int				alphaColor = 0;								// �A���t�@�l
static int				time = 0;									// �X�v���b�V��2D���Ŏ���

#ifdef _DEBUG
const static float		POSITION_X = 160.0f;						// �X�v���b�V��2DX���W
const static float		POSITION_Y = 80.0f;							// �X�v���b�V��2DY���W
#else
const static float		POSITION_X = 480.0f;						// �X�v���b�V��2DX���W
const static float		POSITION_Y = 270.0f;						// �X�v���b�V��2DY���W
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Splash2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Splash2D::textureSplash2D = NULL;				// �X�v���b�V��2D�e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Splash2D::Splash2D()
{
	cntUI++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Splash2D::~Splash2D()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Splash2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (textureSplash2D == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "Team_Logo_Texture.png", &textureSplash2D)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "Team_Logo_Texture.png", MB_OK);
			return E_FAIL;
		}
	}

	splash2D.initialize(device,
		textureSplash2D,							// �e�N�X�`��
		spriteNS::TOP_LEFT,							// ���_
		WIDTH,										// ����
		HEIGHT,										// ����
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// ��]
		SPLASH2D_COLOR
	);

	fadeon = true;									// �t�F�[�h�N����
	gotitle = false;								// �t�F�[�h���I����Ă��Ȃ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Splash2D::uninitialize(void)
{
	splash2D.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(textureSplash2D)
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Splash2D::update(void)
{
	// �t�F�[�h����
	fade();
}


//=============================================================================
// �`�揈��
//=============================================================================
void Splash2D::render(LPDIRECT3DDEVICE9 device)
{
	splash2D.render(device);
}

//=============================================================================
// �t�F�[�h����
//=============================================================================
void Splash2D::fade(void)
{
	// ���ԂɂȂ�����t�F�[�h�A�E�g
	time++;
	if (time >= SPLASH_TIME)
	{
		fadeon = false;
	}

	// �t�F�[�h�C��
	if (fadeon)
	{
		fadein();
	}
	// �t�F�[�h�A�E�g
	else
	{
		fadeout();
	}
}

//=============================================================================
// �t�F�[�h�C������
//=============================================================================
void Splash2D::fadein(void)
{
	// �A���t�@���Z
	alphaColor++;

	if (alphaColor >= SPLASH_ALPHA_MAX)
	{
		alphaColor = SPLASH_ALPHA_MAX;
	}

	splash2D.setAlpha(alphaColor);
}

//=============================================================================
// �t�F�[�h�A�E�g����
//=============================================================================
void Splash2D::fadeout(void)
{
	// �A���t�@���Z
	alphaColor--;

	if (alphaColor <= 0)
	{
		alphaColor = 0;

		// �t�F�[�h���I����ă^�C�g���֑J��
		gotitle = true;
	}

	splash2D.setAlpha(alphaColor);
}
