//=============================================================================
// タイマーUI処理 [TimerUI.cpp]
// 制作者 飯塚春輝
//=============================================================================
#include "TimerUI.h"
//*****************************************************************************
// 定数
//*****************************************************************************
#ifdef _DEBUG
const static int		WIDTH = 300;						// タイマーUI横サイズ
const static int		HEIGHT = 150;						// タイマーUI縦サイズ	
const static float		POSITION_X = 330.0f;				// タイマーUIX座標
const static float		POSITION_Y = 0.0f;					// タイマーUIY座標
#else
const static int		WIDTH = 600;						// リリース時タイマーUIサイズ
const static int		HEIGHT = 300;						// リリース時タイマーUI縦サイズ	
const static float		POSITION_X = 660.0f;				// リリース時タイマーUIX座標
const static float		POSITION_Y = 0.0f;					// リリース時タイマーUIY座標
#endif 
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int TimerUI::cntUI = -1;
LPDIRECT3DTEXTURE9 TimerUI::timerTexture = NULL;			// タイマーテクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
TimerUI::TimerUI(void)
{
	cntUI++;
}
//=============================================================================
// デストラクタ
//=============================================================================
TimerUI::~TimerUI(void)
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT TimerUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// プレイヤーナンバー
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	timerTexture = *textureLoader->getTexture(textureLoaderNS::UI_CHARA_SELECT_TIMER);

	// タイマーUI初期化
	Sprite::initialize(device,
		timerTexture,						// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		WIDTH,								// 横幅
		HEIGHT,								// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		TIMER_UI_COLOR						// 色
	);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void TimerUI::uninitialize(void)
{
	// タイマーUI画像解放
	setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(timerTexture)
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void TimerUI::update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void TimerUI::render(LPDIRECT3DDEVICE9 device)
{
	// タイマーUI描画
	Sprite::render(device);
}