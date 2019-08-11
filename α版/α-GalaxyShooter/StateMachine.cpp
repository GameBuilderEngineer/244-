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
Offense* Offense::instance;
Deffense* Deffense::instance;

static const float TEMPLENGTH = 50.0f;

//=============================================================================
// �X�e�[�g���Ƃ̑J��
//=============================================================================
State* Offense::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (D3DXVec3Length(&(*opponent->getPosition() - *recognitionBB->getMyPosition())) > TEMPLENGTH)
	{
		return Deffense::getInstance();
	}

	return this;
}

State* Deffense::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	Player* a = opponent;
	if (D3DXVec3Length(&(*opponent->getPosition() - *recognitionBB->getMyPosition())) <= TEMPLENGTH)
	{
		return Offense::getInstance();
	}

	return this;
}


//=============================================================================
// �X�e�[�g�}�V��
//=============================================================================
// �R���X�g���N�^
StateMachine::StateMachine(void)
{
	Offense::create();
	Deffense::create();
	initialState = Deffense::getInstance();
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