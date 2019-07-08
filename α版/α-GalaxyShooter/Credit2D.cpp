//=============================================================================
// Creditの描画処理 [Credit2D.cpp]
////=============================================================================
#include "Credit2D.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
//マクロ定義
const static int		WIDTH = WINDOW_WIDTH;						// クレジット2D横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;						// クレジット2D縦サイズ

const static float		POSITION_X = 0.0f;							// クレジット2DX座標
const static float		POSITION_Y = 0.0f;							// クレジット2DY座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Credit2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Credit2D::textureCredit2D = NULL;			// クレジット2Dテクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
Credit2D::Credit2D()
{
	cntUI++;
}

//=============================================================================
// デストラクタ
//=============================================================================
Credit2D::~Credit2D()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Credit2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();
	if (textureCredit2D == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "kurezitto.png", &textureCredit2D)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "kurezitto.png", MB_OK);
			return E_FAIL;
		}
	}

	textureCredit2D = *textureLoader->getTexture(textureLoaderNS::CREDIT);

	credit2D.initialize(device,
		textureCredit2D,							// テクスチャ
		spriteNS::TOP_LEFT,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		CREDIT2D_COLOR
	);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Credit2D::uninitialize(void)
{
	credit2D.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(textureCredit2D)
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Credit2D::update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void Credit2D::render(LPDIRECT3DDEVICE9 device)
{
	credit2D.render(device);
}

