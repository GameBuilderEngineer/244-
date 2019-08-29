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
	selectState[PLAYER_TYPE::PLAYER_1] = 0;
	selectState[PLAYER_TYPE::PLAYER_2] = 1;
	progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::CHARACTER_SELECT;
	progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::CHARACTER_SELECT;

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

	// �e�N�X�`���ǂݍ���( �������� + �҂� )
	texture[TYPE::READY_PLAYER_1_BACKGROUND] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BACKGROUND);
	texture[TYPE::READY_PLAYER_2_BACKGROUND] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BACKGROUND);
	texture[TYPE::READY_PLAYER_1_BAR] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BAR);
	texture[TYPE::READY_PLAYER_2_BAR] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_BAR);
	texture[TYPE::READY_PLAYER_1_CANCEL] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_CANCEL);
	texture[TYPE::READY_PLAYER_2_CANCEL] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_CANCEL);
	texture[TYPE::READY_PLAYER_1_WAITING] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_WAITING);
	texture[TYPE::READY_PLAYER_2_WAITING] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_CHARACTER_SELECT_READY_WAITING);

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
	case TYPE::READY_PLAYER_1_BACKGROUND:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_BACKGROUND_WIDTH,				//	����
			READY_BACKGROUND_HEIGHT,			//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_BACKGROUND_1,	//	���W x
				POSITION_Y_READY_BACKGROUND,	//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::READY_PLAYER_2_BACKGROUND:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_BACKGROUND_WIDTH,				//	����
			READY_BACKGROUND_HEIGHT,			//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_BACKGROUND_2,	//	���W x
				POSITION_Y_READY_BACKGROUND,	//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::READY_PLAYER_1_BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_BAR_WIDTH,					//	����
			READY_BAR_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_BAR_1,			//	���W x
				POSITION_Y_READY_BAR,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::READY_PLAYER_2_BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_BAR_WIDTH,					//	����
			READY_BAR_HEIGHT,					//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_BAR_2,			//	���W x
				POSITION_Y_READY_BAR,			//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::READY_PLAYER_1_CANCEL:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_CANCEL_WIDTH,					//	����
			READY_CANCEL_HEIGHT,				//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_CANCEL_1,		//	���W x
				POSITION_Y_READY_CANCEL,		//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::READY_PLAYER_2_CANCEL:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_CANCEL_WIDTH,					//	����
			READY_CANCEL_HEIGHT,				//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_CANCEL_2,		//	���W x
				POSITION_Y_READY_CANCEL,		//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::READY_PLAYER_1_WAITING:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_WAITING_WIDTH,				//	����
			READY_WAITING_HEIGHT,				//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_WAITING_1,		//	���W x
				POSITION_Y_READY_WAITING,		//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::READY_PLAYER_2_WAITING:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			READY_WAITING_WIDTH,				//	����
			READY_WAITING_HEIGHT,				//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_READY_WAITING_2,		//	���W x
				POSITION_Y_READY_WAITING,		//	���W y
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
// updateInputCharacterSelect
// �X�V - ����( �L�����N�^�[�Z���N�g )
//============================================================================================================================================
void UICharacterSelect::updateInput(Input* _input, Sound *_sound)
{
	// Player 1
	switch (progressState[PLAYER_TYPE::PLAYER_1])
	{
	case PROGRESS_TYPE::CHARACTER_SELECT:
		updateInputCharacterSelectPlayer1(_input, _sound);
		break;
	case PROGRESS_TYPE::READY:
		updateInputReadyPlayer1(_input, _sound);
		break;
	case PROGRESS_TYPE::WAITING:
		updateInputWaitingPlayer1(_input, _sound);
		break;
	default:
		break;
	}

	// Player 2
	switch (progressState[PLAYER_TYPE::PLAYER_2])
	{
	case PROGRESS_TYPE::CHARACTER_SELECT:
		updateInputCharacterSelectPlayer2(_input, _sound);
		break;
	case PROGRESS_TYPE::READY:
		updateInputReadyPlayer2(_input, _sound);
		break;
	case PROGRESS_TYPE::WAITING:
		updateInputWaitingPlayer2(_input, _sound);
		break;
	default:
		break;
	}

	return;
}
//============================================================================================================================================
// updateInputCharacterSelectPlayer1
// �X�V - ����( �L�����N�^�[�Z���N�g�F�v���C���[1 )
//============================================================================================================================================
void UICharacterSelect::updateInputCharacterSelectPlayer1(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_RETURN) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::READY;

		return;
	}

	if (_input->wasKeyPressed('D') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::RIGHT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] += 1;

		return;
	}
	else if (_input->wasKeyPressed('A') || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::LEFT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_1] -= 1;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputCharacterSelectPlayer2
// �X�V - ����( �L�����N�^�[�Z���N�g�F�v���C���[2 )
//============================================================================================================================================
void UICharacterSelect::updateInputCharacterSelectPlayer2(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_SPACE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::READY;

		return;
	}

	if (_input->wasKeyPressed(VK_RIGHT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::RIGHT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] += 1;

		return;
	}
	else if (_input->wasKeyPressed(VK_LEFT) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::LEFT))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		selectState[PLAYER_TYPE::PLAYER_2] -= 1;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputReadyPlayer1
// �X�V - ����( ���������F�v���C���[1 )
//============================================================================================================================================
void UICharacterSelect::updateInputReadyPlayer1(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_BACK) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::CHARACTER_SELECT;

		return;
	}

	if (_input->wasKeyPressed(VK_RETURN) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::WAITING;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputReadyPlayer2
// �X�V - ����( ���������F�v���C���[2 )
//============================================================================================================================================
void UICharacterSelect::updateInputReadyPlayer2(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_DELETE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::CHARACTER_SELECT;

		return;
	}

	if (_input->wasKeyPressed(VK_SPACE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_READY, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::WAITING;

		return;
	}

	return;
}
//============================================================================================================================================
// updateInputWaitingPlayer1
// �X�V - ����( �҂��F�v���C���[1 )
//============================================================================================================================================
void UICharacterSelect::updateInputWaitingPlayer1(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_BACK) || _input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_1] = PROGRESS_TYPE::CHARACTER_SELECT;
	}

	return;
}
//============================================================================================================================================
// updateInputWaitingPlayer2
// �X�V - ����( �҂��F�v���C���[2 )
//============================================================================================================================================
void UICharacterSelect::updateInputWaitingPlayer2(Input* _input, Sound *_sound)
{
	if (_input->wasKeyPressed(VK_DELETE) || _input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::B))
	{
		// �T�E���h�̍Đ�
		_sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		progressState[PLAYER_TYPE::PLAYER_2] = PROGRESS_TYPE::CHARACTER_SELECT;
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
	// �L�����N�^�[�Z���N�g
	renderCharacterSelect1(_device);
	renderCharacterSelect2(_device);

	// �������� + �҂�
	renderReadyWaiting1(_device);
	renderReadyWaiting2(_device);

	return;
}
//============================================================================================================================================
// renderCharacterSelect1
// �`�� - �L�����N�^�[�Z���N�g�F�v���C���[1
//============================================================================================================================================
void UICharacterSelect::renderCharacterSelect1(LPDIRECT3DDEVICE9 _device)
{
	// BackGround
	sprite[TYPE::BACKGROUND_1].render(_device);

	// Character
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_1_EVE].render(_device);
	}

	// Bar
	sprite[TYPE::BAR_1].render(_device);

	// Name
	if (selectState[PLAYER_TYPE::PLAYER_1] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_1_EVE].render(_device);
	}

	// Cursor
	sprite[TYPE::CURSOR_1].render(_device);

	return;
}
//============================================================================================================================================
// renderCharacterSelect2
// �`�� - �L�����N�^�[�Z���N�g�F�v���C���[2
//============================================================================================================================================
void UICharacterSelect::renderCharacterSelect2(LPDIRECT3DDEVICE9 _device)
{
	// BackGround
	sprite[TYPE::BACKGROUND_2].render(_device);

	// Character
	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_2_EVE].render(_device);
	}

	// Bar
	sprite[TYPE::BAR_2].render(_device);

	// Name
	if (selectState[PLAYER_TYPE::PLAYER_2] == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::NAME_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::NAME_PLAYER_2_EVE].render(_device);
	}

	// Cursor
	sprite[TYPE::CURSOR_2].render(_device);

	return;
}
//============================================================================================================================================
// renderReadyWaiting1
// �`�� - �������� + �҂��F�v���C���[1
//============================================================================================================================================
void UICharacterSelect::renderReadyWaiting1(LPDIRECT3DDEVICE9 _device)
{
	if (progressState[PLAYER_TYPE::PLAYER_1] == PROGRESS_TYPE::CHARACTER_SELECT) { return; }

	sprite[TYPE::READY_PLAYER_1_BACKGROUND].render(_device);

	if (progressState[PLAYER_TYPE::PLAYER_1] == PROGRESS_TYPE::READY)
	{
		sprite[TYPE::READY_PLAYER_1_BAR].render(_device);
		sprite[TYPE::READY_PLAYER_1_CANCEL].render(_device);

		return;
	}

	if (progressState[PLAYER_TYPE::PLAYER_1] == PROGRESS_TYPE::WAITING)
	{
		sprite[TYPE::READY_PLAYER_1_WAITING].render(_device);
		sprite[TYPE::READY_PLAYER_1_CANCEL].render(_device);

		return;
	}

	return;
}
//============================================================================================================================================
// renderReadyWaiting2
// �`�� - �������� + �҂��F�v���C���[2
//============================================================================================================================================
void UICharacterSelect::renderReadyWaiting2(LPDIRECT3DDEVICE9 _device)
{
	if (progressState[PLAYER_TYPE::PLAYER_2] == PROGRESS_TYPE::CHARACTER_SELECT) { return; }

	sprite[TYPE::READY_PLAYER_2_BACKGROUND].render(_device);

	if (progressState[PLAYER_TYPE::PLAYER_2] == PROGRESS_TYPE::READY)
	{
		sprite[TYPE::READY_PLAYER_2_BAR].render(_device);
		sprite[TYPE::READY_PLAYER_2_CANCEL].render(_device);

		return;
	}

	if (progressState[PLAYER_TYPE::PLAYER_2] == PROGRESS_TYPE::WAITING)
	{
		sprite[TYPE::READY_PLAYER_2_WAITING].render(_device);
		sprite[TYPE::READY_PLAYER_2_CANCEL].render(_device);

		return;
	}

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