//-----------------------------------------------------------------------------
// ����͏��� [EnvironmentAnalysis.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "EnvironmentAnalysis.h"
#include "AgentAI.h"
#include "Map.h"
using namespace EnvilonmentAnalysisNs;

//----------------
// �r���h�X�C�b�`
//----------------
#ifdef _DEBUG
#if 0
#define DUMP_RECUASION_AREA		// ���J�[�W�����G���A�f�[�^���_���v����
static FILE* fp = NULL;
#endif 

#if 0
#define DUMP_FUZZY_RECOGNITION	// ���J�[�W�����F���̐����i��t�@�W�[�f�[�^���G���A�ʂɃ_���v����
static FILE* fp2 = NULL;
#endif

#if 0	// �f�o�b�O�`�悷��ꍇ��1�i�X�V������`�揈���Ŏ��s���邱�ƂɂȂ�̂Œ��Ӂj					
#define AI_RENDER_MODE
#endif

// �f�o�b�O�`�悪�L���̏ꍇ
#ifdef AI_RENDER_MODE

#if 1
#define RENDER_LINE_CUT_POINT	// �������[���C���ؒf���W��`�悷��
static LPD3DXMESH cutPoint = NULL;
static D3DMATERIAL9 cutPointMat;
#endif

#if 0
#define RENDER_RECUASION_AREA	// ���J�[�W�����G���A���o�X�t�B�A��`�悷��
static BoundingSphere spherePoint;
#endif

#if 0
#define RENDER_PILE_POINT		// �p�C���ݒu���W��`�悷��
static LPD3DXMESH pilePoint = NULL;
static D3DMATERIAL9 pointMat;
#endif

#endif// AI_RENDER_MODE
#endif// _DEBUG


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

	vRecursionFrameCount = 0;

#ifdef RENDER_RECUASION_AREA
	spherePoint.initialize(device, 1.0f);
#endif

#ifdef RENDER_PILE_POINT
	D3DXCreateSphere(device, 1.0f, 5, 5, &pilePoint, NULL);
	// �m�[�h�̕\���}�[�N�p���b�V���̃}�e���A��
	// ���C�g�͐؂�̂�Diffuse, Ambient�͕s���������ł悢
	pointMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Emissive = { 1.0f, 0.0f, 1.0f, 1.0f };	// ��
#endif

#ifdef RENDER_LINE_CUT_POINT
	D3DXCreateSphere(device, 1.0f, 5, 5, &cutPoint, NULL);
	// �m�[�h�̕\���}�[�N�p���b�V���̃}�e���A��
	// ���C�g�͐؂�̂�Diffuse, Ambient�͕s���������ł悢
	cutPointMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	cutPointMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	cutPointMat.Emissive = { 1.0f, 1.0f, 0.0f, 1.0f };// ��
#endif
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
#ifdef AI_RENDER_MODE
	return;
#endif //AI_RENDER_MODE

	analyzeBattle(agentAI);			// �o�g���󋵂����

	//makeCoordForCut(agentAI);		// �������[���C���ؒf���W���Z�o

	if (++vRecursionFrameCount % VIRTUAL_RECURSION_FPS == 0)
	{
		virtualRecursion(agentAI);	// ���z���J�[�W����

		vRecursionFrameCount = 0;
	}

	forgetMemorizedMatter();		// �L��������Y�p
}


//=============================================================================
// �o�g���󋵂����
//=============================================================================
void EnvironmentAnalysis::analyzeBattle(AgentAI* agentAI)
{
	//--------------
	// ����Ƃ̋���
	//--------------
	float lengthBetweenPlayers = D3DXVec3Length(&(*opponent->getPosition() - *agentAI->getPosition()));
	float opponentNearSet = fuzzy.reverseGrade(lengthBetweenPlayers, 0.0f, LENGTH_OPPONENT_IS_NEAR);
	if (opponentNearSet > 0.5f/*�A�o�E�g*/)
	{
		isOpponentNear = true; 
	}
	else
	{
		isOpponentNear = false;
	}


	//----------------
	// �o���b�g�̉��
	//----------------
	std::list<Bullet*> bulletList = recognitionBB->getMemorizedBullet();
	std::list<Bullet*>::iterator itr;
	int cntHostileBullet = 0;				// �G���o���b�g�̐�
	int cntCloseDistance = 0;				// �G�����ߋ����o���b�g�̐�	

	for (itr = bulletList.begin(); itr != bulletList.end(); itr++)
	{
		D3DXVECTOR3 vecBulletToAgent;		// �o���b�g�̎����̃x�N�g��
		D3DXVECTOR3 slipVecBulletToAgent;	// �o���b�g�̎����̊���x�N�g��
		D3DXVECTOR3 slipvecBulletSpeed;		// �o���b�g�̃X�s�[�h�̊���x�N�g��
		float dintanceToBullet;				// �o���b�g�Ƃ̋���
		bool isHostile = false;				// �G���o���b�g�ł��邩

		// �����̃o���b�g�̃x�N�g�����Z�o
		vecBulletToAgent = *agentAI->getPosition() - *(*itr)->getPosition();
		dintanceToBullet = D3DXVec3Length(&vecBulletToAgent);	// ������ۊ�

		// �X���b�v
		slipVecBulletToAgent = slip(vecBulletToAgent, (*itr)->getAxisY()->direction);
		D3DXVec3Normalize(&slipvecBulletSpeed, &vecBulletToAgent);

		// �����̕����Ɍ������Ă���Ȃ�G���o���b�g�ł���
		slipvecBulletSpeed = slip((*itr)->getSpeed(), (*itr)->getAxisY()->direction);
		D3DXVec3Normalize(&slipvecBulletSpeed, &slipvecBulletSpeed);
		float dot = D3DXVec3Dot(&slipvecBulletSpeed, &slipVecBulletToAgent);
		float angleDifferenceForHit = acosf(dot);
		if (angleDifferenceForHit < D3DXToRadian(BULLET_TWO_VECTOR_ANGLE_DEGREE))
		{
			isHostile = true;
			cntHostileBullet++;
		}

		// �G���o���b�g�̋��������ߋ�����
		if (isHostile && dintanceToBullet < LENGHT_BULLET_IS_NEAR)
		{
			cntCloseDistance++;
		}
	}

	if (cntCloseDistance > 0) { isBulletNear = true; }
	float hostileBulletSet = fuzzy.grade((float)cntHostileBullet, 2.0f, 5.0f);


	//----------------
	// ����̍U���ӗ~
	//----------------
	if (fuzzy.OR(opponentNearSet, hostileBulletSet) > 0.8f/*����Ȃ��񂩁H*/)
	{
		isOpponentOffensive = true;
	}


	//----------------
	// �l���`���M����
	//----------------
	int wageDifference = agentAI->getWage() - opponent->getWage();
	if (wageDifference < LOSING_WAGE_DEFFERENSE/*����Ƃ̍��z*/)
	{
		isChinginLow = true;
	}
}


//=============================================================================
// �������[���C���ؒf���W���Z�o
//=============================================================================
void EnvironmentAnalysis::makeCoordForCut(AgentAI* agentAI)
{
	if (opponent->getElementMemoryPile() < 2) { return; }

	//---------------------------------------------------
	// �����Ɉ�ԋ߂��p�C����2�Ԗڂɋ߂��p�C����������
	//---------------------------------------------------
	float nearestLength = 10000.0f;
	float secondNearestLength = 10000.0f;
	MemoryPile* nearestPile = NULL;
	MemoryPile*	secondNearestPile = NULL;

	for (int i = 0; i < opponent->getElementMemoryPile(); i++)
	{
		float sqLen = D3DXVec3LengthSq(&(*opponent->getMemoryPile()[i].getPosition() - *agentAI->getPosition()));
		MemoryPile* p = &opponent->getMemoryPile()[i];

		//if (i < 2)
		//{
		//	secondNearestLength = nearestLength;
		//	nearestLength = sqLen;
		//	secondNearestPile = nearestPile;
		//	nearestPile = p;
		//}
		//if (i == 2)
		//{
		//	if (secondNearestLength < nearestLength)
		//	{
		//		float tempLen;
		//		MemoryPile* temp;
		//		tempLen = nearestLength;
		//		nearestLength = secondNearestLength;
		//		secondNearestLength = tempLen;

		//		temp = nearestPile;
		//		nearestPile = secondNearestPile;
		//		secondNearestPile = temp;
		//	}
		//}

		if (sqLen < nearestLength * nearestLength)
		{
			secondNearestLength = nearestLength;
			nearestLength = sqLen;
			secondNearestPile = nearestPile;
			nearestPile = p;
		}
	}


	//----------------------
	// �ȉ��Ŏg�p����f�[�^
	//----------------------
	D3DXVECTOR3 vecMemoryLine;		// �ŒZ�������[���C���̃x�N�g���i���K���ρj
	D3DXVECTOR3 orthogonalVector;	// �ŒZ�������[���C���ɒ�������x�N�g���i���K���ρj
	bool coordIsCorner;				// �������[���C����؂���W�̓p�C���t�߂��H

	// �������\���C���̃x�N�g�������߂�
	vecMemoryLine = *secondNearestPile->getPosition() - *nearestPile->getPosition();
	D3DXVec3Normalize(&vecMemoryLine, &vecMemoryLine);
	// �O�ςŃ������[���C���ɒ�������x�N�g�������߂�
	D3DXVec3Cross(&orthogonalVector, &vecMemoryLine, &nearestPile->getAxisY()->direction);
	D3DXVec3Normalize(&orthogonalVector, &orthogonalVector);

	//--------------------------------------------------
	// ���߂�ׂ����W���p�C���t�߂����C���t�߂����f����
	//--------------------------------------------------
	// �G�[�W�F���g�ƍŒZ�����p�C���̃x�N�g���ƃ������[���C���̃x�N�g���̓��ς̌��ʂ���
	// �Ŋ��̍��W���������[�p�C����ݒu�����p(�J�h)�t�߂����C���ɕt�߂��𔻒肷��
	D3DXVECTOR3 slipVecAgentToPile = slip(
		*nearestPile->getPosition() - *agentAI->getPosition(),
		nearestPile->getReverseAxisY()->direction);
	if (D3DXVec3Dot(&vecMemoryLine, &slipVecAgentToPile) < 0)
	{
		// 2�̃x�N�g�����Ȃ��p�͓݊p�̂��߃G�[�W�F���g�͕ӂ̊O���ɂ���
		coordIsCorner = true;
	}
	else
	{
		// 2�̃x�N�g�����Ȃ��e�͉s�p�̂��߃G�[�W�F���g�͕ӂ̐���
		coordIsCorner = false;
	}

	//----------------
	// ���W���Z�o����
	//----------------
	if (coordIsCorner)
	{
		recognitionBB->setLineCutCoord(*nearestPile->getPosition());
	}
	else
	{
		// �������[���C�����ʂɃG�[�W�F���g���琂�������낵��
		// �����������W�̃t�B�[���h�Ԃ̃x�N�g����L�������W������

		float d = -(orthogonalVector.x * nearestPile->getPosition()->x
			+ orthogonalVector.y * nearestPile->getPosition()->y
			+ orthogonalVector.z * nearestPile->getPosition()->z);

		float distance = (orthogonalVector.x * agentAI->getPosition()->x
			+ orthogonalVector.y * agentAI->getPosition()->y
			+ orthogonalVector.z * agentAI->getPosition()->z);

		D3DXVECTOR3 intersection = (-orthogonalVector * distance) + *agentAI->getPosition();
		D3DXVECTOR3 vecFieldToMemoryLine = intersection - *Map::getField()->getPosition();
		D3DXVec3Normalize(&vecFieldToMemoryLine, &vecFieldToMemoryLine);
		vecFieldToMemoryLine * Map::getField()->getRadius();

		recognitionBB->setLineCutCoord(vecFieldToMemoryLine);
	}

#ifdef RENDER_LINE_CUT_POINT
	D3DXMATRIX pointWorldMatrix;
	D3DXMatrixIdentity(&pointWorldMatrix);
	D3DXMatrixTranslation(&pointWorldMatrix,
		nearestPile->getPosition()->x,
		nearestPile->getPosition()->y,
		nearestPile->getPosition()->z);
	//D3DXMatrixTranslation(&pointWorldMatrix,
	//	recognitionBB->getLineCutCoord().x,
	//	recognitionBB->getLineCutCoord().y,
	//	recognitionBB->getLineCutCoord().z);
	D3DMATERIAL9 matDef;
	device->GetMaterial(&matDef);
	device->LightEnable(0, false);
	device->SetMaterial(&cutPointMat);
	device->SetTransform(D3DTS_WORLD, &pointWorldMatrix);
	cutPoint->DrawSubset(0);
	device->LightEnable(0, true);
	device->SetMaterial(&matDef);
#endif// RENDER_LINE_CUT_POINT
}


//=============================================================================
// ���z���J�[�W����
//=============================================================================
void EnvironmentAnalysis::virtualRecursion(AgentAI* agentAI)
{
	// �߂��}�b�v�m�[�h�Ō����i��
	MapNode* nearestNode[NUM_NEARLEST_NODE] = { NULL };
	int numNearestNode = 0;
	selectMapNode(nearestNode, &numNearestNode, agentAI);
	if (numNearestNode == 0) { return; }

	//���J�[�W�����ꏊ�̔F�����X�g�b�N����
	RecursionRecognition* recursionRecognition = new RecursionRecognition[numNearestNode * NUM_TEST_CASES_PER_NODE];
	recognizeRecursionArea(recursionRecognition, nearestNode, numNearestNode, agentAI);

	// ���J�[�W�����F���̐����i��
	int selectionRecognition[NUM_RECURSION_RECOGNITION] = { -1, -1, -1 };
	selectRecursionArea(selectionRecognition, recursionRecognition, nearestNode, numNearestNode, agentAI);

	// �������[�p�C����ł����ލ��W�����
	makeCoordForPile(selectionRecognition, recursionRecognition, agentAI);

	// ���F���u���b�N�{�[�h�ɕۊ�
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		if (selectionRecognition[i] == -1)
		{	// ���J�[�W�����F�����I������Ă��Ȃ��ꍇ�͔񊈐���
			recognitionBB->setIsActiveRecursionRecognition(i, false);
		}
		else
		{	// ���J�[�W�����F�����I������Ă���ꍇ�͊��������ăR�s�[����
			recognitionBB->setIsActiveRecursionRecognition(i, true);
			recognitionBB->getRecursionRecognition()[i] = recursionRecognition[selectionRecognition[i]];
		}
	}

	SAFE_DELETE_ARRAY(recursionRecognition)
}


//=============================================================================
//�i���z���J�[�W�����X�e�b�v���̂P�j�߂��}�b�v�m�[�h�Ō����i��
//=============================================================================
void EnvironmentAnalysis::selectMapNode(
	MapNode* nearestNode[],				// �Ŋ��}�b�v�m�[�h�|�C���^�z���Ԃ�
	int* numNearestNode,				// �����������������i=�|�C���^�z��̗v�f���j��Ԃ��@
	AgentAI* agentAI)
{
	std::list<MapNode*> nodeList = recognitionBB->getMemorizedMap();
	std::list<MapNode*>::iterator itr;
	float shortestLen = 1000.0f;
	int index = 0;

	for (itr = nodeList.begin(); itr != nodeList.end(); itr++)
	{
		D3DXVECTOR3* nodePosition = (*itr)->getPosition();
		float tempLen = D3DXVec3LengthSq(&(*nodePosition - *agentAI->getPosition()));
		if (tempLen < shortestLen)
		{
			shortestLen = tempLen;
			nearestNode[index] = (*itr)->getPointer();
			if (++index == NUM_NEARLEST_NODE) index = 0;
			if (++(*numNearestNode) > NUM_NEARLEST_NODE) *numNearestNode = NUM_NEARLEST_NODE;
		}
	}
}


//=============================================================================
//�i���z���J�[�W�����X�e�b�v���̂Q�j���J�[�W�����ꏊ�̔F�����X�g�b�N����
//=============================================================================
void EnvironmentAnalysis::recognizeRecursionArea(
	RecursionRecognition recursionRecognition[],	// �F���ۊǔz��
	MapNode* nearestNode[],							// �Ŋ��}�b�v�m�[�h�|�C���^�z��
	int numNearestNode,								// �|�C���^�z��̗v�f��
	AgentAI* agentAI)
{
	D3DXQUATERNION quaternion;
	D3DXQuaternionIdentity(&quaternion);
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

#ifdef DUMP_RECUASION_AREA
	setDataDirectory();
	fp = fopen("DumpRecuasionArea.txt", "w");
	fprintf(fp, "���J�[�W�����G���A�f�[�^\n�o�͌��FEnvironmentAnalysis.cpp/recognizeRecursionArea()\n");
#endif// DUMP_RECUASION_AREA

	// ���̃m�[�h�t�߂ɃT�C�Y��ς��Ȃ���o�E���f�B���O�X�t�B�A�𓖂Ă܂���
	// ���X�����m��z��`���M���z�Ƃ��̂Ƃ��̃X�t�B�A�̃p�����[�^��ۊǂ���
	int index = 0;
	for (int cntNode = 0; cntNode < numNearestNode; cntNode++)
	{
		for (int cntSize = 0; cntSize < NUM_TEST_SIZE; cntSize++)
		{
			// �p�C����ł��W�Z�o�Ɏg�p�i�O�ډ~�j
			float circumscribedRadius = TEST_SIZE_RADIUS_BASE + cntSize * TEST_SIZE_RADIUS_ADD;
			// �Փ˔��蔻��X�t�B�A�̔��a�i���ډ~�j���܊p�`�̓��ډ~�̔��a�̒萔�ŎZ�o
			float inscribedRadius = circumscribedRadius * 0.25f * (1 + 2.236f);
			// �Փ˔���p�X�t�B�A�̐���
			recursionSphere = new BoundingSphere;
			recursionSphere->initialize(device, inscribedRadius);

			// �܂��m�[�h�̈ʒu�҂�����ŏՓ˔���
			hitCheckAndAssign(agentAI, nearestNode[cntNode]->getPosition(), &recursionRecognition[index], index, circumscribedRadius);
			index++;

			// ���Ƀm�[�h�̎��͂��񂵂Ȃ���Փ˔�����s��������
			// ���̂��߂ɘf�����S�̃m�[�h�Ԃ̃��C�������X����
			ray.update(*Map::getField()->getPosition(), *nearestNode[cntNode]->getPosition() - *Map::getField()->getPosition());
			D3DXVECTOR3 axisToMakeDegree = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			axisToMakeDegree = slip(axisToMakeDegree, ray.direction);// ��]�������C�ɒ�������x�N�g���ɂ���
			switch (cntSize)
			{// �X���p�x���X�t�B�A�T�C�Y�ɂ���ĕς���
			case 0:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, AXIS_TILT_ANGLE_FOR_SMALL_BS);
				break;
			case 1:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, AXIS_TILT_ANGLE_FOR_MIDDLE_BS);
				break;
			case 2:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, AXIS_TILT_ANGLE_FOR_BIG_BS);
				break;
			}
			D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
			D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);

			// �X���Ă��郌�C����]���ŉ񂵂Ȃ��烌�C�̐�[��BS�̏Փ˔���
			D3DXVECTOR3 rotationAxis = *nearestNode[cntNode]->getPosition() - *Map::getField()->getPosition();
			D3DXQuaternionIdentity(&quaternion);
			D3DXMatrixIdentity(&worldMatrix);
			for (int cntZone = 0; cntZone < NUM_TEST_ARROUND; cntZone++)
			{
				D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI * 2 / NUM_TEST_ARROUND);
				D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
				D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);
				hitCheckAndAssign(agentAI, &ray.direction, &recursionRecognition[index], index, circumscribedRadius);
				index++;
			}
			recursionSphere->getMesh()->Release();
			SAFE_DELETE(recursionSphere);
		}
	}

#ifdef DUMP_RECUASION_AREA
	fclose(fp);
#endif// DUMP_RECUASION_AREA
}


//=============================================================================
//�i���z���J�[�W�����X�e�b�v���̂R�j���J�[�W�����F���̐����i��
//=============================================================================
void EnvironmentAnalysis::selectRecursionArea(
	int selectionRecognition[],
	RecursionRecognition recursionRecognition[],	// �F���ۊǔz��
	MapNode* nearestNode[],							// �Ŋ��}�b�v�m�[�h�|�C���^�z��
	int numNearestNode,								// �|�C���^�z��̗v�f��
	AgentAI* agentAI)
{
	float largestWeight = 0.0f;
	int selectionIndex = 0;

#ifdef DUMP_FUZZY_RECOGNITION
	setDataDirectory();
	fp2 = fopen("DumpFuzzyRecognition.txt", "w");
	fprintf(fp2, "���J�[�W�����F���t�@�W�[�f�[�^\n�o�͌��FEnvironmentAnalysis.cpp/selectRecursionArea()\n");
#endif// DUMP_FUZZY_RECOGNITION

	//--------------------------------------------
	// �t�@�W�[���_�łǂ̔F�����̗p���邩�d�݂Â�
	//--------------------------------------------
	for (int i = 0; i < numNearestNode * NUM_TEST_CASES_PER_NODE; i++)
	{
		// �����̋߂��̉������t�@�W�[���͉�
		float lenAgentBetweenArea = D3DXVec3Length(&(recursionRecognition[i].center - *agentAI->getPosition()));
		float distanceNear = fuzzy.reverseGrade(lenAgentBetweenArea, 0.0f, 25.0f);
		float distanceFar = fuzzy.grade(lenAgentBetweenArea, 22.0f, 36.0f);
		// ���J�[�W�����͈͂̏������̑傫�����t�@�W�[���͉�
		float radiusSizeSmall = fuzzy.reverseGrade(recursionRecognition[i].radius,
			TEST_SIZE_RADIUS_BASE - TEST_SIZE_RADIUS_FUZZY_ADJUST, TEST_SIZE_RADIUS_BASE + 2 * TEST_SIZE_RADIUS_ADD);
		float radiusSizeBig = fuzzy.grade(recursionRecognition[i].radius,
			TEST_SIZE_RADIUS_BASE, TEST_SIZE_RADIUS_BASE + 2 * TEST_SIZE_RADIUS_ADD + TEST_SIZE_RADIUS_FUZZY_ADJUST);
		// �͈͓��`���M���z�̏��Ȃ��̑������t�@�W�[���͉�
		float littleAmount = fuzzy.reverseGrade(recursionRecognition[i].totalAmount, 5.0f, 150.0f);
		float lotAmount = fuzzy.grade(recursionRecognition[i].totalAmount, 130.0f, 550.0f);

		// �t�@�W�[�_�����Z���Ń����b�g���Z�o����
		float leastMerit, largestMerit, finalMerit;
		leastMerit = fuzzy.AND(distanceNear, radiusSizeSmall);
		leastMerit = fuzzy.AND(leastMerit, lotAmount);
		largestMerit = fuzzy.OR(distanceNear, radiusSizeSmall);
		largestMerit = fuzzy.OR(largestMerit, lotAmount * 1.8f/*�`���M���z�̕]���E�F�C�g���グ��*/);
		finalMerit = (largestMerit + leastMerit) / 2;
		// �t�@�W�[�_�����Z���Ńf�����b�g���Z�o����
		float leastDemerit, largestDemerit, finalDemerit;
		leastDemerit = fuzzy.AND(distanceFar, radiusSizeBig);
		leastDemerit = fuzzy.AND(leastDemerit, littleAmount);
		largestDemerit = fuzzy.OR(distanceFar * 1.1f/*�����̕]���E�F�C�g���グ��*/, radiusSizeBig);
		largestDemerit = fuzzy.OR(largestDemerit, littleAmount);
		finalDemerit = (largestDemerit + leastDemerit) / 2;

		// �ŏI�I�ȏd�݂��t�@�W�[�o�͂Ƃ��ēf���o��
		recursionRecognition[i].fuzzySelectionWeight = fuzzy.grade(fuzzy.NOT(finalDemerit) + finalMerit, 0.0f, 2.0f);

		//----------------------------------------------------------------------
		// �ȉ��ɊY������F���͑I�����Ȃ�
		if (recursionRecognition[i].totalAmount == 0.0f) { continue; }
		if (recursionRecognition[i].fuzzySelectionWeight == 0.0f) { continue; }
		//----------------------------------------------------------------------

		// �d�݂̑傫���F������I�����Ă���
		if (recursionRecognition[i].fuzzySelectionWeight > largestWeight)
		{
			largestWeight = recursionRecognition[i].fuzzySelectionWeight;
			selectionRecognition[selectionIndex] = i;
			if (++selectionIndex >= NUM_RECURSION_RECOGNITION) selectionIndex = 0;
		}

#ifdef DUMP_FUZZY_RECOGNITION
		fprintf(fp2, "%d\n", recursionRecognition[i].uniqueID);
		fprintf(fp2, "����lenAgentBetweenArea = %.3f\n", lenAgentBetweenArea);
		fprintf(fp2, "����distanceNear = %.3f\n", distanceNear);
		fprintf(fp2, "����distanceFar = %.3f\n", distanceFar);
		fprintf(fp2, "�T�C�YradiusSizeSmall = %.3f\n", radiusSizeSmall);
		fprintf(fp2, "�T�C�YradiusSizeBig = %.3f\n", radiusSizeBig);
		fprintf(fp2, "�`���M��lotAmount = %.3f\n", lotAmount);
		fprintf(fp2, "�`���M��littleAmount = %.3f\n", littleAmount);
		fprintf(fp2, "largestMerit = %.3f leastMerit = %.3f, finalMerit = %.3f\n", largestMerit, leastMerit, finalMerit);
		fprintf(fp2, "largestDemrit = %.3f leastDemerit = %.3f, finalDemerit = %.3f\n", largestDemerit, leastDemerit, finalDemerit);
		fprintf(fp2, "fuzzySelectWeight = %.3f\n\n", recursionRecognition[i].fuzzySelectionWeight);
#endif// DUMP_FUZZY_RECOGNITION
	}

#ifdef DUMP_FUZZY_RECOGNITION
	fclose(fp2);
#endif// DUMP_FUZZY_RECOGNITION
}


//=============================================================================
//�i���z���J�[�W�����X�e�b�v���̂S�j�������[�p�C����ł����ލ��W�����
//=============================================================================
void EnvironmentAnalysis::makeCoordForPile(int selectionRecognition[], RecursionRecognition recursionRecognition[], AgentAI* agentAI)
{
	D3DXQUATERNION quaternion;
	D3DXQuaternionIdentity(&quaternion);
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		//-----------------------------------------------
		// �I������Ă��Ȃ��F���̓p�X����
		if (selectionRecognition[i] == -1) { continue; }
		//-----------------------------------------------

		// �ʓx�@�ł͒��S�p = ���������a�i�g���̂͒��S�p��2�Ȃ̂ŗ\��2�Ŋ����Ă����j
		float angle = recursionRecognition[selectionRecognition[i]].radius / Map::getField()->getRadius();

		// �f�����S�̃��J�[�W�����F�����S���W�̃��C�����߂����S�p�������X����
		D3DXQuaternionIdentity(&quaternion);
		D3DXMatrixIdentity(&worldMatrix);
		D3DXVECTOR3 axisForTilt = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		ray.update(*Map::getField()->getPosition(),
			recursionRecognition[selectionRecognition[i]].center - *Map::getField()->getPosition());
		axisForTilt = slip(axisForTilt, ray.direction);	// ��]�������C�ɒ�������x�N�g���ɂ���
		D3DXQuaternionRotationAxis(&quaternion, &axisForTilt, angle);
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

#ifdef RENDER_PILE_POINT
			static D3DXMATRIX pointWorldMatrix;
			D3DXMatrixIdentity(&pointWorldMatrix);
			D3DXMatrixTranslation(&pointWorldMatrix, ray.direction.x, ray.direction.y, ray.direction.z);
			D3DMATERIAL9 matDef;
			device->GetMaterial(&matDef);
			device->LightEnable(0, false);
			device->SetMaterial(&pointMat);
			device->SetTransform(D3DTS_WORLD, &pointWorldMatrix);
			pilePoint->DrawSubset(0);
			device->LightEnable(0, true);
			device->SetMaterial(&matDef);
#endif// RENDER_PILE_POINT
		}
	}
}


//=============================================================================
// ���J�[�W�����F���ւ̑���i�X�t�B�A�ƃ��X�����m�̏Փ˔���j
//=============================================================================
void EnvironmentAnalysis::hitCheckAndAssign(AgentAI* agentAI,
	D3DXVECTOR3* checkPosition, RecursionRecognition* recursionRecognition, int index, float circumscribedRadius)
{
	recursionRecognition->uniqueID = index;
	recursionRecognition->center = *checkPosition;
	recursionRecognition->totalHit = 0;
	recursionRecognition->totalAmount = 0;
	recursionRecognition->radius = circumscribedRadius;

	// �o�E���f�B���O�X�t�B�A�p���[���h�}�g���N�X�쐬
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

		if (recursionSphere->collide((*wasuremono)[i]->bodyCollide.getCenter(),
			(*wasuremono)[i]->bodyCollide.getRadius(), recursionWorldMatrix, *(*wasuremono)[i]->getMatrixWorld()))
		{
			recursionRecognition->totalHit++;
			recursionRecognition->totalAmount += (float)(*wasuremono)[i]->getAmount();
			recursionRecognition->wasuremonoInArea.push_back((*wasuremono)[i]);	
		}
	}

#ifdef DUMP_RECUASION_AREA
	fprintf(fp, "%d\n", recursionRecognition->uniqueID);
	fprintf(fp, "recursionRecognition->center = (%.2f, %.2f,%.2f) \n",
		recursionRecognition->center.x, recursionRecognition->center.y, recursionRecognition->center.z);
	fprintf(fp, "recursionRecognition->totalHit = %d\n", (int)recursionRecognition->totalHit);
	fprintf(fp, "recursionRecognition->totalAmount = %d\n", (int)recursionRecognition->totalAmount);
	fprintf(fp, "recursionRecognition->radius = %.2f\n", recursionRecognition->radius);
#endif// DUMP_RECUASION_AREA

#ifdef RENDER_RECUASION_AREA
	if (recursionRecognition->uniqueID == 2 /*|| recursionRecognition->uniqueID == 3*/)
	{
		spherePoint.render(device, recursionWorldMatrix);	// �X�t�B�A���W�̕`��

		BoundingSphere bs;
		bs.initialize(device, 15.0f);
		bs.render(device, recursionWorldMatrix);				// �T�C�Y�����p�̃X�t�B�A�`��
		bs.getMesh()->Release();
	}
#endif
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


//=============================================================================
// �f�o�b�O�`�揈��
//=============================================================================
void  EnvironmentAnalysis::debugRender(AgentAI* agentAI)
{
	// �X�V�������`�掞�ɃR�[�������悤�ɂȂ�
#ifdef AI_RENDER_MODE

	analyzeBattle(agentAI);			// �o�g���󋵂����

	makeCoordForCut(agentAI);		// �������[���C���ؒf���W���Z�o

	static int cnt = 0;// ����
	if (++cnt % 5 == 0)
	{
		cnt = 0;
		virtualRecursion(agentAI);// ���z���J�[�W����

	}

	forgetMemorizedMatter();		// �L��������Y�p

#endif
}