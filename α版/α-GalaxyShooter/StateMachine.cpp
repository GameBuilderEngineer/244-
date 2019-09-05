//-----------------------------------------------------------------------------
// �X�e�[�g�}�V������ [StateMachine.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/20
//-----------------------------------------------------------------------------
#include "AICommon.h"
#include "StateMachine.h"

// Static Data
OffenseState* OffenseState::instance;
DeffenseState* DeffenseState::instance;
RecursionState* RecursionState::instance;
DownState* DownState::instance;
SkyState* SkyState::instance;
FallState* FallState::instance;


/////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////// ��ԑJ�� //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
// �I�t�F���X��Ԃ���̑J��
//=============================================================================
State* OffenseState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//if (D3DXVec3Length(&(*opponent->getPosition() - *recognitionBB->getMyPosition())) > TEMPLENGTH)
	//{
	//	return DeffenseState::getInstance();
	//}

	if (recognitionBB->flag)
	{
		return RecursionState::getInstance();
	}

	// �f�B�t�F���X��Ԃ֑J��
	// ���J�[�W������Ԃ֑J��
	// �_�E����Ԃ֑J��
	// ����Ԃ֑J��

	return this;
}


//=============================================================================
// �f�B�t�F���X��Ԃ���̑J��
//=============================================================================
State* DeffenseState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	//Player* a = opponent;
	//if (D3DXVec3Length(&(*opponent->getPosition() - *recognitionBB->getMyPosition())) <= TEMPLENGTH)
	//{
	//	return OffenseState::getInstance();
	//}
	if (recognitionBB->flag)
	{
		return RecursionState::getInstance();
	}

	// �I�t�F���X��Ԃ֑J��
	// ���J�[�W������Ԃ֑J��
	// �_�E����Ԃ֑J��
	// ����Ԃ֑J��


	return this;
}


//=============================================================================
// ���J�[�W������Ԃ���̑J��
//=============================================================================
State* RecursionState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->flag == false)
	{
		return OffenseState::getInstance();
	}

	// �I�t�F���X��Ԃ֑J��
	// �f�B�t�F���X��Ԃ֑J��
	// �_�E����Ԃ֑J��
	// ����Ԃ֑J��

	return this;
}


//=============================================================================
// �_�E����Ԃ���̑J��
//=============================================================================
State* DownState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// �I�t�F���X��Ԃ֑J��
	// �f�B�t�F���X��Ԃ֑J��]
	return this;
}


//=============================================================================
// ����Ԃ���̑J��
//=============================================================================
State* SkyState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// ������Ԃ֑J��
	return this;
}


//=============================================================================
// ������ԏ�Ԃ���̑J��
//=============================================================================
State* FallState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// �I�t�F���X��Ԃ֑J��
	// �f�B�t�F���X��Ԃ֑J��
	return this;
}


///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// �X�e�[�g�}�V�� ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
// �R���X�g���N�^
//=============================================================================
StateMachine::StateMachine(void)
{
	// �X�e�[�g�𐶐�����
	OffenseState::create();
	DeffenseState::create();
	RecursionState::create();

	// �����X�e�[�g���Z�b�g����
	initialState = OffenseState::getInstance();
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
StateMachine::~StateMachine(void)
{
	// �X�e�[�g��j������
	OffenseState::destroy();
	DeffenseState::destroy();
	RecursionState::destroy();
}


//=============================================================================
// ���s
//=============================================================================
int StateMachine::run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	current = current->transition(recognitionBB, memoryBB, bodyBB);	// �J�ڂ�������
	return current->getNumber();									// �X�e�[�g�ԍ���Ԃ�
}