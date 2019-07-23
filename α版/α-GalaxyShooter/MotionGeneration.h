//-----------------------------------------------------------------------------
// �^���������� [MotionGeneration.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MotionGeneration:public KnowledgeSourceBase {
private:
	MemoryBB* memoryBB;
	BodyBB* bodyBB;

public:
	// Method
	MotionGeneration(void);
	~MotionGeneration(void);
	void initialize(void) override;		// ����������
	void uninitialize(void) override;	// �I������
	void update(void) override;			// �X�V����
	void setBlackBoard(MemoryBB* adr1, BodyBB* adr2) { memoryBB = adr1; bodyBB = adr2; }
};