//-----------------------------------------------------------------------------
// 運動生成処理 [MotionGeneration.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "MotionGeneration.h"
#include "AgentAI.h"

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
	//if (bodyBB->getIsMoving()) { agentAI->move(); }

	if (bodyBB->getJump())
	{
		bodyBB->setJump(false);
		bodyBB->setIsJumping(true);
		agentAI->jump();
	}
	if (bodyBB->getIsJumping())
	{
		//// 地上に着地していたら
		//if (agentAI->getGravityRay()->rayIntersect(*field.getMesh(), field.getMatrixWorld()))
		//{
		//	bodyBB->setIsJumping(false);
		//}
	}
}


//=============================================================================
// 移動
//=============================================================================
void MotionGeneration::move(AgentAI* agentAI, D3DXVECTOR3 targetCoord)
{
	////Y軸方向への成分を削除する
	//D3DXVECTOR3 front = slip(cameraAxisZ, axisY.direction);
	//D3DXVECTOR3 right = slip(cameraAxisX, axisY.direction);
	//D3DXVec3Normalize(&front, &front);//正規化
	//D3DXVec3Normalize(&right, &right);//正規化

	D3DXVECTOR3 moveDirection = agentAI->getGravity();
	D3DXVECTOR3 targetDirection = targetCoord - *agentAI->getPosition();
	D3DXVECTOR3 rotationAxis;
	D3DXVec3Cross(&rotationAxis, &moveDirection, &targetDirection);
	//D3DXVec3Normalize(&rotationAxis, &rotationAxis);


	D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotationMatrix;
	D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI / 2.0f);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &quaternion);
	D3DXVec3TransformCoord(&moveDirection, &moveDirection, &rotationMatrix);


	D3DXVec3Normalize(&moveDirection, &moveDirection);
	agentAI->addSpeed(moveDirection * playerNS::SPEED);
	//agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);
}
