//=============================================================================
// チュートリアルの描画処理 [Tutorial2D.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Tutorial2D.h"
//*****************************************************************************
// 定数
//*****************************************************************************
const static int		WIDTH = ((3840 / 2) - 16);					// チュートリアル2D横サイズ
const static int		HEIGHT = ((2160 / 2) - 9);					// チュートリアル2D縦サイズ
const static float		POSITION_X = ((WINDOW_WIDTH / 2) - 8.5f);	// チュートリアル2DX座標
const static float		POSITION_Y = ((WINDOW_HEIGHT / 2) - 10.0f);	// チュートリアル2DY座標
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Tutorial2D::cntUI = -1;
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D = NULL;			// チュートリアル2Dテクスチャ
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D2 = NULL;			// チュートリアル2D2テクスチャ
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D3 = NULL;			// チュートリアル2D3テクスチャ
LPDIRECT3DTEXTURE9 Tutorial2D::textureTutorial2D4 = NULL;			// チュートリアル2D4テクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
Tutorial2D::Tutorial2D()
{
	cntUI++;
}
//=============================================================================
// デストラクタ
//=============================================================================
Tutorial2D::~Tutorial2D()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Tutorial2D::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// プレイヤーナンバー
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	textureTutorial2D = *textureLoader->getTexture(textureLoaderNS::TUTORIAL);
	textureTutorial2D2 = *textureLoader->getTexture(textureLoaderNS::TUTORIAL2);
	textureTutorial2D3 = *textureLoader->getTexture(textureLoaderNS::TUTORIAL3);
	textureTutorial2D4 = *textureLoader->getTexture(textureLoaderNS::TUTORIAL4);

	// チュートリアルのページ
	next = 0;

	// チュートリアル2D初期化
	Sprite::initialize(device,
		textureTutorial2D,							// テクスチャ
		spriteNS::CENTER,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		TUTORIAL2D_COLOR							// 色
	);

	// チュートリアル2D2初期化
	tuto2.initialize(device,
		textureTutorial2D2,							// テクスチャ
		spriteNS::CENTER,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		TUTORIAL2D_COLOR							// 色
	);

	// チュートリアル2D3初期化
	tuto3.initialize(device,
		textureTutorial2D3,							// テクスチャ
		spriteNS::CENTER,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		TUTORIAL2D_COLOR							// 色
	);

	// チュートリアル2D4初期化
	tuto4.initialize(device,
		textureTutorial2D4,							// テクスチャ
		spriteNS::CENTER,							// 原点
		WIDTH,										// 横幅
		HEIGHT,										// 高さ
		D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f),	// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 回転
		TUTORIAL2D_COLOR							// 色
	);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void Tutorial2D::uninitialize(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void Tutorial2D::update(void)
{

}
//=============================================================================
// 描画処理
//=============================================================================
void Tutorial2D::render(LPDIRECT3DDEVICE9 device)
{
	switch (next)
	{
	case 0:
		// チュートリアル2D描画
		Sprite::render(device);

		break;
	case 1:
		// チュートリアル2D2描画
		tuto2.render(device);

		break;
	case 2:
		// チュートリアル2D4描画
		tuto4.render(device);

		break;
	case 3:
		// チュートリアル2D3描画
		tuto3.render(device);

		break;

	}

}
