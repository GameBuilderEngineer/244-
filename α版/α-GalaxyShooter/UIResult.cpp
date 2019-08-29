//============================================================================================================================================
// Document
//============================================================================================================================================
// UIResult.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/24
//============================================================================================================================================
#include "UIResult.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace uiResultNS;
//============================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//============================================================================================================================================
int UIResult::instanceIndex = 0;						//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UIResult::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
UIResult::UIResult(void)
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
UIResult::~UIResult(void)
{
	// ���
	release();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
HRESULT UIResult::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, TextManager* _textManager, GameMaster* _gameMaster)
{
	// �e�L�X�g�}�l�[�W��
	textManager = _textManager;

	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`���ǂݍ���( �L�����N�^�[ )
	texture[TYPE::CHARACTER_PLAYER_1_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_1_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);
	texture[TYPE::CHARACTER_PLAYER_2_ADAM] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_ADAM);
	texture[TYPE::CHARACTER_PLAYER_2_EVE] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::CHARACTER_EVE);

	// �e�N�X�`���ǂݍ���( ���U���g )
	texture[TYPE::WIN_1] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_WIN);
	texture[TYPE::WIN_2] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_WIN);
	texture[TYPE::LOSE_1] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_LOSE);
	texture[TYPE::LOSE_2] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_LOSE);
	texture[TYPE::DRAW_1] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_DRAW);
	texture[TYPE::DRAW_2] = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::RESULT_DRAW);

	// �e�N�X�`�����[�_�[�̃��U���gUI�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::RESULT_WINDOW;

	// �e�N�X�`���ǂݍ���( ���U���g )
	for (int i = TYPE::WINDOW; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// �X�v���C�g������
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}
	
	// ���U���g������
	playerTable = _gameMaster->getPlayerInfomation();
	result = _gameMaster->getResult();

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//============================================================================================================================================
void UIResult::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::CHARACTER_PLAYER_1_ADAM:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			PLAYER_WIDTH,						//	����
			PLAYER_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_PLAYER_CHARACTER_1,	//	���W x
				POSITION_Y_PLAYER_CHARACTER,	//	���W y
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
			PLAYER_WIDTH,						//	����
			PLAYER_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_PLAYER_CHARACTER_1,	//	���W x
				POSITION_Y_PLAYER_CHARACTER,	//	���W y
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
			PLAYER_WIDTH,						//	����
			PLAYER_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_PLAYER_CHARACTER_2,	//	���W x
				POSITION_Y_PLAYER_CHARACTER,	//	���W y
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
			PLAYER_WIDTH,						//	����
			PLAYER_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_PLAYER_CHARACTER_2,	//	���W x
				POSITION_Y_PLAYER_CHARACTER,	//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::WIN_1:
	case TYPE::LOSE_1:
	case TYPE::DRAW_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			RESULT_WIDTH,						//	����
			RESULT_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_1,					//	���W x
				POSITION_Y,						//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::WIN_2:
	case TYPE::LOSE_2:
	case TYPE::DRAW_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			RESULT_WIDTH,						//	����
			RESULT_HEIGHT,						//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_2,					//	���W x
				POSITION_Y,						//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::WINDOW:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			RESULT_WINDOW_WIDTH,				//	����
			RESULT_WINDOW_HEIGHT,				//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_RESULT_WINDOW,		//	���W x
				POSITION_Y_RESULT_WINDOW,		//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::PLAYER_NUMBER_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			PLAYER_NUMBER_WIDTH,				//	����
			PLAYER_NUMBER_HEIGHT,				//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_PLAYER_NUMBER_1,		//	���W x
				POSITION_Y_PLAYER_NUMBER,		//	���W y
				0.0f							//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)	//	�F
		);
		break;
	case TYPE::PLAYER_NUMBER_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],					//	�e�N�X�`��
			spriteNS::CENTER,					//	���_
			PLAYER_NUMBER_WIDTH,				//	����
			PLAYER_NUMBER_HEIGHT,				//	����
			D3DXVECTOR3							//	���W
			(
				POSITION_X_PLAYER_NUMBER_2,		//	���W x
				POSITION_Y_PLAYER_NUMBER,		//	���W y
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
void UIResult::release(void)
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
void UIResult::update(void)
{
	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void UIResult::render(LPDIRECT3DDEVICE9 _device)
{
	// �`���M�������܂ł̉�
	int chingin[2] = { 2353,3294 };

	// Window
	sprite[TYPE::WINDOW].render(_device);

	// Character
	if ((playerTable + gameMasterNS::PLAYER_TYPE::PLAYER_CHARACTER)->playerType == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_1_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_1_EVE].render(_device);
	}
	if ((playerTable + gameMasterNS::PLAYER_TYPE::NON_PLAYER_CHARACTER)->playerType == gameMasterNS::MODEL_ADAM)
	{
		sprite[TYPE::CHARACTER_PLAYER_2_ADAM].render(_device);
	}
	else
	{
		sprite[TYPE::CHARACTER_PLAYER_2_EVE].render(_device);
	}

	// PlayerNumber
	sprite[TYPE::PLAYER_NUMBER_1].render(_device);
	sprite[TYPE::PLAYER_NUMBER_2].render(_device);

	// Result
	switch (result)
	{
	case gameMasterNS::RESULT_LIST::WIN_1P:
		sprite[TYPE::WIN_1].render(_device);
		sprite[TYPE::LOSE_2].render(_device);
		break;
	case gameMasterNS::RESULT_LIST::WIN_2P:
		sprite[TYPE::WIN_2].render(_device);
		sprite[TYPE::LOSE_1].render(_device);
		break;
	case gameMasterNS::RESULT_LIST::DRAW:
		sprite[TYPE::DRAW_1].render(_device);
		sprite[TYPE::DRAW_2].render(_device);
		break;
	default:
		break;
	}

	// Chingin
	renderChingin();

	return;
}
//============================================================================================================================================
// renderChingin
// �`�� - �`���M��
//============================================================================================================================================
void UIResult::renderChingin(void)
{
	// Player 1
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN_BACK]->print((POSITION_X_PLAYER_CHARACTER_1 - 280.0f), ((WINDOW_HEIGHT / 2) + 60.0f), "�� %d ��", (playerTable + gameMasterNS::PLAYER_TYPE::PLAYER_CHARACTER)->wage);
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN]->print((POSITION_X_PLAYER_CHARACTER_1 - 290.0f), ((WINDOW_HEIGHT / 2) + 50.0f), "�� %d ��", (playerTable + gameMasterNS::PLAYER_TYPE::PLAYER_CHARACTER)->wage);
	// Player 2
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN_BACK]->print((POSITION_X_PLAYER_CHARACTER_2 - 280.0f), ((WINDOW_HEIGHT / 2) + 60.0f), "�� %d ��", (playerTable + gameMasterNS::PLAYER_TYPE::NON_PLAYER_CHARACTER)->wage);
	textManager->text[textManagerNS::TYPE::NEW_RODIN_RESULT_CHINGIN]->print((POSITION_X_PLAYER_CHARACTER_2 - 290.0f), ((WINDOW_HEIGHT / 2) + 50.0f), "�� %d ��", (playerTable + gameMasterNS::PLAYER_TYPE::NON_PLAYER_CHARACTER)->wage);
	
	return;
}