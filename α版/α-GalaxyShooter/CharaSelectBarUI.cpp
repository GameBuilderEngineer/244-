//=============================================================================
// キャラセレクトバーUI処理 [CharaSelectBarUI.cpp]
//
//=============================================================================
#include "CharaSelectBarUI.h"
using namespace charaSelectBarUINS;

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
#ifdef _DEBUG
const static int		BAR_WIDTH = WINDOW_WIDTH / 2;					// 横サイズ
const static int		BAR_HEIGHT = 250;								// 縦サイズ
const static int		NO_WIDTH = 180;									// 横サイズ
const static int		NO_HEIGHT = 82;									// 縦サイズ
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;				// 横サイズ
const static int		CURSOR_HEIGHT = 40;								// 縦サイズ
const static int		PLAYER_LOGO_WIDTH = 80;							// 横サイズ
const static int		PLAYER_LOGO_HEIGHT = 40;						// 縦サイズ
const static int		PLAYER_NAME_ENG_WIDTH = 250;					// プレイヤーネーム英語横サイズ
const static int		PLAYER_NAME_ENG_HEIGHT = 82;					// プレイヤーネーム英語縦サイズ
const static int		PLAYER_NAME_JP_WIDTH = 250;						// プレイヤーネーム日本語横サイズ
const static int		PLAYER_NAME_JP_HEIGHT = 20;						// プレイヤーネーム日本語縦サイズ
const static float		BAR_LIGHT_POSITION_X = 0.0f;					// X座標
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;
const static float		BAR_LIGHT_POSITION_Y = 220.0f;					// Y座標
const static float		NO_POSITION_X = 0.0f;							// X座標
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;
const static float		NO_POSITION_Y = 304.0f;							// Y座標
const static float		CURSOR_POSITION_X = 0.0f;						// X座標
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;
const static float		CURSOR_POSITION_Y = 250.0f;						// Y座標
const static float		PLAYER_LOGO_POSITION_X = 0.0f;					// X座標
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;
const static float		PLAYER_LOGO_POSITION_Y = 390.0f;				// Y座標
const static float		POSITION_X_NAME_EVE_ENG = 200.0f;				// X座標
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_ENG = 200.0f;				// X座標
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_ENG = 304.0f;					// Y座標
const static float		POSITION_X_NAME_EVE_JP = 200.0f;				// X座標
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_JP = 200.0f;				// X座標
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_JP = 390.0f;					// Y座標

#else

const static int		BAR_WIDTH = WINDOW_WIDTH / 2;					// 横サイズ
const static int		BAR_HEIGHT = 500;								// 縦サイズ
const static int		NO_WIDTH = 360;									// 横サイズ
const static int		NO_HEIGHT = 164;								// 縦サイズ
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;				// 横サイズ
const static int		CURSOR_HEIGHT = 80;								// 縦サイズ
const static int		PLAYER_LOGO_WIDTH = 160;						// 横サイズ
const static int		PLAYER_LOGO_HEIGHT = 80;						// 縦サイズ
const static int		PLAYER_NAME_ENG_WIDTH = 500;					// プレイヤーネーム英語横サイズ
const static int		PLAYER_NAME_ENG_HEIGHT = 164;					// プレイヤーネーム英語縦サイズ
const static int		PLAYER_NAME_JP_WIDTH = 500;						// プレイヤーネーム日本語横サイズ
const static int		PLAYER_NAME_JP_HEIGHT = 40;						// プレイヤーネーム日本語縦サイズ
const static float		BAR_LIGHT_POSITION_X = 0.0f;					// X座標
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;
const static float		BAR_LIGHT_POSITION_Y = 440.0f;					// Y座標
const static float		NO_POSITION_X = 0.0f;							// X座標
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;
const static float		NO_POSITION_Y = 608.0f;							// Y座標
const static float		CURSOR_POSITION_X = 0.0f;						// X座標
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;
const static float		CURSOR_POSITION_Y = 500.0f;						// Y座標
const static float		PLAYER_LOGO_POSITION_X = 0.0f;					// X座標
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;
const static float		PLAYER_LOGO_POSITION_Y = 780.0f;				// Y座標
const static float		POSITION_X_NAME_EVE_ENG = 400.0f;				// X座標
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_ENG = 400.0f;				// X座標
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_ENG = 608.0f;					// Y座標
const static float		POSITION_X_NAME_EVE_JP = 400.0f;				// X座標
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;
const static float		POSITION_X_NAME_ADAM_JP = 400.0f;				// X座標
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;
const static float		POSITION_Y_NAME_JP = 780.0f;					// Y座標

#endif 

#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))				// キャラセレクトの色
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int CharaSelectBarUI::cntUI = -1;
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectBarLightTexture = NULL;		// キャラセレクトバーテクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectBarLightTexture2 = NULL;		// キャラセレクトバーテクスチャ2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectNoTexture = NULL;			// キャラセレクトナンバーテクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectNoTexture2 = NULL;			// キャラセレクトナンバーテクスチャ2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectCursorTexture = NULL;		// キャラセレクトカーソルテクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectCursorTexture2 = NULL;		// キャラセレクトカーソルテクスチャ2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::selectPlayerLogoTexture = NULL;	// キャラセレクトプレイヤーロゴテクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveEngTexture = NULL;			// イヴ名前英語テクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveEngTexture2 = NULL;			// イヴ名前英語テクスチャ2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamEngTexture = NULL;			// アダム名前英語テクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamEngTexture2 = NULL;		// アダム名前英語テクスチャ2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveJpTexture = NULL;			// イヴ名前日本語テクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameEveJpTexture2 = NULL;			// イヴ名前日本語テクスチャ2
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamJpTexture = NULL;			// アダム名前日本語テクスチャ
LPDIRECT3DTEXTURE9 CharaSelectBarUI::nameAdamJpTexture2 = NULL;			// アダム名前日本語テクスチャ2
//=============================================================================
// コンストラクタ
//=============================================================================
CharaSelectBarUI::CharaSelectBarUI(void)
{
	cntUI++;
}


//=============================================================================
// デストラクタ
//=============================================================================
CharaSelectBarUI::~CharaSelectBarUI(void)
{
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CharaSelectBarUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	selectBarLightTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_BAR);
	selectBarLightTexture2 = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_BAR2);
	selectNoTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_NO);
	selectNoTexture2 = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_NO2);
	selectCursorTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_CURSOR);
	selectCursorTexture2 = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_CURSOR2);
	selectPlayerLogoTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_LOGO);
	nameEveEngTexture = *textureLoader->getTexture(textureLoaderNS::EVE_NAME_ENG);
	nameAdamEngTexture = *textureLoader->getTexture(textureLoaderNS::ADAM_NAME_ENG);
	nameEveJpTexture = *textureLoader->getTexture(textureLoaderNS::EVE_NAME_JP);
	nameAdamJpTexture = *textureLoader->getTexture(textureLoaderNS::ADAM_NAME_JP);

	charaSelectBar.initialize(device,
		selectBarLightTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		BAR_WIDTH,							// 横幅
		BAR_HEIGHT,							// 高さ
		D3DXVECTOR3(BAR_LIGHT_POSITION_X, BAR_LIGHT_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	charaSelectBar2.initialize(device,
		selectBarLightTexture2,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		BAR_WIDTH,							// 横幅
		BAR_HEIGHT,							// 高さ
		D3DXVECTOR3(BAR_LIGHT_POSITION2_X, BAR_LIGHT_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	charaSelectNo.initialize(device,
		selectNoTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		NO_WIDTH,							// 横幅
		NO_HEIGHT,							// 高さ
		D3DXVECTOR3(NO_POSITION_X, NO_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	charaSelectNo2.initialize(device,
		selectNoTexture2,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		NO_WIDTH,							// 横幅
		NO_HEIGHT,							// 高さ
		D3DXVECTOR3(NO_POSITION2_X, NO_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	charaSelectCursor.initialize(device,
		selectCursorTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		CURSOR_WIDTH,						// 横幅
		CURSOR_HEIGHT,						// 高さ
		D3DXVECTOR3(CURSOR_POSITION_X, CURSOR_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	charaSelectCursor2.initialize(device,
		selectCursorTexture2,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		CURSOR_WIDTH,						// 横幅
		CURSOR_HEIGHT,						// 高さ
		D3DXVECTOR3(CURSOR_POSITION2_X, CURSOR_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	charaSelectLogo.initialize(device,
		selectPlayerLogoTexture,			// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_LOGO_WIDTH,					// 横幅
		PLAYER_LOGO_HEIGHT,					// 高さ
		D3DXVECTOR3(playerNumber ? PLAYER_LOGO_POSITION2_X : PLAYER_LOGO_POSITION_X, PLAYER_LOGO_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameEveEng.initialize(device,
		nameEveEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameEveEng2.initialize(device,
		nameEveEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameAdamEng.initialize(device,
		nameAdamEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameAdamEng2.initialize(device,
		nameAdamEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameEveJp.initialize(device,
		nameEveJpTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_JP_WIDTH,				// 横幅
		PLAYER_NAME_JP_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameEveJp2.initialize(device,
		nameEveJpTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_JP_WIDTH,				// 横幅
		PLAYER_NAME_JP_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameAdamJp.initialize(device,
		nameAdamJpTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_JP_WIDTH,				// 横幅
		PLAYER_NAME_JP_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_ADAM_JP, POSITION_Y_NAME_JP, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	nameAdamJp2.initialize(device,
		nameAdamJpTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_JP_WIDTH,				// 横幅
		PLAYER_NAME_JP_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_NAME_ADAM_JP, POSITION_Y_NAME_JP, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void CharaSelectBarUI::uninitialize(void)
{
	charaSelectBar.setTexture(NULL);
	charaSelectBar2.setTexture(NULL);
	charaSelectNo.setTexture(NULL);
	charaSelectNo2.setTexture(NULL);
	charaSelectCursor.setTexture(NULL);
	charaSelectCursor2.setTexture(NULL);
	charaSelectLogo.setTexture(NULL);
	nameEveEng.setTexture(NULL);
	nameAdamEng.setTexture(NULL);
	nameEveJp.setTexture(NULL);
	nameAdamJp.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(selectBarLightTexture)
		SAFE_RELEASE(selectBarLightTexture2)
		SAFE_RELEASE(selectNoTexture)
		SAFE_RELEASE(selectNoTexture2)
		SAFE_RELEASE(selectCursorTexture)
		SAFE_RELEASE(selectCursorTexture2)
		SAFE_RELEASE(selectPlayerLogoTexture)
		SAFE_RELEASE(nameEveEngTexture)
		SAFE_RELEASE(nameAdamEngTexture)
		SAFE_RELEASE(nameEveJpTexture)
		SAFE_RELEASE(nameAdamJpTexture)
	}
}


//=============================================================================
// 更新処理
//=============================================================================
void CharaSelectBarUI::update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void CharaSelectBarUI::render(LPDIRECT3DDEVICE9 device, int selectNo, int select2No)
{
	charaSelectBar.render(device);
	charaSelectBar2.render(device);
	charaSelectNo.render(device);
	charaSelectNo2.render(device);
	charaSelectCursor.render(device);
	charaSelectCursor2.render(device);
	charaSelectLogo.render(device);

	//1Pセレクト
	switch (selectNo)
	{
		// プレイヤー
	case 0:

		nameEveEng.render(device);
		nameEveJp.render(device);

		break;
		// プレイヤー2
	case 1:

		nameAdamEng.render(device);
		nameAdamJp.render(device);

		break;
	}

	//2Pセレクト
	switch (select2No)
	{
		// プレイヤー
	case 0:

		nameEveEng2.render(device);
		nameEveJp2.render(device);

		break;
		// プレイヤー2
	case 1:

		nameAdamEng2.render(device);
		nameAdamJp2.render(device);

		break;
	}

}


