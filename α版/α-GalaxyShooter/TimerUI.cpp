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
const static float		TIMER_ONE_POSITION_X = 480.0f;		// 1桁タイマーX座標
const static float		TIMER_ONE_POSITION_Y = -20.0f;		// 1桁タイマーY座標
const static float		TIMER_TEN_POSITION_X = 440.0f;		// 10桁タイマーX座標
const static float		TIMER_TEN_POSITION_Y = -20.0f;		// 10桁タイマーY座標
#else
const static int		WIDTH = 600;						// リリース時タイマーUIサイズ
const static int		HEIGHT = 300;						// リリース時タイマーUI縦サイズ	
const static float		POSITION_X = 660.0f;				// リリース時タイマーUIX座標
const static float		POSITION_Y = 0.0f;					// リリース時タイマーUIY座標
const static float		TIMER_ONE_POSITION_X = 970.0f;		// リリース時1桁タイマーX座標
const static float		TIMER_ONE_POSITION_Y = 10.0f;		// リリース時1桁タイマーY座標
const static float		TIMER_TEN_POSITION_X = 910.0f;		// リリース時10桁タイマーX座標
const static float		TIMER_TEN_POSITION_Y = 10.0f;		// リリース時10桁タイマーY座標
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
HRESULT TimerUI::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader, TextManager* _textManager)
{
	// プレイヤーナンバー
	playerNumber = _playerNumber;

	// テキストマネージャ
	textManager = _textManager;

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
void TimerUI::render(LPDIRECT3DDEVICE9 device, float _uiOneTimer, float _uiTenTimer)
{
	// タイマーUI描画
	Sprite::render(device);

	// タイム描画
	textManager->text[textManagerNS::TYPE::NEW_RODIN_CHARACTER_SELECT_TIME]->print(TIMER_ONE_POSITION_X, TIMER_ONE_POSITION_Y, "%.0f", _uiOneTimer);
	textManager->text[textManagerNS::TYPE::NEW_RODIN_CHARACTER_SELECT_TIME]->print(TIMER_TEN_POSITION_X, TIMER_TEN_POSITION_Y, "%.0f", _uiTenTimer);
}