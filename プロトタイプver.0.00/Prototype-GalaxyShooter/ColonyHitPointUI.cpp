//=============================================================================
// �R���j�[HP��UI���� [ColonyHitPointUI.cpp]
//
// Author : HAL�������ԕ� 2�N���Q�[���w�� GP12A332 32 �����a�P
// �쐬�� : 2019/6/9
//=============================================================================
#include "ColonyHitPointUI.h"

//*****************************************************************************
// �萔�E�}�N��
//*****************************************************************************
const static int		WIDTH = 75;							// ���T�C�Y
const static int		HEIGHT = 75;						// �c�T�C�Y					
const static float		POSITION_X_PLAYER1 = 20.0f;			// X���W
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;
const static float		POSITION_Y = WINDOW_HEIGHT- 130.0f;	// Y���W
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �o�[�̐F


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int ColonyHitPointUI::cntUI = -1;
LPDIRECT3DTEXTURE9 ColonyHitPointUI::buffTexture = NULL;	// �e�N�X�`��


//=============================================================================
// �R���X�g���N�^
//=============================================================================
ColonyHitPointUI::ColonyHitPointUI(void)
{
	cntUI++;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
ColonyHitPointUI::~ColonyHitPointUI(void)
{
}


//=============================================================================
// ����������
//=============================================================================
HRESULT ColonyHitPointUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// �e�N�X�`����ǂݍ���
	setVisualDirectory();
	if (buffTexture == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "ColonyHitPointUI.jpg", &buffTexture)))
		{
			MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "ColonyHitPointUI.jpg", MB_OK);
			return E_FAIL;
		}
	}

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
void ColonyHitPointUI::uninitialize(void)
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
void ColonyHitPointUI::update(void)
{
}


//=============================================================================
// �`�揈��
//=============================================================================
void ColonyHitPointUI::render(LPDIRECT3DDEVICE9 device)
{
	Sprite::render(device);
}




