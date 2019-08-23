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
	}

	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::HP_EFFECT));
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

		effectIns[i].setSpeed(moveSpeed(*effectIns[i].getPosition(), *player->getPosition()));
		effectIns[i].setPosition(*effectIns[i].getPosition() + *effectIns[i].getSpeed());

		D3DXMatrixIdentity(effectIns[i].getMatrixWorld());
		D3DXMatrixTranslation(effectIns[i].getMatrixWorld(),
			effectIns[i].getPosition()->x, effectIns[i].getPosition()->y, effectIns[i].getPosition()->z);

		// プレイヤーに当たったら終了
		if (effectIns[i].getCollider()->collide(
			player->bodyCollide.getCenter(), player->bodyCollide.getRadius(),
			*effectIns[i].getMatrixWorld(), *player->getMatrixWorld()))
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
//=============================================================================
// エフェクトの速度を設定
//=============================================================================
D3DXVECTOR3 EffectManager::moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition)
{
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 moveDirection = targetPosition - position;
	//float distance = D3DXVec3Length(&moveDirection);
	//float magneticeForce = (target.amount*amount) / distance;
	D3DXVec3Normalize(&moveDirection, &moveDirection);
	speed += moveDirection * 4.0f;// このへんはまだ適当

	return speed;
}
//=============================================================================
// エフェクトを発生させる
//=============================================================================
void EffectManager::generateEffect(int num, D3DXVECTOR3 positionToGenerate)
{
	int cnt = 0;
	D3DXVECTOR3 newPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < NUM_EFFECT; i++)
	{
		if (effectIns[i].getUse()) { continue; }

		if (cnt < num)
		{
			newPosition.x = positionToGenerate.x + rand() % 20;
			newPosition.y = positionToGenerate.y + rand() % 20;
			newPosition.z = positionToGenerate.z + rand() % 20;
			effectIns[i].setPosition(newPosition);

			effectIns[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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

