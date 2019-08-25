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
static const float ADJUST_RANGE = 10.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Sensor::Sensor(Camera* _camera): camera(_camera)
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
	camera->fieldOfView = D3DX_PI / 2.5f;// �Q�Ɛ�ɒl�������Ă��Ȃ����炱���œ���Ă���
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
	D3DXVECTOR3 vecCameraToGaze = camera->gazePosition - camera->position;
	D3DXVec3Normalize(&vecCameraToGaze, &vecCameraToGaze);

	// �t�B�[���h���a�̓��
	float radius2 = Map::getField()->getRadius() * Map::getField()->getRadius();

	mapSensor(agentAI, vecCameraToGaze, radius2);
	opponentSensor(agentAI, vecCameraToGaze);
	bulletSensor(agentAI, vecCameraToGaze, radius2);
}


//=============================================================================
// �}�b�v�Z���T�[
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
		D3DXVECTOR3 vecCameraToNode = *mapNode[i]->getPosition() - camera->position;
		float cameraNodeLength = D3DXVec3Length(&vecCameraToNode);// ��Ŏg���T�C�Y
		D3DXVec3Normalize(&vecCameraToNode, &vecCameraToNode);
		agentAI->slip(vecCameraToNode, camera->getDirectionY());
		// ���ς���p�x�����߂Ď���p�������肷��
		float radian = acosf(D3DXVec3Dot(&vecCameraToNode, &vecCameraToGaze));
		if (radian > camera->fieldOfView / 2.0f) { continue; }
		// �����̂����蒲������Ή�ʂ̉��[�M���M���̃m�[�h�Ƃ��𐳊m�ɔF���������邩������Ȃ�

		//----------------------------------
		// ���ʂ̌������ɉB�ꂽ�m�[�h���p�X
		//----------------------------------
		ray.update(camera->position, *mapNode[i]->getPosition() - camera->position);
		if (ray.rayIntersect(*Map::getField()->getMesh(), *Map::getField()->getMatrixWorld()))
		{
			// �t�B�[���h�Ƃ̋��������͈͓��Ɏ��܂��Ă��Ȃ�
			if (false == (ray.distance < cameraNodeLength + ADJUST_RANGE
				&& ray.distance >cameraNodeLength - ADJUST_RANGE))

			{
				// �ꍇ���������
				// 1-�t�B�[���h���m�[�h����O
				//(�m�[�h�����ʂ̌�����)�̃p�^�[��
				//(�����p�^�[���@�z�u���̌덷�Ńm�[�h���S���W���t�B�[���h���ɂ߂荞��ł���)
				// �t�B�[���h���m�[�h��艜
				//(�����p�^�[���j�m�[�h����̂��Ƃ����ݒu�ꏊ�̃t�B�[���h�ɏՓ˂��Ă���
				continue;
			}
		}

#ifdef _DEBUG
		mapNode[i]->isRed = true;
#endif

		// �}�b�v�m�[�h��F��
		std::list<MapNode*>::iterator it = std::find(recognitionBB->getMemorizedMap().begin(),
			recognitionBB->getMemorizedMap().end(), mapNode[i]);

		if (it == recognitionBB->getMemorizedMap().end())
		{
		}
		else
		{
			recognitionBB->getMemorizedMap().erase(it);
		}
		recognitionBB->getMemorizedMap().push_back(mapNode[i]);
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
		D3DXVECTOR3 vecCameraToOpponent = *opponent->getPosition() - camera->position;
		D3DXVec3Normalize(&vecCameraToOpponent, &vecCameraToOpponent);
		float radian = acosf(D3DXVec3Dot(&vecCameraToOpponent, &vecCameraToGaze));
		if (radian < camera->fieldOfView / 2.0f) { isOpponentInCamera = true; }
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
		D3DXVECTOR3 vecCameraToBullet = *opponent->bullet[i].getPosition() - camera->position;
		float cameraBulletLength = D3DXVec3Length(&vecCameraToBullet);// ��Ŏg���T�C�Y
		D3DXVec3Normalize(&vecCameraToBullet, &vecCameraToBullet);
		agentAI->slip(vecCameraToBullet, agentAI->getAxisY()->direction);
		// ���ς���p�x�����߂Ď���p�������肷��
		float radian = acosf(D3DXVec3Dot(&vecCameraToBullet, &vecCameraToGaze));
		if (radian > camera->fieldOfView / 2.0f) { continue; }

		//------------------------------------
		// ���ʂ̌������ɉB�ꂽ�o���b�g���p�X
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
		 
		// �o���b�g��F��
		std::list<Bullet*>::iterator it = std::find(recognitionBB->getMemorizedBullet().begin(),
			recognitionBB->getMemorizedBullet().end(), &opponent->bullet[i]);

		if (it == recognitionBB->getMemorizedBullet().end())
		{
		}
		else
		{
			recognitionBB->getMemorizedBullet().erase(it);
		}
		recognitionBB->getMemorizedBullet().push_back(&opponent->bullet[i]);
	}
}