//=============================================================================
// HP��UI���� [HitPointUI.cpp]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/9
//=============================================================================
#include "HitPointUI.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 300;						// ���T�C�Y
const static int		HEIGHT = 28;						// �c�T�C�Y					
const static float		POSITION_X_PLAYER1 = 40.0f;			// X���W
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;
const static float		POSITION_Y = 15.0f;					// Y���W
#define BAR_COLOR		(D3DCOLOR_RGBA(0, 255, 0, 255))		// �o�[�̐F
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �o�[�̐F


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int HitPointUI::cntUI = -1;
LPDIRECT3DTEXTURE9 HitPointUI::textureGaugeBase = NULL;		// �Q�[�W�x�[�X�̃e�N�X�`��
LPDIRECT3DTEXTURE9 HitPointUI::textureGaugeBar = NULL;		// �Q�[�W�o�[�̃e�N�X�`��
LPDIRECT3DTEXTURE9 HitPointUI::textureGaugeCover = NULL;	// �Q�[�W�J�o�[�̃e�N�X�`��


//=============================================================================
// �R���X�g���N�^
//=============================================================================
HitPointUI::HitPointUI(void)
{
	cntUI++;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
HitPointUI::~HitPointUI(void)
{
}


//=============================================================================
// ����������
//=============================================================================
HRESULT HitPointUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
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
void HitPointUI::uninitialize(void)
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
void HitPointUI::update(int hp,int hpMax)
{
	float percentage = (float)hp / (float)hpMax;
	gaugeBar.setSize((int)(percentage * WIDTH), HEIGHT);
	gaugeBar.setVertex();
}


//=============================================================================
// �`�揈��
//=============================================================================
void HitPointUI::render(LPDIRECT3DDEVICE9 device)
{
	gaugeBase.render(device);
	gaugeBar.render(device);
	gaugeCover.render(device);
}




