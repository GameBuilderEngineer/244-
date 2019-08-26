//-----------------------------------------------------------------------------
// ����͏��� [EnvironmentAnalysis.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "Fuzzy.h"
#include "BoundingSphere.h"
#include "RecursionRecognition.h"
#include "Ray.h"

//----------
// �萔��`
//----------
namespace EnvilonmentAnalysisNs
{
	static const int	NUM_NEARLEST_NODE = 3;					// ���J�[�W�����͈͂𒲂ׂ�}�b�v�m�[�h�̌�␔
	static const int	NUM_TEST_SIZE = 3;						// ���J�[�W�����̑傫���iBS�̃T�C�Y�j�̐�
	static const int	NUM_TEST_ARROUND = 5;					// �P�̃m�[�h�̎��͂�BS�𓖂Ă�ӏ��̐�
	static const int	NUM_TEST_ZONE = NUM_TEST_ARROUND + 1;	// �m�[�h���̂̍��W���܂߂�BS�𓖂Ă�ӏ��̑���
	static const int	NUM_TEST_CASES_PER_NODE = NUM_TEST_SIZE * NUM_TEST_ZONE;// ��̃m�[�h�ɂ��ďՓˌ��m�̎��s��
	static const float	TEST_SIZE_RADIUS_BASE = 15.0f;			// ���J�[�W�����G���A����pBS�̊�{���a
	static const float	TEST_SIZE_RADIUS_ADD = 10.0f;			// ���J�[�W�����G���A����pBS�̒ǉ����a
}

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EnvironmentAnalysis:public KnowledgeSourceBase {
private:
	RecognitionBB* recognitionBB;			// ���F���u���b�N�{�[�h
	std::vector<Wasuremono*>* wasuremono;	// ���X�����m
	Fuzzy fuzzy;							// �t�@�W�[���_����
	int mapTimeCount;
	int forgettingTimeMap;
	int bulletTimeCount;
	int forgettingTimeBullet;

	BoundingSphere* recursionSphere;						// ���J�[�W���������W�Z�o�pBS
	float recursionRadius;
	D3DXVECTOR3 checkPosition;
	D3DXVECTOR3 posCandidate[7/*�K��*/][5/*�p�C���̐�*/];	// ���J�[�W���������W
	Ray ray;

	void selectMapNode(MapNode* nearestNode[], int* numNearestNode, AgentAI* agentAI);
	void checkRecursionArea(RecursionRecognition recursionRecognition[], MapNode* nearestNode[],
		int numNearestNode, AgentAI* agentAI);
	void selectRecursionArea(int selectionRecognition[], RecursionRecognition recursionRecognition[],
		MapNode* nearestNode[], int numNearestNode, AgentAI* agentAI);
	void makeCoordForPile(int selectionRecognition[], RecursionRecognition recursionRecognition[], AgentAI* agentAI);

public:
	// Method
	EnvironmentAnalysis(std::vector<Wasuremono*>* _wasuremono);
	~EnvironmentAnalysis(void);
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }
	void initialize(void) override;			// ����������
	void uninitialize(void) override;		// �I������
	void update(AgentAI* agentAI) override;	// �X�V����
	void virtualRecursion(AgentAI* agentAI);
	void recognizeRecursionArea(AgentAI* agentAI, D3DXVECTOR3* checkPosition, RecursionRecognition* recursionRecognition);
	void forgetMemorizedMatter(void);		// �L��������Y�p
	void debugRender(AgentAI* agentAI);		// �f�o�b�O�`�揈��
};