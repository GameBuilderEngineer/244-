#include "ScreenEffectBase.h"
#include "Sprite.h"
#include "TextureLoader.h"

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
};
