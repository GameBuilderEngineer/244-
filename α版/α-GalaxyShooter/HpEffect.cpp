#include "HpEffect.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
static int				alphaColor = 255;					// アルファ値
const static int		WIDTH = WINDOW_WIDTH / 2;			// 横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;				// 縦サイズ					
const static float		POSITION_X_PLAYER1 = 0.0f;			// X座標
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;
const static float		POSITION_Y = 0.0f;					// Y座標
#define HP_EFFECT_COLOR		(D3DCOLOR_RGBA(255, 255, 255, 255))		// エフェクトの色

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int HpEffect::cntEffect = -1;
LPDIRECT3DTEXTURE9 HpEffect::textureHpEffect = NULL;		// HPエフェクトのテクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
HpEffect::HpEffect()
{
	cntEffect++;
}

//=============================================================================
// デストラクタ
//=============================================================================
HpEffect::~HpEffect()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT HpEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// ここに書き加えられる
	cntFrame = 0;
	playerNumber = _playerNumber;
	isActive = false;

	// テクスチャを読み込む
	setVisualDirectory();

	textureHpEffect = *textureLoader->getTexture(textureLoaderNS::HP_EFFECT);

	hpEffect.initialize(device,
		textureHpEffect,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		WIDTH,								// 横幅
		HEIGHT,								// 高さ
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		HP_EFFECT_COLOR						// 色
	);

	return S_OK;
}

void HpEffect::uninitialize(void)
{
	hpEffect.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntEffect--;
	if (cntEffect < 0)
	{
		SAFE_RELEASE(textureHpEffect)
	}
}

void HpEffect::update(void)
{
	if (!isActive) return;

	cntFrame++;
	if (cntFrame < settingFrame)
	{
	}

	if (cntFrame == settingFrame)
	{
		isActive = false;
		cntFrame = 0;
	}
}

void HpEffect::render(LPDIRECT3DDEVICE9 device)
{
	hpEffect.render(device);
}
