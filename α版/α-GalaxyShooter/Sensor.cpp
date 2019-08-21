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
static const float ADUST_RANGE = 5.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
Sensor::Sensor(D3DXVECTOR3* _cameraPosition, D3DXVECTOR3* _gazePosition, float* _cameraFieldOfView)
	: cameraPosition(_cameraPosition), cameraGazePosition(_gazePosition), cameraFieldOfView(_cameraFieldOfView)
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
	*cameraFieldOfView = D3DX_PI / 2.5f;
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
	D3DXVECTOR3 vecCameraToGaze = *cameraGazePosition - *cameraPosition;
	D3DXVec3Normalize(&vecCameraToGaze, &vecCameraToGaze);

	// フィールド半径の二乗
	float radius2 = Map::getField()->getRadius() * Map::getField()->getRadius();

	mapSensor(agentAI, vecCameraToGaze, radius2);
	opponentSensor(agentAI, vecCameraToGaze);
	bulletSensor(agentAI, vecCameraToGaze, radius2);

	// HP
	opponent->getHp();
	// 落下中
	opponent->whetherFall();
	// ダウン
	opponent->whetherDown();
	// 上空モードに入っている
	opponent->whetherSky();
	// メモリーパイルの設置数

	// 衝撃波が来る

}


//=============================================================================
// マップセンサー（ワスレモノセンサー）
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
		D3DXVECTOR3 vecCameraToNode = *mapNode[i]->getPosition() - *getCameraPosition();
		float cameraNodeLength = D3DXVec3Length(&vecCameraToNode);// 後で使うサイズ
		D3DXVec3Normalize(&vecCameraToNode, &vecCameraToNode);
		agentAI->slip(vecCameraToNode, agentAI->getAxisY()->direction);
		// 内積から角度を求めて視野角内か判定する
		float radian = acosf(D3DXVec3Dot(&vecCameraToNode, &vecCameraToGaze));
		if (radian > *cameraFieldOfView / 2.0f) { continue; }

		//----------------------------------
		// 球面の向こうに隠れたノードをパス
		//----------------------------------
		ray.update(*getCameraPosition(), *mapNode[i]->getPosition() - *getCameraPosition());
		if (ray.rayIntersect(*Map::getField()->getMesh(), *Map::getField()->getMatrixWorld()))
		{
			if (false == (ray.distance - ADUST_RANGE < cameraNodeLength
				&& cameraNodeLength < ray.distance + ADUST_RANGE)) {
				continue;
			}
		}
#ifdef _DEBUG
		mapNode[i]->isRed = true;
#endif
		//recognitionBB->getMemorizedMap().push_back(mapNode[i]);// ここでマップノードを認識！
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
		D3DXVECTOR3 vecCameraToOpponent = *opponent->getPosition() - *getCameraPosition();
		D3DXVec3Normalize(&vecCameraToOpponent, &vecCameraToOpponent);
		float radian = acosf(D3DXVec3Dot(&vecCameraToOpponent, &vecCameraToGaze));
		if (radian < *cameraFieldOfView / 2.0f) { isOpponentInCamera = true; }
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
		D3DXVECTOR3 vecCameraToBullet = *opponent->bullet[i].getPosition() - *getCameraPosition();
		float cameraBulletLength = D3DXVec3Length(&vecCameraToBullet);// 後で使うサイズ
		D3DXVec3Normalize(&vecCameraToBullet, &vecCameraToBullet);
		agentAI->slip(vecCameraToBullet, agentAI->getAxisY()->direction);
		// 内積から角度を求めて視野角内か判定する
		float radian = acosf(D3DXVec3Dot(&vecCameraToBullet, &vecCameraToGaze));
		if (radian > *cameraFieldOfView / 2.0f) { continue; }

		//------------------------------------
		// 球面の向こうに隠れたバレットをパス
		//------------------------------------
		ray.update(*getCameraPosition(), *opponent->bullet[i].getPosition() - *getCameraPosition());
		if (ray.rayIntersect(*Map::getField()->getMesh(), *Map::getField()->getMatrixWorld()))
		{
			if (false == (ray.distance - ADUST_RANGE < cameraBulletLength
				&& cameraBulletLength < ray.distance + ADUST_RANGE))
			{
				continue;
			}
		}
		 
		//opponent->bullet[i].setSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//recognitionBB->
	}
}