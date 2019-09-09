//=============================================================================
// �񕜃G�t�F�N�g�w�b�_�[ [FeelEffect.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "ScreenEffectBase.h"
#include "Sprite.h"
#include "TextureLoader.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FEEL_EFFECT_COLOR		(D3DCOLOR_RGBA(255, 255, 255, alphaColor))		// �G�t�F�N�g�̐F
#define FEEL_EFFECT_ALPHA_MAX	(255)											// �G�t�F�N�g�ő�A���t�@�l
#define FEEL_EFFECT_SUB_TIME	(10)											// �G�t�F�N�g�̌��Z�X�s�[�h
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FeelEffect :public ScreenEffectBase
{
private:
	int playerNumber;									// �v���C���[�ԍ�
	static int cntEffect;								// �G�t�F�N�g��
	static LPDIRECT3DTEXTURE9 textureFeelEffect;		// �e�N�X�`��
	Sprite feelEffect;
public:
	FeelEffect();
	~FeelEffect();

	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader);
	void uninitialize();
	void update();
	void render(LPDIRECT3DDEVICE9 device);
	void feelEffectFade(); // �G�t�F�N�g���ŏ���
};
