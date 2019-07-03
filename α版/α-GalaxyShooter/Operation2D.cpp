//=============================================================================
// Operationの描画処理 [Operation2D.cpp]
////=============================================================================
#include "Operation2D.h"
//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
//マクロ定義
const static int		WIDTH = 1280;								// 操作確認2D横サイズ
const static int		HEIGHT = 720;								// 操作確認2D縦サイズ

const static float		POSITION_X = 0.0f;							// 操作確認2DX座標
const static float		POSITION_Y = 0.0f;							// 操作確認2DY座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Operation2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Operation2D::textureOperation2D = NULL;			// 操作確認2Dテクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
Operation2D::Operation2D()
{
	cntUI++;
}

//=============================================================================
// デストラクタ
//=============================================================================
Operation2D::~Operation2D()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Operation2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();
	if (textureOperation2D == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "MissileUI.jpg", &textureOperation2D)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "MissileUI.jpg", MB_OK);
			return E_FAIL;
		}
	}

	operation2D.initialize(device,
		textureOperation2D,							// テクスチャ
		spriteNS::TOP_LEFT,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		OPERATION2D_COLOR
	);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Operation2D::uninitialize(void)
{
	operation2D.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(textureOperation2D)
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Operation2D::update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void Operation2D::render(LPDIRECT3DDEVICE9 device)
{
	operation2D.render(device);
}

