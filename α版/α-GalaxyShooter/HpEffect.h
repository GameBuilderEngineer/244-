#include "ScreenEffectBase.h"
#include "Sprite.h"
#include "TextureLoader.h"

#define HP_EFFECT_COLOR		(D3DCOLOR_RGBA(255, 255, 255, alphaColor))		// エフェクトの色
#define HP_EFFECT_ALPHA_MAX	(255)											// エフェクト最大アルファ値
#define HP_EFFECT_SUB_TIME	(20)											// エフェクトの減算スピード

class HpEffect :public ScreenEffectBase
{
private:
	int playerNumber;				// プレイヤー番号
	static int cntEffect;
	static LPDIRECT3DTEXTURE9 textureHpEffect;		// テクスチャ１
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
