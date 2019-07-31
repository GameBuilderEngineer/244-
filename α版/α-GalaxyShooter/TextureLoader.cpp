#include "TextureLoader.h"
using namespace textureLoaderNS;


TextureLoader::TextureLoader()
{
	textureName[TOON_OUT_LINE] = {"outline.bmp"};
	textureName[TOON_SHADE] = {"Shade.bmp"};
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
	textureName[UI_CHARA_SELECT_BG] = { "Character_Select_Back.png" };
	textureName[UI_CHARA_SELECT_TIMER] = { "Character_Select_Time.png" };
	textureName[SPRITE] = {"Sprite.jpg"};
	textureName[RING] = {"ring.png"};
	textureName[UV_GRID] = {"UV�O���b�h.png"};
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
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(device,textureName[i],&texture[i]);
	}
}

void TextureLoader::release() 
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (texture[i] != NULL)
		{//�e�N�X�`���̉��
			texture[i]->Release();
			texture[i] = NULL;
		}
	}
}