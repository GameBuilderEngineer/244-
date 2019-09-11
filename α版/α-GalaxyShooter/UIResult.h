//============================================================================================================================================
// Document
//============================================================================================================================================
// UIResult.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/24
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
#include "UICharacterSelect.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace uiResultNS
{
	const int PLAYER_WIDTH = ((1000 / 2) - (1000 / 10));															//	幅
	const int PLAYER_HEIGHT = ((2160 / 2) - (2160 / 10));															//	高さ
	const int RESULT_WINDOW_WIDTH = (1920);																			//	幅
	const int RESULT_WINDOW_HEIGHT = (670);																			//	高さ
	const int PLAYER_NUMBER_WIDTH = (468);																			//	幅
	const int PLAYER_NUMBER_HEIGHT = (127);																			//	高さ
	const int RESULT_WIDTH = (315);																					//	幅
	const int RESULT_HEIGHT = (120);																				//	高さ
	const float POSITION_X_PLAYER_CHARACTER_1 = (WINDOW_WIDTH / 4);													//	座標 x
	const float POSITION_X_PLAYER_CHARACTER_2 = (uiResultNS::POSITION_X_PLAYER_CHARACTER_1 + (WINDOW_WIDTH / 2));	//	座標 x
	const float POSITION_Y_PLAYER_CHARACTER = (WINDOW_HEIGHT / 2);													//	座標 y
	const float POSITION_X_RESULT_WINDOW = ((WINDOW_WIDTH / 2) - 8.5f);												//	座標 x
	const float POSITION_Y_RESULT_WINDOW = ((WINDOW_HEIGHT / 2) - 10.0f);											//	座標 y
	const float POSITION_X_PLAYER_NUMBER_1 = (WINDOW_WIDTH / 4);													//	座標 x
	const float POSITION_X_PLAYER_NUMBER_2 = (uiResultNS::POSITION_X_PLAYER_NUMBER_1 + (WINDOW_WIDTH / 2));			//	座標 x
	const float POSITION_Y_PLAYER_NUMBER = (WINDOW_HEIGHT / 2.5f);													//	座標 y
	const float POSITION_X_1 = (WINDOW_WIDTH / 4);																	//	座標 x
	const float POSITION_X_2 = (uiResultNS::POSITION_X_1 + (WINDOW_WIDTH / 2));										//	座標 x
	const float POSITION_Y = (WINDOW_HEIGHT / 2);																	//	座標 y

	enum TYPE
	{
		CHARACTER_PLAYER_1_ADAM,
		CHARACTER_PLAYER_1_EVE,
		CHARACTER_PLAYER_2_ADAM,
		CHARACTER_PLAYER_2_EVE,
		WIN_1,
		WIN_2,
		LOSE_1,
		LOSE_2,
		DRAW_1,
		DRAW_2,
		WINDOW,
		PLAYER_NUMBER_1,
		PLAYER_NUMBER_2,
		TYPE_MAX
	};
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class UIResult
{
private:
	static int instanceIndex;										//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture[uiResultNS::TYPE::TYPE_MAX];	//	テクスチャ
	Sprite sprite[uiResultNS::TYPE::TYPE_MAX];						//	スプライト
	TextManager* textManager;										//	テキストマネージャ
	playerTable* playerTable;										//	プレイヤー情報
	int result;														//	リザルト
public:
	UIResult(void);
	~UIResult(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, TextManager* _textManager, GameMaster* _gameMaster);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _index);
	void release(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 _device);
	void renderChingin(void);
};