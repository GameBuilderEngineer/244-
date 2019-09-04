//=============================================================================
// ステンシルヘッダー [TargetDisplayEffect.h]
// 制作者 飯塚春輝
//=============================================================================
#include "Sprite.h"
#include "ScreenEffectBase.h"
#include "TextureLoader.h"
#include "Object.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TRGET_COLOR	(D3DCOLOR_RGBA(255, 255, 255, 255))	// ステンシルの色
//*****************************************************************************
// クラス定義
//*****************************************************************************
class TargetDisplayEffect : public ScreenEffectBase
{
private:
	Sprite image;
	StaticMeshLoader* staticMeshLoader;
	int playerNumber;
	static LPDIRECT3DTEXTURE9 TargetTexture;			// テクスチャ
	static int cntUI;									// インスタンスの数を数える
public:
	TargetDisplayEffect();
	~TargetDisplayEffect();
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader *textureLoader, StaticMeshLoader* _staticMeshLoader);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device);
	void renderStencilMask(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func);	// ステンシルマスクを描画
	void renderEffectImage(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func);	// エフェクト画像を描画
	void renderSetUp(LPDIRECT3DDEVICE9 device);													// ステンシル準備
	void renderStencilEnd(LPDIRECT3DDEVICE9 device);											// ステンシル終了
	void renderGeneral(LPDIRECT3DDEVICE9 device, unsigned char ste, D3DCMPFUNC cmp_func);		// 一般ステンシル
};
