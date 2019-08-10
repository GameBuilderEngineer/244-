//=============================================================================
// �X�v���b�V���̕`�揈�� [Splash.cpp]
////=============================================================================
#include "Splash2D.h"
//*****************************************************************************
// �萔
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;						// �X�v���b�V��2D���T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;						// �X�v���b�V��2D�c�T�C�Y
static int				alphaColor = 0;								// �A���t�@�l
static int				time = 0;									// �X�v���b�V��2D���Ŏ���
const static float		POSITION_X = 0.0f;							// �X�v���b�V��2DX���W
const static float		POSITION_Y = 0.0f;							// �X�v���b�V��2DY���W
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
HRESULT Splash2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	textureSplash2D = *textureLoader->getTexture(textureLoaderNS::SPLASH);

	// �X�v���b�V��2D������
	Sprite::initialize(device,
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
	// �X�v���b�V��2D�摜���
	setTexture(NULL);

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
	// �X�v���b�V��2D�`��
	Sprite::render(device);
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

	setAlpha(alphaColor);
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

	setAlpha(alphaColor);
}
