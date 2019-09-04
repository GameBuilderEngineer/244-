//============================================================================================================================================
// Document
//============================================================================================================================================
// UITitle.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/29
//============================================================================================================================================
#include "UITitle.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace uiTitleNS;
//============================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//============================================================================================================================================
int UITitle::instanceIndex = 0;							//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UITitle::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
UITitle::UITitle(void)
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
UITitle::~UITitle(void)
{
	// ���
	release();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
HRESULT UITitle::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, int _selectStateMemory)
{
	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`�����[�_�[�̃^�C�g��UI�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::TITLE_LOGO;

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

	selectState = _selectStateMemory;

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//============================================================================================================================================
void UITitle::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::TITLE_LOGO:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_TITLE_LOGO,					//	����
			HEIGHT_TITLE_LOGO,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_TITLE_LOGO_X,			//	���W x
				POSITION_TITLE_LOGO_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::TITLE_BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_TITLE_BAR,					//	����
			HEIGHT_TITLE_BAR,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_TITLE_BAR_X,			//	���W x
				POSITION_TITLE_BAR_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::GAME_START:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_GAME_START,					//	����
			HEIGHT_GAME_START,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_GAME_START_X,			//	���W x
				POSITION_GAME_START_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::GAME_START_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_GAME_START,					//	����
			HEIGHT_GAME_START,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_GAME_START_X,			//	���W x
				POSITION_GAME_START_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::TUTORIAL:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_TUTORIAL,						//	����
			HEIGHT_TUTORIAL,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_TUTORIAL_X,			//	���W x
				POSITION_TUTORIAL_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::TUTORIAL_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_TUTORIAL,						//	����
			HEIGHT_TUTORIAL,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_TUTORIAL_X,			//	���W x
				POSITION_TUTORIAL_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::OPERATION:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_OPERATION,					//	����
			HEIGHT_OPERATION,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_OPERATION_X,			//	���W x
				POSITION_OPERATION_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::OPERATION_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_OPERATION,					//	����
			HEIGHT_OPERATION,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_OPERATION_X,			//	���W x
				POSITION_OPERATION_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::CREDIT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_CREDIT,						//	����
			HEIGHT_CREDIT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_CREDIT_X,				//	���W x
				POSITION_CREDIT_Y,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::CREDIT_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_CREDIT,						//	����
			HEIGHT_CREDIT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_CREDIT_X,				//	���W x
				POSITION_CREDIT_Y,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::GAME_EXIT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_GAME_EXIT,					//	����
			HEIGHT_GAME_EXIT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_GAME_EXIT_X,			//	���W x
				POSITION_GAME_EXIT_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::GAME_EXIT_SELECT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			WIDTH_GAME_EXIT,					//	����
			HEIGHT_GAME_EXIT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_GAME_EXIT_X,			//	���W x
				POSITION_GAME_EXIT_Y,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
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
void UITitle::release(void)
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
void UITitle::update(Input* _input, Sound* _sound)
{
	if (_input->wasKeyPressed(VK_DOWN) ||
		_input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::DOWN) ||
		_input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::DOWN))
	{
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState++;
	}
	else if (_input->wasKeyPressed(VK_UP) ||
		_input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::UP) ||
		_input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::UP))
	{
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState--;
	}

	if (selectState > TITLE_MENU_TYPE::MENU_GAME_EXIT)
	{
		selectState = TITLE_MENU_TYPE::MENU_GAME_START;
	}
	else if (selectState < TITLE_MENU_TYPE::MENU_GAME_START)
	{
		selectState = TITLE_MENU_TYPE::MENU_GAME_EXIT;
	}

	updateBar();

	return;
}
//============================================================================================================================================
// updateBar
// �X�V - �o�[
//============================================================================================================================================
void UITitle::updateBar(void)
{
	switch (selectState)
	{
	case TITLE_MENU_TYPE::MENU_GAME_START:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_GAME_START_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_TUTORIAL:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_TUTORIAL_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_OPERATION:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_OPERATION_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_CREDIT:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_CREDIT_Y, 0.0f));
		break;
	case TITLE_MENU_TYPE::MENU_GAME_EXIT:
		sprite[TYPE::TITLE_BAR].setPosition(D3DXVECTOR3(POSITION_TITLE_BAR_X, POSITION_GAME_EXIT_Y, 0.0f));
		break;
	default:
		break;
	}

	sprite[TYPE::TITLE_BAR].setVertex();

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void UITitle::render(LPDIRECT3DDEVICE9 _device)
{
	// Bar
	sprite[TYPE::TITLE_BAR].render(_device);

	// Game Start
	if (selectState == TITLE_MENU_TYPE::MENU_GAME_START)
	{
		sprite[TYPE::GAME_START_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::GAME_START].render(_device);
	}

	// Tutorial
	if (selectState == TITLE_MENU_TYPE::MENU_TUTORIAL)
	{
		sprite[TYPE::TUTORIAL_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::TUTORIAL].render(_device);
	}

	// Operation
	if (selectState == TITLE_MENU_TYPE::MENU_OPERATION)
	{
		sprite[TYPE::OPERATION_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::OPERATION].render(_device);
	}

	// Credit
	if (selectState == TITLE_MENU_TYPE::MENU_CREDIT)
	{
		sprite[TYPE::CREDIT_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::CREDIT].render(_device);
	}

	// Game Exit
	if (selectState == TITLE_MENU_TYPE::MENU_GAME_EXIT)
	{
		sprite[TYPE::GAME_EXIT_SELECT].render(_device);
	}
	else
	{
		sprite[TYPE::GAME_EXIT].render(_device);
	}

	// Title Logo
	sprite[TYPE::TITLE_LOGO].render(_device);

	return;
}