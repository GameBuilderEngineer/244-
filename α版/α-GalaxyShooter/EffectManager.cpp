//-----------------------------------------------------------------------------
// エフェクトマネージャー処理 [EffectManager.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "EffectManager.h"
//=============================================================================
// 初期化処理
//=============================================================================
void EffectManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	for (int i = 0; i < NUM_EFFECT; i++)
	{
		effectIns[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		effectIns[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(effectIns[i].getMatrixWorld());
		effectIns[i].getCollider()->initialize(device, effectIns[i].getPosition(), sphere);
		effectIns[i].setUse(false);
		effectIns[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::BULLET_EFFECT));
}
//=============================================================================
// 更新処理
//=============================================================================
void EffectManager::update(float frameTime, Player* player)
{

	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < NUM_EFFECT; i++)
	{
		if (effectIns[i].getUse() == false) { continue; }

		effectIns[i].time += frameTime;

		effectIns[i].setPosition(*effectIns[i].getPosition() + *effectIns[i].getSpeed());

		// 終了
		if (effectIns[i].time >=0.1)
		{
			effectIns[i].setUse(false);
			numOfUse--;
		}

	}
}
//=============================================================================
// 描画処理
//=============================================================================
void EffectManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (effectIns[i].getUse() == false) { continue; }

		renderList[i] = *effectIns[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// エフェクトを発生させる
//========================================================================================
void EffectManager::generateEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	int cnt = 0;


	for (int i = 0; i < NUM_EFFECT; i++)
	{
		if (effectIns[i].getUse()) { continue; }

		if (cnt < num)
		{
			// ランダムのベクトル作成
			D3DXVECTOR3 randVec(rand()%100-50, rand() % 100 - 50, rand() % 100 - 50);
			// 外積ベクトル作成
			D3DXVECTOR3 crossVec(0.0,0.0,0.0);
			// 結果ベクトル作成
			D3DXVECTOR3 resultVec(0.0, 0.0, 0.0);
			// 外積計算
			D3DXVec3Cross(&crossVec, &effectVec, &randVec);
			D3DXVec3Normalize(&crossVec, &crossVec);//正規化
			// 結果計算
			resultVec=effectVec + crossVec*0.4;
			D3DXVec3Normalize(&resultVec, &resultVec);//正規化

			effectIns[i].time = 0.0;
			effectIns[i].setPosition(positionToGenerate);
			effectIns[i].setSpeed(resultVec*( (float)(rand() % 20) /10.0f));
			D3DXMatrixIdentity(effectIns[i].getMatrixWorld());
			effectIns[i].setUse(true);
			numOfUse++;
		}
		cnt++;
	}

}
//void ChinginManager::reverseAmount()
//{
//	amount *= -1.0f;
//}

