//-----------------------------------------------------------------------------
// �ӎv���菈�� [DecisionMaking.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"
#include "StateMachine.h"
#include "BehaviorTree.h"
#include "BehaviorNodeBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class DecisionMaking: public KnowledgeSourceBase {
private:
	// Data
	RecognitionBB* recognitionBB;	// ���F��
	MemoryBB* memoryBB;				// �L��
	BodyBB* bodyBB;					// �g�̏��
	StateMachine* stateMachine;		// �X�e�[�g�}�V��
	BehaviorTree* behaviorTree;		// �r�w�C�r�A�c���[

	State* currentState;											// ���݂̃X�e�[�g
	std::vector<BehaviorRecord> record[BehaviorTreeNS::NUM_TREE];	// �r�w�C�r�A�c���[�̃m�[�h���



public:
	// Method
	DecisionMaking(void);
	~DecisionMaking(void);
	void initialize(void) override;			// ����������
	void uninitialize(void) override;		// �I������
	void update(void) override;				// �X�V����
	void setBlackBoard(RecognitionBB* adr1, MemoryBB* adr2, BodyBB* adr3) { recognitionBB = adr1; memoryBB = adr2; bodyBB = adr3; }
	void setStateMachine(StateMachine* adr) { stateMachine = adr; }
	void setBehaviorTree(BehaviorTree* adr) { behaviorTree = adr; }
};

