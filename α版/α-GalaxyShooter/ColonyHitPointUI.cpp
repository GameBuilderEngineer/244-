//=============================================================================
// コロニーHPのUI処理 [ColonyHitPointUI.cpp]
//
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成日 : 2019/6/9
//=============================================================================
#include "ColonyHitPointUI.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
const static int		WIDTH = 75;							// 横サイズ
const static int		HEIGHT = 75;						// 縦サイズ					
const static float		POSITION_X_PLAYER1 = 20.0f;			// X座標
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;
const static float		POSITION_Y = WINDOW_HEIGHT- 130.0f;	// Y座標
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// バーの色


//*****************************************************************************
// グローバル変数
//*****************************************************************************
int ColonyHitPointUI::cntUI = -1;
LPDIRECT3DTEXTURE9 ColonyHitPointUI::buffTexture = NULL;	// テクスチャ


//=============================================================================
// コンストラクタ
//=============================================================================
ColonyHitPointUI::ColonyHitPointUI(void)
{
	cntUI++;
}


//=============================================================================
// デストラクタ
//=============================================================================
ColonyHitPointUI::~ColonyHitPointUI(void)
{
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT ColonyHitPointUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	buffTexture = *textureLoader->getTexture(textureLoaderNS::UI_COLONY_HP);

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
void ColonyHitPointUI::uninitialize(void)
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
void ColonyHitPointUI::update(void)
{
}


//=============================================================================
// 描画処理
//=============================================================================
void ColonyHitPointUI::render(LPDIRECT3DDEVICE9 device)
{
	Sprite::render(device);
}




