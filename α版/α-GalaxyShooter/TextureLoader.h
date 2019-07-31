#pragma once
#include "Base.h"

namespace textureLoaderNS
{
	enum TEXTURE_NUMBER {
		TOON_OUT_LINE,
		TOON_SHADE,
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
		UI_COLONY_HP,
		UI_MISSILE,
		UI_WEAPON,
		UI_GAUGE_BAR,
		UI_GAUGE_BASE,
		UI_GAUGE_COVER,
		SPRITE,
		RING,
		UV_GRID,
		SPLASH,
		TITLE_POS,
		TITLE_TRANS,
		TUTORIAL,
		SELECT,
		RESULT,
		KEY_OPE,
		PAD_OPE,
		CREDIT,
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