//============================================================================================================================================
// Document
//============================================================================================================================================
// UICountDown.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/09/10
//============================================================================================================================================
#include "UICountDown.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace uiCountDownNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int UICountDown::instanceIndex = 0;							//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UICountDown::texture[TYPE::TYPE_MAX];	//	テクスチャ
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
UICountDown::UICountDown(void)
{
	// インスタンスインデックスを加算
	instanceIndex++;

	// テクスチャのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = NULL;
	}

	alpha = 0;

	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
UICountDown::~UICountDown(void)
{
	// 解放
	release();

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
HRESULT UICountDown::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader)
{
	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャローダーの復活UIインデックスのスタート位置（テクスチャローダーをオブジェクトごとに定数分割すればもう少し便利になるかも？）
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_COUNT_DOWN_FINISH;

	// テクスチャ読み込み
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		texture[i] = *_textureLoader->getTexture(textureLoaderIndex);
		textureLoaderIndex++;
	}

	// スプライト初期化
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		initializeSprite(_device, _playerIndex, i);
	}

	return S_OK;
}
//============================================================================================================================================
// initializeSprite
// 初期化 - スプライト
//============================================================================================================================================
void UICountDown::initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index)
{
	switch (_index)
	{
	case TYPE::FINISH:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			(WIDTH_COUNT_DOWN * 2),											//	横幅
			(WIDTH_COUNT_DOWN * 2),											//	高さ
			D3DXVECTOR3														//	座標
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y,													//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	case TYPE::GO:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			(WIDTH_COUNT_DOWN * 2),											//	横幅
			(WIDTH_COUNT_DOWN * 2),											//	高さ
			D3DXVECTOR3														//	座標
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y,													//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	case TYPE::ONE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH_COUNT_DOWN,												//	横幅
			HEIGHT_COUNT_DOWN,												//	高さ
			D3DXVECTOR3														//	座標
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y,													//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	case TYPE::TWO:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH_COUNT_DOWN,												//	横幅
			HEIGHT_COUNT_DOWN,												//	高さ
			D3DXVECTOR3														//	座標
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y,													//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	case TYPE::THREE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH_COUNT_DOWN,												//	横幅
			HEIGHT_COUNT_DOWN,												//	高さ
			D3DXVECTOR3														//	座標
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
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
//============================================================================================================================================
// release
// 解放
//============================================================================================================================================
void UICountDown::release(void)
{
	// スプライトのクリア
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].setTexture(NULL);
	}

	// インスタンスインデックスを減算
	instanceIndex--;

	return;
}
//============================================================================================================================================
// update
// 更新
//============================================================================================================================================
void UICountDown::update(bool _startFlag)
{
	updateFadeOut();

	// フェードが終わったらタイトルへ
	if (!_startFlag) { return; }

	return;
}
//============================================================================================================================================
// updateFadeOut
// 更新 - フェードアウト
//============================================================================================================================================
void UICountDown::updateFadeOut(void)
{
	// アルファ減算
	alpha--;

	if (alpha <= 0)
	{
		alpha = 0;
	}

	sprite[0].setAlpha(alpha);

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void UICountDown::render(LPDIRECT3DDEVICE9 _device, int _renderIndex)
{
	sprite[_renderIndex].render(_device);

	return;
}