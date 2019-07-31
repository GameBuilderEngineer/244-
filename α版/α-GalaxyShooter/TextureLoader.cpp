#include "TextureLoader.h"
using namespace textureLoaderNS;

TextureLoader::TextureLoader()
{
	textureName[TOON_OUT_LINE] = {"outline.bmp"};
	textureName[TOON_SHADE] = {"Shade.bmp"};
	textureName[UI_RECURSION_BICYCLE] = { "Game_Recursion_Bicycle.png" };
	textureName[UI_RECURSION_BLACK_PHONE] = { "Game_Recursion_BlackPhone.png" };
	textureName[UI_RECURSION_CHEWING_GUM] = { "Game_Recursion_ChewingGum.png" };
	textureName[UI_RECURSION_FAN] = { "Game_Recursion_Fan.png" };
	textureName[UI_RECURSION_KENDAMA] = { "Game_Recursion_Kendama.png" };
	textureName[UI_RECURSION_NAWATOBI] = { "Game_Recursion_Nawatobi.png" };
	textureName[UI_RECURSION_NINGEN] = { "Game_Recursion_Ningen.png" };
	textureName[UI_RECURSION_RABBIT_DOLL] = { "Game_Recursion_RabbitDoll.png" };
	textureName[UI_RECURSION_SOCCER_BALL] = { "Game_Recursion_SoccerBall.png" };
	textureName[UI_RECURSION_TELEVISION] = { "Game_Recursion_Television.png" };
	textureName[UI_RECURSION_XMAS_TREE] = { "Game_Recursion_XmasTree.png" };
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
	textureName[SELECT] = { "serect.png" };
	textureName[RESULT] = { "result.png" };
	textureName[KEY_OPE] = { "sousasetumei.png" };
	textureName[PAD_OPE] = { "MissileUI.jpg" };
	textureName[CREDIT] = { "kurezitto.png" };
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