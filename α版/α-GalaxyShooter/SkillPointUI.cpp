//=============================================================================
// SP��UI���� [SkillPointUI.cpp]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/9
//=============================================================================
#include "SkillPointUI.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 300;						// ���T�C�Y
const static int		HEIGHT = 28;						// �c�T�C�Y					
const static float		POSITION_X_PLAYER1 = 40.0f;			// X���W
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;
const static float		POSITION_Y = 45.0f;					// Y���W
#define BAR_COLOR		(D3DCOLOR_RGBA(0, 0, 255, 255))		// �o�[�̐F
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �o�[�̐F


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int SkillPointUI::cntUI = -1;
LPDIRECT3DTEXTURE9 SkillPointUI::textureGaugeBase = NULL;	// �Q�[�W�x�[�X�̃e�N�X�`��
LPDIRECT3DTEXTURE9 SkillPointUI::textureGaugeBar = NULL;	// �Q�[�W�o�[�̃e�N�X�`��
LPDIRECT3DTEXTURE9 SkillPointUI::textureGaugeCover = NULL;	// �Q�[�W�J�o�[�̃e�N�X�`��


//=============================================================================
// �R���X�g���N�^
//=============================================================================
SkillPointUI::SkillPointUI(void)
{
	cntUI++;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
SkillPointUI::~SkillPointUI(void)
{
}


//=============================================================================
// ����������
//=============================================================================
HRESULT SkillPointUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	textureGaugeBase = *textureLoader->getTexture(textureLoaderNS::UI_GAUGE_BASE);
	textureGaugeBar = *textureLoader->getTexture(textureLoaderNS::UI_GAUGE_BAR);
	textureGaugeCover = *textureLoader->getTexture(textureLoaderNS::UI_GAUGE_COVER);


	// �X�v���C�g������
	gaugeBase.initialize(device,
		textureGaugeBase,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		DEFAULT_COLOR						// �F
	);
	gaugeBar.initialize(device,
		textureGaugeBar,					// �e�N�X�`��
		spriteNS::TOP_LEFT,					// ���_
		WIDTH,								// ����
		HEIGHT,								// ����
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
		BAR_COLOR							// �F
	);
	gaugeCover.initialize(device,
		textureGaugeCover,					// �e�N�X�`��
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
void SkillPointUI::uninitialize(void)
{
	gaugeBase.setTexture(NULL);
	gaugeBar.setTexture(NULL);
	gaugeCover.setTexture(NULL);

	// �C���X�^���X�����݂��Ȃ���΃e�N�X�`�����
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(textureGaugeBase)
		SAFE_RELEASE(textureGaugeBar)
		SAFE_RELEASE(textureGaugeCover)
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void SkillPointUI::update(int sp, int spMax)
{
	float percentage = (float)sp / (float)spMax;
	gaugeBar.setSize((int)(percentage * WIDTH), HEIGHT);
	gaugeBar.setVertex();
}


//=============================================================================
// �`�揈��
//=============================================================================
void SkillPointUI::render(LPDIRECT3DDEVICE9 device)
{
	gaugeBase.render(device);
	gaugeBar.render(device);
	gaugeCover.render(device);
}




