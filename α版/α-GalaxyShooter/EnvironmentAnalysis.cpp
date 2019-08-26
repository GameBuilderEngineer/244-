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
#if 1
#define DUMP_RECUASION_AREA		// ���J�[�W�����G���A�f�[�^���_���v����
static FILE* fp = NULL;
static int areaLabel = 0;
#endif 

#if 1
#define DUMP_FUZZY_RECOGNITION	// ���J�[�W�����F���̐����i��t�@�W�[�f�[�^���G���A�ʂɃ_���v����
static FILE* fp2 = NULL;
static int	areaLabel2 = 0;
#endif

#if 1	// �f�o�b�O�`�悷��ꍇ��1�i�X�V������`�揈���Ŏ��s���邱�ƂɂȂ�̂Œ��Ӂj					
#define AI_RENDER_MODE
#endif

// �f�o�b�O�`�悪�L���̏ꍇ
#ifdef AI_RENDER_MODE

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

#ifdef RENDER_RECUASION_AREA
	spherePoint.initialize(device, 1.0f);
#endif

#ifdef RENDER_PILE_POINT
	D3DXCreateSphere(device, 1.0f, 5, 5, &pilePoint, NULL);
	// �m�[�h�̕\���}�[�N�p���b�V���̃}�e���A��
	// ���C�g�͐؂�̂�Diffuse, Ambient�͕s���������ł悢
	pointMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Emissive = { 1.0f, 0.0f, 1.0f, 1.0f };
#endif
}


//=============================================================================
// �I������
//=============================================================================
void EnvironmentAnalysis::uninitialize(void)
{
#ifdef RENDER_RECUASION_AREA
	SAFE_DELETE(recursionSphere)
#endif
}


//=============================================================================
// �X�V����
//=============================================================================
void EnvironmentAnalysis::update(AgentAI* agentAI)
{
#ifdef AI_RENDER_MODE
	return;
#endif //AI_RENDER_MODE


	static int cnt = 0;// ����
	if (++cnt % 10 == 0)
	{
		cnt = 0;
		virtualRecursion(agentAI);// ���z���J�[�W����

	}

	forgetMemorizedMatter();		// �L��������Y�p
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

	//���J�[�W��������ꏊ�����߂邽�߂̏Փ˔���
	RecursionRecognition* recursionRecognition = new RecursionRecognition[numNearestNode * NUM_TEST_CASES_PER_NODE];
	checkRecursionArea(recursionRecognition, nearestNode, numNearestNode, agentAI);

	// ���J�[�W�����F���̐����i��
	int selectionRecognition[NUM_RECURSION_RECOGNITION] = { 0 };
	selectRecursionArea(selectionRecognition, recursionRecognition, nearestNode, numNearestNode, agentAI);

	// �������[�p�C����ł����ލ��W�����
	makeCoordForPile(selectionRecognition, recursionRecognition, agentAI);

	// ���F���u���b�N�{�[�h�Ƀt�B�[�h�o�b�N
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		recognitionBB->getRecursionRecognition()[i] = recursionRecognition[selectionRecognition[i]];
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
//�i���z���J�[�W�����X�e�b�v���̂Q�j���J�[�W��������ꏊ�����߂邽�߂̏Փ˔���
//=============================================================================
void EnvironmentAnalysis::checkRecursionArea(
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
	areaLabel = 0;
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
			// ���J�[�W�����`�F�b�N�p�X�t�B�A�𐶐�
			recursionRadius = 15.0f + cntSize * 10.0f;// �������͒����i���ꂪBS���̂̔��a�j
			recursionSphere = new BoundingSphere;
			recursionSphere->initialize(device, recursionRadius);

			// �܂��m�[�h�̈ʒu�҂�����ŏՓ˔���
			recognizeRecursionArea(agentAI, nearestNode[cntNode]->getPosition(), &recursionRecognition[index++]);

			// ���Ƀm�[�h�̎��͂��񂵂Ȃ���Փ˔�����s��������
			// ���̂��߂ɘf�����S�̃m�[�h�Ԃ̃��C�������X����
			ray.update(*Map::getField()->getPosition(), *nearestNode[cntNode]->getPosition() - *Map::getField()->getPosition());
			D3DXVECTOR3 axisToMakeDegree = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			switch (cntSize)
			{// �X���p�x���X�t�B�A�T�C�Y�ɂ���ĕς���
			case 0:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.22f);
				break;
			case 1:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.3f);
				break;
			case 2:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.42f);
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
				recognizeRecursionArea(agentAI, &ray.direction, &recursionRecognition[index++]);
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
	areaLabel2 = 0;
	setDataDirectory();
	fp2 = fopen("DumpFuzzyRecognition.txt", "w");
	fprintf(fp2, "���J�[�W�����F���t�@�W�[�f�[�^\n�o�͌��FEnvironmentAnalysis.cpp/selectRecursionArea()\n");
#endif// DUMP_FUZZY_RECOGNITION

	for (int i = 0; i < numNearestNode * NUM_TEST_CASES_PER_NODE; i++)
	{
		// �t�@�W�[���_�łǂ̔F�����̗p���邩�d�݂Â�
		float radiusSizeBig = fuzzy.grade(recursionRecognition[i].radius, 15.0f, 35.0f);
		float littleAmount = fuzzy.reverseGrade(recursionRecognition[i].totalAmount, 5.0f, 70.0f);
		float demerit = fuzzy.OR(radiusSizeBig, littleAmount);

		float radiusSizeSmall = fuzzy.reverseGrade(recursionRecognition[i].radius, 15.0f, 25.0f);
		float lotAmount = fuzzy.grade(recursionRecognition[i].totalAmount, 50.0f, 300.0f);
		float merit = fuzzy.OR(radiusSizeSmall, lotAmount);

		recursionRecognition[i].fuzzySelectionWeight = fuzzy.grade(fuzzy.NOT(demerit) + merit, 0.0f, 2.0f);// �ŏI�I�ȏd��

		// �d�݂̑傫���F������I�����Ă���
		for (int k = 0; k < NUM_RECURSION_RECOGNITION; k++)
		{
			if (recursionRecognition[i].fuzzySelectionWeight > largestWeight)
			{
				largestWeight = recursionRecognition[i].fuzzySelectionWeight;
				selectionRecognition[selectionIndex] = i;
				if (++selectionIndex >= NUM_RECURSION_RECOGNITION) selectionIndex = 0;
			}
		}

#ifdef DUMP_FUZZY_RECOGNITION
		fprintf(fp2, "%d\n", areaLabel2++);
		fprintf(fp2, "radiusSizeSmall = %.3f\n", radiusSizeSmall);
		fprintf(fp2, "littleAmount = %.3f\n", littleAmount);
		fprintf(fp2, "demerit = %.3f\n", demerit);
		fprintf(fp2, "radiusSizeBig = %.3f\n", radiusSizeBig);
		fprintf(fp2, "lotAmount = %.3f\n", lotAmount);
		fprintf(fp2, "merit = %.3f\n\n", merit);
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
// ���J�[�W�����F���ւ̑���i�X�t�B�A�ƃ��X�����m�̏Փ˔��肪��j
//=============================================================================
void EnvironmentAnalysis::recognizeRecursionArea(AgentAI* agentAI, D3DXVECTOR3* checkPosition, RecursionRecognition* recursionRecognition)
{
	recursionRecognition->center = *checkPosition;
	recursionRecognition->totalHit = 0;
	recursionRecognition->totalAmount = 0;
	recursionRecognition->radius = recursionSphere->getRadius();

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
	fprintf(fp, "%d\n", areaLabel++);
	fprintf(fp, "recursionRecognition->center = (%.2f, %.2f,%.2f) \n",
		recursionRecognition->center.x, recursionRecognition->center.y, recursionRecognition->center.z);
	fprintf(fp, "recursionRecognition->totalHit = %d\n", (int)recursionRecognition->totalHit);
	fprintf(fp, "recursionRecognition->totalAmount = %d\n", (int)recursionRecognition->totalAmount);
	fprintf(fp, "recursionRecognition->radius = %.2f\n", recursionRecognition->radius);
#endif// DUMP_RECUASION_AREA

#ifdef RENDER_RECUASION_AREA
	if (recursionRecognition->radius == 35.0f)
	{
		spherePoint.render(device, recursionWorldMatrix);	// �X�t�B�A���W�̕`��
	}
	BoundingSphere bs;
	bs.initialize(device, 35.0f);
	bs.render(device, recursionWorldMatrix);				// �T�C�Y�����p�̃X�t�B�A�`��
	bs.getMesh()->Release();
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
	//static int cnt = 0;// ����
	//if (++cnt % 5 == 0)
	//{
	//	cnt = 0;
		virtualRecursion(agentAI);// ���z���J�[�W����

	//}

	forgetMemorizedMatter();		// �L��������Y�p

#endif
}

