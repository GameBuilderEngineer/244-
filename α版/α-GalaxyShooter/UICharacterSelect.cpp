//============================================================================================================================================
// Document
//============================================================================================================================================
// UICharacterSelect.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/25
//============================================================================================================================================
#include "UICharacterSelect.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace uiCharacterSelectNS;
//============================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//============================================================================================================================================
int UICharacterSelect::instanceIndex = 0;						//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UICharacterSelect::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
UICharacterSelect::UICharacterSelect(void)
{
	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex++;

	// �e�N�X�`���̃N���A
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	// ������
	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
	{
		selectState[i] = NULL;
	}

	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
UICharacterSelect::~UICharacterSelect(void)
{
	// ���
	release();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
HRESULT UICharacterSelect::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader)
{
	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`���ǂݍ���( �L�����N�^�[ )
	texture[TYPE::CHARACTER_PLAYER_1_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_1_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);
	texture[TYPE::CHARACTER_PLAYER_2_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_2_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);

	// �e�N�X�`���ǂݍ���( �L�����N�^�[�� )
	texture[TYPE::NAME_PLAYER_1_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_ADAM);
	texture[TYPE::NAME_PLAYER_1_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_EVE);
	texture[TYPE::NAME_PLAYER_2_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_ADAM);
	texture[TYPE::NAME_PLAYER_2_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_NAME_EVE);

	// �e�N�X�`�����[�_�[�̃��U���gUI�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_BACKGROUND_1;

	// �e�N�X�`���ǂݍ���( ���U���g )
	for (int i = TYPE::BACKGROUND_1; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// �X�v���C�g������
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//============================================================================================================================================
void UICharacterSelect::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::CHARACTER_PLAYER_1_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			CHARACTER_WIDTH,					//	����
			CHARACTER_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_CHARACTER_1,			//	���W x
				POSITION_Y_CHARACTER,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::CHARACTER_PLAYER_1_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			CHARACTER_WIDTH,					//	����
			CHARACTER_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_CHARACTER_1,			//	���W x
				POSITION_Y_CHARACTER,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::CHARACTER_PLAYER_2_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			CHARACTER_WIDTH,					//	����
			CHARACTER_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_CHARACTER_2,			//	���W x
				POSITION_Y_CHARACTER,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::CHARACTER_PLAYER_2_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			CHARACTER_WIDTH,					//	����
			CHARACTER_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_CHARACTER_2,			//	���W x
				POSITION_Y_CHARACTER,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::NAME_PLAYER_1_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			NAME_WIDTH,							//	����
			NAME_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_NAME_1,				//	���W x
				POSITION_Y_NAME,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::NAME_PLAYER_1_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			NAME_WIDTH,							//	����
			NAME_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_NAME_1,				//	���W x
				POSITION_Y_NAME,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::NAME_PLAYER_2_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			NAME_WIDTH,							//	����
			NAME_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_NAME_2,				//	���W x
				POSITION_Y_NAME,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::NAME_PLAYER_2_EVE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			NAME_WIDTH,							//	����
			NAME_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_NAME_2,				//	���W x
				POSITION_Y_NAME,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::BACKGROUND_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			BACKGROUND_WIDTH,					//	����
			BACKGROUND_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_BACKGROUND_1,		//	���W x
				POSITION_Y_BACKGROUND,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::BACKGROUND_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			BACKGROUND_WIDTH,					//	����
			BACKGROUND_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_BACKGROUND_2,		//	���W x
				POSITION_Y_BACKGROUND,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::BAR_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			BAR_WIDTH,							//	����
			BAR_HEIGHT,							//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_BAR_1,				//	���W x
				POSITION_Y_BAR,					//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::BAR_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			BAR_WIDTH,							//	����
			BAR_HEIGHT,							//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_BAR_2,				//	���W x
				POSITION_Y_BAR,					//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::CURSOR_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			CURSOR_WIDTH,						//	����
			CURSOR_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_CURSOR_1,			//	���W x
				POSITION_Y_CURSOR,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::CURSOR_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			CURSOR_WIDTH,						//	����
			CURSOR_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_CURSOR_2,			//	���W x
				POSITION_Y_CURSOR,				//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::TIME:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			TIME_WIDTH,							//	����
			TIME_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_TIME,				//	���W x
				POSITION_Y_TIME,				//	���W y
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
void UICharacterSelect::release(void)
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
void UICharacterSelect::update(Input* _input, Sound *_sound)
{
	// ���͂̍X�V
	updateInput(_input, _sound);

	// UI�̐���
	updateControl();

	return;
}
//============================================================================================================================================
// updateInput
// �X�V - ����
//============================================================================================================================================
void UICharacterSelect::updateInput(Input* _input, Sound *_sound)
{
	// �e�v���C���[�̓��͍X�V
	updateInputPlayer1(_input, _sound);
	updateInputPlayer2(_input, _sound);

	return;
}
//============================================================================================================================================
// updateInputPlayer1
// �X�V - ����( �v���C���[1 )
//============================================================================================================================================
void UICharacterSelect::updateInputPlayer1(Input* _input, Sound *_sound)
{
	// UI�؂�ւ�( Player 1 )
	if (_input->wasKeyPressed('D') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::RIGHT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] += 1;
	}
	else if (_input->wasKeyPressed('A') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::LEFT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] -= 1;
	}

	return;
}
//============================================================================================================================================
// updateInputPlayer2
// �X�V - ����( �v���C���[2 )
//============================================================================================================================================
void UICharacterSelect::updateInputPlayer2(Input* _input, Sound *_sound)
{
	// UI�؂�ւ�( Player 2 )
	if (_input->wasKeyPressed(VK_RIGHT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::RIGHT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] += 1;
	}
	else if (_input->wasKeyPressed(VK_LEFT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::LEFT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] -= 1;
	}

	return;
}
//============================================================================================================================================
// updateControl
// �X�V - ����
//============================================================================================================================================
void UICharacterSelect::updateControl(void)
{
	// �e�v���C���[��UI����
	updateControlPlayer1();
	updateControlPlayer2();

	return;
}
//============================================================================================================================================
// updateControlPlayer1
// �X�V - ����( �v���C���[1 )
//============================================================================================================================================
void UICharacterSelect::updateControlPlayer1(void)
{
	// UI����( Player 1 )
	if (selectState[PLAYER_TYPE::PLAYER_1] > gameMasterNS::MODEL_EVE)
	{
		selectState[PLAYER_TYPE::PLAYER_1] = gameMasterNS::MODEL_ADAM;
	}
	else if (selectState[PLAYER_TYPE::PLAYER_1] < gameMasterNS::MODEL_ADAM)
	{
		selectState[PLAYER_TYPE::PLAYER_1] = gameMasterNS::MODEL_EVE;
	}

	return;
}
//============================================================================================================================================
// updateControlPlayer2
// �X�V - ����( �v���C���[2 )
//============================================================================================================================================
void UICharacterSelect::updateControlPlayer2(void)
{
	// UI����( Player 2 )
	if (selectState[PLAYER_TYPE::PLAYER_2] > gameMasterNS::MODEL_EVE)
	{
		selectState[PLAYER_TYPE::PLAYER_2] = gameMasterNS::MODEL_ADAM;
	}
	else if (selectState[PLAYER_TYPE::PLAYER_2] < gameMasterNS::MODEL_ADAM)
	{
		selectState[PLAYER_TYPE::PLAYER_2] = gameMasterNS::MODEL_EVE;
	}

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void UICharacterSelect::render(LPDIRECT3DDEVICE9 _device)
{
	// BackGround
	sprite[TYPE::BACKGROUND_1].render(_device);
	sprite[TYPE::BACKGROUND_2].render(_device);

	// Character
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_1_EVE].render(_device);
	}

	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_2_EVE].render(_device);
	}

	// Bar
	sprite[TYPE::BAR_1].render(_device);
	sprite[TYPE::BAR_2].render(_device);

	// Name
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_1_EVE].render(_device);
	}

	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_2_EVE].render(_device);
	}

	// Cursor
	sprite[TYPE::CURSOR_1].render(_device);
	sprite[TYPE::CURSOR_2].render(_device);

	return;
}
//============================================================================================================================================
// renderTime
// �`�� - ����
//============================================================================================================================================
void UICharacterSelect::renderTime(LPDIRECT3DDEVICE9 _device)
{
	// Time
	sprite[TYPE::TIME].render(_device);

	return;
}
//============================================================================================================================================
// getSelectState
// �擾 - �I�����
//============================================================================================================================================
int UICharacterSelect::getSelectState(int _index)
{ 
	return selectState[_index];
}