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

#if 1	// �f�o�b�O�`�悷��ꍇ��1�i�X�V������`�揈���Ŏ��s���邱�ƂɂȂ�̂Œ��Ӂj					
#define AI_RENDER_MODE
#endif

// �f�o�b�O�`�悪�L���̏ꍇ
#ifdef AI_RENDER_MODE

#if 0
#define RENDER_LINE_CUT_POINT	// �������[���C���ؒf���W��`�悷��
static LPD3DXMESH cutPoint = NULL;
static D3DMATERIAL9 cutPointMat;
#endif

#if 0
#define RENDER_RECUASION_AREA	// ���J�[�W�����G���A���o�X�t�B�A��`�悷��
static BoundingSphere spherePoint;
#endif

#if 1
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

	battleAnalysisFrameCount = 0;
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

	if (++battleAnalysisFrameCount % BATTLE_ANALYSIS_FPS)
	{
		analyzeBattle(agentAI);			// �o�g���󋵂����
		battleAnalysisFrameCount = 0;
	}

	makeCoordForCut(agentAI);			// �������[���C���ؒf���W���Z�o

	if (++vRecursionFrameCount % VIRTUAL_RECURSION_FPS == 0)
	{
		virtualRecursion(agentAI);			// ���z���J�[�W����
		virtualRecursionForOpponent(agentAI);	// ���z���J�[�W����for����
		vRecursionFrameCount = 0;
	}

	forgetMemorizedMatter();			// �L��������Y�p
}


//=============================================================================
// �o�g���󋵂����
//=============================================================================
void EnvironmentAnalysis::analyzeBattle(AgentAI* agentAI)
{
	//------
	// ����
	//------
	// ����
	// �Z���T�[�Ŏ��E�ɓ������Ƃ��̋����Ŕ���
	float opponentNearSet = 
		fuzzy.reverseGrade(recognitionBB->getDistanceBetweenPlayers(), 0.0f, LENGTH_OPPONENT_IS_NEAR);
	if (opponentNearSet > 0.5f/*����*/)
	{
		recognitionBB->setIsOpponentNear(true);
	}
	else
	{
		recognitionBB->setIsOpponentNear(false);
	}

	// �Ռ��g
	recognitionBB->setMayHappenShockWave(false);
	if (recognitionBB->getIsOpponentInCamera())
	{
		if (opponent->getState() == playerNS::SKY || opponent->getState() == playerNS::FALL)
		{
			recognitionBB->setMayHappenShockWave(true);
		}
	}


	//----------------
	// �o���b�g�̉��
	//----------------
	std::list<Bullet*> bulletList = recognitionBB->getMemorizedBullet();
	std::list<Bullet*>::iterator itr;
	int cntHostileBullet = 0;				// �G���o���b�g�̐�
	int cntCloseDistanceBullet = 0;			// �G�����ߋ����o���b�g�̐�	

	for (itr = bulletList.begin(); itr != bulletList.end(); itr++)
	{
		D3DXVECTOR3 vecBulletToAgent;		// �o���b�g�̎����̃x�N�g��
		D3DXVECTOR3 slipVecBulletToAgent;	// �o���b�g�̎����̊���x�N�g��
		D3DXVECTOR3 slipVecBulletSpeed;		// �o���b�g�̃X�s�[�h�̊���x�N�g��
		float dintanceToBullet;				// �o���b�g�Ƃ̋���
		bool isHostile = false;				// �G���o���b�g�ł��邩

		// �����̃o���b�g�̃x�N�g�����Z�o������x�N�g���ɂ��Đ��K��
		vecBulletToAgent = *agentAI->getPosition() - *(*itr)->getPosition();
		dintanceToBullet = D3DXVec3Length(&vecBulletToAgent);	// ������ۊ�
		slipVecBulletToAgent = slip(vecBulletToAgent, (*itr)->getAxisY()->direction);
		D3DXVec3Normalize(&slipVecBulletToAgent, &slipVecBulletToAgent);

		// �o���b�g�̃X�s�[�h������x�N�g���ɂ��Ă𐳋K��
		slipVecBulletSpeed = slip((*itr)->getSpeed(), (*itr)->getAxisY()->direction);
		D3DXVec3Normalize(&slipVecBulletSpeed, &slipVecBulletSpeed);

		// �����̕����Ɍ������Ă���Ȃ�G���o���b�g�ł���
		float dot = D3DXVec3Dot(&slipVecBulletSpeed, &slipVecBulletToAgent);
		float angleDifferenceForHit = acosf(dot);
		if (angleDifferenceForHit < D3DXToRadian(BULLET_TWO_VECTOR_ANGLE_DEGREE))
		{
			isHostile = true;
			cntHostileBullet++;
		}

		// �����̋߂��G���o���b�g�𒲂ׂ�
		if (isHostile && dintanceToBullet < LENGHT_BULLET_IS_NEAR)
		{
			cntCloseDistanceBullet++;
		}
	}

	// ���ߋ����̓G���o���b�g�����邩�ݒ肷��
	if (cntCloseDistanceBullet > 0)
	{ 
		recognitionBB->setIsBuletNear(true);
	}
	else
	{
		recognitionBB->setIsBuletNear(false);
	}

	float hostileBulletSet = fuzzy.grade((float)cntHostileBullet, 0.0f, 3.0f);


	//----------------
	// ����̍U���ӗ~
	//----------------
	if (fuzzy.OR(opponentNearSet, hostileBulletSet) > 0.65f/*����Ȃ��񂩁H*/)
	{
		recognitionBB->setIsOpponentOffensive(true);
	}
	else
	{
		recognitionBB->setIsOpponentOffensive(false);
	}


	//----------------
	// �l���`���M����
	//----------------
	int wageDifference = agentAI->getWage() - opponent->getWage();
	if (wageDifference < LOSING_WAGE_DEFFERENSE/*����Ƃ̍��z*/)
	{
		recognitionBB->setIsChinginLow(true);
	}
	else
	{
		recognitionBB->setIsChinginLow(false);
	}
}


//=============================================================================
// �������[���C���ؒf���W���Z�o (�s���S�Ë���)
//=============================================================================
void EnvironmentAnalysis::makeCoordForCut(AgentAI* agentAI)
{
	// �������[���C����������Ă��Ȃ���ΏI��
	if (opponent->getElementMemoryPile() == 0) { return; }
	
	int numPile = opponent->getElementMemoryPile() + 1; // �p�C���̐��i���ɑł����ރp�C����������j
	float length[5 + 1] = { 0.0f };						// �p�C���Ƃ̋����������Ƀ\�[�g���Ċi�[
	MemoryPile* pile[5 + 1] = { NULL };					// �p�C���Ƃ̋����ŏ����Ƀ\�[�g�����������[�p�C��
	MemoryPile pileBeforeHitting;						// ���ɑł����ރp�C���i�ΐ푊����W���i�[�j

	//--------------------------------------------
	// �ߋ����̃p�C�����擾���ċ߂����Ƀ\�[�g����
	//--------------------------------------------
	for (int i = 0; i < numPile; i++)
	{
		// �T�ł��؂�O�͎��ɑł����ރp�C����������
		if (i == opponent->getElementMemoryPile() && i != 5/*5�{�ڂ̎��̃p�C���͖����̂�*/)
		{
			length[i] = D3DXVec3Length(&(*opponent->getPosition() - *agentAI->getPosition()));
			pileBeforeHitting.setPosition(*opponent->getPosition());
			pileBeforeHitting.getAxisY()->initialize(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), opponent->getAxisY()->direction);
			pile[i] = &pileBeforeHitting;
		}

		// ���ɑł����ރp�C���ȍ~�̓p�X
		if (i >= opponent->getElementMemoryPile()) { continue; }

		length[i] = D3DXVec3Length(&(*opponent->getMemoryPile()[i].getPosition() - *agentAI->getPosition()));
		pile[i] = &opponent->getMemoryPile()[i];
	}

	// �o�u���\�[�g
	for (int i = 0; i < numPile - 1; i++)
	{
		for (int k = numPile - 1; k > i; k--)
		{
			if (length[i] > length[k])
			{
				if (pile[i] == NULL || pile[k] == NULL) { continue; }

				float tempLen = length[k];
				MemoryPile* tempPile = pile[k];
				length[k] = length[i];
				pile[k] = pile[i];
				length[i] = tempLen;
				pile[i] = tempPile;
			}
		}
	}

	//------------------------
	// �ȉ��Ŏg�p����f�[�^�Q
	//------------------------
	D3DXVECTOR3 vecLine0to1;		// �ŒZ�p�C���̑�2�ŒZ�p�C���̃x�N�g���i���K���ρj
	D3DXVECTOR3 orthogonal0to1;		// ���̃������[���C���ɒ�������x�N�g���i���K���ρj
	D3DXVECTOR3 vecLine0to2;		// �ŒZ�p�C���̑�3�ŒZ�p�C���̃x�N�g���i���K���ρj
	D3DXVECTOR3 orthogonal0to2;		// ���̃������[���C���ɒ�������x�N�g���i���K���ρj
	//D3DXVECTOR3 vecLine1to2;		// ��2�ŒZ�p�C���̑�3�ŒZ�p�C���̃x�N�g���i���K���ρj
	//D3DXVECTOR3 orthogonal1to2;		// ���̃������[���C���ɒ�������x�N�g���i���K���ρj
	// �x�N�g���̒��g�𖄂߂�
	vecLine0to1 = *pile[1]->getPosition() - *pile[0]->getPosition();
	D3DXVec3Normalize(&vecLine0to1, &vecLine0to1);
	D3DXVec3Cross(&orthogonal0to1, &vecLine0to1, &pile[0]->getAxisY()->direction);
	D3DXVec3Normalize(&orthogonal0to1, &orthogonal0to1);
	if (opponent->getElementMemoryPile() > 1/*�������[���C����2�{�ȏ�*/)
	{
		vecLine0to2 = *pile[2]->getPosition() - *pile[0]->getPosition();
		D3DXVec3Normalize(&vecLine0to2, &vecLine0to2);
		D3DXVec3Cross(&orthogonal0to2, &vecLine0to2, &pile[0]->getAxisY()->direction);
		D3DXVec3Normalize(&orthogonal0to2, &orthogonal0to2);
		//vecLine1to2 = *pile[2]->getPosition() - *pile[1]->getPosition();
		//D3DXVec3Normalize(&vecLine1to2, &vecLine1to2);
		//D3DXVec3Cross(&orthogonal1to2, &vecLine1to2, &pile[1]->getAxisY()->direction);
		//D3DXVec3Normalize(&orthogonal1to2, &orthogonal1to2);
	}
	D3DXVECTOR3 posLine0to1;		// �ŒZ�p�C���̑�2�ŒZ�p�C���̃��C����ؒf������W
	D3DXVECTOR3 posLine0to2;		// �ŒZ�p�C���̑�3�ŒZ�p�C���̃��C����ؒf������W


	//----------------
	// ���W���Z�o����
	//----------------
	// �����ł���Ă��邱��
	// (1)���ʂ̕����������߂ăG�[�W�F���g�̍��W�Ƃ̋��������߂�
	// (2)�����𗘗p���ĕ��ʂƂ̌�_�����߂�
	// (3)�t�B�[���h���W�����_�܂ł̃x�N�g�����t�B�[���h���a�܂ŐL�������W�Ƃ���

	{// �ŒZ�p�C���̑�2�ŒZ�p�C���̃��C����ؒf������W�����߂�
		float d = -(orthogonal0to1.x * pile[0]->getPosition()->x
			+ orthogonal0to1.y * pile[0]->getPosition()->y
			+ orthogonal0to1.z * pile[0]->getPosition()->z);

		float distance = (orthogonal0to1.x * agentAI->getPosition()->x
			+ orthogonal0to1.y * agentAI->getPosition()->y
			+ orthogonal0to1.z * agentAI->getPosition()->z + d);

		D3DXVECTOR3 intersection = (-orthogonal0to1 * distance) + *agentAI->getPosition();
		D3DXVECTOR3 vecFieldToMemoryLine = intersection - *Map::getField()->getPosition();
		D3DXVec3Normalize(&vecFieldToMemoryLine, &vecFieldToMemoryLine);
		posLine0to1 = vecFieldToMemoryLine * Map::getField()->getRadius();
	}

	if(opponent->getElementMemoryPile() > 1/*�������[���C����2�{�ȏ�*/)
	{// �ŒZ�p�C���̑�3�ŒZ�p�C���̃��C����ؒf������W�����߂�
		float d = -(orthogonal0to2.x * pile[0]->getPosition()->x
			+ orthogonal0to2.y * pile[0]->getPosition()->y
			+ orthogonal0to2.z * pile[0]->getPosition()->z);

		float distance = (orthogonal0to2.x * agentAI->getPosition()->x
			+ orthogonal0to2.y * agentAI->getPosition()->y
			+ orthogonal0to2.z * agentAI->getPosition()->z + d);

		D3DXVECTOR3 intersection = (-orthogonal0to2 * distance) + *agentAI->getPosition();
		D3DXVECTOR3 vecFieldToMemoryLine = intersection - *Map::getField()->getPosition();
		D3DXVec3Normalize(&vecFieldToMemoryLine, &vecFieldToMemoryLine);
		posLine0to2 = vecFieldToMemoryLine * Map::getField()->getRadius();
	}


	//----------------
	// ���W�����肷��
	//----------------
#define DIFFERENSE_BETWEEN_GROUND	(2.5f)

	D3DXVECTOR3 slipVecPile0ToAgent = slip(
		*agentAI->getPosition() - *pile[0]->getPosition(),
		pile[0]->getReverseAxisY()->direction);
	D3DXVec3Normalize(&slipVecPile0ToAgent, &slipVecPile0ToAgent);
	float radian0and1 = acosf(D3DXVec3Dot(&vecLine0to1, &slipVecPile0ToAgent));
	float radian0and2 = acosf(D3DXVec3Dot(&vecLine0to2, &slipVecPile0ToAgent));


	//if (opponent->getElementMemoryPile() == 1/*�������[���C����1�{�̂Ƃ�����*/)
	//{
	//	if (radian0and1 < D3DX_PI * 0.5f)
	//	{
	//		recognitionBB->setLineCutCoord(posLine0to1);
	//	}
	//	else
	//	{
	//		recognitionBB->setLineCutCoord(
	//			*pile[0]->getPosition() + pile[0]->getReverseAxisY()->direction * DIFFERENSE_BETWEEN_GROUND);
	//	}
	//}


	// �G�[�W�F���g�̍ŒZ�p�C���̃x�N�g�����p�C�����m�̃x�N�g���Q�ɑ΂���
	// �ǂ̒��x�p�x���J���Ă��邩�ɂ����W���R����I������
	if (radian0and1 > D3DX_PI * 0.5f && radian0and2 > D3DX_PI * 0.5f)
	{// �����̃x�N�g���ɑ΂��݊p
		recognitionBB->setLineCutCoord(
			*pile[0]->getPosition() + pile[0]->getReverseAxisY()->direction * DIFFERENSE_BETWEEN_GROUND);
	}
	else if (radian0and1 < D3DX_PI * 0.5f)
	{
		recognitionBB->setLineCutCoord(posLine0to1);
	}
	else if (radian0and2 < D3DX_PI * 0.5f)
	{
		recognitionBB->setLineCutCoord(posLine0to2);
	}


#ifdef RENDER_LINE_CUT_POINT
	D3DXMATRIX pointWorldMatrix;
	D3DXMatrixIdentity(&pointWorldMatrix);
	//D3DXMatrixTranslation(&pointWorldMatrix,
	//	pile[0]->getPosition()->x,
	//	pile[0]->getPosition()->y,
	//	pile[0]->getPosition()->z);
	D3DXMatrixTranslation(&pointWorldMatrix,
		recognitionBB->getLineCutCoordPointer()->x,
		recognitionBB->getLineCutCoordPointer()->y,
		recognitionBB->getLineCutCoordPointer()->z);
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
		float littleAmount = fuzzy.reverseGrade(recursionRecognition[i].totalAmount, 5.0f, 100.0f);
		float lotAmount = fuzzy.grade(recursionRecognition[i].totalAmount, 80.0f, 200.0f);

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
		if (len > radius2 * radius2/*�O�����̒藝*/) { continue; }

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
// ���z���J�[�W����for����
//=============================================================================
void EnvironmentAnalysis::virtualRecursionForOpponent(AgentAI* agentAI)
{
	RecursionRecognition* recursionRecognition = new RecursionRecognition[1];

	float tempLen = D3DXVec3Length(&(*opponent->getPosition() - *Map::getField()->getPosition()));
	float height = tempLen - Map::getField()->getRadius();
	D3DXVECTOR3 pos = *opponent->getPosition() + opponent->getReverseAxisY()->direction * height;

	recursionRecognition[0].uniqueID = 0;
	recursionRecognition[0].center = pos;
	recursionRecognition[0].totalHit = 0;
	recursionRecognition[0].totalAmount = 0;
	recursionRecognition[0].radius = SIZE_RADIUS_OPPONENT_RECURSION;

	int selectionRecognition[NUM_RECURSION_RECOGNITION] = { 0, -1, -1 };

	// �������[�p�C����ł����ލ��W�����
	makeCoordForPile(selectionRecognition, recursionRecognition, agentAI);

	// ���F���u���b�N�{�[�h�ɕۊ�
	*recognitionBB->getRecursionRecognitionForOpponent() = *recursionRecognition;

	SAFE_DELETE_ARRAY(recursionRecognition)
}


//=============================================================================
// �L��������Y�p
//=============================================================================
void EnvironmentAnalysis::forgetMemorizedMatter(void)
{
	if (recognitionBB->getMemorizedMap().size() != 0)
	{
		mapTimeCount++;
		forgettingTimeMap = 60/*FPS*/ * 8/*�b*/ / recognitionBB->getMemorizedMap().size();
		if (mapTimeCount > forgettingTimeMap)
		{
			recognitionBB->getMemorizedMap().pop_front();
			mapTimeCount = 0;
		}
	}

	if (recognitionBB->getMemorizedBullet().size() != 0)
	{
		bulletTimeCount++;
		forgettingTimeBullet = 60/*FPS*/ * 3/*�b*/ / recognitionBB->getMemorizedBullet().size();
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
		virtualRecursionForOpponent(agentAI);	// ���z���J�[�W����for����

	}

	forgetMemorizedMatter();		// �L��������Y�p

#endif
}