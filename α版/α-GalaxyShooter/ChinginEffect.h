//-----------------------------------------------------------------------------
// 賃金エフェクトヘッダー [ChinginEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int CHINGIN_EFFECT = 200;			// 同時に表示するうえで妥当そうな数
static const float CHINGIN_EFFECT_TIME = 0.4;	// エフェクト生存時間

//--------------------
// 賃金エフェクトクラス
//--------------------
class ChinginEffect :public EffectManager
{
private:
	EffectIns chinginEffect[CHINGIN_EFFECT];	// エフェクト配列

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// 賃金エフェクトを発生させる
	void generateChinginEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};

