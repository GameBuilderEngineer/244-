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
	// Data
	int number;

	// Method
	void setNumber(int _number) { number = _number; }
public:
	int getNumber(void) { return number; }
	virtual State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB) = 0;
};

class Offense: public State
{
private:
	static Offense* instance;

	// Method
	Offense() { setNumber(0); }// �r�w�C�r�A�c���[�̔ԍ��ƍ��킹��
public:
	static void destroy(void) { SAFE_DELETE(instance) }					// �C���X�^���X�j��
	static State* getInstance(void) { return instance; }				// �C���X�^���X�擾
	static void create(void) { if (!instance)instance = new Offense; }	// �C���X�^���X����
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

class Deffense: public State
{
private:
	static Deffense* instance;

	// Method
	Deffense() { setNumber(1); }// �r�w�C�r�A�c���[�̔ԍ��ƍ��킹��
public:
	static void destroy(void) { SAFE_DELETE(instance) }					// �C���X�^���X�j��
	static State* getInstance(void) { return instance; }				// �C���X�^���X�擾
	static void create(void) { if (!instance)instance = new Deffense; }	// �C���X�^���X����
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};


//*****************************************************************************
// �X�e�[�g�}�V��
//*****************************************************************************
class StateMachine
{
private:
	// Data
	static StateMachine* instance;

	// Method
	StateMachine();
	~StateMachine();
public:
	static void create(void) { if (!instance)instance = new StateMachine; }	// �C���X�^���X����
	static void destroy(void) { SAFE_DELETE(instance) }						// �C���X�^���X�j��
	static StateMachine* getInstance(void) { return instance; }				// �C���X�^���X�擾
	int run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);// ���s
};
