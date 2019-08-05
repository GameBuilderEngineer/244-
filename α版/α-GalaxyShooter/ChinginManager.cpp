//-----------------------------------------------------------------------------
// チンギン処理 [Chingin.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/8/1
//-----------------------------------------------------------------------------
#include "ChinginManager.h"


//=============================================================================
// 初期化処理
//=============================================================================
void ChinginManager::initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect)
{
	D3DXCreateSphere(device, 3.0f, 9, 9, &sphere, NULL);	// 当たり判定用にスフィアを作る

	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		chingin[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		chingin[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(chingin[i].getMatrixWorld());
		chingin[i].getCollider()->initialize(device, chingin[i].getPosition(), sphere);
		chingin[i].setUse(false);
	}
	
	numOfUse = 0;
	renderList = NULL;

	instancingProcedure.initialize(device, effect, *_textureLoader->getTexture(textureLoaderNS::UI_GAUGE_BAR));
}


//=============================================================================
// 更新処理
//=============================================================================
void ChinginManager::update(float frameTime, Player* player)
{
	// 使用中のチンギンの挙動を更新する
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		if (chingin[i].getUse() == false) { continue; }

		chingin[i].setSpeed(moveSpeed(*chingin[i].getPosition(), *player->getPosition()));
		chingin[i].setPosition(*chingin[i].getPosition() + *chingin[i].getSpeed());

		D3DXMatrixIdentity(chingin[i].getMatrixWorld());
		D3DXMatrixTranslation(chingin[i].getMatrixWorld(),
			chingin[i].getPosition()->x, chingin[i].getPosition()->y, chingin[i].getPosition()->z);

		// プレイヤーに当たったら終了
		if (chingin[i].getCollider()->collide(
			player->bodyCollide.getCenter(), player->bodyCollide.getRadius(),
			*chingin[i].getMatrixWorld(), *player->getMatrixWorld()))
		{
			chingin[i].setUse(false);
			numOfUse--;
		}
	}
}


//=============================================================================
// 描画処理
//=============================================================================
void ChinginManager::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 使用中のチンギンをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[numOfUse];
	for (int i = 0; i < numOfUse; i++)
	{
		if (chingin[i].getUse() == false) { continue; }

		renderList[i] = *chingin[i].getPosition();
	}
	instancingProcedure.setNumOfRender(device, numOfUse, renderList);
	SAFE_DELETE_ARRAY(renderList)

	instancingProcedure.render(device, view, projection, cameraPosition);
}


//=============================================================================
// チンギンの速度を設定
//=============================================================================
D3DXVECTOR3 ChinginManager::moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition)
{
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 moveDirection = targetPosition - position;
	//float distance = D3DXVec3Length(&moveDirection);
	//float magneticeForce = (target.amount*amount) / distance;
	D3DXVec3Normalize(&moveDirection, &moveDirection);
	speed += moveDirection * 2.0f;// このへんはまだ適当

	return speed;
}


//=============================================================================
// チンギンを発生させる
//=============================================================================
void ChinginManager::generateChingin(int num, D3DXVECTOR3 positionToGenerate)
{
	int cnt = 0;
	D3DXVECTOR3 newPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		if (chingin[i].getUse()) { continue; }
		
		if (cnt < num)
		{
			newPosition.x = positionToGenerate.x + rand() % 20;
			newPosition.y = positionToGenerate.y + rand() % 20;
			newPosition.z = positionToGenerate.z + rand() % 20;
			chingin[i].setPosition(newPosition);

			chingin[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			D3DXMatrixIdentity(chingin[i].getMatrixWorld());
			chingin[i].setUse(true);
			numOfUse++;
		}
		cnt++;
	}
}


//void ChinginManager::reverseAmount()
//{
//	amount *= -1.0f;
//}

