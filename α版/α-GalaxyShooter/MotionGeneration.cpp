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
	bodyBB->setMovingDestination(&D3DXVECTOR3(100.0f, 0.0f, 0.0f));
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
	bodyBB->movingDestination = Map::getMapNode()[20]->getPosition();
	bodyBB->setMove(true);

	// 移動
	if (bodyBB->getMove())
	{
		move(agentAI, bodyBB->getMovingDestination());
	}

	//// ジャンプ
	//jumpFlagCycle(agentAI);
}


//=============================================================================
// 移動
//=============================================================================
void MotionGeneration::move(AgentAI* agentAI, D3DXVECTOR3* movingDestination)
{
	// ターゲット座標へのベクトルからプレイヤーY軸方向の成分を削除して
	// 進行方向を指すベクトルを作る
	D3DXVECTOR3 targetDirection = *movingDestination - *agentAI->getPosition();
	D3DXVECTOR3 adjustDirection = agentAI->getAxisY()->direction;

	float adjustScale = D3DXVec3Length(&targetDirection);
	D3DXVec3Scale(&adjustDirection, &adjustDirection, adjustScale);

	D3DXVECTOR3 moveDirection = agentAI->slip(targetDirection, adjustDirection);
	D3DXVec3Normalize(&moveDirection, &moveDirection);

	// 移動させる
	agentAI->addSpeed(moveDirection * playerNS::SPEED);
	agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);

	//// 目的地に着いたら自動停止
	//if (autoStop(agentAI->getPosition(), movingDestination))
	//{
	//	bodyBB->setMove(false);
	//}
}


//=============================================================================
// 自動停止
//=============================================================================
bool MotionGeneration::autoStop(D3DXVECTOR3* position1, D3DXVECTOR3* position2)
{
	float length = D3DXVec3Length(&(*position2 - *position1));
	if (length < STOP_MOVE_LENGTH)
	{
		return true;
	}
	else
	{
		return false;
	}
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
			*Map::getField()->getMesh(), *Map::getField()->getMatrixWorld()))
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
