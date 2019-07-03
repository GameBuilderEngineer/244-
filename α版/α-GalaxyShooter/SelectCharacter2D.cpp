//=============================================================================
// SelecCharacterの描画処理 [SelectCharacter.cpp]
////=============================================================================
#include "SelectCharacter2D.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
const static int		WIDTH = 1280;						// 横サイズ
const static int		HEIGHT = 720;						// 縦サイズ					
const static float		POSITION_X_PLAYER1 = 0.0f;			// X座標
const static float		POSITION_X_PLAYER2 = 0.0f;
const static float		POSITION_Y = 0.0f;					// Y座標
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// バーの色

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int SelectCharacter2D::cntUI = -1;
LPDIRECT3DTEXTURE9 SelectCharacter2D::buffTexture = NULL;	// テクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
SelectCharacter2D::SelectCharacter2D()
{
	cntUI++;
}


SelectCharacter2D::~SelectCharacter2D()
{
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT SelectCharacter2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();
	if (buffTexture == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "nTex.png", &buffTexture)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "nTex.png", MB_OK);
			return E_FAIL;
		}
	}

	Sprite::initialize(device,
		buffTexture,						// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		WIDTH,								// 横幅
		HEIGHT,								// 高さ
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void SelectCharacter2D::uninitialize(void)
{
	setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(buffTexture)
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void SelectCharacter2D::update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void SelectCharacter2D::render(LPDIRECT3DDEVICE9 device)
{
	Sprite::render(device);
}
