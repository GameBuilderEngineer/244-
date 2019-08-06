//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRevivalGauge.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/07
//======================================================================================================================================================
#include "UIRevivalGauge.h"
//
//#define BAR_COLOR		(D3DCOLOR_RGBA(0, 255, 0, 255))		// バーの色
//#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// バーの色

//======================================================================================================================================================
// Using Declaration
// using宣言
//======================================================================================================================================================
using namespace uiRevivalGaugeNS;
//======================================================================================================================================================
// Global Variable
// グローバル変数
//======================================================================================================================================================
int UIRevivalGauge::instanceIndex = (-1);					//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UIRevivalGauge::texture[TYPE::TYPE_MAX];	//	テクスチャ
//======================================================================================================================================================
// Constructor
// コンストラクタ
//======================================================================================================================================================
UIRevivalGauge::UIRevivalGauge(void)
{
	// インスタンスインデックスを加算
	instanceIndex++;

	// テクスチャのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	return;
}
//======================================================================================================================================================
// Destructor
// デストラクタ
//======================================================================================================================================================
UIRevivalGauge::~UIRevivalGauge(void)
{
	// 解放
	release();

	return;
}
//======================================================================================================================================================
// initialize
// 初期化
//======================================================================================================================================================
HRESULT UIRevivalGauge::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader)
{
	// テクスチャローダーの復活ゲージインデックスのスタート位置（テクスチャローダーをオブジェクトごとに定数分割すればもう少し便利になるかも？）
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_REVIVAL_GAUGE_00;

	// プレイヤーインデックス
	playerIndex = _playerIndex;

	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャ読み込み
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// スプライト初期化
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, i);
	}

	//// スプライト初期化
	//gaugeBase.initialize(device,
	//	textureGaugeBase,					// テクスチャ
	//	spriteNS::TOP_LEFT,					// 原点
	//	WIDTH,								// 横幅
	//	HEIGHT,								// 高さ
	//	D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
	//	DEFAULT_COLOR						// 色
	//);
	//gaugeBar.initialize(device,
	//	textureGaugeBar,					// テクスチャ
	//	spriteNS::TOP_LEFT,					// 原点
	//	WIDTH,								// 横幅
	//	HEIGHT,								// 高さ
	//	D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
	//	BAR_COLOR							// 色
	//);
	//gaugeCover.initialize(device,
	//	textureGaugeCover,					// テクスチャ
	//	spriteNS::TOP_LEFT,					// 原点
	//	WIDTH,								// 横幅
	//	HEIGHT,								// 高さ
	//	D3DXVECTOR3(playerNumber ? POSITION_X_PLAYER2 : POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
	//	DEFAULT_COLOR						// 色
	//);

	return S_OK;
}
//======================================================================================================================================================
// initializeSprite
// 初期化 - スプライト
//======================================================================================================================================================
void UIRevivalGauge::initializeSprite(LPDIRECT3DDEVICE9 _device, int _index)
{
	switch (_index)
	{
	case TYPE::FOUNDATION:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH,															//	横幅
			HEIGHT,															//	高さ
			D3DXVECTOR3														//	座標
			(
				playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y,													//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	case TYPE::CURRENT:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH,															//	横幅
			HEIGHT,															//	高さ
			D3DXVECTOR3														//	座標
			(
				playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y,													//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	default:
		break;
	}

	return;
}
//======================================================================================================================================================
// release
// 解放
//======================================================================================================================================================
void UIRevivalGauge::release(void)
{
	// スプライトのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].setTexture(NULL);
	}

	// インスタンスインデックスを減算
	instanceIndex--;

	// インスタンスが存在しなければ、テクスチャを解放
	if (instanceIndex >= 0)
	{
		return;
	}

	SAFE_RELEASE(texture[TYPE::FOUNDATION]);
	SAFE_RELEASE(texture[TYPE::CURRENT]);

	return;
}
//======================================================================================================================================================
// update
// 更新
//======================================================================================================================================================
void UIRevivalGauge::update(int _revivalPoint)
{
	float percentage = ((float)_revivalPoint / (float)50000);

	sprite[TYPE::CURRENT].setSize((int)(percentage * WIDTH), HEIGHT);
	sprite[TYPE::CURRENT].setVertex();

	return;
}
//======================================================================================================================================================
// render
// 描画
//======================================================================================================================================================
void UIRevivalGauge::render(LPDIRECT3DDEVICE9 _device)
{
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}