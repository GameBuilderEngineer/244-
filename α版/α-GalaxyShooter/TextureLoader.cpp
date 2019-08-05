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
	textureName[UI_PLAY_TIME_CHINGIN] = { "Game_PlayTime_Chingin_BackGround.png" };
	textureName[RECURSION] = { "starRecursion.png" };
	textureName[UI_COLONY_HP] = {"ColonyHitPointUI.jpg"};
	textureName[UI_MISSILE] = {"MissileUI.jpg"};
	textureName[UI_WEAPON] = {"WeaponUI.jpg"};
	textureName[UI_GAUGE_BAR] = {"GaugeBar.png"};
	textureName[UI_GAUGE_BASE] = {"GaugeBase.png"};
	textureName[UI_GAUGE_COVER] = {"GaugeCover.png"};
	textureName[UI_CHARA_SELECT_BAR] = { "Character_Select_Bar_01.png" };
	textureName[UI_CHARA_SELECT_BAR2] = { "Character_Select_Bar_02.png" };
	textureName[UI_CHARA_SELECT_NO] = { "Character_Select_Bar_Player_No_01.png" };
	textureName[UI_CHARA_SELECT_NO2] = { "Character_Select_Bar_Player_No_02.png" };
	textureName[UI_CHARA_SELECT_CURSOR] = { "Character_Select_Cursor_01.png" };
	textureName[UI_CHARA_SELECT_CURSOR2] = { "Character_Select_Cursor_02.png" };
	textureName[UI_CHARA_SELECT_LOGO] = { "Character_Select_PLAYER.png" };
	textureName[CHARA_SELECT_BG] = { "Character_Select_Back.png" };
	textureName[EVE_NAME_ENG] = { "Character_Select_Name_EVE_ENG.png" };
	textureName[ADAM_NAME_ENG] = { "Character_Select_Name_ADAM_ENG.png" };
	textureName[EVE_NAME_JP] = { "Character_Select_Name_EVE_JP.png" };
	textureName[ADAM_NAME_JP] = { "Character_Select_Name_ADAM_JP.png" };
	textureName[UI_CHARA_SELECT_TIMER] = { "Character_Select_Time.png" };
	textureName[SPRITE] = {"Sprite.jpg"};
	textureName[RING] = {"ring.png"};
	textureName[UV_GRID] = {"UVグリッド.png"};
	textureName[SPLASH] = { "Team_Logo_Texture.png" };
	textureName[TITLE_POS] = { "Title_Bar.png" };
	textureName[TITLE_GAME] = { "Title_Game_White.png" };
	textureName[TITLE_TUTORIAL] = { "Title_Tutorial_White.png" };
	textureName[TITLE_OPERATION] = { "Title_Operation_White.png" };
	textureName[TITLE_CREDIT] = { "Title_Credit_White.png" };
	textureName[TITLE_GAMEEND] = { "Title_GameExit_White.png" };
	textureName[TITLE_GAME_B] = { "Title_Game_Black.png" };
	textureName[TITLE_TUTORIAL_B] = { "Title_Tutorial_Black.png" };
	textureName[TITLE_OPERATION_B] = { "Title_Operation_Black.png" };
	textureName[TITLE_CREDIT_B] = { "Title_Credit_Black.png" };
	textureName[TITLE_GAMEEND_B] = { "Title_GameExit_Black.png" };
	textureName[TUTORIAL] = { "tutorial.png" };
	textureName[SELECT] = { "Title_BackGround.png" };
	textureName[SELECT_PLAYER] = { "Chara1.png" };
	textureName[SELECT_PLAYER2] = { "Chara2.png" };
	textureName[RESULT] = { "result.png" };
	textureName[KEY_OPE] = { "Operation_KeyBoard.png" };
	textureName[PAD_OPE] = { "Operation_GamePad.png" };
	textureName[CREDIT] = { "credit.png" };
	textureName[WHITE_TEXTURE] = { "backGround1080p.png" };
	textureName[LIGHT001] = { "light001.png" };
	textureName[HP_EFFECT] = { "effect2.png" };
	textureName[TARGET] = { "kurezitto.png" };
	textureName[POSE] = { "Pause.png" };
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