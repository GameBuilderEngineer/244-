//=============================================================================
// Titleの描画処理 [Title2D.cpp]
////=============================================================================
#include "Title2D.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
const static int		WIDTH = 1280;								// タイトル横サイズ
const static int		HEIGHT = 720;								// タイトル縦サイズ
const static int		WIDTH2 = 600;								// 選択画像横サイズ
const static int		HEIGHT2 = 50;								// 選択画像縦サイズ

const static float		POSITION_X = 0.0f;							// タイトルX座標
const static float		POSITION_Y = 0.0f;							// タイトルY座標
const static float		POSITION_X_2 = 0.0f;						// 選択画像X座標
static float			POSITION_Y_2 = CNT_TITLE_START;				// 選択画像Y座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Title2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Title2D::titleTexture2D = NULL;					// タイトルテクスチャ
LPDIRECT3DTEXTURE9 Title2D::choiceTexture = NULL;					// 選択画像テクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
Title2D::Title2D()
{
	cntUI++;

}

//=============================================================================
// デストラクタ
//=============================================================================
Title2D::~Title2D()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Title2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();
	if (titleTexture2D == NULL)
	{
		//if (FAILED(D3DXCreateTextureFromFile(device, "ColonyHitPointUI.jpg", &titleTexture2D)))
		if (FAILED(D3DXCreateTextureFromFile(device, "Title.png", &titleTexture2D)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "ColonyHitPointUI.jpg", MB_OK);
			return E_FAIL;
		}
	}
	if (choiceTexture == NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(device, "Title_Bar.png", &choiceTexture)))
		{
			MessageBox(NULL, "テクスチャの読み込みに失敗しました", "nTex.png", MB_OK);
			return E_FAIL;
		}
	}

	title2D.initialize(device,
		titleTexture2D,									// テクスチャ
		spriteNS::TOP_LEFT,								// 原点
		WIDTH,											// 横幅
		HEIGHT,											// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),		// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// 回転
		TITLE2D_COLOR									// 色
	);

	choice.initialize(device,
		choiceTexture,									// テクスチャ
		spriteNS::TOP_LEFT,								// 原点
		WIDTH2,											// 横幅
		HEIGHT2,										// 高さ
		D3DXVECTOR3(POSITION_X_2, POSITION_Y_2, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),					// 回転
		TITLE2D_COLOR									// 色
	);

	cntTitle = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Title2D::uninitialize(void)
{
	title2D.setTexture(NULL);
	choice.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(titleTexture2D)
		SAFE_RELEASE(choiceTexture)
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Title2D::update(void)
{
	titleUImove();

	choice.setVertex();
}


//=============================================================================
// 描画処理
//=============================================================================
void Title2D::render(LPDIRECT3DDEVICE9 device)
{
	choice.render(device);
	title2D.render(device);

}

//=============================================================================
// 選択UI移動処理
//=============================================================================
void Title2D::titleUImove(void)
{
	switch (cntTitle)
	{
		// ゲーム開始
	case 0:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_START, 0));
		break;

		// チュートリアル
	case 1:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_TUTORIAL, 0));
		break;

		// 操作方法
	case 2:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_OPERATION, 0));
		break;

		// クレジット
	case 3:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_CREDIT, 0));
		break;

		// ゲーム終了
	case 4:
		choice.setPosition2(D3DXVECTOR3(0, CNT_TITLE_END, 0));
		break;
	}
}