//-----------------------------------------------------------------------------
// パイルエフェクトヘッダー [PileEffect.h]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Player.h"
#include "Bullet.h"
#include "EffectManager.h"

static const int PILE_EFFECT = 100;	// 同時に表示するうえで妥当そうな数

//--------------------
// パイルエフェクトクラス
//--------------------
class PileEffect :public EffectManager
{
private:
	InstancingEffect instancingProcedure;	// ビルボードのインスタンシング描画処理クラス
	EffectIns pileEffect[PILE_EFFECT];		// エフェクト配列
	int numOfUse;							// 使用中の数
	D3DXVECTOR3* renderList;				// インスタンシング描画するエフェクトの座標
	LPD3DXMESH sphere;						// バウンディングスフィア用球形メッシュ

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// エフェクトを発生させる
	void generatePileEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};

