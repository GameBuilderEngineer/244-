//-----------------------------------------------------------------------------
// �X�e�[�g�}�V������ [StateMachine.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/20
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"

//*****************************************************************************
// �X�e�[�g
//*****************************************************************************
class State// ���N���X
{
protected:
	int number;					// �X�e�[�g�ԍ�

	void setNumber(int _number) { number = _number; }
public:
	int getNumber(void) { return number; }
	// �X�e�[�g�J��
	virtual State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB) = 0;
};

class Offense: public State
{
private:
	static Offense* instance;

	Offense() { setNumber(0); }	// �r�w�C�r�A�c���[�̔ԍ��ƍ��킹��
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new Offense; }
	// �X�e�[�g�J��
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

class Deffense: public State
{
private:
	static Deffense* instance;

	Deffense() { setNumber(1); }// �r�w�C�r�A�c���[�̔ԍ��ƍ��킹��
public:
	static void destroy(void) { SAFE_DELETE(instance) }	
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new Deffense; }
	// �X�e�[�g�J��
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};


//*****************************************************************************
// �X�e�[�g�}�V��
//*****************************************************************************
class StateMachine
{
private:
	State* initialState;		// �����X�e�[�g

public:
	StateMachine();
	~StateMachine();
	State* getInitialState(void) { return initialState; }
	// �X�e�[�g�}�V���̎��s
	static int run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
