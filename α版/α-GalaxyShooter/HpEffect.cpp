#include "HpEffect.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
static int				alphaColor = 255;					// �A���t�@�l
const static int		WIDTH = WINDOW_WIDTH / 2;			// ���T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;				// �c�T�C�Y					
const static float		POSITION_X_PLAYER1 = 0.0f;			// X���W
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;
const static float		POSITION_Y = 0.0f;					// Y���W
#define HP_EFFECT_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))		// �G�t�F�N�g�̐F

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int HpEffect::cntEffect = -1;
LPDIRECT3DTEXTURE9 HpEffect::textureHpEffect = NULL;		// HP�G�t�F�N�g�̃e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
HpEffect::HpEffect()
{
	cntEffect++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
HpEffect::~HpEffect()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT HpEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �����ɏ�����������
	cntFrame = 0;
	playerNumber = _playerNumber;
	isActive = false;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	textureHpEffect = *textureLoader->getTexture(textureLoaderNS::HP_EFFECT);

	hpEffect.initialize(device,
		textureHpEffect,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		HP_EFFECT_COLOR						// �F
	);

	return S_OK;
}

void HpEffect::uninitialize(void)
{
	hpEffect.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntEffect--;
	if (cntEffect < 0)
	{
		SAFE_RELEASE(textureHpEffect)
	}
}

void HpEffect::update(void)
{
	if (!isActive) return;

	cntFrame++;
	if (cntFrame < settingFrame)
	{
	}

	if (cntFrame == settingFrame)
	{
		isActive = false;
		cntFrame = 0;
	}
}

void HpEffect::render(LPDIRECT3DDEVICE9 device)
{
	hpEffect.render(device);
}
