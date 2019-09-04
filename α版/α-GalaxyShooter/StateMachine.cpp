//-----------------------------------------------------------------------------
// ステートマシン処理 [StateMachine.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/20
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
/////////////////////////////////// 状態遷移 //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
// オフェンス状態からの遷移
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

	// ディフェンス状態へ遷移
	// リカージョン状態へ遷移
	// ダウン状態へ遷移
	// 上空状態へ遷移

	return this;
}


//=============================================================================
// ディフェンス状態からの遷移
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

	// オフェンス状態へ遷移
	// リカージョン状態へ遷移
	// ダウン状態へ遷移
	// 上空状態へ遷移


	return this;
}


//=============================================================================
// リカージョン状態からの遷移
//=============================================================================
State* RecursionState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->flag == false)
	{
		return OffenseState::getInstance();
	}

	// オフェンス状態へ遷移
	// ディフェンス状態へ遷移
	// ダウン状態へ遷移
	// 上空状態へ遷移

	return this;
}


//=============================================================================
// ダウン状態からの遷移
//=============================================================================
State* DownState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// オフェンス状態へ遷移
	// ディフェンス状態へ遷移]
	return this;
}


//=============================================================================
// 上空状態からの遷移
//=============================================================================
State* SkyState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// 落下状態へ遷移
	return this;
}


//=============================================================================
// 落下状態状態からの遷移
//=============================================================================
State* FallState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	// オフェンス状態へ遷移
	// ディフェンス状態へ遷移
	return this;
}


///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// ステートマシン ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//=============================================================================
// コンストラクタ
//=============================================================================
StateMachine::StateMachine(void)
{
	// ステートを生成する
	OffenseState::create();
	DeffenseState::create();
	RecursionState::create();

	// 初期ステートをセットする
	initialState = OffenseState::getInstance();
}


//=============================================================================
// デストラクタ
//=============================================================================
StateMachine::~StateMachine(void)
{
	// ステートを破棄する
	OffenseState::destroy();
	DeffenseState::destroy();
	RecursionState::destroy();
}


//=============================================================================
// 実行
//=============================================================================
int StateMachine::run(State* current, RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	current = current->transition(recognitionBB, memoryBB, bodyBB);	// 遷移をさせる
	return current->getNumber();									// ステート番号を返す
}