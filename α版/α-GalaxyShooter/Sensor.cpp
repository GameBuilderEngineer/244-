//-----------------------------------------------------------------------------
// センサー処理 [Sensor.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "Sensor.h"
#include "BlackBoardRecognition.h"
#include <memory>
#include "AgentAI.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Sensor::Sensor(D3DXVECTOR3* _cameraPosition, float _cameraFieldOfView)
	: cameraPosition(_cameraPosition), cameraFieldOfView(_cameraFieldOfView)
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
	std::vector<MapNode*>& mapNode = Map::getMapNode();

	for (size_t i = 0; mapNode.size(); i++)
	{
		// 自分の反対側の半球にあるマップノードは処理しない
		float radius = Map::getField()->getRadius();
		D3DXVECTOR3 vec = *mapNode[i]->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius * radius * 2/*三平方の定理*/) { continue; }

		// カメラの視野角内にあるか検知
		D3DXVECTOR3 adjustDirection = agentAI->getAxisY()->direction;
		D3DXVec3Scale(&adjustDirection, &adjustDirection, len);

		Base::slip(*mapNode[i]->getPosition(), agentAI->getAxisY()->direction);
		ray.update(*getCameraPosition(), *mapNode[i]->getPosition() - *getCameraPosition());
		D3DXVec3Dot(agent->.direction
	}

	agentAI->getAxisZ()->direction - *getCameraPosition();

	
}
