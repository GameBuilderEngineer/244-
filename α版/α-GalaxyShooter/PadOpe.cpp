//=============================================================================
// パッド操作説明処理 [PadOpe.cpp]
//=============================================================================
#include "PadOpe.h"
//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
//マクロ定義
const static int		WIDTH = 1280;								// パッド操作説明横サイズ
const static int		HEIGHT = 720;								// パッド操作説明縦サイズ

const static float		POSITION_X = 0.0f;							// パッド操作説明X座標
const static float		POSITION_Y = 0.0f;							// パッド操作説明Y座標
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int PadOpe::cntUI = -1;
LPDIRECT3DTEXTURE9 PadOpe::texturePadOpe = NULL;					// パッド操作説明テクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
PadOpe::PadOpe()
{
	cntUI++;
}

//=============================================================================
// デストラクタ
//=============================================================================
PadOpe::~PadOpe()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT PadOpe::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();
	if (texturePadOpe == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "MissileUI.jpg", &texturePadOpe)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "MissileUI.jpg", MB_OK);
			return E_FAIL;
		}
	}

	padOpe.initialize(device,
		texturePadOpe,								// テクスチャ
		spriteNS::TOP_LEFT,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		PAD_OPE_COLOR								// 色
	);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void PadOpe::uninitialize(void)
{
	padOpe.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(texturePadOpe)
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void PadOpe::update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void PadOpe::render(LPDIRECT3DDEVICE9 device)
{
	padOpe.render(device);
}

