//=============================================================================
// �~�T�C��UI���� [MissileUI.cpp]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/9
//=============================================================================
#include "MissileUI.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 25;							// ���T�C�Y
const static int		HEIGHT = 75;						// �c�T�C�Y	
															// X���W
const static float		POSITION_X_PLAYER1 = WINDOW_WIDTH / 2.0f - 100.0f;
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;
const static float		POSITION_Y = WINDOW_HEIGHT- 210.0f;	// Y���W
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �o�[�̐F


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int MissileUI::cntUI = -1;
LPDIRECT3DTEXTURE9 MissileUI::buffTexture = NULL;	// �e�N�X�`��


//=============================================================================
// �R���X�g���N�^
//=============================================================================
MissileUI::MissileUI(void)
{
	cntUI++;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
MissileUI::~MissileUI(void)
{
}


//=============================================================================
// ����������
//=============================================================================
HRESULT MissileUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();

	buffTexture = *textureLoader->getTexture(textureLoaderNS::UI_MISSILE);

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
void MissileUI::uninitialize(void)
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
void MissileUI::update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void MissileUI::render(LPDIRECT3DDEVICE9 device)
{
	Sprite::render(device);
}


