//-----------------------------------------------------------------------------
// ステートマシン処理 [StateMachine.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/20
//-----------------------------------------------------------------------------
#include "AICommon.h"
#include "StateMachine.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
Offense* Offense::instance;
Deffense* Deffense::instance;


//=============================================================================
// ステートごとの遷移
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
// ステートマシン
//=============================================================================
// コンストラクタ
StateMachine::StateMachine(void)
{
	Offense::create();
	Deffense::create();
	initialState = Offense::getInstance();
}

// デストラクタ
StateMachine::~StateMachine(void)
{
	Offense::destroy();
	Deffense::destroy();
}

// 実行
int StateMachine::run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	current = current->transition(recognitionBB, memoryBB, bodyBB);
	return current->getNumber();
}