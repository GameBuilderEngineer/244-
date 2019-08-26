//=============================================================================
// キャラセレクトバーUI処理 [CharaSelectBarUI.cpp]
// 制作者 飯塚春輝
//=============================================================================
#include "CharaSelectBarUI.h"
// キャラクターセレクトバー名前空間有効
using namespace charaSelectBarUINS;
//*****************************************************************************
// 定数
//*****************************************************************************
#ifdef _DEBUG
const static int		BAR_WIDTH = WINDOW_WIDTH / 2;											// セレクトバーライト横サイズ
const static int		BAR_HEIGHT = 250;														// セレクトバーライトサイズ
const static int		NO_WIDTH = 180;															// セレクトナンバー横サイズ
const static int		NO_HEIGHT = 82;															// セレクトナンバー縦サイズ
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;										// セレクトカーソル横サイズ
const static int		CURSOR_HEIGHT = 40;														// セレクトカーソル縦サイズ
const static int		PLAYER_LOGO_WIDTH = 80;													// セレクトプレイヤーロゴ横サイズ
const static int		PLAYER_LOGO_HEIGHT = 40;												// セレクトプレイヤーロゴ縦サイズ
const static int		PLAYER_NAME_ENG_WIDTH = 250;											// プレイヤーネーム英語横サイズ
const static int		PLAYER_NAME_ENG_HEIGHT = 82;											// プレイヤーネーム英語縦サイズ
const static int		PLAYER_NAME_JP_WIDTH = 250;												// プレイヤーネーム日本語横サイズ
const static int		PLAYER_NAME_JP_HEIGHT = 20;												// プレイヤーネーム日本語縦サイズ
const static float		BAR_LIGHT_POSITION_X = 0.0f;											// セレクトバーライトX座標
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;		// セレクトバーライト2X座標
const static float		BAR_LIGHT_POSITION_Y = 220.0f;											// セレクトバーライトY座標
const static float		NO_POSITION_X = 0.0f;													// セレクトナンバーX座標
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;						// セレクトナンバー2X座標
const static float		NO_POSITION_Y = 304.0f;													// セレクトナンバーY座標
const static float		CURSOR_POSITION_X = 0.0f;												// セレクトカーソルX座標
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;				// セレクトカーソル2X座標
const static float		CURSOR_POSITION_Y = 250.0f;												// セレクトカーソルY座標
const static float		PLAYER_LOGO_POSITION_X = 0.0f;											// セレクトプレイヤーロゴX座標
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;	// セレクトプレイヤーロゴ2X座標
const static float		PLAYER_LOGO_POSITION_Y = 390.0f;										// セレクトプレイヤーロゴY座標
const static float		POSITION_X_NAME_EVE_ENG = 200.0f;										// イヴ名前英語テクスチャX座標
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;	// イヴ名前英語テクスチャ2X座標
const static float		POSITION_X_NAME_ADAM_ENG = 200.0f;										// アダム名前英語テクスチャX座標
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;// アダム名前英語テクスチャ2X座標
const static float		POSITION_Y_NAME_ENG = 304.0f;											// 名前英語テクスチャY座標
const static float		POSITION_X_NAME_EVE_JP = 200.0f;										// イヴ名前日本語テクスチャX座標
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;	// イヴ名前日本語テクスチャ2X座標
const static float		POSITION_X_NAME_ADAM_JP = 200.0f;										// アダム名前日本語テクスチャX座標
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;	// アダム名前日本語テクスチャ2X座標
const static float		POSITION_Y_NAME_JP = 390.0f;											// 名前日本語テクスチャY座標
#else
const static int		BAR_WIDTH = WINDOW_WIDTH / 2;											// リリース時セレクトバーライト横サイズ
const static int		BAR_HEIGHT = 500;														// リリース時セレクトバーライト縦サイズ
const static int		NO_WIDTH = 360;															// リリース時セレクトナンバー横サイズ
const static int		NO_HEIGHT = 164;														// リリース時セレクトナンバー縦サイズ
const static int		CURSOR_WIDTH = WINDOW_WIDTH / 2;										// リリース時セレクトカーソル横サイズ
const static int		CURSOR_HEIGHT = 80;														// リリース時セレクトカーソル縦サイズ
const static int		PLAYER_LOGO_WIDTH = 160;												// リリース時セレクトプレイヤーロゴ横サイズ
const static int		PLAYER_LOGO_HEIGHT = 80;												// リリース時セレクトプレイヤーロゴ縦サイズ
const static int		PLAYER_NAME_ENG_WIDTH = 500;											// リリース時プレイヤーネーム英語横サイズ
const static int		PLAYER_NAME_ENG_HEIGHT = 164;											// リリース時プレイヤーネーム英語縦サイズ
const static int		PLAYER_NAME_JP_WIDTH = 500;												// リリース時プレイヤーネーム日本語横サイズ
const static int		PLAYER_NAME_JP_HEIGHT = 40;												// リリース時プレイヤーネーム日本語縦サイズ
const static float		BAR_LIGHT_POSITION_X = 0.0f;											// リリース時セレクトバーライトX座標
const static float		BAR_LIGHT_POSITION2_X = BAR_LIGHT_POSITION_X + WINDOW_WIDTH / 2;		// リリース時セレクトバーライト2X座標
const static float		BAR_LIGHT_POSITION_Y = 440.0f;											// リリース時セレクトバーライトY座標
const static float		NO_POSITION_X = 0.0f;													// リリース時セレクトナンバーX座標
const static float		NO_POSITION2_X = NO_POSITION_X + WINDOW_WIDTH / 2;						// リリース時セレクトナンバー2X座標
const static float		NO_POSITION_Y = 608.0f;													// リリース時セレクトナンバーY座標
const static float		CURSOR_POSITION_X = 0.0f;												// リリース時セレクトカーソルX座標
const static float		CURSOR_POSITION2_X = CURSOR_POSITION_X + WINDOW_WIDTH / 2;				// リリース時セレクトカーソル2X座標
const static float		CURSOR_POSITION_Y = 500.0f;												// リリース時セレクトカーソルY座標
const static float		PLAYER_LOGO_POSITION_X = 0.0f;											// リリース時セレクトプレイヤーロゴX座標
const static float		PLAYER_LOGO_POSITION2_X = PLAYER_LOGO_POSITION_X + WINDOW_WIDTH / 2;	// リリース時セレクトプレイヤーロゴ2X座標
const static float		PLAYER_LOGO_POSITION_Y = 780.0f;										// リリース時セレクトプレイヤーロゴY座標
const static float		POSITION_X_NAME_EVE_ENG = 400.0f;										// リリース時イヴ名前英語テクスチャX座標
const static float		POSITION2_X_NAME_EVE_ENG = POSITION_X_NAME_EVE_ENG + WINDOW_WIDTH / 2;	// リリース時イヴ名前英語テクスチャ2X座標
const static float		POSITION_X_NAME_ADAM_ENG = 400.0f;										// リリース時アダム名前英語テクスチャX座標
const static float		POSITION2_X_NAME_ADAM_ENG = POSITION_X_NAME_ADAM_ENG + WINDOW_WIDTH / 2;// リリース時アダム名前英語テクスチャ2X座標
const static float		POSITION_Y_NAME_ENG = 608.0f;											// リリース時名前英語テクスチャY座標
const static float		POSITION_X_NAME_EVE_JP = 400.0f;										// リリース時イヴ名前日本語テクスチャX座標
const static float		POSITION2_X_NAME_EVE_JP = POSITION_X_NAME_EVE_JP + WINDOW_WIDTH / 2;	// リリース時イヴ名前日本語テクスチャ2X座標
const static float		POSITION_X_NAME_ADAM_JP = 400.0f;										// リリース時アダム名前日本語テクスチャX座標
const static float		POSITION2_X_NAME_ADAM_JP = POSITION_X_NAME_ADAM_JP + WINDOW_WIDTH / 2;	// リリース時アダム名前日本語テクスチャ2X座標
const static float		POSITION_Y_NAME_JP = 780.0f;											// リリース時名前日本語テクスチャY座標
#endif 
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
	// プレイヤーナンバー
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

	// セレクトバーライト初期化
	charaSelectBar.initialize(device,
		selectBarLightTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		BAR_WIDTH,							// 横幅
		BAR_HEIGHT,							// 高さ
		D3DXVECTOR3(BAR_LIGHT_POSITION_X, BAR_LIGHT_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// セレクトバーライト2初期化
	charaSelectBar2.initialize(device,
		selectBarLightTexture2,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		BAR_WIDTH,							// 横幅
		BAR_HEIGHT,							// 高さ
		D3DXVECTOR3(BAR_LIGHT_POSITION2_X, BAR_LIGHT_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// セレクトナンバー初期化
	charaSelectNo.initialize(device,
		selectNoTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		NO_WIDTH,							// 横幅
		NO_HEIGHT,							// 高さ
		D3DXVECTOR3(NO_POSITION_X, NO_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// セレクトナンバー2初期化
	charaSelectNo2.initialize(device,
		selectNoTexture2,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		NO_WIDTH,							// 横幅
		NO_HEIGHT,							// 高さ
		D3DXVECTOR3(NO_POSITION2_X, NO_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// セレクトカーソル初期化
	charaSelectCursor.initialize(device,
		selectCursorTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		CURSOR_WIDTH,						// 横幅
		CURSOR_HEIGHT,						// 高さ
		D3DXVECTOR3(CURSOR_POSITION_X, CURSOR_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// セレクトカーソル2初期化
	charaSelectCursor2.initialize(device,
		selectCursorTexture2,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		CURSOR_WIDTH,						// 横幅
		CURSOR_HEIGHT,						// 高さ
		D3DXVECTOR3(CURSOR_POSITION2_X, CURSOR_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// セレクトプレイヤーロゴ初期化
	charaSelectLogo.initialize(device,
		selectPlayerLogoTexture,			// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_LOGO_WIDTH,					// 横幅
		PLAYER_LOGO_HEIGHT,					// 高さ
		D3DXVECTOR3(playerNumber ? PLAYER_LOGO_POSITION2_X : PLAYER_LOGO_POSITION_X, PLAYER_LOGO_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// イヴ名前英語テクスチャ初期化
	nameEveEng.initialize(device,
		nameEveEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// イヴ名前英語テクスチャ2初期化
	nameEveEng2.initialize(device,
		nameEveEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_NAME_EVE_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// アダム名前英語テクスチャ初期化
	nameAdamEng.initialize(device,
		nameAdamEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// アダム名前英語テクスチャ2初期化
	nameAdamEng2.initialize(device,
		nameAdamEngTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_ENG_WIDTH,				// 横幅
		PLAYER_NAME_ENG_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_NAME_ADAM_ENG, POSITION_Y_NAME_ENG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// イヴ名前日本語テクスチャ初期化
	nameEveJp.initialize(device,
		nameEveJpTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_JP_WIDTH,				// 横幅
		PLAYER_NAME_JP_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// イヴ名前日本語テクスチャ2初期化
	nameEveJp2.initialize(device,
		nameEveJpTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_JP_WIDTH,				// 横幅
		PLAYER_NAME_JP_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_NAME_EVE_JP, POSITION_Y_NAME_JP, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// アダム名前日本語テクスチャ初期化
	nameAdamJp.initialize(device,
		nameAdamJpTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NAME_JP_WIDTH,				// 横幅
		PLAYER_NAME_JP_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_NAME_ADAM_JP, POSITION_Y_NAME_JP, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);
	// アダム名前日本語テクスチャ2初期化
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
	charaSelectBar.render(device);			// セレクトバーライトテクスチャ描画
	charaSelectBar2.render(device);			// セレクトバーライトテクスチャ2描画
	charaSelectNo.render(device);			// セレクトナンバーテクスチャ描画
	charaSelectNo2.render(device);			// セレクトナンバーテクスチャ2描画
	charaSelectCursor.render(device);		// セレクトカーソルテクスチャ描画
	charaSelectCursor2.render(device);		// セレクトカーソルテクスチャ2描画
	charaSelectLogo.render(device);			// セレクトプレイヤーロゴテクスチャ描画

	//1Pセレクト
	switch (selectNo)
	{
		// プレイヤー1
	case 0:

		nameEveEng.render(device);			// イヴ名前英語テクスチャ描画
		nameEveJp.render(device);			// イヴ名前日本語テクスチャ描画

		break;
		// プレイヤー2
	case 1:

		nameAdamEng.render(device);			// アダム名前英語テクスチャ描画
		nameAdamJp.render(device);			// アダム名前日本語テクスチャ描画

		break;
	}

	//2Pセレクト
	switch (select2No)
	{
		// プレイヤー1
	case 0:

		nameEveEng2.render(device);			// イヴ名前英語テクスチャ2描画
		nameEveJp2.render(device);			// イヴ名前日本語テクスチャ2描画

		break;
		// プレイヤー2
	case 1:

		nameAdamEng2.render(device);		// アダム名前英語テクスチャ2描画
		nameAdamJp2.render(device);			// アダム名前日本語テクスチャ2描画

		break;
	}
}