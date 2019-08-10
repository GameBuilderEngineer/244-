//=============================================================================
// タイトル遷移画像描画処理 [TitleTransition.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "TitleTransition.h"
//*****************************************************************************
// 定数
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH / 2;						// タイトル遷移画像横サイズ
const static float		GAME_POSITION_X = 0.0f;							// ゲーム遷移画像X座標
const static float		TUTORIAL_POSITION_X = 0.0f;						// チュートリアル遷移画像X座標
const static float		OPERATION_POSITION_X = 0.0f;					// オペレーション遷移画像X座標
const static float		CREDIT_POSITION_X = 0.0f;						// クレジット遷移画像X座標
const static float		GAMEEND_POSITION_X = 0.0f;						// ゲームエンド遷移画像X座標
#ifdef _DEBUG
const static int		HEIGHT = WINDOW_HEIGHT/9;						// タイトル遷移画像縦サイズ
const static float		GAME_POSITION_Y = TITLE_GAME_POS;				// ゲーム遷移画像Y座標
const static float		TUTORIAL_POSITION_Y = TITLE_TUTORIAL_POS;		// チュートリアル遷移画像Y座標
const static float		OPERATION_POSITION_Y = TITLE_OPERATION_POS;		// オペレーション遷移画像Y座標
const static float		CREDIT_POSITION_Y = TITLE_CREDIT_POS;			// クレジット遷移画像Y座標
const static float		GAMEEND_POSITION_Y = TITLE_GAMEEND_POS;			// ゲームエンド遷移画像Y座標
#else
const static int		HEIGHT = WINDOW_HEIGHT / 9;						// リリース時タイトル遷移画像縦サイズ
const static float		GAME_POSITION_Y = RELEASE_START_POS;			// リリース時ゲーム遷移画像Y座標
const static float		TUTORIAL_POSITION_Y = RELEASE_TUTORIAL_POS;		// リリース時チュートリアル遷移画像Y座標
const static float		OPERATION_POSITION_Y = RELEASE_OPERATION_POS;	// リリース時オペレーション遷移画像Y座標
const static float		CREDIT_POSITION_Y = RELEASE_CREDIT_POS;			// リリース時クレジット遷移画像Y座標
const static float		GAMEEND_POSITION_Y = RELEASE_GAMEEND_POS;		// リリース時ゲームエンド遷移画像Y座標
#endif 
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int TitleTransition::cntUI = -1;
LPDIRECT3DTEXTURE9 TitleTransition::titleGameTex = NULL;				// ゲーム遷移画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleTutorialTex = NULL;			// チュートリアル遷移画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleOperationTex = NULL;			// オペレーション遷移画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleCreditTex = NULL;				// クレジット遷移画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleGameendTex = NULL;				// ゲームエンド遷移画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleGameBTex = NULL;				// ゲーム遷移時画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleTutorialBTex = NULL;			// チュートリアル遷移時画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleOperationBTex = NULL;			// オペレーション遷移時画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleCreditBTex = NULL;				// クレジット遷移時画像テクスチャ
LPDIRECT3DTEXTURE9 TitleTransition::titleGameendBTex = NULL;			// ゲームエンド遷移時画像テクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
TitleTransition::TitleTransition()
{
	cntUI++;
}
//=============================================================================
// デストラクタ
//=============================================================================
TitleTransition::~TitleTransition()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT TitleTransition::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// プレイヤーナンバー
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	titleGameTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAME);					// ゲーム
	titleTutorialTex = *textureLoader->getTexture(textureLoaderNS::TITLE_TUTORIAL);			// チュートリアル
	titleOperationTex = *textureLoader->getTexture(textureLoaderNS::TITLE_OPERATION);		// オペレーション
	titleCreditTex = *textureLoader->getTexture(textureLoaderNS::TITLE_CREDIT);				// クレジット
	titleGameendTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAMEEND);			// ゲームエンド
	titleGameBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAME_B);				// ゲーム遷移時
	titleTutorialBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_TUTORIAL_B);		// チュートリアル遷移時
	titleOperationBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_OPERATION_B);	// オペレーション遷移時
	titleCreditBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_CREDIT_B);			// クレジット遷移時
	titleGameendBTex = *textureLoader->getTexture(textureLoaderNS::TITLE_GAMEEND_B);		// ゲームエンド遷移時

	// ゲーム遷移画像初期化
	TitleGame.initialize(device,
		titleGameTex,														// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(GAME_POSITION_X, GAME_POSITION_Y, 0.0f),				// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// チュートリアル遷移画像初期化
	TitleTutorial.initialize(device,
		titleTutorialTex,													// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(TUTORIAL_POSITION_X, TUTORIAL_POSITION_Y, 0.0f),		// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// オペレーション遷移画像初期化
	TitleOperation.initialize(device,
		titleOperationTex,													// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(OPERATION_POSITION_X, OPERATION_POSITION_Y, 0.0f),		// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// クレジット遷移画像初期化
	TitleCredit.initialize(device,
		titleCreditTex,														// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(CREDIT_POSITION_X, CREDIT_POSITION_Y, 0.0f),			// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// ゲームエンド遷移画像初期化
	TitleGameend.initialize(device,
		titleGameendTex,													// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(GAMEEND_POSITION_X, GAMEEND_POSITION_Y, 0.0f),			// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);


	// ゲーム遷移時画像初期化
	TitleGameB.initialize(device,
		titleGameBTex,														// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(GAME_POSITION_X, GAME_POSITION_Y, 0.0f),				// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// チュートリアル遷移時画像初期化
	TitleTutorialB.initialize(device,
		titleTutorialBTex,													// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(TUTORIAL_POSITION_X, TUTORIAL_POSITION_Y, 0.0f),		// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// オペレーション遷移時画像初期化
	TitleOperationB.initialize(device,
		titleOperationBTex,													// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(OPERATION_POSITION_X, OPERATION_POSITION_Y, 0.0f),		// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// クレジット遷移時画像初期化
	TitleCreditB.initialize(device,
		titleCreditBTex,													// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(CREDIT_POSITION_X, CREDIT_POSITION_Y, 0.0f),			// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);
	// ゲームエンド遷移時画像初期化
	TitleGameendB.initialize(device,
		titleGameendBTex,													// テクスチャ
		spriteNS::TOP_LEFT,													// 原点
		WIDTH,																// 横幅
		HEIGHT,																// 高さ
		D3DXVECTOR3(GAMEEND_POSITION_X, GAMEEND_POSITION_Y, 0.0f),			// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),										// 回転
		DEFAULT_COLOR														// 色
	);

	// 遷移位置初期化
	cntTitle = NULL;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void TitleTransition::uninitialize(void)
{
	TitleGame.setTexture(NULL);				// ゲーム遷移画像解放
	TitleTutorial.setTexture(NULL);			// チュートリアル遷移画像解放
	TitleOperation.setTexture(NULL);		// オペレーション遷移画像解放
	TitleCredit.setTexture(NULL);			// クレジット遷移画像解放
	TitleGameend.setTexture(NULL);			// ゲームエンド遷移画像解放
	TitleGameB.setTexture(NULL);			// ゲーム遷移時画像解放
	TitleTutorialB.setTexture(NULL);		// チュートリアル遷移時画像解放
	TitleOperationB.setTexture(NULL);		// オペレーション遷移時画像解放
	TitleCreditB.setTexture(NULL);			// クレジット遷移時画像解放
	TitleGameendB.setTexture(NULL);			// ゲームエンド遷移時画像解放

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(titleGameTex)
		SAFE_RELEASE(titleTutorialTex)
		SAFE_RELEASE(titleOperationTex)
		SAFE_RELEASE(titleCreditTex)
		SAFE_RELEASE(titleGameendTex)
		SAFE_RELEASE(titleGameBTex)
		SAFE_RELEASE(titleTutorialBTex)
		SAFE_RELEASE(titleOperationBTex)
		SAFE_RELEASE(titleCreditBTex)
		SAFE_RELEASE(titleGameendBTex)
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void TitleTransition::update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void TitleTransition::render(LPDIRECT3DDEVICE9 device)
{
	TitleGame.render(device);			// ゲーム遷移画像描画
	TitleTutorial.render(device);		// チュートリアル遷移画像描画
	TitleOperation.render(device);		// オペレーション遷移画像描画
	TitleCredit.render(device);			// クレジット遷移画像描画
	TitleGameend.render(device);		// ゲームエンド遷移画像描画
	titleTransBlack(device);			// タイトル選択位置画像移動処理
}
//=============================================================================
// タイトル選択位置画像移動処理
//=============================================================================
void TitleTransition::titleTransBlack(LPDIRECT3DDEVICE9 device)
{
	switch (cntTitle)
	{
		// セレクト
	case 0:
		TitleGameB.render(device);			// ゲーム遷移時画像描画
		break;

		// チュートリアル
	case 1:
		TitleTutorialB.render(device);		// チュートリアル遷移時画像描画
		break;

		// 操作方法
	case 2:
		TitleOperationB.render(device);		// オペレーション遷移時画像描画
		break;

		// クレジット
	case 3:
		TitleCreditB.render(device);		// クレジット遷移時画像描画
		break;

		// ゲーム終了
	case 4:
		TitleGameendB.render(device);		// ゲームエンド遷移時画像描画
		break;
	}
}