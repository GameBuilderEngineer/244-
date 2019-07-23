//-----------------------------------------------------------------------------
// ����͏��� [EnvironmentAnalysis.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "BlackBoardRecognition.h"
#include "Fuzzy.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EnvironmentAnalysis:public KnowledgeSourceBase {
private:
	Fuzzy fuzzy;						// �t�@�W�[���_����
	RecognitionBB* recognitionBB;

public:
	// Method
	EnvironmentAnalysis(void);
	~EnvironmentAnalysis(void);
	void initialize(void) override;		// ����������
	void uninitialize(void) override;	// �I������
	void update(void) override;			// �X�V����
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }

	
};