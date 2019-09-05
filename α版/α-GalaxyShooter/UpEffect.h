//-----------------------------------------------------------------------------
// アップエフェクトヘッダー [UpEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int UP_EFFECT = 200;	// 同時に表示するうえで妥当そうな数

//--------------------
// アップエフェクトクラス
//--------------------
class UpEffect :public EffectManager
{
private:
	InstancingEffect instancingProcedure;	// ビルボードのインスタンシング描画処理クラス
	EffectIns upEffect[UP_EFFECT];			// エフェクト配列
	int numOfUse;							// 使用中の数
	D3DXVECTOR3* renderList;				// インスタンシング描画するエフェクトの座標
	LPD3DXMESH sphere;						// バウンディングスフィア用球形メッシュ

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// アップエフェクトを発生させる
	void generateUpEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};

