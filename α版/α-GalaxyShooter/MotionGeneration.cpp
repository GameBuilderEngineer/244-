//-----------------------------------------------------------------------------
// 運動生成処理 [MotionGeneration.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "MotionGeneration.h"
#include "AbstractScene.h"
#include "AgentAI.h"
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
	// 移動
	if (bodyBB->getMove())
	{
		move(agentAI, bodyBB->getMovingDestination());
	}

	// ジャンプ
	if (bodyBB->getJump())
	{
		agentAI->jump();
	}

	// バレットを打つ
	if (bodyBB->getShootingBullet())
	{
		agentAI->shootBullet(bodyBB->getTargetCoordValue());
	}

	// メモリーパイルの設置
	if (bodyBB->getLocatingPile())
	{
		agentAI->locateMemoryPile();
	}

	// フラグのリセット
	bodyBB->setMove(false);
	bodyBB->setJump(false);				//（これが無くても別フラグで止まる）
	bodyBB->setShootingBullet(false);
	bodyBB->setLocatingPile(false);
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
	agentAI->addSpeed(moveDirection * bodyBB->getSpeed());
	agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);
}
