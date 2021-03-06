//=============================================================================
// スプラッシュの描画処理 [Splash.cpp]
// 制作者 飯塚春輝
////=============================================================================
#include "Splash2D.h"
//*****************************************************************************
// 定数
//*****************************************************************************
const static int		WIDTH = (800 - 16);							// スプラッシュ2D横サイズ
const static int		HEIGHT = (568 - 9);							// スプラッシュ2D縦サイズ
static int				alphaColor = 0;								// アルファ値
static int				time = 0;									// スプラッシュ2D消滅時間
const static float		POSITION_X = ((WINDOW_WIDTH / 2) - 8.5f);	// スプラッシュ2DX座標
const static float		POSITION_Y = ((WINDOW_HEIGHT / 2) - 10.0f);	// スプラッシュ2DY座標
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Splash2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Splash2D::textureSplash2D = NULL;				// スプラッシュ2Dテクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
Splash2D::Splash2D()
{
	cntUI++;
}
//=============================================================================
// デストラクタ
//=============================================================================
Splash2D::~Splash2D()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Splash2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// プレイヤーナンバー
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	textureSplash2D = *textureLoader->getTexture(textureLoaderNS::SPLASH);

	// スプラッシュ2D初期化
	Sprite::initialize(device,
		textureSplash2D,							// テクスチャ
		spriteNS::CENTER,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		SPLASH2D_COLOR
	);

	fadeon = true;									// フェード起動中
	gotitle = false;								// フェードが終わっていない

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Splash2D::uninitialize(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void Splash2D::update(void)
{
	// フェード処理
	fade();
}
//=============================================================================
// 描画処理
//=============================================================================
void Splash2D::render(LPDIRECT3DDEVICE9 device)
{
	// スプラッシュ2D描画
	Sprite::render(device);
}
//=============================================================================
// フェード処理
//=============================================================================
void Splash2D::fade(void)
{
	// 時間になったらフェードアウト
	time++;
	if (time >= SPLASH_TIME)
	{
		fadeon = false;
	}

	// フェードイン
	if (fadeon)
	{
		fadein();
	}
	// フェードアウト
	else
	{
		fadeout();
	}
}
//=============================================================================
// フェードイン処理
//=============================================================================
void Splash2D::fadein(void)
{
	// アルファ加算
	alphaColor++;

	if (alphaColor >= SPLASH_ALPHA_MAX)
	{
		alphaColor = SPLASH_ALPHA_MAX;
	}

	setAlpha(alphaColor);
}
//=============================================================================
// フェードアウト処理
//=============================================================================
void Splash2D::fadeout(void)
{
	// アルファ減算
	alphaColor--;

	if (alphaColor <= 0)
	{
		alphaColor = 0;

		// フェードが終わってタイトルへ遷移
		gotitle = true;
	}

	setAlpha(alphaColor);
}
