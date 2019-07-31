//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRecursion.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/07/27
//======================================================================================================================================================
#include "UIRecursion.h"
//======================================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//======================================================================================================================================================
int UIRecursion::instanceIndex = (-1);									//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UIRecursion::texture[uiRecursionNS::TYPE::TYPE_MAX];	//	�e�N�X�`��

bool moveFlag = false;

//======================================================================================================================================================
// Constructor
// �R���X�g���N�^
//======================================================================================================================================================
UIRecursion::UIRecursion(void)
{
	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex++;

	// �e�N�X�`���̃N���A
	for (int i = 0; i < uiRecursionNS::TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
		destinationIndex[i] = uiRecursionNS::POSITION::POP;
	}

	return;
}
//======================================================================================================================================================
// Destructor
// �f�X�g���N�^
//======================================================================================================================================================
UIRecursion::~UIRecursion(void)
{
	release();

	return;
}
//======================================================================================================================================================
// initialize
// ������
//======================================================================================================================================================
HRESULT UIRecursion::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader,
	
	Input* _input
	
	)
{


	input = _input;



	// �e�N�X�`�����[�_�[�̃��J�[�W����UI�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_RECURSION_BICYCLE;

	// �v���C���[�C���f�b�N�X
	playerIndex = _playerIndex;

	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`���ǂݍ���
	for (int i = 0; i < uiRecursionNS::TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// �X�v���C�g������
	for (int i = 0; i < uiRecursionNS::TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}

	return S_OK;
}
//======================================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//======================================================================================================================================================
void UIRecursion::initializeSprite(LPDIRECT3DDEVICE9 _device, int _Index)
{
	switch (_Index)
	{
	case uiRecursionNS::TYPE::BICYCLE:
		sprite[_Index].initialize
		(
			_device,
			texture[_Index],																													//	�e�N�X�`��
			spriteNS::CENTER,																													//	���_
			uiRecursionNS::WIDTH,																												//	����
			uiRecursionNS::HEIGHT,																												//	����
			D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y_POP, 0.0f),	//	���W
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
		);
		break;
	//case uiRecursionNS::TYPE::BLACK_PHONE:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::MOVE_01 + 30.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::CHEWING_GUM:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::MOVE_02 + 60.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::FAN:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::KENDAMA:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::NAWATOBI:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::NINGEN:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::RABBIT_DOLL:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::SOCCER_BALL:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::TELEVISION:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	//case uiRecursionNS::TYPE::XMAS_TREE:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																													//	�e�N�X�`��
	//		spriteNS::CENTER,																													//	���_
	//		uiRecursionNS::WIDTH,																												//	����
	//		uiRecursionNS::HEIGHT,																												//	����
	//		D3DXVECTOR3(playerIndex ? uiRecursionNS::POSITION_X_PLAYER2 : uiRecursionNS::POSITION_X_PLAYER1, uiRecursionNS::POSITION_Y + 20.0f, 0.0f),	//	���W
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																										//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)																									//	�F
	//	);
	//	break;
	default:
		break;
	}

	return;
}
//======================================================================================================================================================
// release
// ���
//======================================================================================================================================================
void UIRecursion::release(void)
{
	// �X�v���C�g�̃N���A
	for (int i = 0; i < uiRecursionNS::TYPE::TYPE_MAX; i++)
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

	return;
}
//======================================================================================================================================================
// update
// �X�V
//======================================================================================================================================================
void UIRecursion::update(void)
{
	if (moveFlag)
	{
		updateMove();
		return;
	}
	else
	{
		if (input->wasKeyPressed(VK_RETURN))
		{
			moveFlag = true;
		}
	}

	return;
}

void UIRecursion::updateMove(void)
{
	D3DXVECTOR3 position = sprite[0].getPosition();
	static float move = 1.5f;

	switch (destinationIndex[0])
	{
	case uiRecursionNS::POSITION::POP:

		if (move >= 0.01f) { move -= 0.01f; }

		position = sprite[0].getPosition();
		sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		sprite[0].setVertex();

		if (position.y <= uiRecursionNS::POSITION_Y_MOVE_01)
		{
			moveFlag = false;
			destinationIndex[0]++;
			move = 1.5f;
		}

		break;
	case uiRecursionNS::POSITION::MOVE_01:

		if (move >= 0.01f) { move -= 0.01f; }

		position = sprite[0].getPosition();
		sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		sprite[0].setVertex();

		if (position.y <= uiRecursionNS::POSITION_Y_MOVE_02)
		{
			moveFlag = false;
			destinationIndex[0]++;
			move = 1.5f;
		}

		break;
	case uiRecursionNS::POSITION::MOVE_02:

		if (move >= 0.01f) { move -= 0.01f; }

		position = sprite[0].getPosition();
		sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		sprite[0].setVertex();

		if (position.y <= uiRecursionNS::POSITION_Y_CLOSE)
		{
			moveFlag = false;
			destinationIndex[0]++;
			move = 1.5f;
		}

		break;
	case uiRecursionNS::POSITION::CLOSE:

		//if (move >= 0.01f) { move -= 0.01f; }

		//position = sprite[0].getPosition();
		//sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		//sprite[0].setVertex();

		//if (position.y <= uiRecursionNS::POSITION_Y_MOVE_01)
		//{
		//	moveFlag = false;
		//	destinationIndex[0]++;
		//	move = 1.0f;
		//}

		break;
	default:
		break;
	}

	return;
}

//======================================================================================================================================================
// render
// �`��
//======================================================================================================================================================
void UIRecursion::render(LPDIRECT3DDEVICE9 _device)
{
	for (int i = 0; i < uiRecursionNS::TYPE::TYPE_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}