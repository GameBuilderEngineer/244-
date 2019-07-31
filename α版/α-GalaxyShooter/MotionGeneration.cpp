//-----------------------------------------------------------------------------
// �^���������� [MotionGeneration.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "MotionGeneration.h"
#include "AgentAI.h"
#include "Map.h"// ��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
MotionGeneration::MotionGeneration(void)
{

}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
MotionGeneration::~MotionGeneration(void)
{

}


//=============================================================================
// ����������
//=============================================================================
void MotionGeneration::initialize(void)
{

}


//=============================================================================
// �I������
//=============================================================================
void MotionGeneration::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void MotionGeneration::update(AgentAI* agentAI)
{
	std::vector<MapNode*> mapNode = Map::getMapNode();
	D3DXVECTOR3 target = mapNode[5]->getPosition();
	move(agentAI, target);
	// �Ղ�Ղ锭��

	if (bodyBB->getJump())
	{
		bodyBB->setJump(false);
		bodyBB->setIsJumping(true);
		agentAI->jump();
	}
	//if (bodyBB->getIsJumping())
	//{
	//	// �n��ɒ��n���Ă�����
	//	if (agentAI->getGravityRay()->rayIntersect(*field.getMesh(), field.getMatrixWorld()))
	//	{
	//		bodyBB->setIsJumping(false);
	//	}
	//}
}


//=============================================================================
// �ړ�
//=============================================================================
void MotionGeneration::move(AgentAI* agentAI, D3DXVECTOR3 targetCoord)
{
	////Y�������ւ̐������폜����
	//D3DXVECTOR3 front = slip(cameraAxisZ, axisY.direction);
	//D3DXVECTOR3 right = slip(cameraAxisX, axisY.direction);
	//D3DXVec3Normalize(&front, &front);//���K��
	//D3DXVec3Normalize(&right, &right);//���K��

	// �d�͕����ƖړI�n���W�����]�����쐬
	D3DXVECTOR3 moveDirection = agentAI->getGravity();
	D3DXVECTOR3 targetDirection = targetCoord - *agentAI->getPosition();
	D3DXVECTOR3 rotationAxis;
	D3DXVec3Cross(&rotationAxis, &moveDirection, &targetDirection);

	// �d�͕����̈ړ��x�N�g��������90�x��]������
	D3DXQUATERNION quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotationMatrix;
	D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI / 2.0f);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &quaternion);
	D3DXVec3TransformCoord(&moveDirection, &moveDirection, &rotationMatrix);

	// �ړ�������
	D3DXVec3Normalize(&moveDirection, &moveDirection);
	agentAI->addSpeed(moveDirection * playerNS::SPEED);
	agentAI->postureControl(agentAI->getAxisZ()->direction, moveDirection, 0.1f);
}
