#include "ScreenEffectBase.h"
#include "Sprite.h"
#include "TextureLoader.h"

#define HP_EFFECT_COLOR		(D3DCOLOR_RGBA(255, 255, 255, alphaColor))		// �G�t�F�N�g�̐F
#define HP_EFFECT_ALPHA_MAX	(255)											// �G�t�F�N�g�ő�A���t�@�l
#define HP_EFFECT_SUB_TIME	(20)											// �G�t�F�N�g�̌��Z�X�s�[�h

class HpEffect :public ScreenEffectBase
{
private:
	int playerNumber;				// �v���C���[�ԍ�
	static int cntEffect;
	static LPDIRECT3DTEXTURE9 textureHpEffect;		// �e�N�X�`���P
	Sprite hpEffect;

public:
	HpEffect();
	~HpEffect();

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize();
	void update();
	void render(LPDIRECT3DDEVICE9 device);
	void effectFade(); // �G�t�F�N�g���ŏ���

};
