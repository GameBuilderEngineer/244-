//=============================================================================
// �̗̓G�t�F�N�g���� [HpEffect.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "HpEffect.h"
//*****************************************************************************
// �萔
//*****************************************************************************
static int				alphaColor = HP_EFFECT_ALPHA_MAX;								// �̗̓G�t�F�N�g�A���t�@�l
const static int		WIDTH = WINDOW_WIDTH / 2;										// �̗̓G�t�F�N�g���T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;											// �̗̓G�t�F�N�g�c�T�C�Y
const static float		POSITION_X_PLAYER1 = 0.0f;										// �̗̓G�t�F�N�gX���W
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;	// �̗̓G�t�F�N�g2X���W
const static float		POSITION_Y = 0.0f;												// �̗̓G�t�F�N�gY���W
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int HpEffect::cntEffect = -1;
LPDIRECT3DTEXTURE9 HpEffect::textureHpEffect = NULL;									// HP�G�t�F�N�g�̃e�N�X�`��
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
	// �������ԏ�����
	cntFrame = 0;
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;
	// �G�t�F�N�g�s�g�p
	isActive = false;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	textureHpEffect = *textureLoader->getTexture(textureLoaderNS::HP_EFFECT);

	// �̗̓G�t�F�N�g������
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
//=============================================================================
// �I������
//=============================================================================
void HpEffect::uninitialize(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void HpEffect::update(void)
{
	if (!isActive) return;

	// �̗̓G�t�F�N�g�X�V����
	cntFrame++;
	if (cntFrame < settingFrame)
	{
		// ����������
		effectFade();
	}
	// ���ԂɂȂ�����I��
	if (cntFrame == settingFrame)
	{
		isActive = false;
		alphaColor = HP_EFFECT_ALPHA_MAX;
		cntFrame = 0;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void HpEffect::render(LPDIRECT3DDEVICE9 device)
{
	// �g�p���Ă��Ȃ�������߂�
	if (!isActive) return;

	// �̗̓G�t�F�N�g�`��
	hpEffect.render(device);
}
//=============================================================================
// �t�F�[�h�A�E�g����
//=============================================================================
void HpEffect::effectFade(void)
{
	// �A���t�@���Z
	alphaColor -= HP_EFFECT_SUB_TIME;

	// �A���t�@��0�ɂȂ����猳�ɖ߂�
	if (alphaColor <= 0)
	{
		alphaColor = HP_EFFECT_ALPHA_MAX;
	}

	// �G�t�F�N�g�ʒu�ݒ�
	hpEffect.setAlpha(alphaColor);
}
