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
};