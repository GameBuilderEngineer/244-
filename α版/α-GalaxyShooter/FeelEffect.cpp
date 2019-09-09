//=============================================================================
// �񕜃G�t�F�N�g���� [FeelEffect.cpp]
// ����� �ђˏt�P
////===========================================================================
#include "FeelEffect.h"
//*****************************************************************************
// �萔
//*****************************************************************************
static int				alphaColor = FEEL_EFFECT_ALPHA_MAX;								// �񕜃G�t�F�N�g�A���t�@�l
const static int		WIDTH = WINDOW_WIDTH / 2;										// �񕜃G�t�F�N�g���T�C�Y
const static int		HEIGHT = WINDOW_HEIGHT;											// �񕜃G�t�F�N�g�c�T�C�Y
const static float		POSITION_X_PLAYER1 = 0.0f;										// �񕜃G�t�F�N�gX���W
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;	// �񕜃G�t�F�N�g2X���W
const static float		POSITION_Y = 0.0f;												// �񕜃G�t�F�N�gY���W
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int FeelEffect::cntEffect = -1;
LPDIRECT3DTEXTURE9 FeelEffect::textureFeelEffect = NULL;								// FEEL�G�t�F�N�g�̃e�N�X�`��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
FeelEffect::FeelEffect()
{
	cntEffect++;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
FeelEffect::~FeelEffect()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT FeelEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// �������ԏ�����
	cntFrame = 0;
	// �v���C���[�i���o�[
	playerNumber = _playerNumber;
	// �G�t�F�N�g�s�g�p
	isActive = false;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	textureFeelEffect = *textureLoader->getTexture(textureLoaderNS::EFFECT_FEEL);

	// �񕜃G�t�F�N�g������
	feelEffect.initialize(device,
		textureFeelEffect,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		FEEL_EFFECT_COLOR					// �F
	);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void FeelEffect::uninitialize(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void FeelEffect::update(void)
{
	if (!isActive) return;

	// �񕜃G�t�F�N�g�X�V����
	cntFrame++;
	if (cntFrame < settingFrame)
	{
		// ����������
		feelEffectFade();
	}
	// ���ԂɂȂ�����I��
	if (cntFrame == settingFrame)
	{
		isActive = false;
		alphaColor = FEEL_EFFECT_ALPHA_MAX;
		cntFrame = 0;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void FeelEffect::render(LPDIRECT3DDEVICE9 device)
{
	// �g�p���Ă��Ȃ�������߂�
	if (!isActive) return;

	// �񕜃G�t�F�N�g�`��
	feelEffect.render(device);
}
//=============================================================================
// �t�F�[�h�A�E�g����
//=============================================================================
void FeelEffect::feelEffectFade(void)
{
	// �A���t�@���Z
	alphaColor -= FEEL_EFFECT_SUB_TIME;

	// �A���t�@��0�ɂȂ����猳�ɖ߂�
	if (alphaColor <= 0)
	{
		alphaColor = FEEL_EFFECT_ALPHA_MAX;
		isActive = false;
	}

	// �G�t�F�N�g�ʒu�ݒ�
	feelEffect.setAlpha(alphaColor);
}
