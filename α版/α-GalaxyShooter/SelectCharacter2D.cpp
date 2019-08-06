//=============================================================================
// SelecCharacterの描画処理 [SelectCharacter.cpp]
////=============================================================================
#include "SelectCharacter2D.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
const static int		BG_WIDTH = WINDOW_WIDTH / 2;			// セレクトBG横サイズ
const static int		BG_HEIGHT = WINDOW_HEIGHT;				// セレクトBG縦サイズ
const static int		PLAYER_WIDTH = WINDOW_WIDTH / 3;		// セレクトキャラ横サイズ
const static int		PLAYER_HEIGHT = WINDOW_HEIGHT;			// セレクトキャラ縦サイズ
const static int		PLAYER_BG_WIDTH = WINDOW_WIDTH / 2;		// プレイヤーBG横サイズ
const static int		PLAYER_BG_HEIGHT = WINDOW_HEIGHT;		// プレイヤーBG縦サイズ
const static float		POSITION_X_BG = 0.0f;					// X座標
const static float		POSITION_X_BG2 = POSITION_X_BG + WINDOW_WIDTH / 2;
const static float		POSITION_Y_BG = 0.0f;					// Y座標
const static float		PLAYER_BG_POSITION_X = 0.0f;			// X座標
const static float		PLAYER_BG_POSITION2_X = PLAYER_BG_POSITION_X + WINDOW_WIDTH / 2;
const static float		PLAYER_BG_POSITION_Y = 0.0f;			// Y座標
#ifdef _DEBUG
const static float		POSITION_X_PLAYER = 0.0f;				// X座標
const static float		POSITION_Y_PLAYER = -20.0f;				// Y座標
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;
const static float		POSITION2_Y_PLAYER = -20.0f;			// Y座標
#else
const static float		POSITION_X_PLAYER = 0.0f;				// X座標
const static float		POSITION_Y_PLAYER = -40.0f;				// Y座標
const static float		POSITION2_X_PLAYER = POSITION_X_PLAYER + WINDOW_WIDTH / 2;
const static float		POSITION2_Y_PLAYER = -40.0f;			// Y座標

#endif 

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int SelectCharacter2D::cntUI = -1;
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectBgTexture = NULL;		// セレクトBGテクスチャ
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayerTexture = NULL;	// セレクトプレイヤーテクスチャ
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayer2Texture = NULL;	// セレクトプレイヤー2テクスチャ
LPDIRECT3DTEXTURE9 SelectCharacter2D::select2PlayerTexture = NULL;	// セレクト2プレイヤーテクスチャ
LPDIRECT3DTEXTURE9 SelectCharacter2D::select2Player2Texture = NULL;	// セレクト2プレイヤー2テクスチャ
LPDIRECT3DTEXTURE9 SelectCharacter2D::selectPlayerBGTexture = NULL;	// キャラセレクトプレイヤーBGテクスチャ
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
HRESULT SelectCharacter2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	selectBgTexture = *textureLoader->getTexture(textureLoaderNS::SELECT);
	selectPlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	selectPlayer2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	select2PlayerTexture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER);
	select2Player2Texture = *textureLoader->getTexture(textureLoaderNS::SELECT_PLAYER2);
	selectPlayerBGTexture = *textureLoader->getTexture(textureLoaderNS::CHARA_SELECT_BG);

	selectBG.initialize(device,
		selectBgTexture,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		BG_WIDTH,							// 横幅
		BG_HEIGHT,							// 高さ
		D3DXVECTOR3(playerNumber ? POSITION_X_BG2 : POSITION_X_BG, POSITION_Y_BG, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	selectPlayer.initialize(device,
		selectPlayerTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	selectPlayer2.initialize(device,
		selectPlayer2Texture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER, POSITION_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	select2Player.initialize(device,
		select2PlayerTexture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	select2Player2.initialize(device,
		select2Player2Texture,				// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_WIDTH,						// 横幅
		PLAYER_HEIGHT,						// 高さ
		D3DXVECTOR3(POSITION2_X_PLAYER, POSITION2_Y_PLAYER, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	charaSelectBG.initialize(device,
		selectPlayerBGTexture,			// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		PLAYER_BG_WIDTH,					// 横幅
		PLAYER_BG_HEIGHT,					// 高さ
		D3DXVECTOR3(playerNumber ? PLAYER_BG_POSITION2_X : PLAYER_BG_POSITION_X, PLAYER_BG_POSITION_Y, 0.0f),// 座標
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
	selectBG.setTexture(NULL);
	selectPlayer.setTexture(NULL);
	selectPlayer2.setTexture(NULL);
	select2Player.setTexture(NULL);
	select2Player2.setTexture(NULL);
	charaSelectBG.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(selectBgTexture)
		SAFE_RELEASE(selectPlayerTexture)
		SAFE_RELEASE(selectPlayer2Texture)
		SAFE_RELEASE(select2PlayerTexture)
		SAFE_RELEASE(select2Player2Texture)
		SAFE_RELEASE(selectPlayerBGTexture)
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
void SelectCharacter2D::render(LPDIRECT3DDEVICE9 device,int selectNo, int select2No)
{
	selectBG.render(device);
	charaSelectBG.render(device);

	//1Pセレクト
	switch (selectNo)
	{
		// プレイヤー
	case 0:

		selectPlayer.render(device);

		break;
		// プレイヤー2
	case 1:

		selectPlayer2.render(device);

		break;
	}

	//2Pセレクト
	switch (select2No)
	{
		// プレイヤー
	case 0:

		select2Player.render(device);

		break;
		// プレイヤー2
	case 1:

		select2Player2.render(device);

		break;
	}

}

