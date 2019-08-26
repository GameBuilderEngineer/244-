//-----------------------------------------------------------------------------
// ����͏��� [EnvironmentAnalysis.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "EnvironmentAnalysis.h"
#include "AgentAI.h"
#include "Map.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
EnvironmentAnalysis::EnvironmentAnalysis(std::vector<Wasuremono*>* _wasuremono): wasuremono(_wasuremono)
{
	recursionSphere = NULL;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
EnvironmentAnalysis::~EnvironmentAnalysis(void)
{
	SAFE_DELETE(recursionSphere)
}


//=============================================================================
// ����������
//=============================================================================
void EnvironmentAnalysis::initialize(void)
{
	mapTimeCount = 0;
	forgettingTimeMap = 0;
	bulletTimeCount = 0;
	forgettingTimeBullet = 0;
}


//=============================================================================
// �I������
//=============================================================================
void EnvironmentAnalysis::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void EnvironmentAnalysis::update(AgentAI* agentAI)
{
	//static int cnt = 0;// ����
	//if (++cnt % 10 == 0)
	//{
	//	cnt = 0;
	//	virtualRecursion(agentAI);
	//}

	forgetMemorizedMatter();
}


//=============================================================================
// ���z���J�[�W����
//=============================================================================
void EnvironmentAnalysis::virtualRecursion(AgentAI* agentAI)
{
	static const int NUM_NEARLEST_NODE = 3;					// ���J�[�W�����͈͂𒲂ׂ�}�b�v�m�[�h�̌�␔
	static const int NUM_TEST_SIZE = 3;						// ���J�[�W�����̑傫���iBS�̃T�C�Y�j�̐�
	static const int NUM_TEST_ARROUND = 5;					// �P�̃m�[�h�̎��͂�BS�𓖂Ă�ӏ��̐�
	static const int NUM_TEST_ZONE = NUM_TEST_ARROUND + 1;	
	static const int NUM_TEMP_RECOGNITION = NUM_NEARLEST_NODE * NUM_TEST_SIZE* NUM_TEST_ZONE;

	// �ȉ��̏����Ńx�N�g�������낢���]������̂Ɏg�p
	D3DXQUATERNION quaternion;
	D3DXQuaternionIdentity(&quaternion);
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

	//------------------------------
	// �߂��}�b�v�m�[�h�Ō����i��
	//------------------------------
	std::list<MapNode*> nodeList = recognitionBB->getMemorizedMap();
	std::list<MapNode*>::iterator itr;
	float shortestLen = 1000.0f;
	std::list<MapNode*>::iterator nearestNode[NUM_NEARLEST_NODE]; // �C�e���[�^�z��
	int element = 0;		// �C�e���[�^�z��index
	int numNearestNode = 0;	// �C�e���[�^�z�񂪂������܂������J�E���g
	for (itr = nodeList.begin(); itr != nodeList.end(); itr++)
	{
		D3DXVECTOR3* nodePosition = (*itr)->getPosition();
		float tempLen = D3DXVec3LengthSq(&(*nodePosition - *agentAI->getPosition()));
		if (tempLen < shortestLen)
		{
			shortestLen = tempLen;
			nearestNode[element] = itr;
			if (++element == NUM_NEARLEST_NODE) element = 0;
			if (++numNearestNode > NUM_NEARLEST_NODE) numNearestNode = NUM_NEARLEST_NODE;
		}
	}

	//------------------------------------------------------------------------
	// ���̃m�[�h�t�߂ɃT�C�Y��ς��Ȃ���o�E���f�B���O�X�t�B�A�𓖂Ă܂���
	// ���X�����m��z��`���M���z�Ƃ��̂Ƃ��̃X�t�B�A�̃p�����[�^��ۊǂ���
	//------------------------------------------------------------------------
	RecursionRecognition recursionRecognition[NUM_TEMP_RECOGNITION];	// �ۊǐ�
	int index = 0;														// �ۊǐ�z��index
	for (int cntNode = 0; cntNode < numNearestNode; cntNode++)
	{
		for (int cntSize = 0; cntSize < NUM_TEST_SIZE; cntSize++)
		{
			// ���J�[�W�����`�F�b�N�p�X�t�B�A�𐶐�
			recursionRadius = 10.0f + cntSize * 8.0f;// �������͒��� 
			recursionSphere = new BoundingSphere;
			recursionSphere->initialize(device, recursionRadius);

			// �܂��m�[�h�̈ʒu�҂�����ŏՓ˔���
			recognizeRecursionArea(agentAI, (*nearestNode[cntNode])->getPosition(), &recursionRecognition[index++]);
			
			// ���Ƀm�[�h�̎��͂��񂵂Ȃ���Փ˔�����s��������
			// ���̂��߂ɘf�����S�̃m�[�h�Ԃ̃��C�������X����
			ray.update(*Map::getField()->getPosition(), *(*nearestNode[cntNode])->getPosition() - *Map::getField()->getPosition());
			D3DXVECTOR3 axisToMakeDegree = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.1f);// �������͒���
			D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
			D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);

			// �X���Ă��郌�C����]���ŉ񂵂Ȃ��烌�C�̐�[��BS�̏Փ˔���
			D3DXVECTOR3 rotationAxis = *(*nearestNode[cntNode])->getPosition() - *Map::getField()->getPosition();
			D3DXQuaternionIdentity(&quaternion);
			D3DXMatrixIdentity(&worldMatrix);
			for (int cntZone = 0; cntZone < NUM_TEST_ARROUND; cntZone++)
			{
				D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI * 2 / NUM_TEST_ARROUND);
				D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
				D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);
				recognizeRecursionArea(agentAI, &ray.direction, &recursionRecognition[index++]);
			}
			SAFE_DELETE(recursionSphere);
		}
	}
	
	//----------------------------
	// ���J�[�W�����F���̐����i��
	//----------------------------
	int selectionRecognition[NUM_RECURSION_RECOGNITION] = { 0 };
	float largestWeight = 0.0f;
	int selectionIndex = 0;
	for (int i = 0; i < NUM_TEMP_RECOGNITION; i++)
	{
		// �t�@�W�[���_�łǂ̔F�����̗p���邩�d�݂Â�
		float radiusSizeSmall = fuzzy.reverseGrade(recursionRecognition->radius, 3.0f, 15.0f);
		float littleAmount = fuzzy.reverseGrade(recursionRecognition->totalAmount, 5.0f, 70.0f);
		float demerit = fuzzy.OR(radiusSizeSmall, littleAmount);
		float radiusSizeBig = fuzzy.grade(recursionRecognition->radius, 12.0f, 34.0f);
		float lotAmount = fuzzy.grade(recursionRecognition->totalAmount, 50.0f, 300.0f);
		float merit = fuzzy.OR(radiusSizeBig, lotAmount);
		recursionRecognition->fuzzySelectionWeight = fuzzy.grade(fuzzy.NOT(demerit) + merit, 0.0f, 2.0f);// �ŏI�I�ȏd��

		// �d�݂̑傫���F������I�����Ă���
		for (int k = 0; k < NUM_RECURSION_RECOGNITION; k++)
		{
			if (recursionRecognition->fuzzySelectionWeight > largestWeight)
			{
				largestWeight = recursionRecognition->fuzzySelectionWeight;
				selectionRecognition[selectionIndex] = i;
				if (selectionIndex++ >= NUM_RECURSION_RECOGNITION) element = 0;
			}
		}
	}

	//------------------------------------
	// �������[�p�C����ł����ލ��W�����
	//------------------------------------
	// �A���S���Y���l�Ē�
	// ���͎v�����Ȃ��̂łƂ肠�������܊p�`�ɂ��Ƃ�
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		// �ʓx�@�ł͒��S�p = ���������a
		float angle = recursionRecognition[selectionRecognition[i]].radius / Map::getField()->getRadius();

		// �f�����S�̃��J�[�W�����F�����S���W�̃��C�����߂����S�p�������X����
		D3DXQuaternionIdentity(&quaternion);
		D3DXMatrixIdentity(&worldMatrix);
		D3DXVECTOR3 axisForTilt = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXQuaternionRotationAxis(&quaternion, &axisForTilt, angle);
		ray.update(*Map::getField()->getPosition(),
			recursionRecognition[selectionRecognition[i]].center - *Map::getField()->getPosition());
		D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
		D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);

		// �X���Ă��郌�C����]���ŉ񂵂Ȃ��烌�C�̐�[�̍��W���p�C����ł��W�Ƃ��ċL�^����
		D3DXQuaternionIdentity(&quaternion);
		D3DXMatrixIdentity(&worldMatrix);
		D3DXVECTOR3 rotationAxis = recursionRecognition[selectionRecognition[i]].center - *Map::getField()->getPosition();
		D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI * 2 / 5/*�p�C���̐�������5*/);
		D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
		for (int k = 0; k < 5; k++)
		{
			D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);
			recursionRecognition[selectionRecognition[i]].pilePosition[k] = ray.direction;
		}
	}

	// ���F���u���b�N�{�[�h�Ƀt�B�[�h�o�b�N
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		recognitionBB->getRecursionRecognition()[i] = recursionRecognition[selectionRecognition[i]];
	}
}


//=============================================================================
// ���J�[�W�����F���ւ̑���i�X�t�B�A�ƃ��X�����m�̏Փ˔��肪��j
//=============================================================================
void EnvironmentAnalysis::recognizeRecursionArea(AgentAI* agentAI, D3DXVECTOR3* checkPosition, RecursionRecognition* recursionRecognition)
{
	recursionRecognition->center = *checkPosition;
	recursionRecognition->totalHit = 0;
	recursionRecognition->totalAmount = 0;
	recursionRecognition->radius = recursionSphere->getRadius();

	D3DXMATRIX recursionWorldMatrix;
	D3DXMatrixIdentity(&recursionWorldMatrix);
	D3DXMatrixTranslation(&recursionWorldMatrix, checkPosition->x, checkPosition->y, checkPosition->z);

	// �t�B�[���h���a�̓��
	float radius2 = Map::getField()->getRadius() * Map::getField()->getRadius();

	// �o�E���f�B���O�X�t�B�A�ƃ��X�����m�̏Փ˔���
	for (size_t i = 0; i < wasuremono->size(); i++)
	{
		// �����̔��Α��̔����ɂ��郏�X�����m�͔�΂��Ă�����ƍ�����
		D3DXVECTOR3 vec = *(*wasuremono)[i]->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius2/*�O�����̒藝*/) { continue; }

		if (recursionSphere->collide(*(*wasuremono)[i]->getPosition(),
			(*wasuremono)[i]->getRadius(), recursionWorldMatrix, *(*wasuremono)[i]->getMatrixWorld()))
		{
			recursionRecognition->totalHit++;
			recursionRecognition->totalAmount += (float)(*wasuremono)[i]->getAmount();
			recursionRecognition->wasuremonoInArea.push_back((*wasuremono)[i]);
		}
	}
}


//=============================================================================
// �L��������Y�p
//=============================================================================
void EnvironmentAnalysis::forgetMemorizedMatter(void)
{
	if (recognitionBB->getMemorizedMap().size() != 0)
	{
		mapTimeCount++;
		forgettingTimeMap = 60/*FPS*/ * 15/*�b*/ / recognitionBB->getMemorizedMap().size();
		if (mapTimeCount > forgettingTimeMap)
		{
			recognitionBB->getMemorizedMap().pop_front();
			mapTimeCount = 0;
		}
	}

	if (recognitionBB->getMemorizedBullet().size() != 0)
	{
		bulletTimeCount++;
		forgettingTimeBullet = 60/*FPS*/ * 4/*�b*/ / recognitionBB->getMemorizedBullet().size();
		if (bulletTimeCount > forgettingTimeBullet)
		{
			recognitionBB->getMemorizedBullet().pop_front();
			bulletTimeCount = 0;
		}
	}
}

