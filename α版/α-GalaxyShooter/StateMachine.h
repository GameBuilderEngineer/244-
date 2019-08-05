//-----------------------------------------------------------------------------
// ステートマシン処理 [StateMachine.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/20
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"

//*****************************************************************************
// ステート
//*****************************************************************************
class State// 基底クラス
{
protected:
	int number;					// ステート番号

	void setNumber(int _number) { number = _number; }
public:
	int getNumber(void) { return number; }
	// ステート遷移
	virtual State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB) = 0;
};

class Offense: public State
{
private:
	static Offense* instance;

	Offense() { setNumber(0); }	// ビヘイビアツリーの番号と合わせる
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new Offense; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

class Deffense: public State
{
private:
	static Deffense* instance;

	Deffense() { setNumber(1); }// ビヘイビアツリーの番号と合わせる
public:
	static void destroy(void) { SAFE_DELETE(instance) }	
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new Deffense; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};


//*****************************************************************************
// ステートマシン
//*****************************************************************************
class StateMachine
{
private:
	State* initialState;		// 初期ステート

public:
	StateMachine();
	~StateMachine();
	State* getInitialState(void) { return initialState; }
	// ステートマシンの実行
	static int run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
