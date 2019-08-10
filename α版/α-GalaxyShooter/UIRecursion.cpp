//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRecursion.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/07/27
//======================================================================================================================================================
#include "UIRecursion.h"
#include "Sprite.h"
//======================================================================================================================================================
// Using Declaration
// using�錾
//======================================================================================================================================================
using namespace uiRecursionNS;
//======================================================================================================================================================
// Global Variable
// �O���[�o���ϐ�
//======================================================================================================================================================
int UIRecursion::instanceIndex = 0;							//	�C���X�^���X�C���f�b�N�X
LPDIRECT3DTEXTURE9 UIRecursion::texture[TYPE::TYPE_MAX];	//	�e�N�X�`��
//======================================================================================================================================================
// Constructor
// �R���X�g���N�^
//======================================================================================================================================================
UIRecursion::UIRecursion(void)
{
	// �C���X�^���X�C���f�b�N�X�����Z
	instanceIndex++;

	// ������
	moveFlag = false;
	moveValue = 1.5f;

	// �e�N�X�`���̃N���A
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	for (int i = 0; i < POSITION::POSITION_MAX; i++)
	{
		positionIndex[i] = i;
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

	// �f�B���N�g���ݒ�
	setVisualDirectory();

	// �e�N�X�`���ǂݍ���
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// �X�v���C�g������
	for (int i = 0; i < POSITION::POSITION_MAX; i++)
	{
		initializeSprite(_device, _playerIndex, i);
	}

	return S_OK;
}
//======================================================================================================================================================
// initializeSprite
// ������ - �X�v���C�g
//======================================================================================================================================================
void UIRecursion::initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index)
{
	switch (_index)
	{
	case POSITION::POP:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH,															//	����
			HEIGHT,															//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y_POP,												//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	case POSITION::MOVE_1:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH,															//	����
			HEIGHT,															//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y_MOVE_1,											//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	case POSITION::MOVE_2:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH,															//	����
			HEIGHT,															//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y_MOVE_2,											//	���W y
				0.0f														//	���W z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	��]
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	�F
		);
		break;
	case POSITION::CLOSE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	�e�N�X�`��
			spriteNS::CENTER,												//	���_
			WIDTH,															//	����
			HEIGHT,															//	����
			D3DXVECTOR3														//	���W
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	���W x
				POSITION_Y_CLOSE,											//	���W y
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
void UIRecursion::release(void)
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

	if (input->wasKeyPressed(VK_RETURN))
	{
		moveFlag = !moveFlag;
	}

	return;
}
//======================================================================================================================================================
// updateMove
// �X�V - �ړ�
//======================================================================================================================================================
void UIRecursion::updateMove(void)
{
	//D3DXVECTOR3 spritePosition;

	//if (moveValue > 0.01f) { moveValue -= 0.01f; }

	//for (int i = 0; i < POSITION::POSITION_MAX; i++)
	//{
	//	spritePosition = sprite[i].getPosition();

	//	switch (positionIndex[i])
	//	{
	//	case POSITION::POP:
	//		sprite[i].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
	//		sprite[i].setVertex();

	//		if (spritePosition.y <= POSITION_Y_MOVE_1)
	//		{
	//			moveFlag = !moveFlag;
	//			positionIndex[i]++;
	//			moveValue = INITIAL_MOVE_VALUE;
	//		}
	//		break;
	//	case POSITION::MOVE_1:
	//		sprite[i].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
	//		sprite[i].setVertex();

	//		if (spritePosition.y <= POSITION_Y_MOVE_2)
	//		{
	//			moveFlag = !moveFlag;
	//			positionIndex[i]++;
	//			moveValue = INITIAL_MOVE_VALUE;
	//		}
	//		break;
	//	case POSITION::MOVE_2:
	//		sprite[i].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
	//		sprite[i].setVertex();

	//		if (spritePosition.y <= POSITION_Y_CLOSE)
	//		{
	//			moveFlag = !moveFlag;
	//			positionIndex[i]++;
	//			moveValue = INITIAL_MOVE_VALUE;
	//		}
	//		break;
	//	case POSITION::CLOSE:
	//		break;
	//	default:
	//		break;
	//	}
	//}

	////switch (positionIndex[TYPE::BICYCLE])
	////{
	////case POSITION::POP:
	////	if (moveValue > 0.01f) { moveValue -= 0.01f; }

	////	sprite[TYPE::BICYCLE].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
	////	sprite[TYPE::BICYCLE].setVertex();

	////	if (spritePosition.y <= POSITION_Y_MOVE_1)
	////	{
	////		moveFlag = !moveFlag;
	////		positionIndex[TYPE::BICYCLE]++;
	////		moveValue = INITIAL_MOVE_VALUE;
	////	}
	////	break;
	////case POSITION::MOVE_1:
	////	if (moveValue > 0.01f) { moveValue -= 0.01f; }

	////	sprite[TYPE::BICYCLE].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
	////	sprite[TYPE::BICYCLE].setVertex();

	////	if (spritePosition.y <= POSITION_Y_MOVE_2)
	////	{
	////		moveFlag = !moveFlag;
	////		positionIndex[TYPE::BICYCLE]++;
	////		moveValue = INITIAL_MOVE_VALUE;
	////	}
	////	break;
	////case POSITION::MOVE_2:
	////	if (moveValue > 0.01f) { moveValue -= 0.01f; }

	////	sprite[TYPE::BICYCLE].setPosition2(D3DXVECTOR3(spritePosition.x, spritePosition.y - moveValue, spritePosition.z));
	////	sprite[TYPE::BICYCLE].setVertex();

	////	if (spritePosition.y <= POSITION_Y_CLOSE)
	////	{
	////		moveFlag = !moveFlag;
	////		positionIndex[TYPE::BICYCLE]++;
	////		moveValue = INITIAL_MOVE_VALUE;
	////	}
	////	break;
	////case POSITION::CLOSE:
	////	break;
	////default:
	////	break;
	////}

	return;
}
//======================================================================================================================================================
// render
// �`��
//======================================================================================================================================================
void UIRecursion::render(LPDIRECT3DDEVICE9 _device)
{
	for (int i = 0; i < POSITION::POSITION_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}