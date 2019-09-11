//============================================================================================================================================
// Document
//============================================================================================================================================
// UITitle.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/29
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace uiTitleNS
{
	const int WIDTH_TITLE_LOGO = (960);							//	幅
	const int HEIGHT_TITLE_LOGO = (125);						//	高さ
	const int WIDTH_TITLE_BAR = (600);							//	幅
	const int HEIGHT_TITLE_BAR = (75);							//	高さ
	const int WIDTH_GAME_START = (600);							//	幅
	const int HEIGHT_GAME_START = (75);							//	高さ
	const int WIDTH_TUTORIAL = (600);							//	幅
	const int HEIGHT_TUTORIAL = (75);							//	高さ
	const int WIDTH_OPERATION = (600);							//	幅
	const int HEIGHT_OPERATION = (75);							//	高さ
	const int WIDTH_CREDIT = (600);								//	幅
	const int HEIGHT_CREDIT = (75);								//	高さ
	const int WIDTH_GAME_EXIT = (600);							//	幅
	const int HEIGHT_GAME_EXIT = (75);							//	高さ
	const float POSITION_TITLE_LOGO_X = (WINDOW_WIDTH / 3.5f);	//	座標 x
	const float POSITION_TITLE_LOGO_Y = (WINDOW_HEIGHT / 4);	//	座標 y
	const float POSITION_TITLE_BAR_X = (WIDTH_TITLE_BAR / 2);	//	座標 x
	const float POSITION_TITLE_BAR_Y = (475.0f);				//	座標 y
	const float POSITION_GAME_START_X = (WIDTH_TITLE_BAR / 2);	//	座標 x
	const float POSITION_GAME_START_Y = (475.0f);				//	座標 y
	const float POSITION_TUTORIAL_X = (WIDTH_TITLE_BAR / 2);	//	座標 x
	const float POSITION_TUTORIAL_Y = (575.0f);					//	座標 y
	const float POSITION_OPERATION_X = (WIDTH_TITLE_BAR / 2);	//	座標 x
	const float POSITION_OPERATION_Y = (675.0f);				//	座標 y
	const float POSITION_CREDIT_X = (WIDTH_TITLE_BAR / 2);		//	座標 x
	const float POSITION_CREDIT_Y = (775.0f);					//	座標 y
	const float POSITION_GAME_EXIT_X = (WIDTH_TITLE_BAR / 2);	//	座標 x
	const float POSITION_GAME_EXIT_Y = (875.0f);				//	座標 y

	enum TYPE
	{
		TITLE_LOGO,
		TITLE_BAR,
		GAME_START,
		GAME_START_SELECT,
		TUTORIAL,
		TUTORIAL_SELECT,
		OPERATION,
		OPERATION_SELECT,
		CREDIT,
		CREDIT_SELECT,
		GAME_EXIT,
		GAME_EXIT_SELECT,
		TYPE_MAX
	};

	enum TITLE_MENU_TYPE
	{
		MENU_GAME_START,
		MENU_TUTORIAL,
		MENU_OPERATION,
		MENU_CREDIT,
		MENU_GAME_EXIT,
		TITLE_MENU_TYPE_MAX
	};
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class UITitle
{
private:
	static int instanceIndex;										//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture[uiTitleNS::TYPE::TYPE_MAX];	//	テクスチャ
	Sprite sprite[uiTitleNS::TYPE::TYPE_MAX];						//	スプライト
	int selectState;												//	選択状態
public:
	UITitle(void);
	~UITitle(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, int _selectStateMemory);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _index);
	void release(void);
	void update(Input* _input, Sound* _sound);
	void updateBar(void);
	void render(LPDIRECT3DDEVICE9 _device);
	int getSelectState(void) { return selectState; }
};