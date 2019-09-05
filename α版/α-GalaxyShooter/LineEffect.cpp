//-----------------------------------------------------------------------------
// ラインエフェクト処理 [LineEffect.cpp]
// 製作者 飯塚春輝
//-----------------------------------------------------------------------------
#include "LineEffect.h"
//=============================================================================
// 初期化処理
//=============================================================================
void LineEffect::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	// ラインエフェクト初期化
	for (int i = 0; i < LINE_EFFECT; i++)
	{
		lineEffect[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		lineEffect[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(lineEffect[i].getMatrixWorld());
		lineEffect[i].getCollider()->initialize(device, lineEffect[i].getPosition(), sphere);
		lineEffect[i].setUse(false);
		lineEffect[i].time = 0;
	}

	numOfUse = 0;
	renderList = NULL;

	// インスタンシング初期化
	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::UP_EFFECT));
}
//=============================================================================
// 更新処理
//=============================================================================
void LineEffect::update(float frameTime)
{
	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < LINE_EFFECT; i++)
	{
		// 出ていなかったら更新しない
		if (lineEffect[i].getUse() == false) { continue; }

		// 時間をフレームに合わせる
		lineEffect[i].time += frameTime;

		// エフェクト位置更新
		lineEffect[i].setPosition(*lineEffect[i].getPosition() + *lineEffect[i].getSpeed());

		// 時間になったら終了
		if (lineEffect[i].time >= 0.2)
		{
			lineEffect[i].setUse(false);
			numOfUse--;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void LineEffect::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (lineEffect[i].getUse() == false) { continue; }

		renderList[i] = *lineEffect[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

		// インスタンシング描画
		instancingProcedure.render(device, view, projection, cameraPosition);
}
//==================================================================
// エフェクトを発生させる
//========================================================================================
void LineEffect::generateLineEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec)
{
	// エフェクトカウント初期化
	int cnt = 0;

	for (int i = 0; i < LINE_EFFECT; i++)
	{
		// エフェクトが使用されていたら入らない
		if (lineEffect[i].getUse()) { continue; }

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
			lineEffect[i].time = 0.0;
			// エフェクト位置設定
			lineEffect[i].setPosition(positionToGenerate - (effectVec * 8));
			// エフェクトスピード設定
			lineEffect[i].setSpeed(resultVec*((float)(rand() % 20) / 10.0f));
			D3DXMatrixIdentity(lineEffect[i].getMatrixWorld());
			// 使用へ
			lineEffect[i].setUse(true);
			// 使用中エフェクトカウント加算
			numOfUse++;
		}
		// エフェクトカウント加算
		cnt++;
	}
}
