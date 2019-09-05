//============================================================================================================================================
// Document
//============================================================================================================================================
// UIRevival.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/07
//============================================================================================================================================
#include "UIRevival.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace uiRevivalNS;
//============================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//============================================================================================================================================
int UIRevival::instanceIndex = 0;						//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UIRevival::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
UIRevival::UIRevival(void)
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
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
UIRevival::~UIRevival(void)
{
	// ���
	release();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
HRESULT UIRevival::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader)
{
	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`�����[�_�[�̕���UI�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_REVIVAL_BAR;

	// �e�N�X�`���ǂݍ���
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// �X�v���C�g������
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, _playerIndex, i);
	}

	// �X�v���C�g������
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, _playerIndex, i);
	}

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//============================================================================================================================================
void UIRevival::initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index)
{
	switch (_index)
	{
	case TYPE::BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH_BAR,														//	����
			HEIGHT_BAR,														//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y_BAR,												//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	case TYPE::GAUGE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH_GAUGE,													//	����
			HEIGHT_GAUGE,													//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y,													//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	case TYPE::CONCENTRATION:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH_CONCENTRATION,											//	����
			HEIGHT_CONCENTRATION,											//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y,													//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	case TYPE::TONE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH_TONE,														//	����
			HEIGHT_TONE,													//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
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
//============================================================================================================================================
// release
// ���
//============================================================================================================================================
void UIRevival::release(void)
{
	// �X�v���C�g�̃N���A
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].setTexture(NULL);
	}

	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex--;

	return;
}
//============================================================================================================================================
// update
// �X�V
//============================================================================================================================================
void UIRevival::update(int _revivalPoint)
{
	float percentage = ((float)_revivalPoint / (float)MAX_REVIVAL_POINT);

	sprite[GAUGE].setSize((int)(percentage * WIDTH_GAUGE), HEIGHT_GAUGE);
	sprite[GAUGE].setVertex();

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void UIRevival::render(LPDIRECT3DDEVICE9 _device)
{
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}