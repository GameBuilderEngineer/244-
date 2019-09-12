//-----------------------------------------------------------------------------
// 回復エフェクトヘッダー [FeelEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int FEEL_EFFECT = 200;	// 同時に表示するうえで妥当そうな数

//--------------------
// 回復エフェクトクラス
//--------------------
class FeelEffect :public EffectManager
{
private:
	EffectIns feelEffect[FEEL_EFFECT];			// エフェクト配列

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// 回復エフェクトを発生させる
	void generateFeelEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
	bool feel;
};

