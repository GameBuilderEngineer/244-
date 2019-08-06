//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRevivalGauge.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/07
//======================================================================================================================================================
#include "UIRevivalGauge.h"
//
//#define BAR_COLOR		(D3DCOLOR_RGBA(0, 255, 0, 255))		// �o�[�̐F
//#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// �o�[�̐F

//======================================================================================================================================================
// Using Declaration
// using�錾
//======================================================================================================================================================
using namespace uiRevivalGaugeNS;
//======================================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//======================================================================================================================================================
int UIRevivalGauge::instanceIndex = (-1);					//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UIRevivalGauge::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��
//======================================================================================================================================================
// Constructor
// �R���X�g���N�^
//======================================================================================================================================================
UIRevivalGauge::UIRevivalGauge(void)
{
	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex++;

	// �e�N�X�`���̃N���A
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	return;
}
//======================================================================================================================================================
// Destructor
// �f�X�g���N�^
//======================================================================================================================================================
UIRevivalGauge::~UIRevivalGauge(void)
{
	// ���
	release();

	return;
}
//======================================================================================================================================================
// initialize
// ������
//======================================================================================================================================================
HRESULT UIRevivalGauge::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader)
{
	// �e�N�X�`�����[�_�[�̕����Q�[�W�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_REVIVAL_GAUGE_00;

	// �v���C���[�C���f�b�N�X
	playerIndex = _playerIndex;

	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`���ǂݍ���
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// �X�v���C�g������
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}

	//// �X�v���C�g������
	//gaugeBase.initialize(device,
	//	textureGaugeBase,					// �e�N�X�`��
	//	spriteNS::TOP_LEFT,					// ���_
	//	WIDTH,								// ����
	//	HEIGHT,								// ����
	//	D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
	//	DEFAULT_COLOR						// �F
	//);
	//gaugeBar.initialize(device,
	//	textureGaugeBar,					// �e�N�X�`��
	//	spriteNS::TOP_LEFT,					// ���_
	//	WIDTH,								// ����
	//	HEIGHT,								// ����
	//	D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
	//	BAR_COLOR							// �F
	//);
	//gaugeCover.initialize(device,
	//	textureGaugeCover,					// �e�N�X�`��
	//	spriteNS::TOP_LEFT,					// ���_
	//	WIDTH,								// ����
	//	HEIGHT,								// ����
	//	D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// ���W
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// ��]
	//	DEFAULT_COLOR						// �F
	//);

	return S_OK;
}
//======================================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//======================================================================================================================================================
void UIRevivalGauge::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::FOUNDATION:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH,															//	����
			HEIGHT,															//	����
			D3DXVECTOR3														//	���W
			(
				playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y,													//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	case TYPE::CURRENT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH,															//	����
			HEIGHT,															//	����
			D3DXVECTOR3														//	���W
			(
				playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y,													//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	default:
		break;
	}

	return;
}
//======================================================================================================================================================
// release
// ���
//======================================================================================================================================================
void UIRevivalGauge::release(void)
{
	// �X�v���C�g�̃N���A
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].setTexture(NULL);
	}

	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex--;

	// �C���X�^���X�����݂��Ȃ���΁A�e�N�X�`�������
	if (instanceIndex >= 0)
	{
		return;
	}

	SAFE_RELEASE(texture[TYPE::FOUNDATION]);
	SAFE_RELEASE(texture[TYPE::CURRENT]);

	return;
}
//======================================================================================================================================================
// update
// �X�V
//======================================================================================================================================================
void UIRevivalGauge::update(int _revivalPoint)
{
	float percentage = ((float)_revivalPoint / (float)50000);

	sprite[TYPE::CURRENT].setSize((int)(percentage * WIDTH), HEIGHT);
	sprite[TYPE::CURRENT].setVertex();

	return;
}
//======================================================================================================================================================
// render
// �`��
//======================================================================================================================================================
void UIRevivalGauge::render(LPDIRECT3DDEVICE9 _device)
{
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}