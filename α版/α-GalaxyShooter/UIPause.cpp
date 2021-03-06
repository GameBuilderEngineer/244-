//============================================================================================================================================
// Document
//============================================================================================================================================
// UIPause.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/27
//============================================================================================================================================
#include "UIPause.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace uiPauseNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int UIPause::instanceIndex = 0;			//	インスタンスインデックス
LPDIRECT3DTEXTURE9 UIPause::texture;	//	テクスチャ
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
UIPause::UIPause(void)
{
	// インスタンスインデックスを加算
	instanceIndex++;

	// テクスチャのクリア
	texture = NULL;

	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
UIPause::~UIPause(void)
{
	// 解放
	release();

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
HRESULT UIPause::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader)
{
	// ディレクトリ設定
	setVisualDirectory();

	// テクスチャ読み込み( キャラクター )
	texture = *_textureLoader->getTexture(textureLoaderNS::TEXTURE_NUMBER::PAUSE);

	// スプライト初期化
	sprite.initialize
	(
		_device,
		texture,							//	テクスチャ
		spriteNS::CENTER,					//	原点
		WIDTH,								//	横幅
		HEIGHT,								//	高さ
		D3DXVECTOR3							//	座標
		(
			POSITION_X,						//	座標 x
			POSITION_Y,						//	座標 y
			0.0f							//	座標 z
		),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//	回転
		D3DCOLOR_RGBA(255, 255, 255, 255)	//	色
	);

	return S_OK;
}
//============================================================================================================================================
// release
// 解放
//============================================================================================================================================
void UIPause::release(void)
{
	// スプライトのクリア
	sprite.setTexture(NULL);

	// インスタンスインデックスを減算
	instanceIndex--;

	return;
}
//============================================================================================================================================
// update
// 更新
//============================================================================================================================================
void UIPause::update(void)
{
	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void UIPause::render(LPDIRECT3DDEVICE9 _device)
{
	if (!renderFlag) { return; }

	sprite.render(_device);

	return;
}
//============================================================================================================================================
// setRenderFlag
// 設定 - 描画フラグ
//============================================================================================================================================
void UIPause::setRenderFlag(bool _flag)
{
	renderFlag = _flag;

	return;
}
//============================================================================================================================================
// getRenderFlag
// 取得 - 描画フラグ
//============================================================================================================================================
bool UIPause::getRenderFlag(void)
{
	return renderFlag;
}