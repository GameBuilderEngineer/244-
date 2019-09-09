//=============================================================================
// 回復エフェクト処理 [FeelEffect.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "FeelEffect.h"
//*****************************************************************************
// 定数
//*****************************************************************************
static int				alphaColor = FEEL_EFFECT_ALPHA_MAX;								// 回復エフェクトアルファ値
const static int		WIDTH = WINDOW_WIDTH / 2;										// 回復エフェクト横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;											// 回復エフェクト縦サイズ
const static float		POSITION_X_PLAYER1 = 0.0f;										// 回復エフェクトX座標
const static float		POSITION_X_PLAYER2 = POSITION_X_PLAYER1 + WINDOW_WIDTH / 2.0f;	// 回復エフェクト2X座標
const static float		POSITION_Y = 0.0f;												// 回復エフェクトY座標
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int FeelEffect::cntEffect = -1;
LPDIRECT3DTEXTURE9 FeelEffect::textureFeelEffect = NULL;								// FEELエフェクトのテクスチャ
//=============================================================================
// コンストラクタ
//=============================================================================
FeelEffect::FeelEffect()
{
	cntEffect++;
}
//=============================================================================
// デストラクタ
//=============================================================================
FeelEffect::~FeelEffect()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT FeelEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader)
{
	// 生存時間初期化
	cntFrame = 0;
	// プレイヤーナンバー
	playerNumber = _playerNumber;
	// エフェクト不使用
	isActive = false;

	// テクスチャを読み込む
	setVisualDirectory();

	textureFeelEffect = *textureLoader->getTexture(textureLoaderNS::EFFECT_FEEL);

	// 回復エフェクト初期化
	feelEffect.initialize(device,
		textureFeelEffect,					// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		WIDTH,								// 横幅
		HEIGHT,								// 高さ
		D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		FEEL_EFFECT_COLOR					// 色
	);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void FeelEffect::uninitialize(void)
{
}
//=============================================================================
// 更新処理
//=============================================================================
void FeelEffect::update(void)
{
	if (!isActive) return;

	// 回復エフェクト更新処理
	cntFrame++;
	if (cntFrame < settingFrame)
	{
		// 処理をつくる
		feelEffectFade();
	}
	// 時間になったら終了
	if (cntFrame == settingFrame)
	{
		isActive = false;
		alphaColor = FEEL_EFFECT_ALPHA_MAX;
		cntFrame = 0;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void FeelEffect::render(LPDIRECT3DDEVICE9 device)
{
	// 使用していなかったら戻る
	if (!isActive) return;

	// 回復エフェクト描画
	feelEffect.render(device);
}
//=============================================================================
// フェードアウト処理
//=============================================================================
void FeelEffect::feelEffectFade(void)
{
	// アルファ減算
	alphaColor -= FEEL_EFFECT_SUB_TIME;

	// アルファが0になったら元に戻す
	if (alphaColor <= 0)
	{
		alphaColor = FEEL_EFFECT_ALPHA_MAX;
		isActive = false;
	}

	// エフェクト位置設定
	feelEffect.setAlpha(alphaColor);
}
