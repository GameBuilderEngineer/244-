//=============================================================================
// 体力エフェクト処理 [HpEffect.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "HpEffect.h"
//*****************************************************************************
// 定数
//*****************************************************************************
static int				alphaColor = HP_EFFECT_ALPHA_MAX;								// 体力エフェクトアルファ値
const static int		WIDTH = WINDOW_WIDTH / 2;										// 体力エフェクト横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;											// 体力エフェクト縦サイズ
const static float		POSITION_X_PLAYER1 = 0.0f;										// 体力エフェクトX座標
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;	// 体力エフェクト2X座標
const static float		POSITION_Y = 0.0f;												// 体力エフェクトY座標
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int HpEffect::cntEffect = -1;
LPDIRECT3DTEXTURE9 HpEffect::textureHpEffect = NULL;									// HPエフェクトのテクスチャ
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
	// 生存時間初期化
	cntFrame = 0;
	// プレイヤーナンバー
	playerNumber = _playerNumber;
	// エフェクト不使用
	isActive = false;

	// テクスチャを読み込む
	setVisualDirectory();

	textureHpEffect = *textureLoader->getTexture(textureLoaderNS::HP_EFFECT);

	// 体力エフェクト初期化
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
//=============================================================================
// 終了処理
//=============================================================================
void HpEffect::uninitialize(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void HpEffect::update(void)
{
	if (!isActive) return;

	// 体力エフェクト更新処理
	cntFrame++;
	if (cntFrame < settingFrame)
	{
		// 処理をつくる
		effectFade();
	}
	// 時間になったら終了
	if (cntFrame == settingFrame)
	{
		isActive = false;
		alphaColor = HP_EFFECT_ALPHA_MAX;
		cntFrame = 0;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void HpEffect::render(LPDIRECT3DDEVICE9 device)
{
	// 使用していなかったら戻る
	if (!isActive) return;

	// 体力エフェクト描画
	hpEffect.render(device);
}
//=============================================================================
// フェードアウト処理
//=============================================================================
void HpEffect::effectFade(void)
{
	// アルファ減算
	alphaColor -= HP_EFFECT_SUB_TIME;

	// アルファが0になったら元に戻す
	if (alphaColor <= 0)
	{
		alphaColor = HP_EFFECT_ALPHA_MAX;
	}

	// エフェクト位置設定
	hpEffect.setAlpha(alphaColor);
}
