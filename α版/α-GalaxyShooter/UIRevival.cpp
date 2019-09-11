//============================================================================================================================================
// Document
//============================================================================================================================================
// UIRevival.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/07
//============================================================================================================================================
#include "UIRevival.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace uiRevivalNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int UIRevival::instanceIndex = 0;						//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UIRevival::texture[TYPE::TYPE_MAX];	//	テクスチャ
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
UIRevival::UIRevival(void)
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
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
UIRevival::~UIRevival(void)
{
	// 解放
	release();

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
HRESULT UIRevival::initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader)
{
	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャローダーの復活UIインデックスのスタート位置（テクスチャローダーをオブジェクトごとに定数分割すればもう少し便利になるかも？）
	int textureLoaderIndex = textureLoaderNS::TEXTURE_NUMBER::UI_REVIVAL_BAR;

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
void UIRevival::initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index)
{
	switch (_index)
	{
	case TYPE::BAR:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH_BAR,														//	横幅
			HEIGHT_BAR,														//	高さ
			D3DXVECTOR3														//	座標
			(
				_playerIndex ? POSITION_X_PLAYER_2 : POSITION_X_PLAYER_1,	//	座標 x
				POSITION_Y_BAR,												//	座標 y
				0.0f														//	座標 z
			),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),									//	回転
			D3DCOLOR_RGBA(255, 255, 255, 255)								//	色
		);
		break;
	case TYPE::GAUGE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH_GAUGE,													//	横幅
			HEIGHT_GAUGE,													//	高さ
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
	case TYPE::CONCENTRATION:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH_CONCENTRATION,											//	横幅
			HEIGHT_CONCENTRATION,											//	高さ
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
	case TYPE::TONE:
		sprite[_index].initialize
		(
			_device,
			texture[_index],												//	テクスチャ
			spriteNS::CENTER,												//	原点
			WIDTH_TONE,														//	横幅
			HEIGHT_TONE,													//	高さ
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
void UIRevival::release(void)
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
void UIRevival::update(int _revivalPoint)
{
	float percentage = ((float)_revivalPoint / (float)MAX_REVIVAL_POINT);

	sprite[GAUGE].setSize((int)(percentage * WIDTH_GAUGE), HEIGHT_GAUGE);
	sprite[GAUGE].setVertex();

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void UIRevival::render(LPDIRECT3DDEVICE9 _device)
{
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		sprite[i].render(_device);
	}

	return;
}