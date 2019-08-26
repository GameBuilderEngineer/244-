//============================================================================================================================================
// Document
//============================================================================================================================================
// UICharacterSelect.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/25
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace uiCharacterSelectNS
{
	const int CHARACTER_WIDTH = ((1000 / 2) - (1000 / 10));														//	��
	const int CHARACTER_HEIGHT = ((2160 / 2) - (2160 / 10));													//	����
	const int NAME_WIDTH = (1416 / 2);																			//	��
	const int NAME_HEIGHT = (356 / 2);																			//	����
	const int BACKGROUND_WIDTH = (1920 / 2);																	//	��
	const int BACKGROUND_HEIGHT = (2160 / 2);																	//	����
	const int BAR_WIDTH = (1920 / 2);																			//	��
	const int BAR_HEIGHT = (900 / 2);																			//	����
	const int CURSOR_WIDTH = (1836 / 2);																		//	��
	const int CURSOR_HEIGHT = (180 / 2);																		//	����
	const int TIME_WIDTH = (1180 / 2);																			//	��
	const int TIME_HEIGHT = (552 / 2);																			//	����
	const float POSITION_X_CHARACTER_1 = (WINDOW_WIDTH / 8);													//	���W x
	const float POSITION_X_CHARACTER_2 = (uiCharacterSelectNS::POSITION_X_CHARACTER_1 + (WINDOW_WIDTH / 2));	//	���W x
	const float POSITION_Y_CHARACTER = (WINDOW_HEIGHT / 2);														//	���W y
	const float POSITION_X_NAME_1 = (WINDOW_WIDTH / 3.25f);														//	���W x
	const float POSITION_X_NAME_2 = (uiCharacterSelectNS::POSITION_X_NAME_1 + (WINDOW_WIDTH / 2));				//	���W x
	const float POSITION_Y_NAME = (WINDOW_HEIGHT / 1.65f);														//	���W y
	const float POSITION_X_BACKGROUND_1 = (WINDOW_WIDTH / 4);													//	���W x
	const float POSITION_X_BACKGROUND_2 = (uiCharacterSelectNS::POSITION_X_BACKGROUND_1 + (WINDOW_WIDTH / 2));	//	���W x
	const float POSITION_Y_BACKGROUND = (WINDOW_HEIGHT / 2);													//	���W y
	const float POSITION_X_BAR_1 = (WINDOW_WIDTH / 4);															//	���W x
	const float POSITION_X_BAR_2 = (uiCharacterSelectNS::POSITION_X_BAR_1 + (WINDOW_WIDTH / 2));				//	���W x
	const float POSITION_Y_BAR = (WINDOW_HEIGHT / 1.75f);														//	���W y
	const float POSITION_X_CURSOR_1 = (WINDOW_WIDTH / 4);														//	���W x
	const float POSITION_X_CURSOR_2 = (uiCharacterSelectNS::POSITION_X_CURSOR_1 + (WINDOW_WIDTH / 2));			//	���W x
	const float POSITION_Y_CURSOR = (WINDOW_HEIGHT / 2.25f);													//	���W y
	const float POSITION_X_TIME = (WINDOW_WIDTH / 2);															//	���W x
	const float POSITION_Y_TIME = (uiCharacterSelectNS::TIME_HEIGHT / 2);										//	���W y

	enum TYPE
	{
		CHARACTER_PLAYER_1_ADAM,
		CHARACTER_PLAYER_1_EVE,
		CHARACTER_PLAYER_2_ADAM,
		CHARACTER_PLAYER_2_EVE,
		NAME_PLAYER_1_ADAM,
		NAME_PLAYER_1_EVE,
		NAME_PLAYER_2_ADAM,
		NAME_PLAYER_2_EVE,
		BACKGROUND_1,
		BACKGROUND_2,
		BAR_1,
		BAR_2,
		CURSOR_1,
		CURSOR_2,
		TIME,
		TYPE_MAX
	};

	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX
	};
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class UICharacterSelect
{
private:
	static int instanceIndex;												//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture[uiCharacterSelectNS::TYPE::TYPE_MAX];	//	�e�N�X�`��
	Sprite sprite[uiCharacterSelectNS::TYPE::TYPE_MAX];						//	�X�v���C�g
	int selectState[uiCharacterSelectNS::PLAYER_TYPE::PLAYER_TYPE_MAX];		//	�I�����
public:
	UICharacterSelect(void);
	~UICharacterSelect(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _index);
	void release(void);
	void update(Input* _input, Sound *_sound);
	void updateInput(Input* _input, Sound *_sound);
	void updateInputPlayer1(Input* _input, Sound *_sound);
	void updateInputPlayer2(Input* _input, Sound *_sound);
	void updateControl(void);
	void updateControlPlayer1(void);
	void updateControlPlayer2(void);
	void render(LPDIRECT3DDEVICE9 _device);
	void renderTime(LPDIRECT3DDEVICE9 _device);
	int getSelectState(int _index);
};