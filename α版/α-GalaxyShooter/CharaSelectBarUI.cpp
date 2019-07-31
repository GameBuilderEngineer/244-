//=============================================================================
// キャラセレクトバーUI処理 [CharaSelectBarUI.cpp]
//
//=============================================================================
#include "CharaSelectBarUI.h"
using namespace charaSelectBarUINS;

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
const static int		BAR_WIDTH = WINDOW_WIDTH/2;						// 横サイズ
const static int		BAR_HEIGHT = 250;								// 縦サイズ
const static int		NO_WIDTH = 180;									// 横サイズ
const static int		NO_HEIGHT = 82;									// 縦サイズ
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;				// 横サイズ
const static int		CURSOR_HEIGHT = 40;								// 縦サイズ
const static int		PLAYER_LOGO_WIDTH = 80;							// 横サイズ
const static int		PLAYER_LOGO_HEIGHT = 40;						// 縦サイズ
const static float		BAR_LIGHT_POSITION_X = 0.0f;					// X座標
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X+ WINDOW_WIDTH / 2;
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
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))				// キャラセレクトバーの色
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
void CharaSelectBarUI::render(LPDIRECT3DDEVICE9 device)
{
	charaSelectBar.render(device);
	charaSelectBar2.render(device);
	charaSelectNo.render(device);
	charaSelectNo2.render(device);
	charaSelectCursor.render(device);
	charaSelectCursor2.render(device);
	charaSelectLogo.render(device);
}


