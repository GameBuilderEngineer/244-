//============================================================================================================================================
// Document
//============================================================================================================================================
// UIResult.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/24
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
#include "UICharacterSelect.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace uiResultNS
{
	const int PLAYER_WIDTH = ((1000 / 2) - (1000 / 10));															//	��
	const int PLAYER_HEIGHT = ((2160 / 2) - (2160 / 10));															//	����
	const int RESULT_WINDOW_WIDTH = (3840 / 2);																		//	��
	const int RESULT_WINDOW_HEIGHT = (1340 / 2);																	//	����
	const int PLAYER_NUMBER_WIDTH = (936 / 2);																		//	��
	const int PLAYER_NUMBER_HEIGHT = (254 / 2);																		//	����
	const int RESULT_WIDTH = (630 / 2);																				//	��
	const int RESULT_HEIGHT = (240 / 2);																			//	����
	const float POSITION_X_PLAYER_CHARACTER_1 = (WINDOW_WIDTH / 4);													//	���W x
	const float POSITION_X_PLAYER_CHARACTER_2 = (uiResultNS::POSITION_X_PLAYER_CHARACTER_1 + (WINDOW_WIDTH / 2));	//	���W x
	const float POSITION_Y_PLAYER_CHARACTER = (WINDOW_HEIGHT / 2);													//	���W y
	const float POSITION_X_RESULT_WINDOW = ((WINDOW_WIDTH / 2) - 8.5f);												//	���W x
	const float POSITION_Y_RESULT_WINDOW = ((WINDOW_HEIGHT / 2) - 10.0f);											//	���W y
	const float POSITION_X_PLAYER_NUMBER_1 = (WINDOW_WIDTH / 4);													//	���W x
	const float POSITION_X_PLAYER_NUMBER_2 = (uiResultNS::POSITION_X_PLAYER_NUMBER_1 + (WINDOW_WIDTH / 2));			//	���W x
	const float POSITION_Y_PLAYER_NUMBER = (WINDOW_HEIGHT / 2.5f);													//	���W y
	const float POSITION_X_1 = (WINDOW_WIDTH / 4);																	//	���W x
	const float POSITION_X_2 = (uiResultNS::POSITION_X_1 + (WINDOW_WIDTH / 2));										//	���W x
	const float POSITION_Y = (WINDOW_HEIGHT / 2);																	//	���W y

	enum TYPE
	{
		CHARACTER_PLAYER_1_ADAM,
		CHARACTER_PLAYER_1_EVE,
		CHARACTER_PLAYER_2_ADAM,
		CHARACTER_PLAYER_2_EVE,
		WINDOW,
		PLAYER_NUMBER_1,
		PLAYER_NUMBER_2,
		WIN,
		LOSE,
		DRAW,
		TYPE_MAX
	};
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class UIResult
{
private:
	static int instanceIndex;										//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture[uiResultNS::TYPE::TYPE_MAX];	//	�e�N�X�`��
	Sprite sprite[uiResultNS::TYPE::TYPE_MAX];						//	�X�v���C�g
public:
	UIResult(void);
	~UIResult(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _index);
	void release(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 _device);
};