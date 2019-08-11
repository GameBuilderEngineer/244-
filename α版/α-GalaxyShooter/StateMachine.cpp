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

static const float TEMPLENGTH = 50.0f;

//=============================================================================
// ステートごとの遷移
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
// ステートマシン
//=============================================================================
// コンストラクタ
StateMachine::StateMachine(void)
{
	Offense::create();
	Deffense::create();
	initialState = Deffense::getInstance();
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