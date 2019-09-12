//-----------------------------------------------------------------------------
// ラインエフェクトヘッダー [LineEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int LINE_EFFECT = 200;	// 同時に表示するうえで妥当そうな数

//--------------------
// ラインエフェクトクラス
//--------------------
class LineEffect :public EffectManager
{
private:
	EffectIns lineEffect[LINE_EFFECT];		// エフェクト配列

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// ラインエフェクトを発生させる
	void generateLineEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};
