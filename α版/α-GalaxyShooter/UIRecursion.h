//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRecursion.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/07/27
//======================================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//======================================================================================================================================================
// NameSpace
// ���O���
//======================================================================================================================================================
namespace uiRecursionNS
{
	const int WIDTH = (560 / 2);														//	���i�ЂƂ܂����Q�j
	const int HEIGHT = (100 / 2);														//	�����i�ЂƂ܂����Q�j
	const int FADE_START_TIME = (200);													//	�t�F�[�h�J�n����
	const float POSITION_X_PLAYER1 = ((WINDOW_WIDTH / 2) - (uiRecursionNS::WIDTH / 2));	//	X���W
	const float POSITION_X_PLAYER2 = (POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f);		//	X���W
	//const float POSITION_Y = (WINDOW_HEIGHT / 4);										//	Y���W
	const float POSITION_Y_POP = (130.0f);										//	Y���W
	const float POSITION_Y_MOVE_01 = (100.0f);										//	Y���W
	const float POSITION_Y_MOVE_02 = (70.0f);										//	Y���W
	const float POSITION_Y_CLOSE = (40.0f);										//	Y���W

	enum TYPE
	{
		BICYCLE,		//	���]��
		BLACK_PHONE,	//	���d�b
		CHEWING_GUM,	//	�`���[�C���O�K��
		FAN,			//	��@
		KENDAMA,		//	�����
		NAWATOBI,		//	�Ȃ�Ƃ�
		NINGEN,			//	�l��
		RABBIT_DOLL,	//	�E�T�M�̂ʂ������
		SOCCER_BALL,	//	�T�b�J�[�{�[��
		TELEVISION,		//	�e���r
		XMAS_TREE,		//	�N���X�}�X�c���[
		TYPE_MAX		//	�ő�l
	};

	enum POSITION
	{
		POP,
		MOVE_01,
		MOVE_02,
		CLOSE,
		POSITION_MAX
	};
}

//======================================================================================================================================================
// Class
// �N���X
//======================================================================================================================================================
class UIRecursion
{
private:

	Input* input;

	static int instanceIndex;											//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture[uiRecursionNS::TYPE::TYPE_MAX];	//	�e�N�X�`��
	Sprite sprite[uiRecursionNS::TYPE::TYPE_MAX];						//	�X�v���C�g
	int playerIndex;													//	�v���C���[�C���f�b�N�X

	int destinationIndex[uiRecursionNS::TYPE::TYPE_MAX];

public:
	UIRecursion(void);
	~UIRecursion(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerNumber, TextureLoader* _textureLoader,
		
		Input* _input
		
		);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _Index);
	void release(void);
	void update(void);

	void updateMove(void);

	void render(LPDIRECT3DDEVICE9 _device);
};