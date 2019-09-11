//===================================================================================================================================
//�yTextureLoader.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/09/05
//===================================================================================================================================
#include "TextureLoader.h"
using namespace textureLoaderNS;

TextureLoader::TextureLoader()
{
	// Splash
	textureName[SPLASH] = { "Splash.png" };

	// Tutorial
	textureName[TUTORIAL] = { "tutorial1.png" };
	textureName[TUTORIAL2] = { "tutorial2.png" };
	textureName[TUTORIAL3] = { "tutorial3.png" };
	textureName[TUTORIAL4] = { "tutorial4.png" };

	// Title
	textureName[TITLE_LOGO] = { "Title_Logo.png" };
	textureName[TITLE_BAR] = { "Title_Bar.png" };
	textureName[TITLE_GAME_WHITE] = { "Title_Game_White.png" };
	textureName[TITLE_GAME_BLACK] = { "Title_Game_Black.png" };
	textureName[TITLE_TUTORIAL_WHITE] = { "Title_Tutorial_White.png" };
	textureName[TITLE_TUTORIAL_BLACK] = { "Title_Tutorial_Black.png" };
	textureName[TITLE_OPERATION_WHITE] = { "Title_Operation_White.png" };
	textureName[TITLE_OPERATION_BLACK] = { "Title_Operation_Black.png" };
	textureName[TITLE_CREDIT_WHITE] = { "Title_Credit_White.png" };
	textureName[TITLE_CREDIT_BLACK] = { "Title_Credit_Black.png" };
	textureName[TITLE_EXIT_WHITE] = { "Title_Exit_White.png" };
	textureName[TITLE_EXIT_BLACK] = { "Title_Exit_Black.png" };

	// Operation
	textureName[OPERATION_GAMEPAD] = { "Operation_GamePad.png" };
	textureName[OPERATION_KEYBOARD] = { "Operation_KeyBoard.png" };

	// Credit
	textureName[CREDIT] = { "Credit.png" };

	// CharacterSelect
	textureName[UI_CHARACTER_SELECT_NAME_ADAM] = { "CharacterSelect_Name_Adam.png" };
	textureName[UI_CHARACTER_SELECT_NAME_EVE] = { "CharacterSelect_Name_Eve.png" };
	textureName[UI_CHARACTER_SELECT_BACKGROUND_1] = { "CharacterSelect_BackGround_1.png" };
	textureName[UI_CHARACTER_SELECT_BACKGROUND_2] = { "CharacterSelect_BackGround_2.png" };
	textureName[UI_CHARACTER_SELECT_BAR_1] = { "CharacterSelect_Bar_1.png" };
	textureName[UI_CHARACTER_SELECT_BAR_2] = { "CharacterSelect_Bar_2.png" };
	textureName[UI_CHARACTER_SELECT_CURSOR_1] = { "CharacterSelect_Cursor_1.png" };
	textureName[UI_CHARACTER_SELECT_CURSOR_2] = { "CharacterSelect_Cursor_2.png" };
	textureName[UI_CHARACTER_SELECT_TIME] = { "CharacterSelect_Time.png" };
	textureName[UI_CHARACTER_SELECT_READY_BACKGROUND] = { "CharacterSelect_Ready_BackGround.png" };
	textureName[UI_CHARACTER_SELECT_READY_BAR] = { "CharacterSelect_Ready_Bar.png" };
	textureName[UI_CHARACTER_SELECT_READY_CANCEL] = { "CharacterSelect_Ready_Cancel.png" };
	textureName[UI_CHARACTER_SELECT_READY_WAITING] = { "CharacterSelect_Ready_Waiting.png" };

	// Game
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
	textureName[UI_CUT_MEMORY_LINE] = { "Game_Cut_Memory_Line.png" };
	textureName[UI_REVIVAL_BAR] = { "Game_Revival_Bar.png" };
	textureName[UI_REVIVAL_GAUGE] = { "Game_Revival_Gauge.png" };
	textureName[EFFECT_DAMAGE] = { "Game_Damage.png" };
	textureName[EFFECT_FEEL] = { "feelEffect.png" };

	textureName[POSE] = { "Pause.png" };
	textureName[BULLET_EFFECT] = { "bakuha.png" };
	textureName[DOWN_EFFECT] = { "Down.png" };
	textureName[UP_EFFECT] = { "UP.png" };
	textureName[LINE_EFFECT] = { "LineEffect.png" };
	textureName[CHINGIN_EFFECT] = { "chingineffe.png" };

	textureName[UI_REVIVAL_CONCENTRATION] = { "Game_Revival_Concentration.png" };
	textureName[UI_REVIVAL_TONE] = { "Game_Revival_Tone.png" };
	textureName[EFFECT_DAMAGE] = { "Game_Damage_Effect.png" };
	textureName[EFFECT_REVIVAL] = { "Game_Revival_Effect.png" };
	textureName[PAUSE] = { "Pause.png" };
	textureName[RECURSION] = { "Game_Recursion.png" };
	textureName[SHOCKWAVE] = { "Game_Shockwave.png" };
	textureName[BACKGROUND_STAR] = { "Game_BackGround_Star.jpg" };
	textureName[BACKGROUND_DUST] = { "Game_BackGround_Dust.png" };

	// Result
	textureName[RESULT_WINDOW] = { "Result_Window.png" };
	textureName[RESULT_PLAYER_NUMBER_1] = { "Result_Player_No_01.png" };
	textureName[RESULT_PLAYER_NUMBER_2] = { "Result_Player_No_02.png" };
	textureName[RESULT_WIN] = { "Result_Win.png" };
	textureName[RESULT_LOSE] = { "Result_Lose.png" };
	textureName[RESULT_DRAW] = { "Result_Draw.png" };

	// etc
	textureName[CHARACTER_ADAM] = { "Character_Adam.png" };
	textureName[CHARACTER_EVE] = { "Character_Eve.png" };
	textureName[TOON_OUT_LINE] = { "Outline.bmp" };
	textureName[TOON_SHADE] = { "Shade.bmp" };
	textureName[UI_SCREEN_SPLIT_LINE] = { "Screen_Split_Line.png" };
	textureName[LIGHT_001] = { "Light_001.png" };
	textureName[TARGET] = { "stencil.png" };
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