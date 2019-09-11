//============================================================================================================================================
// Document
//============================================================================================================================================
// EffectDew.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/09/30
//============================================================================================================================================
#include "EffectDew.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace effectDewNS;

EffectDewManager::~EffectDewManager()
{
	SAFE_RELEASE(sphere)
}


//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
void EffectDewManager::initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, LPD3DXEFFECT _effect)
{
	// 当たり判定用にスフィアを作る
	D3DXCreateSphere(_device, 3.0f, 9, 9, &sphere, NULL);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effectDew[i].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		effectDew[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXMatrixIdentity(effectDew[i].getMatrixWorld());
		effectDew[i].getCollider()->initialize(_device, effectDew[i].getPosition(), sphere);
		effectDew[i].setExistenceFlag(false);
	}

	existence = 0;
	renderList = NULL;

	instancingProcedure.initialize(_device, _effect, *_textureLoader->getTexture(textureLoaderNS::EFFECT_DAMAGE));

	return;
}

//============================================================================================================================================
// update
// 更新
//============================================================================================================================================
void EffectDewManager::update(float _frameTime, Player* _player)
{
	// 使用中のエフェクトの挙動を更新する
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (effectDew[i].getExistenceFlag() == false) { continue; }

		effectDew[i].setSpeed(moveSpeed(*effectDew[i].getPosition(), *_player->getPosition()));
		effectDew[i].setPosition(*effectDew[i].getPosition() + *effectDew[i].getSpeed());

		D3DXMatrixIdentity(effectDew[i].getMatrixWorld());
		D3DXMatrixTranslation(effectDew[i].getMatrixWorld(), effectDew[i].getPosition()->x, effectDew[i].getPosition()->y, effectDew[i].getPosition()->z);

		// プレイヤーに当たったら終了
		if (effectDew[i].getCollider()->collide(_player->bodyCollide.getCenter(), _player->bodyCollide.getRadius(), *effectDew[i].getMatrixWorld(), *_player->getMatrixWorld()))
		{
			effectDew[i].setExistenceFlag(false);
			existence--;
		}
	}

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void EffectDewManager::render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPosition)
{
	// 使用中のエフェクトをインスタンシング描画に流す
	renderList = new D3DXVECTOR3[existence];

	for (int i = 0; i < existence; i++)
	{
		if (effectDew[i].getExistenceFlag() == false) { continue; }

		renderList[i] = *effectDew[i].getPosition();
	}

	instancingProcedure.setNumOfRender(_device, existence, renderList);

	SAFE_DELETE_ARRAY(renderList);

	instancingProcedure.render(_device, _view, _projection, _cameraPosition);

	return;
}
//============================================================================================================================================
// moveSpeed
// エフェクトの速度を設定
//============================================================================================================================================
D3DXVECTOR3 EffectDewManager::moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition)
{
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 moveDirection = targetPosition - position;

	D3DXVec3Normalize(&moveDirection, &moveDirection);
	speed += (moveDirection * 4.0f);

	return speed;
}
//============================================================================================================================================
// generateEffect
// エフェクトを発生させる
//============================================================================================================================================
void EffectDewManager::generateEffect(int _index, D3DXVECTOR3 _positionToGenerate)
{
	int count = 0;

	D3DXVECTOR3 newPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (effectDew[i].getExistenceFlag()) { continue; }

		if (count < _index)
		{
			newPosition.x = (_positionToGenerate.x + rand() % 20);
			newPosition.y = (_positionToGenerate.y + rand() % 20);
			newPosition.z = (_positionToGenerate.z + rand() % 20);
			effectDew[i].setPosition(newPosition);

			effectDew[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			D3DXMatrixIdentity(effectDew[i].getMatrixWorld());
			effectDew[i].setExistenceFlag(true);
			existence++;
		}
		count++;
	}

	return;
}