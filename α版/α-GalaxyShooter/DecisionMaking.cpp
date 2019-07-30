//-----------------------------------------------------------------------------
// �ӎv���菈�� [DecisionMaking.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "DecisionMaking.h"
#include "AgentAI.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
StateMachine* DecisionMaking::stateMachine = NULL;
BehaviorTree* DecisionMaking::behaviorTree = NULL;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
DecisionMaking::DecisionMaking(void)
{
	// �X�e�[�g�}�V���ƃr�w�C�r�A�c���[��ÓI�����o�ɐ����iAgentAI���p�̂��߁j
	if (!stateMachine) { stateMachine = new StateMachine; }
	if (!behaviorTree) { behaviorTree = new BehaviorTree; }

	// �����X�e�[�g��ݒ�
	currentState = stateMachine->getInitialState();
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
DecisionMaking::~DecisionMaking(void)
{
	// �X�e�[�g�}�V���ƃr�w�C�r�A�c���[��j��
	SAFE_DELETE(stateMachine)
	SAFE_DELETE(behaviorTree)
}


//=============================================================================
// ����������
//=============================================================================
void DecisionMaking::initialize(void)
{

}


//=============================================================================
// �I������
//=============================================================================
void DecisionMaking::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void DecisionMaking::update(AgentAI* agentAI)
{
	int treeNumber = stateMachine->run(currentState, recognitionBB, memoryBB, bodyBB);
	behaviorTree->run(treeNumber, recognitionBB, memoryBB, bodyBB);
}
