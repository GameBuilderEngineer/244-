//-----------------------------------------------------------------------------
// �Z���T�[���� [Sensor.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "Sensor.h"
#include "BlackBoardRecognition.h"
#include <memory>
#include "AgentAI.h"

// �J�����ƃm�[�h�Ԃ̃x�N�g�������ƃJ�����ƃt�B�[���h�Ԃ̃x�N�g�������̍�
// ���͈͓̔��Ȃ狅�ʎ�O���Ƀm�[�h���t�B�[���h�Ƃ̌�_������ƌ��Ȃ���
// �t�B�[�����O�Ō��߂���̂̐��l
static const float ADUST_RANGE = 5.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Sensor::Sensor(D3DXVECTOR3* _cameraPosition, D3DXVECTOR3* _gazePosition, float* _cameraFieldOfView)
	: cameraPosition(_cameraPosition), cameraGazePosition(_gazePosition), cameraFieldOfView(_cameraFieldOfView)
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
	*cameraFieldOfView = D3DX_PI / 2.5f;
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
	// �J�����������_�̃x�N�g��
	D3DXVECTOR3 vecCameraToGaze = *cameraGazePosition - *cameraPosition;
	D3DXVec3Normalize(&vecCameraToGaze, &vecCameraToGaze);

	// �t�B�[���h���a�̓��
	float radius2 = Map::getField()->getRadius() * Map::getField()->getRadius();

	mapSensor(agentAI, vecCameraToGaze, radius2);
	opponentSensor(agentAI, vecCameraToGaze);
	bulletSensor(agentAI, vecCameraToGaze, radius2);

	// HP
	opponent->getHp();
	// ������
	opponent->whetherFall();
	// �_�E��
	opponent->whetherDown();
	// ��󃂁[�h�ɓ����Ă���
	opponent->whetherSky();
	// �������[�p�C���̐ݒu��

	// �Ռ��g������

}


//=============================================================================
// �}�b�v�Z���T�[�i���X�����m�Z���T�[�j
//=============================================================================
void Sensor::mapSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2)
{
	std::vector<MapNode*>& mapNode = Map::getMapNode();

	for (size_t i = 0; i < mapNode.size(); i++)
	{
#ifdef _DEBUG
		mapNode[i]->isRed = false;
#endif
		// �����̔��Α��̔����ɂ���}�b�v�m�[�h�͏�������������
		D3DXVECTOR3 vec = *mapNode[i]->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius2/*�O�����̒藝*/) { continue; }

		//----------------------------------------
		// �J�����̐�������p���ɖ����m�[�h���p�X
		//----------------------------------------
		// �J�������}�b�v�m�[�h�̃x�N�g�������߂�
		D3DXVECTOR3 vecCameraToNode = *mapNode[i]->getPosition() - *getCameraPosition();
		float cameraNodeLength = D3DXVec3Length(&vecCameraToNode);// ��Ŏg���T�C�Y
		D3DXVec3Normalize(&vecCameraToNode, &vecCameraToNode);
		agentAI->slip(vecCameraToNode, agentAI->getAxisY()->direction);
		// ���ς���p�x�����߂Ď���p�������肷��
		float radian = acosf(D3DXVec3Dot(&vecCameraToNode, &vecCameraToGaze));
		if (radian > *cameraFieldOfView / 2.0f) { continue; }

		//----------------------------------
		// ���ʂ̌������ɉB�ꂽ�m�[�h���p�X
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
		//recognitionBB->getMemorizedMap().push_back(mapNode[i]);// �����Ń}�b�v�m�[�h��F���I
	}
}


//=============================================================================
// �ΐ푊��Z���T�[
//=============================================================================
void Sensor::opponentSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze)
{
	bool isOpponentInCamera = false;
	{
		// �J�������Ɂi�X�e���V���`����܂߁j���肪�ʂ��Ă��邩�𔻒�
		D3DXVECTOR3 vecCameraToOpponent = *opponent->getPosition() - *getCameraPosition();
		D3DXVec3Normalize(&vecCameraToOpponent, &vecCameraToOpponent);
		float radian = acosf(D3DXVec3Dot(&vecCameraToOpponent, &vecCameraToGaze));
		if (radian < *cameraFieldOfView / 2.0f) { isOpponentInCamera = true; }
	}
	if (isOpponentInCamera)
	{
		// �������X�V
		D3DXVECTOR3 temp = *opponent->getPosition() - *agentAI->getPosition();
		recognitionBB->setDistanceBetweenPlayers(D3DXVec3Length(&temp));
	}
}


//=============================================================================
// �o���b�g�Z���T�[
//=============================================================================
void Sensor::bulletSensor(AgentAI* agentAI, D3DXVECTOR3 vecCameraToGaze, float radius2)
{
	for (int i = 0; i < playerNS::NUM_BULLET; i++)
	{
		if (opponent->bullet[i].getActive() == false) { continue; }

		// �����̔��Α��̔����ɂ���o���b�g�͏�������������
		D3DXVECTOR3 vec = *opponent->bullet->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius2/*�O�����̒藝*/) { continue; }

		//------------------------------------------
		// �J�����̐�������p���ɖ����o���b�g���p�X
		//------------------------------------------
		// �J�������o���b�g�̃x�N�g�������߂�
		D3DXVECTOR3 vecCameraToBullet = *opponent->bullet[i].getPosition() - *getCameraPosition();
		float cameraBulletLength = D3DXVec3Length(&vecCameraToBullet);// ��Ŏg���T�C�Y
		D3DXVec3Normalize(&vecCameraToBullet, &vecCameraToBullet);
		agentAI->slip(vecCameraToBullet, agentAI->getAxisY()->direction);
		// ���ς���p�x�����߂Ď���p�������肷��
		float radian = acosf(D3DXVec3Dot(&vecCameraToBullet, &vecCameraToGaze));
		if (radian > *cameraFieldOfView / 2.0f) { continue; }

		//------------------------------------
		// ���ʂ̌������ɉB�ꂽ�o���b�g���p�X
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