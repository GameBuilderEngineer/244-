//-----------------------------------------------------------------------------
// 賃金エフェクト処理 [ChinginEffect.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "ChinginEffect.h"
//=============================================================================
// 初期化処理
//=============================================================================
void ChinginEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	// 賃金エフェクト初期化
	for (int i = 0; i < CHINGIN_EFFECT; i++)
	{
		chinginEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		chinginEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(chinginEffect[i].getMatrixWorld());
		chinginEffect[i].getCollider()->initialize(device, chinginEffect[i].getPosition(), sphere);
		chinginEffect[i].setUse(false);
		chinginEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;
	// インスタンシング初期化
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::CHINGIN_EFFECT));
}
//=============================================================================
// 更新処理
//=============================================================================
void ChinginEffect::update(float frameTime)
{

	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < CHINGIN_EFFECT; i++)
	{
		// 出てなかったら更新しない
		if (chinginEffect[i].getUse() == false) { continue; }

		// 時間をフレームに合わせる
		chinginEffect[i].time += frameTime;

		// 賃金エフェクト位置更新
		chinginEffect[i].setPosition(*chinginEffect[i].getPosition() + *chinginEffect[i].getSpeed());

		// 時間になったら終了
		if (chinginEffect[i].time >= CHINGIN_EFFECT_TIME)
		{
			chinginEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void ChinginEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (chinginEffect[i].getUse() == false) { continue; }

		renderList[i] = *chinginEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// インスタンシングレンダー
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// エフェクトを発生させる
//========================================================================================
void ChinginEffect::generateChinginEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// エフェクトカウント初期化
	int cnt = 0;

	for (int i = 0; i < CHINGIN_EFFECT; i++)
	{
		// エフェクトが使用されていたら入らない
		if (chinginEffect[i].getUse()) { continue; }

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
			resultVec = effectVec + crossVec;
			D3DXVec3Normalize(&resultVec, &resultVec);//正規化
			// 生存時間初期化
			chinginEffect[i].time = 0.0;
			// エフェクト位置設定
			chinginEffect[i].setPosition(positionToGenerate - (effectVec * 6));
			// エフェクトスピード設定
			chinginEffect[i].setSpeed(resultVec*((float)(rand() % 6 + 1) / 10.0f));
			D3DXMatrixIdentity(chinginEffect[i].getMatrixWorld());
			// 使用へ
			chinginEffect[i].setUse(true);
			// 使用中エフェクトカウント加算
			numOfUse++;
		}
		// エフェクトカウント加算
		cnt++;
	}
}
