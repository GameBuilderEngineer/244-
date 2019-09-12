//-----------------------------------------------------------------------------
// ダウンエフェクトヘッダー [DownEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int DOWN_EFFECT = 200;			// 同時に表示するうえで妥当そうな数
static const float DOWN_EFFECT_TIME = 2.0;	// エフェクト生存時間

//--------------------
// ダウンエフェクトクラス
//--------------------
class DownEffect :public EffectManager
{
private:
	EffectIns downEffect[DOWN_EFFECT];		// エフェクト配列

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// ダウンエフェクトを発生させる
	void generateDownEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};

