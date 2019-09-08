//-----------------------------------------------------------------------------
// センサー処理 [Sensor.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "Sensor.h"
#include "BlackBoardRecognition.h"
#include <memory>
#include "AgentAI.h"

// カメラとノード間のベクトル距離とカメラとフィールド間のベクトル距離の差
// この範囲内なら球面手前側にノードもフィールドとの交点もあると見なせる
// フィーリングで決めた大体の数値
static const float ADJUST_RANGE = 10.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
Sensor::Sensor(Camera* _camera): camera(_camera)
{

}


//=============================================================================
// デストラクタ
//=============================================================================
Sensor::~Sensor(void)
{

}


//=============================================================================
// 初期化処理
//=============================================================================
void Sensor::initialize(void)
{

}


//=============================================================================
// 終了処理
//=============================================================================
void Sensor::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void Sensor::update(AgentAI* agentAI)
{
	// カメラ→注視点のベクトル
	D3DXVECTOR3 vecCameraToGaze = camera->getDirectionZ();
	D3DXVec3Normalize(&vecCameraToGaze, &vecCameraToGaze);

	// フィールド半径の二乗
	float radius2 = Map::getField()->getRadius() * Map::getField()->getRadius();

	if (recognitionBB->getPlayerState() == playerNS::SKY || recognitionBB->getPlayerState() == playerNS::FALL)
	{
		mapSensorSky();
	}
	else
	{
		mapSensor(agentAI, vecCameraToGaze, radius2);
	}
	opponentSensor(agentAI, vecCameraToGaze);
	bulletSensor(agentAI, vecCameraToGaze, radius2);
}


//=============================================================================
// マップセンサー
//=============================================================================
void Sensor::mapSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2)
{
	std::vector<MapNode*>& mapNode = Map::getMapNode();

	for (size_t i = 0; i < mapNode.size(); i++)
	{
#ifdef _DEBUG
		mapNode[i]->isRed = false;
#endif
		// 自分の反対側の半球にあるマップノードは処理せず高速化
		D3DXVECTOR3 vec = *mapNode[i]->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius2/*三平方の定理*/) { continue; }

		//----------------------------------------
		// カメラの水平視野角内に無いノードをパス
		//----------------------------------------
		// カメラ→マップノードのベクトルを求める
		D3DXVECTOR3 vecCameraToNode = *mapNode[i]->getPosition() - camera->position;
		float cameraNodeLength = D3DXVec3Length(&vecCameraToNode);// 後で使うサイズ
		D3DXVec3Normalize(&vecCameraToNode, &vecCameraToNode);
		agentAI->slip(vecCameraToNode, camera->getDirectionY());
		// 内積から角度を求めて視野角内か判定する
		float radian = acosf(D3DXVec3Dot(&vecCameraToNode, &vecCameraToGaze));
		if (radian > camera->fieldOfView / 2.0f) { continue; }
		// ↑このあたり調整すれば画面の下端ギリギリのノードとかを正確に認識させられるかもしれない

		//----------------------------------
		// 球面の向こうに隠れたノードをパス
		//----------------------------------
		ray.update(camera->position, *mapNode[i]->getPosition() - camera->position);
		if (ray.rayIntersect(*Map::getField()->getMesh(), *Map::getField()->getMatrixWorld()))
		{
			// フィールドとの距離が一定範囲内に収まっていない
			if (false == (ray.distance < cameraNodeLength + ADJUST_RANGE
				&& ray.distance >cameraNodeLength - ADJUST_RANGE))

			{
				// 場合分けすると
				// 1-フィールドがノードより手前
				//(ノードが球面の向こう)のパターン
				//(成功パターン　配置時の誤差でノード中心座標がフィールド内にめり込んでいる)
				// フィールドがノードより奥
				//(成功パターン）ノードが先のあとすぐ設置場所のフィールドに衝突している
				continue;
			}
		}

#ifdef _DEBUG
		mapNode[i]->isRed = true;
#endif

		// マップノードを認識
		std::list<MapNode*>::iterator it = std::find(recognitionBB->getMemorizedMap().begin(),
			recognitionBB->getMemorizedMap().end(), mapNode[i]);

		if (it != recognitionBB->getMemorizedMap().end())
		{
			recognitionBB->getMemorizedMap().erase(it);
		}
		recognitionBB->getMemorizedMap().push_back(mapNode[i]);
	}
}


//=============================================================================
// マップセンサー（上空モード）
//=============================================================================
void Sensor::mapSensorSky(void)
{
	std::vector<MapNode*>& mapNode = Map::getMapNode();

	// 平面の方程式を求める
	D3DXVECTOR3 nor = camera->position - *Map::getField()->getPosition();
	float d = -(nor.x * 0.0f + nor.y * 0.0f + nor.z * 0.0f);

	// カメラがある側の平面に有れば認識
	for (size_t i = 0; i < mapNode.size(); i++)
	{
#ifdef _DEBUG
		mapNode[i]->isRed = false;
#endif
		float distance = (nor.x * mapNode[i]->getPosition()->x
			+ nor.y * mapNode[i]->getPosition()->y
			+ nor.z *mapNode[i]->getPosition()->z + d);

		if (distance < 0) { continue; }

#ifdef _DEBUG
		mapNode[i]->isRed = true;
#endif
		// マップノードを認識
		std::list<MapNode*>::iterator it = std::find(recognitionBB->getMemorizedMap().begin(),
			recognitionBB->getMemorizedMap().end(), mapNode[i]);

		if (it != recognitionBB->getMemorizedMap().end())
		{
			recognitionBB->getMemorizedMap().erase(it);
		}
		recognitionBB->getMemorizedMap().push_back(mapNode[i]);
	}
}


//=============================================================================
// 対戦相手センサー
//=============================================================================
void Sensor::opponentSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze)
{
	bool isOpponentInCamera = false;
	{
		// カメラ内に（ステンシル描画も含め）相手が写っているかを判定
		D3DXVECTOR3 vecCameraToOpponent = *opponent->getPosition() - camera->position;
		D3DXVec3Normalize(&vecCameraToOpponent, &vecCameraToOpponent);
		float radian = acosf(D3DXVec3Dot(&vecCameraToOpponent, &vecCameraToGaze));
		if (radian < camera->fieldOfView / 2.0f) { isOpponentInCamera = true; }
	}
	if (isOpponentInCamera)
	{
		// 距離を更新
		D3DXVECTOR3 temp = *opponent->getPosition() - *agentAI->getPosition();
		recognitionBB->setDistanceBetweenPlayers(D3DXVec3Length(&temp));
	}
}


//=============================================================================
// バレットセンサー
//=============================================================================
void Sensor::bulletSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2)
{
	for (int i = 0; i < playerNS::NUM_BULLET; i++)
	{
		if (opponent->bullet[i].getActive() == false) { continue; }

		// 自分の反対側の半球にあるバレットは処理せず高速化
		D3DXVECTOR3 vec = *opponent->bullet->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius2/*三平方の定理*/) { continue; }

		//------------------------------------------
		// カメラの水平視野角内に無いバレットをパス
		//------------------------------------------
		// カメラ→バレットのベクトルを求める
		D3DXVECTOR3 vecCameraToBullet = *opponent->bullet[i].getPosition() - camera->position;
		float cameraBulletLength = D3DXVec3Length(&vecCameraToBullet);// 後で使うサイズ
		D3DXVec3Normalize(&vecCameraToBullet, &vecCameraToBullet);
		agentAI->slip(vecCameraToBullet, agentAI->getAxisY()->direction);
		// 内積から角度を求めて視野角内か判定する
		float radian = acosf(D3DXVec3Dot(&vecCameraToBullet, &vecCameraToGaze));
		if (radian > camera->fieldOfView / 2.0f) { continue; }

		//------------------------------------
		// 球面の向こうに隠れたバレットをパス
		//------------------------------------
		ray.update(camera->position, *opponent->bullet[i].getPosition() - camera->position);
		if (ray.rayIntersect(*Map::getField()->getMesh(), *Map::getField()->getMatrixWorld()))
		{
			if (false == (ray.distance - ADJUST_RANGE < cameraBulletLength
				&& cameraBulletLength < ray.distance + ADJUST_RANGE))
			{
				continue;
			}
		}
		 
		// バレットを認識
		std::list<Bullet*>::iterator it = std::find(recognitionBB->getMemorizedBullet().begin(),
			recognitionBB->getMemorizedBullet().end(), &opponent->bullet[i]);

		if (it != recognitionBB->getMemorizedBullet().end())
		{
			recognitionBB->getMemorizedBullet().erase(it);
		}
	
		recognitionBB->getMemorizedBullet().push_back(&opponent->bullet[i]);
	}
}