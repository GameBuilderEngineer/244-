//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRecursion.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/07/27
//======================================================================================================================================================
#include "UIRecursion.h"
//======================================================================================================================================================
// Using Declaration
// using�錾
//======================================================================================================================================================
using namespace uiRecursionNS;
//======================================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//======================================================================================================================================================
int UIRecursion::instanceIndex = (-1);						//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UIRecursion::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��

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
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
		destinationIndex[i] = POSITION::POP;
	}

	return;
}
//======================================================================================================================================================
// Destructor
// �f�X�g���N�^
//======================================================================================================================================================
UIRecursion::~UIRecursion(void)
{
	// ���
	release();

	return;
}
//======================================================================================================================================================
// initialize
// ������
//======================================================================================================================================================
HRESULT UIRecursion::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, Input* _input)
{

	input = _input;

	// �e�N�X�`�����[�_�[�̃��J�[�W����UI�C���f�b�N�X�̃X�^�[�g�ʒu�i�e�N�X�`�����[�_�[���I�u�W�F�N�g���Ƃɒ萔��������΂��������֗��ɂȂ邩���H�j
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_RECURSION_BICYCLE;

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

	return S_OK;
}
//======================================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//======================================================================================================================================================
void UIRecursion::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::BICYCLE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],																			//	�e�N�X�`��
			spriteNS::CENTER,																			//	���_
			uiRecursionNS::WIDTH,																		//	����
			uiRecursionNS::HEIGHT,																		//	����
			D3DXVECTOR3																					//	���W
			(
				playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
				uiRecursionNS::POSITION_Y_POP,															//	���W y
				0.0f																					//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
		);
		break;
	//case TYPE::BLACK_PHONE:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::CHEWING_GUM:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::FAN:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::KENDAMA:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::NAWATOBI:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::NINGEN:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::RABBIT_DOLL:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::SOCCER_BALL:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::TELEVISION:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
	//	);
	//	break;
	//case TYPE::XMAS_TREE:
	//	sprite[_Index].initialize
	//	(
	//		_device,
	//		texture[_Index],																			//	�e�N�X�`��
	//		spriteNS::CENTER,																			//	���_
	//		uiRecursionNS::WIDTH,																		//	����
	//		uiRecursionNS::HEIGHT,																		//	����
	//		D3DXVECTOR3																					//	���W
	//		(
	//			playerIndex ? uiRecursionNS::POSITION_X_PLAYER_2 : uiRecursionNS::POSITION_X_PLAYER_1,	//	���W x
	//			uiRecursionNS::POSITION_Y_POP,															//	���W y
	//			0.0f																					//	���W z
	//		),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f),																//	��]
	//		D3DCOLOR_RGBA(255, 255, 255, 255)															//	�F
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
	case POSITION::POP:

		if (move >= 0.01f) { move -= 0.01f; }

		position = sprite[0].getPosition();
		sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		sprite[0].setVertex();

		if (position.y <= POSITION_Y_MOVE_1)
		{
			moveFlag = false;
			destinationIndex[0]++;
			move = 1.5f;
		}

		break;
	case POSITION::MOVE_01:

		if (move >= 0.01f) { move -= 0.01f; }

		position = sprite[0].getPosition();
		sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		sprite[0].setVertex();

		if (position.y <= POSITION_Y_MOVE_2)
		{
			moveFlag = false;
			destinationIndex[0]++;
			move = 1.5f;
		}

		break;
	case POSITION::MOVE_02:

		if (move >= 0.01f) { move -= 0.01f; }

		position = sprite[0].getPosition();
		sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		sprite[0].setVertex();

		if (position.y <= POSITION_Y_CLOSE)
		{
			moveFlag = false;
			destinationIndex[0]++;
			move = 1.5f;
		}

		break;
	case POSITION::CLOSE:

		//if (move >= 0.01f) { move -= 0.01f; }

		//position = sprite[0].getPosition();
		//sprite[0].setPosition2(D3DXVECTOR3(position.x, position.y - move, position.z));
		//sprite[0].setVertex();

		//if (position.y <= POSITION_Y_MOVE_01)
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
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}