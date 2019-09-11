//-----------------------------------------------------------------------------
// 回復エフェクト処理 [FeelEffect.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "FeelEffect.h"
//=============================================================================
// 初期化処理
//=============================================================================
void FeelEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	// 回復エフェクト初期化
	for (int i = 0; i < FEEL_EFFECT; i++)
	{
		feelEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		feelEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(feelEffect[i].getMatrixWorld());
		feelEffect[i].getCollider()->initialize(device, feelEffect[i].getPosition(), sphere);
		feelEffect[i].setUse(false);
		feelEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;
	feel = false;
	// インスタンシング初期化
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::EFFECT_FEEL));
}
//=============================================================================
// 更新処理
//=============================================================================
void FeelEffect::update(float frameTime)
{
	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < FEEL_EFFECT; i++)
	{
		// 出ていなかったら更新しない
		if (feelEffect[i].getUse() == false) { continue; }

		// 時間をフレームに合わせる
		feelEffect[i].time += frameTime;

		// エフェクト位置更新
		feelEffect[i].setPosition(*feelEffect[i].getPosition() + *feelEffect[i].getSpeed());

		// 時間になったら終了
		if (feelEffect[i].time >= 0.2)
		{
			feelEffect[i].setUse(false);
			numOfUse--;
			feel = false;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void FeelEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (feelEffect[i].getUse() == false) { continue; }

		renderList[i] = *feelEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// インスタンシング描画
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// エフェクトを発生させる
//========================================================================================
void FeelEffect::generateFeelEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// エフェクトカウント初期化
	int cnt = 0;

	for (int i = 0; i < FEEL_EFFECT; i++)
	{
		// エフェクトが使用されていたら入らない
		if (feelEffect[i].getUse()) { continue; }

		if (cnt < num)
		{
			// ランダムのベクトル作成
			D3DXVECTOR3 randVec((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50));
			// 外積ベクトル作成
			D3DXVECTOR3 crossVec(0.0, 0.0, 0.0);
			// 結果ベクトル作成
			D3DXVECTOR3 resultVec(0.0, 0.0, 0.0);
			// 外積計算
			D3DXVec3Cross(&crossVec, &effectVec, &randVec);
			D3DXVec3Normalize(&crossVec, &crossVec);//正規化
			// 結果計算
			resultVec = effectVec + crossVec * 0.8;
			D3DXVec3Normalize(&resultVec, &resultVec);//正規化
			// 生存時間初期化
			feelEffect[i].time = 0.0;
			// エフェクト位置設定
			feelEffect[i].setPosition(positionToGenerate - (effectVec * 8));
			// エフェクトスピード設定
			feelEffect[i].setSpeed(resultVec*((float)(rand() % 20) / 10.0f));
			D3DXMatrixIdentity(feelEffect[i].getMatrixWorld());
			// 使用へ
			feelEffect[i].setUse(true);
			// 使用中エフェクトカウント加算
			numOfUse++;
		}
		// エフェクトカウント加算
		cnt++;
	}
}
