//-----------------------------------------------------------------------------
// �Z���T�[���� [Sensor.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "Sensor.h"
#include "BlackBoardRecognition.h"
#include <memory>
#include "AgentAI.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Sensor::Sensor(D3DXVECTOR3* _cameraPosition, float _cameraFieldOfView)
	: cameraPosition(_cameraPosition), cameraFieldOfView(_cameraFieldOfView)
{

}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
Sensor::~Sensor(void)
{

}


//=============================================================================
// ����������
//=============================================================================
void Sensor::initialize(void)
{
}


//=============================================================================
// �I������
//=============================================================================
void Sensor::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void Sensor::update(AgentAI* agentAI)
{
	std::vector<MapNode*>& mapNode = Map::getMapNode();

	for (size_t i = 0; mapNode.size(); i++)
	{
		// �����̔��Α��̔����ɂ���}�b�v�m�[�h�͏������Ȃ�
		float radius = Map::getField()->getRadius();
		D3DXVECTOR3 vec = *mapNode[i]->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius * radius * 2/*�O�����̒藝*/) { continue; }

		// �J�����̎���p���ɂ��邩���m
		D3DXVECTOR3 adjustDirection = agentAI->getAxisY()->direction;
		D3DXVec3Scale(&adjustDirection, &adjustDirection, len);

		Base::slip(*mapNode[i]->getPosition(), agentAI->getAxisY()->direction);
		ray.update(*getCameraPosition(), *mapNode[i]->getPosition() - *getCameraPosition());
		D3DXVec3Dot(agent->.direction
	}

	agentAI->getAxisZ()->direction - *getCameraPosition();

	
}
