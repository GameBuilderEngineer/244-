#include "TargetDisplayEffect.h"

//*****************************************************************************
// 定数・マクロ
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;						// 横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;						// 縦サイズ	
															// X座標
const static float		POSITION_X_PLAYER1 = 0.0f;
const static float		POSITION_Y = 0.0f;	// Y座標
#define DEFAULT_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// バーの色

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 TargetDisplayEffect::TargetTexture = NULL;	// テクスチャ
int TargetDisplayEffect::cntUI = -1;

TargetDisplayEffect::TargetDisplayEffect()
{

}


TargetDisplayEffect::~TargetDisplayEffect()
{

}

HRESULT TargetDisplayEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader *textureLoader, StaticMeshLoader* _staticMeshLoader)
{
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	TargetTexture = *textureLoader->getTexture(textureLoaderNS::TARGET);

	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;

	image.initialize(device,
		TargetTexture,						// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		WIDTH,								// 横幅
		HEIGHT,								// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		DEFAULT_COLOR						// 色
	);

	isActive = true;



return S_OK;
}

void TargetDisplayEffect::uninitialize(void)
{
	image.setTexture(NULL);

	// インスタンスが存在しなければテクスチャ解放
	cntUI--;
	if (cntUI < 0)
	{
		SAFE_RELEASE(TargetTexture)
	}

	inactivate();
}

void TargetDisplayEffect::update(void)
{

}

void TargetDisplayEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	
	if (!isActive) return;


}

void TargetDisplayEffect::renderStencilMask(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	device->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用

	device->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// ステンシルマスクの設定
	device->SetRenderState(D3DRS_STENCILMASK, 0xff);

	// ステンシルテストに強制的に合格
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	// バックバッファへRBG値を書き込まない
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);

	// ステンシルテストに不合格の場合はステンシル値に何もしない
	device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	// Zテストに不合格な場合はステンシル値に何もしない
	device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	// ステンシルテストに合格の場合ステンシル値を1にする
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);

}

void TargetDisplayEffect::renderEffectImage(LPDIRECT3DDEVICE9 device)
{
	// ステンシルバッファの値と比較する参照値
	device->SetRenderState(D3DRS_STENCILREF, 0x01);

	// 比較関数条件が真のときステンシルテスト合格
	device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);

	// ステンシルテストに合格した場合ステンシル値には何もしない
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// フレームバッファへRGBを書き込めるようにする
	device->SetRenderState(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_RED |
		D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE |
		D3DCOLORWRITEENABLE_ALPHA);

	// Zバッファへの書き込みを許可する
	device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	image.render(device);

	// ステンシルテスト禁止
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// バックバッファとフロントバッファの入れ替え
	device->Present(NULL, NULL, NULL, NULL);

}