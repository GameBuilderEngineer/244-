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
	enum TEXTURE_NUMBER {
		TOON_OUT_LINE,
		TOON_SHADE,
		UI_SCREEN_SPLIT_LINE,
		UI_RECURSION_BICYCLE,
		UI_RECURSION_BLACK_PHONE,
		UI_RECURSION_CHEWING_GUM,
		UI_RECURSION_FAN,
		UI_RECURSION_KENDAMA,
		UI_RECURSION_NAWATOBI,
		UI_RECURSION_NINGEN,
		UI_RECURSION_RABBIT_DOLL,
		UI_RECURSION_SOCCER_BALL,
		UI_RECURSION_TELEVISION,
		UI_RECURSION_XMAS_TREE,
		UI_PLAY_TIME_CHINGIN,
		UI_CUT_MEMORY_LINE,
		UI_REVIVAL,
		UI_REVIVAL_GAUGE,
		RECURSION,
		UI_CHARA_SELECT_BAR,
		UI_CHARA_SELECT_BAR2,
		UI_CHARA_SELECT_NO,
		UI_CHARA_SELECT_NO2,
		UI_CHARA_SELECT_CURSOR,
		UI_CHARA_SELECT_CURSOR2,
		UI_CHARA_SELECT_LOGO,
		CHARA_SELECT_BG,
		EVE_NAME_ENG,
		ADAM_NAME_ENG,
		EVE_NAME_JP,
		ADAM_NAME_JP,
		UI_CHARA_SELECT_TIMER,
		SPRITE,
		RING,
		UV_GRID,
		SPLASH,
		TITLE_POS,
		TITLE_GAME,
		TITLE_TUTORIAL,
		TITLE_OPERATION,
		TITLE_CREDIT,
		TITLE_GAMEEND,
		TITLE_GAME_B,
		TITLE_TUTORIAL_B,
		TITLE_OPERATION_B,
		TITLE_CREDIT_B,
		TITLE_GAMEEND_B,
		TITLE2D,
		TUTORIAL,
		RESULT,
		WIN,
		DRAW,
		LOSE,
		KEY_OPE,
		PAD_OPE,
		CREDIT,
		WHITE_TEXTURE,
		LIGHT001,
		HP_EFFECT,
		TARGET,
		POSE,
		SELECT,
		SELECT_PLAYER,
		SELECT_PLAYER2,
		SELECT_PLAYER_NUMBER,
		SELECT_PLAYER2_NUMBER,
		CHARA_RESULT_BG,
		BULLET_EFFECT,
		DOWN_EFFECT,
		UP_EFFECT,
		BULLET_SMOKE_EFFECT,
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