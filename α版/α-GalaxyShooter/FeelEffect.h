//-----------------------------------------------------------------------------
// �񕜃G�t�F�N�g�w�b�_�[ [FeelEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int FEEL_EFFECT = 200;	// �����ɕ\�����邤���őÓ������Ȑ�

//--------------------
// �񕜃G�t�F�N�g�N���X
//--------------------
class FeelEffect :public EffectManager
{
private:
	EffectIns feelEffect[FEEL_EFFECT];			// �G�t�F�N�g�z��

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// �񕜃G�t�F�N�g�𔭐�������
	void generateFeelEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
	bool feel;
};

