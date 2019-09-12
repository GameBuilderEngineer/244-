//============================================================================================================================================
// Document
//============================================================================================================================================
// UIChingin.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/01
//============================================================================================================================================
#include "UIChingin.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace uiChinginNS;
//============================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//============================================================================================================================================
int UIChingin::instanceIndex = 0;		//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UIChingin::texture;	//	�e�N�X�`��
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
UIChingin::UIChingin(void)
{
	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex++;

	// �e�N�X�`���̃N���A
	texture = NULL;

	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
UIChingin::~UIChingin(void)
{
	// ���
	release();

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
HRESULT UIChingin::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, TextManager* _textManager)
{
	// �e�L�X�g�}�l�[�W��
	textManager = _textManager;

	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`���ǂݍ���
	texture = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::UI_PLAY_TIME_CHINGIN);

	// �X�v���C�g������
	sprite.initialize
	(
		_device,
		texture,														//	�e�N�X�`��
		spriteNS::CENTER,												//	���_
		WIDTH,															//	����
		HEIGHT,															//	����
		D3DXVECTOR3														//	���W
		(
			!_playerIndex ? POSITION_X_PLAYER_1 : POSITION_X_PLAYER_2,	//	���W x
			POSITION_Y,													//	���W y
			0.0f														//	���W z
		),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
		D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
	);

	return S_OK;
}
//============================================================================================================================================
// release
// ���
//============================================================================================================================================
void UIChingin::release(void)
{
	// �X�v���C�g�̃N���A
	sprite.setTexture(NULL);

	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex--;

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void UIChingin::render(LPDIRECT3DDEVICE9 _device, float _time, int _chingin,int playerID)
{
	// UI�w�i
	sprite.render(_device);
	switch (playerID)
	{
	case playerNS::PLAYER1:
		// �e�L�X�g
		textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_1 - 165.0f, POSITION_Y - 25.0f, "SCORE");
		// �Q�[�����Ԃ������i�Q���j��؂�����A�`���M�����B���i�\�����u???�v�ɕύX�j
		if (_time > gameMasterNS::GAME_TIME / 2.0f)
		{
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_1 - 30.0f, POSITION_Y - 25.0f, "%05d", _chingin);
		}
		else {
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_1 - 30.0f, POSITION_Y - 25.0f, "?????");
		}
		break;
	case playerNS::PLAYER2:
		// �e�L�X�g
		textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_2 - 165.0f, POSITION_Y - 25.0f, "SCORE");
		// �Q�[�����Ԃ������i�Q���j��؂�����A�`���M�����B���i�\�����u???�v�ɕύX�j
		if (_time > gameMasterNS::GAME_TIME / 2.0f)
		{
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_2 - 30.0f, POSITION_Y - 25.0f, "%05d", _chingin);
		}
		else {
			textManager->text[textManagerNS::TYPE::NEW_RODIN_GAME_TIME]->print(POSITION_X_PLAYER_2 - 30.0f, POSITION_Y - 25.0f, "?????");
		}
		break;
	}
}