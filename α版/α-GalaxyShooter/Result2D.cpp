//=============================================================================
// リザルト描画処理 [Result2D.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Result2D.h"
//*****************************************************************************
// 定数
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;												// リザルト2D横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;												// リザルト2D縦サイズ
const static int		PLAYER_WIDTH = WINDOW_WIDTH / 3;									// リザルトキャラ横サイズ
const static int		PLAYER_HEIGHT = WINDOW_HEIGHT;										// リザルトキャラ縦サイズ
const static int		PLAYER_BG_WIDTH = WINDOW_WIDTH;										// プレイヤーBG横サイズ
const static int		PLAYER_BG_HEIGHT = WINDOW_HEIGHT /2;								// プレイヤーBG縦サイズ
const static int		PLAYER_NUMBER_WIDTH = WINDOW_WIDTH / 4;								// リザルトキャラナンバー横サイズ
const static int		PLAYER_NUMBER_HEIGHT = WINDOW_HEIGHT / 12;							// リザルトキャラナンバー縦サイズ
const static int		JUDGE_WIDTH = WINDOW_WIDTH / 4;										// リザルトジャッジ横サイズ
const static int		JUDGE_HEIGHT = WINDOW_HEIGHT / 12;									// リザルトジャッジ縦サイズ
const static float		POSITION_X_PLAYER1 = 0.0f;											// リザルト2DX座標
const static float		POSITION_Y = 0.0f;													// リザルト2DY座標
#ifdef _DEBUG
const static float		POSITION_X_PLAYER = 80.0f;											// リザルトキャラX座標
const static float		POSITION_Y_PLAYER = -20.0f;											// リザルトキャラY座標
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;			// リザルトキャラ2X座標
const static float		POSITION2_Y_PLAYER = -20.0f;										// リザルトキャラY座標
const static float		POSITION_X_PLAYER_NO = 110.0f;										// リザルトキャラナンバーX座標
const static float		POSITION2_X_PLAYER_NO = POSITION_X_PLAYER_NO + WINDOW_WIDTH / 2;	// リザルトキャラ2ナンバーX座標
const static float		POSITION_Y_PLAYER_NO = 220.0f;										// リザルトキャラナンバーY座標
const static float		POSITION_X_JUDGE = 110.0f;											// リザルトジャッジX座標
const static float		POSITION2_X_JUDGE = POSITION_X_JUDGE + WINDOW_WIDTH / 2;			// リザルトジャッジ2X座標
const static float		POSITION_Y_JUDGE = 270.0f;											// リザルトジャッジY座標
const static float		PLAYER_BG_POSITION_X = 0.0f;										// プレイヤーBGX座標
const static float		PLAYER_BG_POSITION_Y = 150.0f;										// プレイヤーBGY座標
#else
const static float		POSITION_X_PLAYER = 160.0f;											// リリース時リザルトキャラX座標
const static float		POSITION_Y_PLAYER = -40.0f;											// リリース時リザルトキャラY座標
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;			// リリース時リザルトキャラ2X座標
const static float		POSITION2_Y_PLAYER = -40.0f;										// リリース時リザルトキャラY座標
const static float		POSITION_X_PLAYER_NO = 220.0f;										// リリース時リザルトキャラナンバーX座標
const static float		POSITION2_X_PLAYER_NO = POSITION_X_PLAYER_NO + WINDOW_WIDTH / 2;	// リリース時リザルトキャラ2ナンバーX座標
const static float		POSITION_Y_PLAYER_NO = 440.0f;										// リリース時リザルトキャラナンバーY座標
const static float		POSITION_X_JUDGE = 220.0f;											// リリース時リザルトジャッジX座標
const static float		POSITION2_X_JUDGE = POSITION_X_JUDGE + WINDOW_WIDTH / 2;			// リリース時リザルトジャッジ2X座標
const static float		POSITION_Y_JUDGE = 540.0f;											// リリース時リザルトジャッジY座標
const static float		PLAYER_BG_POSITION_X = 0.0f;										// リリース時プレイヤーBGX座標
const static float		PLAYER_BG_POSITION_Y = 300.0f;										// リリース時プレイヤーBGY座標
#endif 
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Result2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Result2D::result2DTexture = NULL;										// リザルト2Dテクスチャ
LPDIRECT3DTEXTURE9 Result2D::resultPlayerTexture = NULL;									// リザルトプレイヤーテクスチャ
LPDIRECT3DTEXTURE9 Result2D::resultPlayer2Texture = NULL;									// リザルトプレイヤー2テクスチャ
LPDIRECT3DTEXTURE9 Result2D::result2PlayerTexture = NULL;									// リザルト2プレイヤーテクスチャ
LPDIRECT3DTEXTURE9 Result2D::result2Player2Texture = NULL;									// リザルト2プレイヤー2テクスチャ
LPDIRECT3DTEXTURE9 Result2D::resultPlayerBGTexture = NULL;									// キャラセレクトプレイヤーBGテクスチャ
LPDIRECT3DTEXTURE9 Result2D::resultPlayerNumberTexture = NULL;								// リザルトプレイヤーナンバーテクスチャ
LPDIRECT3DTEXTURE9 Result2D::resultPlayer2NumberTexture = NULL;								// リザルトプレイヤー2ナンバーテクスチャ
LPDIRECT3DTEXTURE9 Result2D::resultJadgeTexture = NULL;										// リザルトジャッジテクスチャ
LPDIRECT3DTEXTURE9 Result2D::resultJadge2Texture = NULL;									// リザルトジャッジ2テクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
Result2D::Result2D()
{
	cntUI++;
}
//=============================================================================
// デストラクタ
//=============================================================================
Result2D::~Result2D()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Result2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// プレイヤーナンバー
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	result2DTexture = *textureLoader->getTexture(textureLoaderNS::RESULT);
	resultPlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	resultPlayer2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	result2PlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	result2Player2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	resultPlayerBGTexture = *textureLoader->getTexture(textureLoaderNS::CHARA_RESULT_BG);
	resultPlayerNumberTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER_NUMBER);
	resultPlayer2NumberTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2_NUMBER);
	resultJadgeTexture = *textureLoader->getTexture(textureLoaderNS::WIN);
	resultJadge2Texture = *textureLoader->getTexture(textureLoaderNS::LOSE);

	// リザルト2D初期化
	Sprite::initialize(device,
		result2DTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		WIDTH,								// 横幅
		HEIGHT,								// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// リザルトキャラ初期化
	resultPlayer.initialize(device,
		resultPlayerTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// リザルトキャラ2初期化
	resultPlayer2.initialize(device,
		resultPlayer2Texture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// リザルト2キャラ初期化
	result2Player.initialize(device,
		result2PlayerTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// リザルト2キャラ2初期化
	result2Player2.initialize(device,
		result2Player2Texture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// キャラクターBG初期化
	charaResultBG.initialize(device,
		resultPlayerBGTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_BG_WIDTH,					// 横幅
		PLAYER_BG_HEIGHT,					// 高さ
		D3DXVECTOR3(PLAYER_BG_POSITION_X, PLAYER_BG_POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// リザルトキャラナンバー初期化
	resultPlayerNumber.initialize(device,
		resultPlayerNumberTexture,			// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NUMBER_WIDTH,				// 横幅
		PLAYER_NUMBER_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER_NO, POSITION_Y_PLAYER_NO, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// リザルトキャラ2ナンバー初期化
	resultPlayer2Number.initialize(device,
		resultPlayer2NumberTexture,			// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_NUMBER_WIDTH,				// 横幅
		PLAYER_NUMBER_HEIGHT,				// 高さ
		D3DXVECTOR3(POSITION2_X_PLAYER_NO, POSITION_Y_PLAYER_NO, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// ジャッジ初期化
	resultJadge.initialize(device,
		resultJadgeTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		JUDGE_WIDTH,						// 横幅
		JUDGE_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION_X_JUDGE, POSITION_Y_JUDGE, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);
	// ジャッジ2初期化
	resultJadge2.initialize(device,
		resultJadge2Texture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		JUDGE_WIDTH,						// 横幅
		JUDGE_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION2_X_JUDGE, POSITION_Y_JUDGE, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		RESULT2D_COLOR						// 色
	);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Result2D::uninitialize(void)
{
	setTexture(NULL);						// リザルト2D画像解放
	resultPlayer.setTexture(NULL);			// リザルトキャラ画像解放
	resultPlayer2.setTexture(NULL);			// リザルトキャラ2画像解放
	result2Player.setTexture(NULL);			// リザルト2キャラ画像解放
	result2Player2.setTexture(NULL);		// リザルト2キャラ2画像解放
	charaResultBG.setTexture(NULL);			// キャラクターBG画像解放
	resultPlayerNumber.setTexture(NULL);	// リザルトキャラナンバー画像解放
	resultPlayer2Number.setTexture(NULL);	// リザルトキャラ2ナンバー画像解放
	resultJadge.setTexture(NULL);			// リザルトジャッジ画像解放
	resultJadge2.setTexture(NULL);			// リザルトジャッジ2画像解放

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(result2DTexture)
		SAFE_RELEASE(resultPlayerTexture)
		SAFE_RELEASE(resultPlayer2Texture)
		SAFE_RELEASE(result2PlayerTexture)
		SAFE_RELEASE(result2Player2Texture)
		SAFE_RELEASE(resultPlayerBGTexture)
		SAFE_RELEASE(resultPlayerNumberTexture)
		SAFE_RELEASE(resultPlayer2NumberTexture)
		SAFE_RELEASE(resultJadgeTexture)
		SAFE_RELEASE(resultJadge2Texture)
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void Result2D::update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void Result2D::render(LPDIRECT3DDEVICE9 device, int resultNo, int result2No)
{
	// リザルト2D描画
	Sprite::render(device);

	// キャラクターBG描画
	charaResultBG.render(device);

	//1Pリザルト
	switch (resultNo)
	{
		// プレイヤー
	case 0:

		resultPlayer.render(device);

		break;
		// プレイヤー2
	case 1:

		resultPlayer2.render(device);

		break;
	}

	//2Pリザルト
	switch (result2No)
	{
		// プレイヤー
	case 0:

		result2Player.render(device);

		break;
		// プレイヤー2
	case 1:

		result2Player2.render(device);

		break;
	}

	// キャラクターナンバー描画
	resultPlayerNumber.render(device);

	// キャラクターナンバー2描画
	resultPlayer2Number.render(device);

	// ジャッジ描画
	resultJadge.render(device);

	// ジャッジ2描画
	resultJadge2.render(device);
}
