//-----------------------------------------------------------------------------
// パイルエフェクト処理 [PileEffect.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "PileEffect.h"
//=============================================================================
// 初期化処理
//=============================================================================
void PileEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	for (int i = 0; i < PILE_EFFECT; i++)
	{
		pileEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pileEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(pileEffect[i].getMatrixWorld());
		pileEffect[i].getCollider()->initialize(device, pileEffect[i].getPosition(), sphere);
		pileEffect[i].setUse(false);
		pileEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::LOSE));
}
//=============================================================================
// 更新処理
//=============================================================================
void PileEffect::update(float frameTime)
{

	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < PILE_EFFECT; i++)
	{
		if (pileEffect[i].getUse() == false) { continue; }

		pileEffect[i].time += frameTime;

		pileEffect[i].setPosition(*pileEffect[i].getPosition() + *pileEffect[i].getSpeed());


		// 終了
		if (pileEffect[i].time >= 0.05)
		{
			pileEffect[i].setUse(false);
			numOfUse--;
		}

	}
}
//=============================================================================
// 描画処理
//=============================================================================
void PileEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (pileEffect[i].getUse() == false) { continue; }

		renderList[i] = *pileEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// エフェクトを発生させる
//========================================================================================
void PileEffect::generatePileEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	int cnt = 0;


	for (int i = 0; i < PILE_EFFECT; i++)
	{
		if (pileEffect[i].getUse()) { continue; }

		if (cnt < num)
		{
			// ランダムのベクトル作成
			D3DXVECTOR3 randVec(0.0,0.0,0.0);
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

			pileEffect[i].time = 0.0;
			pileEffect[i].setPosition(positionToGenerate);
			pileEffect[i].setSpeed(resultVec);
			D3DXMatrixIdentity(pileEffect[i].getMatrixWorld());
			pileEffect[i].setUse(true);
			numOfUse++;
		}
		cnt++;
	}
}
