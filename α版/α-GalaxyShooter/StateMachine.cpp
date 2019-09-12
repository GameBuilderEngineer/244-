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
RecursionOpponentState* RecursionOpponentState::instance;
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
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{// �_�E����Ԃ֑J��
		return DownState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// ����Ԃ֑J��
		return SkyState::getInstance();
	}

	if (recognitionBB->getIsStartRecursion())
	{// ���J�[�W������Ԃ֑J��
		recognitionBB->setIsStartRecursion(false);
		return RecursionState::getInstance();
	}

	if (recognitionBB->getIsStartRecursionForOpponent())
	{// ���J�[�W�����i����j��Ԃ֑J��
		recognitionBB->setIsStartRecursionForOpponent(false);
 		return RecursionOpponentState::getInstance();
	}

	static int cnt = 0;
	cnt++;
	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false
		&& cnt > 60)
	{// �f�B�t�F���X��Ԃ֑J��
		cnt = 0;
		return DeffenseState::getInstance();
	}

	return this;
}


//=============================================================================
// �f�B�t�F���X��Ԃ���̑J��
//=============================================================================
State* DeffenseState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{// �_�E����Ԃ֑J��
		return DownState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// ����Ԃ֑J��
		return SkyState::getInstance();
	}

 	if (recognitionBB->getIsStartRecursion())
	{// ���J�[�W������Ԃ֑J��
		recognitionBB->setIsStartRecursion(false);
		return RecursionState::getInstance();
	}

	if (recognitionBB->getIsStartRecursionForOpponent())
	{// ���J�[�W�����i����j��Ԃ֑J��
		recognitionBB->setIsStartRecursionForOpponent(false);
		return RecursionOpponentState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// �I�t�F���X��Ԃ֑J��
		return OffenseState::getInstance();
	}

	return this;
}


//=============================================================================
// ���J�[�W������Ԃ���̑J��
//=============================================================================
State* RecursionState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{// �_�E����Ԃ֑J��
		recognitionBB->setIsRecursionRunning(false);
		recognitionBB->setNextElementMemoryPile(0);
		return DownState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// ����Ԃ֑J��
		recognitionBB->setIsRecursionRunning(false);
		recognitionBB->setNextElementMemoryPile(0);
		return SkyState::getInstance();
	}

	if (recognitionBB->getIsRecursionRunning())
	{
		// ���}����
		static int cnt = 0;
		cnt++;
		if ((recognitionBB->getElementMemoryPile() == 0 &&
			recognitionBB->getNextElementMemoryPile() > 0) || cnt > 600)
		{//	�J�ڈȊO�̗v���Ń��J�[�W�������I�������ꍇ
			recognitionBB->setIsRecursionRunning(false);
			recognitionBB->setNextElementMemoryPile(0);
			cnt = 0;
		}
		else
		{
			recognitionBB->setNextElementMemoryPile(recognitionBB->getElementMemoryPile());
			return this;	// ���J�[�W������Ԃ��p������
		}
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// �I�t�F���X��Ԃ֑J��
		recognitionBB->setNextElementMemoryPile(0);
		return OffenseState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// �f�B�t�F���X��Ԃ֑J��
		recognitionBB->setNextElementMemoryPile(0);
		return DeffenseState::getInstance();
	}

	return this;// �x���h�~�i�l��Ԃ��Ȃ��R���g���[���p�X�`�j
}


//=============================================================================
// ���J�[�W�����i����j��Ԃ���̑J��
//=============================================================================
State* RecursionOpponentState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{// �_�E����Ԃ֑J��
		recognitionBB->setIsRecursionRunning(false);
		recognitionBB->setNextElementMemoryPile(0);
		return DownState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// ����Ԃ֑J��
		recognitionBB->setIsRecursionRunning(false);
		recognitionBB->setNextElementMemoryPile(0);
		return SkyState::getInstance();
	}

	if (recognitionBB->getIsRecursionRunning())
	{
		if (recognitionBB->getElementMemoryPile() == 0 &&
			recognitionBB->getNextElementMemoryPile() > 0 )
		{//	�J�ڈȊO�̗v���Ń��J�[�W�������I�������ꍇ
			recognitionBB->setIsRecursionRunning(false);
			recognitionBB->setNextElementMemoryPile(0);
		}
		else
		{
			recognitionBB->setNextElementMemoryPile(recognitionBB->getElementMemoryPile());
			return this;	// ���J�[�W������Ԃ��p������
		}
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// �I�t�F���X��Ԃ֑J��
		recognitionBB->setNextElementMemoryPile(0);
		return OffenseState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// �f�B�t�F���X��Ԃ֑J��
		recognitionBB->setNextElementMemoryPile(0);
		return DeffenseState::getInstance();
	}

	return this;// �x���h�~�i�l��Ԃ��Ȃ��R���g���[���p�X�`�j
}


//=============================================================================
// �_�E����Ԃ���̑J��
//=============================================================================
State* DownState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// ����Ԃ֑J��
		return SkyState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{
		return this;	// �_�E����Ԃ��p������
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// �I�t�F���X��Ԃ֑J��
		return OffenseState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// �f�B�t�F���X��Ԃ֑J��
		return DeffenseState::getInstance();
	}

	return this;// �x���h�~�i�l��Ԃ��Ȃ����R���g���[���p�X�`�j
}


//=============================================================================
// ����Ԃ���̑J��
//=============================================================================
State* SkyState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::FALL)
	{// ������Ԃ֑J��
		recognitionBB->setWhetherDestinationDecided(false);
		return FallState::getInstance();
	}

	return this;
}


//=============================================================================
// ������ԏ�Ԃ���̑J��
//=============================================================================
State* FallState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::FALL)
	{
		return this;
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// �I�t�F���X��Ԃ֑J��
		return OffenseState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// �f�B�t�F���X��Ԃ֑J��
		return DeffenseState::getInstance();
	}

	return this;// �x���h�~�i�l��Ԃ��Ȃ����R���g���[���p�X�`�j
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
	RecursionOpponentState::create();
	DownState::create();
	SkyState::create();
	FallState::create();

	// �����X�e�[�g���Z�b�g����
	current = DeffenseState::getInstance();
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
	RecursionOpponentState::destroy();
	DownState::destroy();
	SkyState::destroy();
	FallState::destroy();
}


//=============================================================================
// ���s
//=============================================================================
int StateMachine::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	current = current->transition(recognitionBB, memoryBB, bodyBB);	// �J�ڂ�������
	return current->getNumber();									// �X�e�[�g�ԍ���Ԃ�
}