//=============================================================================
// 体力エフェクトヘッダー [HpEffect.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "ScreenEffectBase.h"
#include "Sprite.h"
#include "TextureLoader.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define HP_EFFECT_COLOR		(D3DCOLOR_RGBA(255, 255, 255, alphaColor))		// エフェクトの色
#define HP_EFFECT_ALPHA_MAX	(255)											// エフェクト最大アルファ値
#define HP_EFFECT_SUB_TIME	(10)											// エフェクトの減算スピード
//*****************************************************************************
// クラス定義
//*****************************************************************************
class HpEffect :public ScreenEffectBase
{
private:
	int playerNumber;								// プレイヤー番号
	static int cntEffect;							// エフェクト個数
	static LPDIRECT3DTEXTURE9 textureHpEffect;		// テクスチャ
	Sprite hpEffect;
public:
	HpEffect();
	~HpEffect();

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize();
	void update();
	void render(LPDIRECT3DDEVICE9 device);
	void effectFade(); // エフェクト消滅処理
};
