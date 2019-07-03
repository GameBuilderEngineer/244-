//=============================================================================
// Splashの描画処理 [Splash.cpp]
////=============================================================================
#include "Splash2D.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
//マクロ定義
const static int		WIDTH = 960;								// スプラッシュ2D横サイズ
const static int		HEIGHT = 540;								// スプラッシュ2D縦サイズ
static int				alphaColor = 0;								// アルファ値
static int				time = 0;									// スプラッシュ2D消滅時間

#ifdef _DEBUG
const static float		POSITION_X = 160.0f;						// スプラッシュ2DX座標
const static float		POSITION_Y = 80.0f;							// スプラッシュ2DY座標
#else
const static float		POSITION_X = 480.0f;						// スプラッシュ2DX座標
const static float		POSITION_Y = 270.0f;						// スプラッシュ2DY座標
#endif

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
HRESULT Splash2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();
	if (textureSplash2D == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "Team_Logo_Texture.png", &textureSplash2D)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "Team_Logo_Texture.png", MB_OK);
			return E_FAIL;
		}
	}

	splash2D.initialize(device,
		textureSplash2D,							// テクスチャ
		spriteNS::TOP_LEFT,							// 原点
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
	splash2D.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(textureSplash2D)
	}
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
	splash2D.render(device);
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

	splash2D.setAlpha(alphaColor);
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

	splash2D.setAlpha(alphaColor);
}
