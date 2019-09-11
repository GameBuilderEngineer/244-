//-----------------------------------------------------------------------------
// シーンエフェクト処理 [SceneEffect.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "SceneEffect.h"
//=============================================================================
// 初期化処理
//=============================================================================
void SceneEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	// シーンエフェクト初期化
	for (int i = 0; i < SCENE_EFFECT; i++)
	{
		sceneEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		sceneEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(sceneEffect[i].getMatrixWorld());
		sceneEffect[i].getCollider()->initialize(device, sceneEffect[i].getPosition(), sphere);
		sceneEffect[i].setUse(false);
		sceneEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	// インスタンシング初期化
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::LIGHT_001));

}
//=============================================================================
// 更新処理
//=============================================================================
void SceneEffect::update(float frameTime)
{

	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < SCENE_EFFECT; i++)
	{
		// 出てなかったら更新しない
		if (sceneEffect[i].getUse() == false) { continue; }

		// 時間をフレームに合わせる
		sceneEffect[i].time += frameTime;

		// シーンエフェクト位置更新
		sceneEffect[i].setPosition(*sceneEffect[i].getPosition() + *sceneEffect[i].getSpeed());

		// 時間になったら終了
		if (sceneEffect[i].time >= (float)(rand() % SCENE_EFFECT + 1))
		{
			sceneEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void SceneEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (sceneEffect[i].getUse() == false) { continue; }

		renderList[i] = *sceneEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// インスタンシングレンダー
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// エフェクトを発生させる
//========================================================================================
void SceneEffect::generateSceneEffect(int num, D3DXVECTOR3 positionToGenerate)
{
	// エフェクトカウント初期化
	int cnt = 0;

	for (int i = 0; i < SCENE_EFFECT; i++)
	{
		// エフェクトが使用されていたら入らない
		if (sceneEffect[i].getUse()) { continue; }

		if (cnt < num)
		{
			// 生存時間初期化
			sceneEffect[i].time = 0.0;
			// エフェクト位置設定
			sceneEffect[i].setPosition(positionToGenerate);
			// エフェクトスピード設定
			sceneEffect[i].setSpeed(D3DXVECTOR3(0.0,(float)(rand()%1+0.1),0.0));
			D3DXMatrixIdentity(sceneEffect[i].getMatrixWorld());
			// 使用へ
			sceneEffect[i].setUse(true);
			// 使用中エフェクトカウント加算
			numOfUse++;
		}
		// エフェクトカウント加算
		cnt++;
	}
}
