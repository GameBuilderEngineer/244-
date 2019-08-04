//-----------------------------------------------------------------------------
// 運動生成処理 [MotionGeneration.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "MotionGeneration.h"
#include "AbstractScene.h"
#include "AgentAI.h"
#include "Map.h"// ●
#include "input.h"
using namespace MotionGenerationNS;

//=============================================================================
// コンストラクタ
//=============================================================================
MotionGeneration::MotionGeneration(void)
{

}


//=============================================================================
// デストラクタ
//=============================================================================
MotionGeneration::~MotionGeneration(void)
{

}


//=============================================================================
// 初期化処理
//=============================================================================
void MotionGeneration::initialize(void)
{
	bodyBB->setJump(true);

	memoryBB->tempRandomNode = 0;
}


//=============================================================================
// 終了処理
//=============================================================================
void MotionGeneration::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void MotionGeneration::update(AgentAI* agentAI)
{

	std::vector<MapNode*> mapNode = Map::getMapNode();
	D3DXVECTOR3 target = mapNode[memoryBB->tempRandomNode]->getPosition();

	// 移動
	if (bodyBB->getIsMoving())
	{
		move(agentAI, &target);
	}

	// ジャンプ
	jumpFlagCycle(agentAI);
}


//=============================================================================
// 移動
//=============================================================================
void MotionGeneration::move(AgentAI* agentAI, D3DXVECTOR3* targetCoord)
{
	// ターゲット座標へのベクトルからプレイヤーY軸方向の成分を削除して
	// 進行方向を指すベクトルを作る
	D3DXVECTOR3 targetDirection = *targetCoord - *agentAI->getPosition();
	D3DXVECTOR3 adjustDirection = agentAI->getAxisY()->direction;

	float adjustScale = D3DXVec3Length(&targetDirection);
	D3DXVec3Scale(&adjustDirection, &adjustDirection, adjustScale);

	D3DXVECTOR3 moveDirection = agentAI->slip(targetDirection, adjustDirection);
	D3DXVec3Normalize(&moveDirection, &moveDirection);

	//------------------------------
	// 外積とかで頑張ろうとした残骸
	//------------------------------
	//// 重力方向と目的地座標から回転軸を作成
	//D3DXVECTOR3 moveDirection = agentAI->getGravity();
	//D3DXVECTOR3 targetDirection = targetCoord - *agentAI->getPosition();
	//D3DXVECTOR3 rotationAxis;
	//D3DXVec3Cross(&rotationAxis, &moveDirection, &targetDirection);

	//// 目的地座標が真反対のときの境界条件


	//// 重力方向の移動ベクトルを軸で90度回転させる
	//D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	//D3DXMATRIX rotationMatrix;
	//D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI / 2.0f);
	//D3DXMatrixRotationQuaternion(&rotationMatrix, &quaternion);
	//D3DXVec3TransformCoord(&moveDirection, &moveDirection, &rotationMatrix);

	// 移動させる
	D3DXVec3Normalize(&moveDirection, &moveDirection);
	agentAI->addSpeed(moveDirection * playerNS::SPEED);
	agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);

	// 目的地に着いたら自動停止
	if (autoStop(agentAI->getPosition(), targetCoord))
	{
		bodyBB->setIsMoving(false);
	}
}


//=============================================================================
// 自動停止
//=============================================================================
bool MotionGeneration::autoStop(D3DXVECTOR3* position1, D3DXVECTOR3* position2)
{
	// 一番まし
	float length = D3DXVec3Length(&(*position2 - *position1));
	if (length < STOP_MOVE_LENGTH)
	{
		return true;
	}
	else
	{
		return false;
	}

	//if (	(position2->x - ADJUST < position1->x && position1->x < position2->x + ADJUST)
	//	&&	(position2->y - ADJUST < position1->y && position1->y < position2->y + ADJUST)
	//	&&	(position2->z - ADJUST < position1->z && position1->z < position2->z + ADJUST))
	//{
	//	return  true;
	//}
	//else
	//{
	//	return false;
	//}

	//int x1 = (int)position1.x;
	//int y1 = (int)position1.y;
	//int z1 = (int)position1.z;

	//int x2 = (int)position2.x;
	//int y2 = (int)position2.y;
	//int z2 = (int)position2.z;

	//if (x1 == x2 && y1 == y2 && z1 == z2)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}


//=============================================================================
// ジャンプのフラグ循環
//=============================================================================
void MotionGeneration::jumpFlagCycle(AgentAI* agentAI)
{
	// ジャンプ中でなければジャンプ命令を受け付ける
	if (bodyBB->getIsJumping() == false)
	{
		if (bodyBB->getJump())
		{
			bodyBB->setJump(false);
			bodyBB->setIsJumping(true);
			agentAI->jump();// ここでアクション
		}
	}

	// ジャンプ中の場合地上に接したタイミングでジャンプ中状態を解除する
	else
	{
		// いま空中？
		if (agentAI->getReverseAxisY()->rayIntersect(
			*Map::getField()->getMesh(), Map::getField()->getMatrixWorld()))
		{

		}
		else
		{
			bodyBB->setIsAir(true);
		}

		// 空中じゃないなら
		if (bodyBB->getIsAir() == false) return;

		// 空中なら地面に近いとジャンプ終了とみなす
		if (agentAI->getReverseAxisY()->distance < 3.0f)
		{
			bodyBB->setIsAir(false);
			bodyBB->setIsJumping(false);
		}
	}
}
