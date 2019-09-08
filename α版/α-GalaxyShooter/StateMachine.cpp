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
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{// ダウン状態へ遷移
		return DownState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// 上空状態へ遷移
		return SkyState::getInstance();
	}

	if (recognitionBB->getIsStartRecursion())
	{// リカージョン状態へ遷移
		return RecursionState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// ディフェンス状態へ遷移
		return DeffenseState::getInstance();
	}

	return this;
}


//=============================================================================
// ディフェンス状態からの遷移
//=============================================================================
State* DeffenseState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{// ダウン状態へ遷移
		return DownState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// 上空状態へ遷移
		return SkyState::getInstance();
	}

	if (recognitionBB->getIsStartRecursion())
	{// リカージョン状態へ遷移
		return RecursionState::getInstance();
	}

	//if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	//{// オフェンス状態へ遷移
	//	return OffenseState::getInstance();
	//}

	return this;
}


//=============================================================================
// リカージョン状態からの遷移
//=============================================================================
State* RecursionState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{// ダウン状態へ遷移
		// ●プレイヤーの方でリカージョン中のダウンや上空モードについて対策ができたらコメントアウト
		// メモリーパイルやメモリーラインのフラグを完全にリセットすればいけるはず
		//recognitionBB->setIsRecursionRunning(false);
		return DownState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// 上空状態へ遷移
		// ●プレイヤーの方でリカージョン中のダウンや上空モードについて対策ができたらコメントアウト
		// メモリーパイルやメモリーラインのフラグを完全にリセットすればいけるはず
		//recognitionBB->setIsRecursionRunning(false);
		return SkyState::getInstance();
	}

	if (recognitionBB->getIsRecursionRunning())
	{
		return this;	// リカージョン状態を継続する
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// オフェンス状態へ遷移
		return OffenseState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// ディフェンス状態へ遷移
		return DeffenseState::getInstance();
	}

	return this;// 警告防止（値を返さないこコントロールパス～）
}


//=============================================================================
// ダウン状態からの遷移
//=============================================================================
State* DownState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::SKY)
	{// 上空状態へ遷移
		return SkyState::getInstance();
	}

	if (recognitionBB->getPlayerState() == playerNS::DOWN)
	{
		return this;	// ダウン状態を継続する
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// オフェンス状態へ遷移
		return OffenseState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// ディフェンス状態へ遷移
		return DeffenseState::getInstance();
	}

	//return this;// 警告防止（値を返さないこコントロールパス～）
}


//=============================================================================
// 上空状態からの遷移
//=============================================================================
State* SkyState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::FALL)
	{// 落下状態へ遷移
		recognitionBB->setWhetherFallingDestinationDecided(false);
		return FallState::getInstance();
	}

	return this;
}


//=============================================================================
// 落下状態状態からの遷移
//=============================================================================
State* FallState::transition(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	if (recognitionBB->getPlayerState() == playerNS::FALL)
	{
		return this;
	}

	if (recognitionBB->getIsOpponentNear() || recognitionBB->getIsOpponentOffensive())
	{// オフェンス状態へ遷移
		return OffenseState::getInstance();
	}

	if (recognitionBB->getIsOpponentNear() == false
		&& recognitionBB->getIsOpponentOffensive() == false)
	{// ディフェンス状態へ遷移
		return DeffenseState::getInstance();
	}

	return this;// 警告防止（値を返さないこコントロールパス～）
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
	DownState::create();
	SkyState::create();
	FallState::create();

	// 初期ステートをセットする
	current = DeffenseState::getInstance();
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
	DownState::destroy();
	SkyState::destroy();
	FallState::destroy();
}


//=============================================================================
// 実行
//=============================================================================
int StateMachine::run(RecognitionBB* recognitionBB, MemoryBB* memoryBB, BodyBB* bodyBB)
{
	current = current->transition(recognitionBB, memoryBB, bodyBB);	// 遷移をさせる
	return current->getNumber();									// ステート番号を返す
}