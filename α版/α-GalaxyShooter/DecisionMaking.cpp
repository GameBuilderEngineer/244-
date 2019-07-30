//-----------------------------------------------------------------------------
// 意思決定処理 [DecisionMaking.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "DecisionMaking.h"
#include "AgentAI.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
StateMachine* DecisionMaking::stateMachine = NULL;
BehaviorTree* DecisionMaking::behaviorTree = NULL;


//=============================================================================
// コンストラクタ
//=============================================================================
DecisionMaking::DecisionMaking(void)
{
	// ステートマシンとビヘイビアツリーを静的メンバに生成（AgentAI共用のため）
	if (!stateMachine) { stateMachine = new StateMachine; }
	if (!behaviorTree) { behaviorTree = new BehaviorTree; }

	// 初期ステートを設定
	currentState = stateMachine->getInitialState();
}


//=============================================================================
// デストラクタ
//=============================================================================
DecisionMaking::~DecisionMaking(void)
{
	// ステートマシンとビヘイビアツリーを破棄
	SAFE_DELETE(stateMachine)
	SAFE_DELETE(behaviorTree)
}


//=============================================================================
// 初期化処理
//=============================================================================
void DecisionMaking::initialize(void)
{

}


//=============================================================================
// 終了処理
//=============================================================================
void DecisionMaking::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void DecisionMaking::update(AgentAI* agentAI)
{
	int treeNumber = stateMachine->run(currentState, recognitionBB, memoryBB, bodyBB);
	behaviorTree->run(treeNumber, recognitionBB, memoryBB, bodyBB);
}
