//-----------------------------------------------------------------------------
// �X�e�[�g�}�V������ [StateMachine.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/20
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"

//*****************************************************************************
// �X�e�[�g�i��ԁj�ꗗ
//*****************************************************************************
// �X�e�[�g�}�V������transition()���R�[�����邱�ƂŎ����ŏ�ԑJ�ڂ��s��
// number�̓X�e�[�g�̃��j�[�N�L�[�ł���r�w�C�r�A�c���[�̔ԍ��ƘA������
// �e�X�e�[�g��Singleton�p�^�[����K�p���Ă���

//------------
// ���N���X
//------------
class State
{
protected:
	int number;

public:
	void setNumber(int _number) { number = _number; }
	int getNumber(void) { return number; }
	virtual State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB) = 0;
};

//------------
// �I�t�F���X
//------------
// ������_�E���������J�[�W�������邱�Ƃɒ��͂���U�����
class OffenseState: public State
{
private:
	// Data
	static OffenseState* instance;

	// Method
	OffenseState() { setNumber(BehaviorTreeNS::TREE::OFFENSE_TREE); }	
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new OffenseState; }
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//--------------
// �f�B�t�F���X
//--------------
// ���X�����m�����J�[�W�������ă`���M�����҂�������
class DeffenseState: public State
{
private:
	static DeffenseState* instance;

	DeffenseState() { setNumber(BehaviorTreeNS::TREE::DEFFENSE_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }	
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new DeffenseState; }
	// �X�e�[�g�J��
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//--------------
// ���J�[�W����
//--------------
// ���J�[�W�������s�����
class RecursionState : public State
{
private:
	static RecursionState* instance;

	RecursionState() { setNumber(BehaviorTreeNS::TREE::RECURSION_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new RecursionState; }
	// �X�e�[�g�J��
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//--------
// �_�E��
//--------
// �_�E�����
class DownState : public State
{
private:
	static DownState* instance;

	DownState() { setNumber(BehaviorTreeNS::TREE::DOWN_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new DownState; }
	// �X�e�[�g�J��
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//------
// ���
//------
// ��󃂁[�h�ɓ��������
class SkyState : public State
{
private:
	static SkyState* instance;

	SkyState() { setNumber(BehaviorTreeNS::TREE::SKY_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new SkyState; }
	// �X�e�[�g�J��
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//------
// ����
//------
// ��󂩂�n��ւ̗������

class FallState : public State
{
private:
	static FallState* instance;

	FallState() { setNumber(BehaviorTreeNS::TREE::FALL_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new FallState; }
	// �X�e�[�g�J��
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};


//*****************************************************************************
// �X�e�[�g�}�V��(��ԋ@�B)
//*****************************************************************************
class StateMachine
{
private:
	State* current;		// ���݂̃X�e�[�g

public:
	StateMachine();
	~StateMachine();
	int run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
