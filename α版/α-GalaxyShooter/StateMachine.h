//-----------------------------------------------------------------------------
// ステートマシン処理 [StateMachine.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/20
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"

//*****************************************************************************
// ステート（状態）一覧
//*****************************************************************************
// ステートマシンからtransition()をコールすることで自動で状態遷移を行う
// numberはステートのユニークキーでありビヘイビアツリーの番号と連動する
// 各ステートはSingletonパターンを適用している

//------------
// 基底クラス
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
// オフェンス
//------------
// 相手をダウンさせリカージョンすることに注力する攻撃状態
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
// ディフェンス
//--------------
// ワスレモノをリカージョンしてチンギンを稼ぐ守備状態
class DeffenseState: public State
{
private:
	static DeffenseState* instance;

	DeffenseState() { setNumber(BehaviorTreeNS::TREE::DEFFENSE_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }	
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new DeffenseState; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//--------------
// リカージョン
//--------------
// リカージョン実行中状態
class RecursionState : public State
{
private:
	static RecursionState* instance;

	RecursionState() { setNumber(BehaviorTreeNS::TREE::RECURSION_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new RecursionState; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//-----------------------
// リカージョン（相手版）
//-----------------------
// リカージョン実行中状態
class RecursionOpponentState : public State
{
private:
	static RecursionOpponentState* instance;

	RecursionOpponentState() { setNumber(BehaviorTreeNS::TREE::RECURSION_TREE_OPPONENT_VER); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new RecursionOpponentState; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//--------
// ダウン
//--------
// ダウン状態
class DownState : public State
{
private:
	static DownState* instance;

	DownState() { setNumber(BehaviorTreeNS::TREE::DOWN_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new DownState; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//------
// 上空
//------
// 上空モードに入った状態
class SkyState : public State
{
private:
	static SkyState* instance;

	SkyState() { setNumber(BehaviorTreeNS::TREE::SKY_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new SkyState; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};

//------
// 落下
//------
// 上空から地上への落下状態

class FallState : public State
{
private:
	static FallState* instance;

	FallState() { setNumber(BehaviorTreeNS::TREE::FALL_TREE); }
public:
	static void destroy(void) { SAFE_DELETE(instance) }
	static State* getInstance(void) { return instance; }
	static void create(void) { if (!instance)instance = new FallState; }
	// ステート遷移
	State* transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};


//*****************************************************************************
// ステートマシン(状態機械)
//*****************************************************************************
class StateMachine
{
private:
	State* current;		// 現在のステート

public:
	StateMachine();
	~StateMachine();
	int run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB);
};
