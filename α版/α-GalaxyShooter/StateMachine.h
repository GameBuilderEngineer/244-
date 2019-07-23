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
	Offense() { setNumber(0); }// ビヘイビアツリーの番号と合わせる
public:
	static void destroy(void) { SAFE_DELETE(instance) }					// インスタンス破棄
	static State* getInstance(void) { return instance; }				// インスタンス取得
	static void create(void) { if (!instance)instance = new Offense; }	// インスタンス生成
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

class Deffense: public State
{
private:
	static Deffense* instance;

	// Method
	Deffense() { setNumber(1); }// ビヘイビアツリーの番号と合わせる
public:
	static void destroy(void) { SAFE_DELETE(instance) }					// インスタンス破棄
	static State* getInstance(void) { return instance; }				// インスタンス取得
	static void create(void) { if (!instance)instance = new Deffense; }	// インスタンス生成
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};


//*****************************************************************************
// ステートマシン
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
	static void create(void) { if (!instance)instance = new StateMachine; }	// インスタンス生成
	static void destroy(void) { SAFE_DELETE(instance) }						// インスタンス破棄
	static StateMachine* getInstance(void) { return instance; }				// インスタンス取得
	int run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);// 実行
};
