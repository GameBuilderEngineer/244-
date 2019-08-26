//============================================================================================================================================
// Document
//============================================================================================================================================
// UICharacterSelect.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/25
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace uiCharacterSelectNS
{
	const int CHARACTER_WIDTH = ((1000 / 2) - (1000 / 10));														//	幅
	const int CHARACTER_HEIGHT = ((2160 / 2) - (2160 / 10));													//	高さ
	const int NAME_WIDTH = (1416 / 2);																			//	幅
	const int NAME_HEIGHT = (356 / 2);																			//	高さ
	const int BACKGROUND_WIDTH = (1920 / 2);																	//	幅
	const int BACKGROUND_HEIGHT = (2160 / 2);																	//	高さ
	const int BAR_WIDTH = (1920 / 2);																			//	幅
	const int BAR_HEIGHT = (900 / 2);																			//	高さ
	const int CURSOR_WIDTH = (1836 / 2);																		//	幅
	const int CURSOR_HEIGHT = (180 / 2);																		//	高さ
	const int TIME_WIDTH = (1180 / 2);																			//	幅
	const int TIME_HEIGHT = (552 / 2);																			//	高さ
	const float POSITION_X_CHARACTER_1 = (WINDOW_WIDTH / 8);													//	座標 x
	const float POSITION_X_CHARACTER_2 = (uiCharacterSelectNS::POSITION_X_CHARACTER_1 + (WINDOW_WIDTH / 2));	//	座標 x
	const float POSITION_Y_CHARACTER = (WINDOW_HEIGHT / 2);														//	座標 y
	const float POSITION_X_NAME_1 = (WINDOW_WIDTH / 3.25f);														//	座標 x
	const float POSITION_X_NAME_2 = (uiCharacterSelectNS::POSITION_X_NAME_1 + (WINDOW_WIDTH / 2));				//	座標 x
	const float POSITION_Y_NAME = (WINDOW_HEIGHT / 1.65f);														//	座標 y
	const float POSITION_X_BACKGROUND_1 = (WINDOW_WIDTH / 4);													//	座標 x
	const float POSITION_X_BACKGROUND_2 = (uiCharacterSelectNS::POSITION_X_BACKGROUND_1 + (WINDOW_WIDTH / 2));	//	座標 x
	const float POSITION_Y_BACKGROUND = (WINDOW_HEIGHT / 2);													//	座標 y
	const float POSITION_X_BAR_1 = (WINDOW_WIDTH / 4);															//	座標 x
	const float POSITION_X_BAR_2 = (uiCharacterSelectNS::POSITION_X_BAR_1 + (WINDOW_WIDTH / 2));				//	座標 x
	const float POSITION_Y_BAR = (WINDOW_HEIGHT / 1.75f);														//	座標 y
	const float POSITION_X_CURSOR_1 = (WINDOW_WIDTH / 4);														//	座標 x
	const float POSITION_X_CURSOR_2 = (uiCharacterSelectNS::POSITION_X_CURSOR_1 + (WINDOW_WIDTH / 2));			//	座標 x
	const float POSITION_Y_CURSOR = (WINDOW_HEIGHT / 2.25f);													//	座標 y
	const float POSITION_X_TIME = (WINDOW_WIDTH / 2);															//	座標 x
	const float POSITION_Y_TIME = (uiCharacterSelectNS::TIME_HEIGHT / 2);										//	座標 y

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
// クラス
//============================================================================================================================================
class UICharacterSelect
{
private:
	static int instanceIndex;												//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture[uiCharacterSelectNS::TYPE::TYPE_MAX];	//	テクスチャ
	Sprite sprite[uiCharacterSelectNS::TYPE::TYPE_MAX];						//	スプライト
	int selectState[uiCharacterSelectNS::PLAYER_TYPE::PLAYER_TYPE_MAX];		//	選択状態
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