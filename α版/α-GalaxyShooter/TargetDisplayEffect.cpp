//=============================================================================
// ステンシル処理 [TargetDisplayEffect.cpp]
// 制作者 飯塚春輝
//=============================================================================
#include "TargetDisplayEffect.h"
//*****************************************************************************
// 定数
//*****************************************************************************
const static int		WIDTH = WINDOW_WIDTH;						// ステンシル横サイズ
const static int		HEIGHT = WINDOW_HEIGHT;						// ステンシル縦サイズ	
const static float		POSITION_X_PLAYER1 = 0.0f;					// ステンシルX座標
const static float		POSITION_Y = 0.0f;							// ステンシルY座標
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 TargetDisplayEffect::TargetTexture = NULL;		// ステンシルテクスチャ
int TargetDisplayEffect::cntUI = -1;
//=============================================================================
// コンストラクタ
//=============================================================================
TargetDisplayEffect::TargetDisplayEffect()
{
	cntUI++;
}
//=============================================================================
// デストラクタ
//=============================================================================
TargetDisplayEffect::~TargetDisplayEffect()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT TargetDisplayEffect::initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader *textureLoader, StaticMeshLoader* _staticMeshLoader)
{
	// プレイヤーナンバー
	playerNumber = _playerNumber;

	// テクスチャを読み込む
	setVisualDirectory();

	TargetTexture = *textureLoader->getTexture(textureLoaderNS::TARGET);

	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;

	// ステンシル初期化
	image.initialize(device,
		TargetTexture,						// テクスチャ
		spriteNS::TOP_LEFT,					// 原点
		WIDTH,								// 横幅
		HEIGHT,								// 高さ
		D3DXVECTOR3(POSITION_X_PLAYER1, POSITION_Y, 0.0f),// 座標
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 回転
		TRGET_COLOR							// 色
	);

	// ステンシル有効
	isActive = true;

return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void TargetDisplayEffect::uninitialize(void)
{

	// ステンシル終了
	inactivate();
}
//=============================================================================
// 更新処理
//=============================================================================
void TargetDisplayEffect::update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void TargetDisplayEffect::render(LPDIRECT3DDEVICE9 device)
{
	//device->SetRenderState(D3DRS_LIGHTING, false);
	image.render(device);
}
//=============================================================================
// ステンシルマスク処理
//=============================================================================
void TargetDisplayEffect::renderStencilMask(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func)
{
	// Zバッファを使用しない
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ステンシルバッファを使用する
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// ステンシルバッファの値と比較する参照値
	device->SetRenderState(D3DRS_STENCILREF, 2);

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
//=============================================================================
// ステンシル描画処理
//=============================================================================
void TargetDisplayEffect::renderEffectImage(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func)
{
	// ステンシルバッファの値と比較する参照値
	device->SetRenderState(D3DRS_STENCILREF, ste);

	// 比較関数条件が真のときステンシルテスト合格
	device->SetRenderState(D3DRS_STENCILFUNC, cmp_func);

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
}
//=============================================================================
// ステンシル開始処理
//=============================================================================
void TargetDisplayEffect::renderSetUp(LPDIRECT3DDEVICE9 device)
{
	// 初期化
	device->Clear(0, 0, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL , D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	device->BeginScene();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	device->SetRenderState(D3DRS_ALPHAREF, 0x01);
}
//=============================================================================
// ステンシル終了処理
//=============================================================================
void TargetDisplayEffect::renderStencilEnd(LPDIRECT3DDEVICE9 device)
{
	// ステンシルテスト禁止
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// バックバッファとフロントバッファの入れ替え
	device->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
// 一般ステンシル描画処理
//=============================================================================
void TargetDisplayEffect::renderGeneral(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func)
{
	// Zバッファ設定 => 有効
	device->SetRenderState(D3DRS_ZENABLE, TRUE);

	// ZBUFFER比較設定変更 => (参照値 <= バッファ値)
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// ステンシルバッファ => 有効
	device->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// ステンシルバッファと比較する参照値設定 => ref
	device->SetRenderState(D3DRS_STENCILREF, ste);

	// ステンシルバッファの値に対してのマスク設定 => 0xff(全て真)
	device->SetRenderState(D3DRS_STENCILMASK, 0xff);

	// ステンシルテストの比較方法設定 => 
	//		この描画での参照値 >= ステンシルバッファの参照値なら合格
	device->SetRenderState(D3DRS_STENCILFUNC, cmp_func);

	// ステンシルテストの結果に対しての反映設定
	device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
}
