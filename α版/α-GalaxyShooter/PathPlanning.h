//-----------------------------------------------------------------------------
// �o�H�T������ [PathPlanning.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PathPlanning:public KnowledgeSourceBase {
private:
	RecognitionBB* recognitionBB;
	MemoryBB* memoryBB;

public:
	// Method
	PathPlanning(void);
	~PathPlanning(void);
	void initialize(void) override;			// ����������
	void uninitialize(void) override;		// �I������
	void update(AgentAI* agent) override;	// �X�V����
	void setBlackBoard(RecognitionBB* adr1, MemoryBB* adr2) { recognitionBB = adr1; memoryBB = adr2; }

};