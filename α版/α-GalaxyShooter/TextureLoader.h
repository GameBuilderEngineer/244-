//===================================================================================================================================
//ÅyTextureLoader.hÅz
// [çÏê¨é“]HALìåãûGP12A332 11 êõñÏ é˜
// [çÏê¨ì˙]2019/05/16
// [çXêVì˙]2019/08/07
//===================================================================================================================================
#pragma once
#include "Base.h"

namespace textureLoaderNS
{
	enum TEXTURE_NUMBER
	{
		// Splash
		SPLASH,

		// Tutorial
		TUTORIAL,
		TUTORIAL2,
		TUTORIAL3,
		TUTORIAL4,

		// Title
		TITLE_LOGO,
		TITLE_BAR,
		TITLE_GAME_WHITE,
		TITLE_GAME_BLACK,
		TITLE_TUTORIAL_WHITE,
		TITLE_TUTORIAL_BLACK,
		TITLE_OPERATION_WHITE,
		TITLE_OPERATION_BLACK,
		TITLE_CREDIT_WHITE,
		TITLE_CREDIT_BLACK,
		TITLE_FINISH_WHITE,
		TITLE_FINISH_BLACK,

		// Operation
		OPERATION_GAMEPAD,
		OPERATION_KEYBOARD,

		// Credit
		CREDIT,

		// CharacterSelect
		UI_CHARACTER_SELECT_NAME_ADAM,
		UI_CHARACTER_SELECT_NAME_EVE,
		UI_CHARACTER_SELECT_BACKGROUND_1,
		UI_CHARACTER_SELECT_BACKGROUND_2,
		UI_CHARACTER_SELECT_BAR_1,
		UI_CHARACTER_SELECT_BAR_2,
		UI_CHARACTER_SELECT_CURSOR_1,
		UI_CHARACTER_SELECT_CURSOR_2,
		UI_CHARACTER_SELECT_TIME,
		UI_CHARACTER_SELECT_READY_BACKGROUND,
		UI_CHARACTER_SELECT_READY_BAR,
		UI_CHARACTER_SELECT_READY_CANCEL,
		UI_CHARACTER_SELECT_READY_WAITING,

		// Game
		UI_COUNT_DOWN_FINISH,
		UI_COUNT_DOWN_GO,
		UI_COUNT_DOWN_ONE,
		UI_COUNT_DOWN_TWO,
		UI_COUNT_DOWN_THREE,
		UI_PLAY_TIME_CHINGIN,
		UI_CUT_MEMORY_LINE,
		UI_REVIVAL_BAR,
		UI_REVIVAL_GAUGE,
		UI_REVIVAL_CONCENTRATION,
		UI_REVIVAL_TONE,
		PAUSE,
		RECURSION,
		SHOCKWAVE,
		BACKGROUND_STAR,
		BACKGROUND_DUST,
		CHINGIN_STAR,

		//effect
		EFFECT_DAMAGE,
		EFFECT_FEEL,
		CHINGIN_EFFECT,
		BULLET_EFFECT,
		DOWN_EFFECT,
		UP_EFFECT,
		LINE_EFFECT,

		// Result
		RESULT_WINDOW,
		RESULT_PLAYER_NUMBER_1,
		RESULT_PLAYER_NUMBER_2,
		RESULT_WIN,
		RESULT_LOSE,
		RESULT_DRAW,

		// etc
		CHARACTER_ADAM,
		CHARACTER_EVE,
		TOON_OUT_LINE,
		TOON_SHADE,
		UI_SCREEN_SPLIT_LINE,
		LIGHT_001,
		TARGET,

		MAX_TEXTURE,
	};
}

class TextureLoader : public Base
{
private:
	const char* textureName[textureLoaderNS::MAX_TEXTURE];
	LPDIRECT3DTEXTURE9 texture[textureLoaderNS::MAX_TEXTURE];
public:
	TextureLoader();
	~TextureLoader();

	void load(LPDIRECT3DDEVICE9 device);
	void release();

	LPDIRECT3DTEXTURE9* getTexture(int textureNo) { return &texture[textureNo]; }
};