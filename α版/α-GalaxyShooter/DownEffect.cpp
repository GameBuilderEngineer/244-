//-----------------------------------------------------------------------------
// ダウンエフェクト処理 [DownEffect.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "DownEffect.h"
//=============================================================================
// 初期化処理
//=============================================================================
void DownEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	// ダウンエフェクト初期化
	for (int i = 0; i < DOWN_EFFECT; i++)
	{
		downEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		downEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(downEffect[i].getMatrixWorld());
		downEffect[i].getCollider()->initialize(device, downEffect[i].getPosition(), sphere);
		downEffect[i].setUse(false);
		downEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	// インスタンシング初期化
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::DOWN_EFFECT));
}
//=============================================================================
// 更新処理
//=============================================================================
void DownEffect::update(float frameTime)
{

	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < DOWN_EFFECT; i++)
	{
		// 出てなかったら更新しない
		if (downEffect[i].getUse() == false) { continue; }

		// 時間をフレームに合わせる
		downEffect[i].time += frameTime;

		// ダウンエフェクト位置更新
		downEffect[i].setPosition(*downEffect[i].getPosition() + *downEffect[i].getSpeed());

		// 時間になったら終了
		if (downEffect[i].time >= DOWN_EFFECT_TIME)
		{
			downEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DownEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (downEffect[i].getUse() == false) { continue; }

		renderList[i] = *downEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

	// インスタンシングレンダー
	instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// エフェクトを発生させる
//========================================================================================
void DownEffect::generateDownEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// エフェクトカウント初期化
	int cnt = 0;

	for (int i = 0; i < DOWN_EFFECT; i++)
	{
		// エフェクトが使用されていたら入らない
		if (downEffect[i].getUse()) { continue; }

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
			resultVec = effectVec + crossVec*0.8;
			D3DXVec3Normalize(&resultVec, &resultVec);//正規化
			// 生存時間初期化
			downEffect[i].time = 0.0;
			// エフェクト位置設定
			downEffect[i].setPosition(positionToGenerate - (effectVec*6));
			// エフェクトスピード設定
			downEffect[i].setSpeed(resultVec*((float)(rand() % 6+1) / 10.0f));
			D3DXMatrixIdentity(downEffect[i].getMatrixWorld());
			// 使用へ
			downEffect[i].setUse(true);
			// 使用中エフェクトカウント加算
			numOfUse++;
		}
		// エフェクトカウント加算
		cnt++;
	}
}
