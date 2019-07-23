#include "TextureLoader.h"
using namespace textureLoaderNS;


TextureLoader::TextureLoader()
{
	textureName[TOON_OUT_LINE] = {"outline.bmp"};
	textureName[TOON_SHADE] = {"Shade.bmp"};
	textureName[UI_COLONY_HP] = {"ColonyHitPointUI.jpg"};
	textureName[UI_MISSILE] = {"MissileUI.jpg"};
	textureName[UI_WEAPON] = {"WeaponUI.jpg"};
	textureName[UI_GAUGE_BAR] = {"GaugeBar.png"};
	textureName[UI_GAUGE_BASE] = {"GaugeBase.png"};
	textureName[UI_GAUGE_COVER] = {"GaugeCover.png"};
	textureName[SPRITE] = {"Sprite.jpg"};
	textureName[RING] = {"ring.png"};
	textureName[UV_GRID] = {"UVグリッド.png"};
	textureName[SPLASH] = { "Team_Logo_Texture.png" };
	textureName[TITLE_POS] = { "Title_Bar.png" };
	textureName[TITLE_TRANS] = { "Title.png" };
	textureName[TUTORIAL] = { "tutorial.png" };
	textureName[RESULT] = { "result.png" };
	textureName[KEY_OPE] = { "sousasetumei.png" };
	textureName[PAD_OPE] = { "MissileUI.jpg" };
	textureName[CREDIT] = { "kurezitto.png" };
	textureName[HP_EFFECT] = { "effect2.png" };
	textureName[TARGET] = { "kurezitto.png" };
	textureName[POSE] = { "effect2.png" };
}


TextureLoader::~TextureLoader()
{
	release();
}

void TextureLoader::load(LPDIRECT3DDEVICE9 device)
{
	setVisualDirectory();
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(device,textureName[i],&texture[i]);
	}
}

void TextureLoader::release() 
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (texture[i] != NULL)
		{//テクスチャの解放
			texture[i]->Release();
			texture[i] = NULL;
		}
	}
}