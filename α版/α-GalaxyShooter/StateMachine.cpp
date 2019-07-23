//-----------------------------------------------------------------------------
// �X�e�[�g�}�V������ [StateMachine.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/20
//-----------------------------------------------------------------------------
#include "AICommon.h"
#include "StateMachine.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
StateMachine* StateMachine::instance;
Offense* Offense::instance;
Deffense* Deffense::instance;

//=============================================================================
// �X�e�[�g���Ƃ̑J��
//=============================================================================
State* Offense::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return this;
	//return Deffense::getInstance();
}

State* Deffense::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	return this;
	//return Offense::getInstance();
}


//=============================================================================
// �X�e�[�g�}�V��
//=============================================================================
// �R���X�g���N�^
StateMachine::StateMachine(void)
{
	Offense::create();
	Deffense::create();
}

// �f�X�g���N�^
StateMachine::~StateMachine(void)
{
	Offense::destroy();
	Deffense::destroy();
}

// ���s
int StateMachine::run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	current = current->transition(recognitionBB, memoryBB, bodyBB);
	return current->getNumber();
}