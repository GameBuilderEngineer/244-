//-----------------------------------------------------------------------------
// �ӎv���菈�� [DecisionMaking.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "StateMachine.h"
#include "BehaviorTree.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class DecisionMaking: public KnowledgeSourceBase {
private:
	// Data
	RecognitionBB* recognitionBB;			// ���F��
	MemoryBB* memoryBB;						// �L��
	BodyBB* bodyBB;							// �g�̏��
	State* currentState;					// ���݂̃X�e�[�g

	static StateMachine* stateMachine;
	static BehaviorTree* behaviorTree;
	
public:
	// Method
	DecisionMaking(void);
	~DecisionMaking(void);
	void initialize(void) override;			// ����������
	void uninitialize(void) override;		// �I������
	void update(AgentAI* agentAI) override;	// �X�V����
	void setBlackBoard(RecognitionBB* adr1, MemoryBB* adr2, BodyBB* adr3) { recognitionBB = adr1; memoryBB = adr2; bodyBB = adr3; }
};

