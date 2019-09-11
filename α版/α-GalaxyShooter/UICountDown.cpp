//============================================================================================================================================
// Document
//============================================================================================================================================
// UICountDown.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/09/10
//============================================================================================================================================
#include "UICountDown.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace uiCountDownNS;
//============================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//============================================================================================================================================
int UICountDown::instanceIndex = 0;							//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UICountDown::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
UICountDown::UICountDown(void)
{
	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex++;

	// �e�N�X�`���̃N���A
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	alpha = 0;

	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
UICountDown::~UICountDown(void)
{
	// ���
	release();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
HRESULT UICountDown::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader)
{
	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`�����[�_�[�̕���UI�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_COUNT_DOWN_FINISH;

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

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//============================================================================================================================================
void UICountDown::initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index)
{
	switch (_index)
	{
	case TYPE::FINISH:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			(WIDTH_COUNT_DOWN * 2),											//	����
			(WIDTH_COUNT_DOWN * 2),											//	����
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
	case TYPE::GO:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			(WIDTH_COUNT_DOWN * 2),											//	����
			(WIDTH_COUNT_DOWN * 2),											//	����
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
	case TYPE::ONE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH_COUNT_DOWN,												//	����
			HEIGHT_COUNT_DOWN,												//	����
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
	case TYPE::TWO:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH_COUNT_DOWN,												//	����
			HEIGHT_COUNT_DOWN,												//	����
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
	case TYPE::THREE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH_COUNT_DOWN,												//	����
			HEIGHT_COUNT_DOWN,												//	����
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
void UICountDown::release(void)
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
void UICountDown::update(bool _startFlag)
{
	updateFadeOut();

	// �t�F�[�h���I�������^�C�g����
	if (!_startFlag) { return; }

	return;
}
//============================================================================================================================================
// updateFadeOut
// �X�V - �t�F�[�h�A�E�g
//============================================================================================================================================
void UICountDown::updateFadeOut(void)
{
	// �A���t�@���Z
	alpha--;

	if (alpha <= 0)
	{
		alpha = 0;
	}

	sprite[0].setAlpha(alpha);

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void UICountDown::render(LPDIRECT3DDEVICE9 _device, int _renderIndex)
{
	sprite[_renderIndex].render(_device);

	return;
}