//-----------------------------------------------------------------------------
// シーンエフェクトヘッダー [SceneEffectEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int SCENE_EFFECT = 2000;		// 同時に表示するうえで妥当そうな数

//--------------------
// シーンエフェクトクラス
//--------------------
class SceneEffect :public EffectManager
{
private:
	InstancingEffect instancingProcedure;	// ビルボードのインスタンシング描画処理クラス
	EffectIns sceneEffect[SCENE_EFFECT];	// エフェクト配列
	int numOfUse;							// 使用中の数
	D3DXVECTOR3* renderList;				// インスタンシング描画するエフェクトの座標

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// シーンエフェクトを発生させる
	void generateSceneEffect(int num, D3DXVECTOR3 positionToGenerate);
};

