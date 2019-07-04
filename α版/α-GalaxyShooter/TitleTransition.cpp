//=============================================================================
// タイトル遷移画像遷移画像の描画処理 [TitleTransition.cpp]
////=============================================================================
#include "TitleTransition.h"
//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;								// タイトル遷移画像横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;								// タイトル遷移画像縦サイズ

const static float		POSITION_X = 0.0f;							// タイトル遷移画像X座標
const static float		POSITION_Y = 0.0f;							// タイトル遷移画像Y座標
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int TitleTransition::cntUI = -1;
LPDIRECT3DTEXTURE9 TitleTransition::titleTransTex = NULL;			// タイトル遷移画像テクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
TitleTransition::TitleTransition()
{
	cntUI++;

}

//=============================================================================
// デストラクタ
//=============================================================================
TitleTransition::~TitleTransition()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT TitleTransition::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	titleTransTex = *textureLoader->getTexture(textureLoaderNS::TITLE_TRANS);

	titleTrans.initialize(device,
		titleTransTex,									// テクスチャ
		spriteNS::TOP_LEFT,								// 原点
		WIDTH,											// 横幅
		HEIGHT,											// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),		// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// 回転
		TITLE_TRANS_COLOR								// 色
	);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void TitleTransition::uninitialize(void)
{
	titleTrans.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(titleTransTex)
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void TitleTransition::update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void TitleTransition::render(LPDIRECT3DDEVICE9 device)
{
	titleTrans.render(device);
}