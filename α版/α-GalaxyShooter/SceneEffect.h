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
const float GENERATE_TIME = 0.1;
const int GAME_SCENE_GENERATE_NUM = 12;
//--------------------
// シーンエフェクトクラス
//--------------------
class SceneEffect :public EffectManager
{
private:
	EffectIns sceneEffect[SCENE_EFFECT];	// エフェクト配列
	float generateTimer;					//生成時間
	bool onGameScene;
public:
	SceneEffect() {
		onGameScene = false;
		generateTimer = 0.0f;
	}
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// シーンエフェクトを発生させる
	void generateSceneEffect(int num, D3DXVECTOR3 positionToGenerate);
	void generateSceneEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 initialSpeed);
	//void createPositionSphericalEffect(LPDIRECT3DDEVICE9 device, int num, float radius);
	void setOnGameScene(bool flag) { onGameScene = flag; };
};

