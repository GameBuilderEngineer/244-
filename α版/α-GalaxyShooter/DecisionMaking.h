//-----------------------------------------------------------------------------
// 意思決定処理 [DecisionMaking.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "StateMachine.h"
#include "BehaviorTree.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class DecisionMaking: public KnowledgeSourceBase {
private:
	// Data
	RecognitionBB* recognitionBB;			// 環境認識
	MemoryBB* memoryBB;						// 記憶
	BodyBB* bodyBB;							// 身体状態
	State* currentState;					// 現在のステート

	static StateMachine* stateMachine;
	static BehaviorTree* behaviorTree;
	
public:
	// Method
	DecisionMaking(void);
	~DecisionMaking(void);
	void initialize(void) override;			// 初期化処理
	void uninitialize(void) override;		// 終了処理
	void update(AgentAI* agentAI) override;	// 更新処理
	void setBlackBoard(RecognitionBB* adr1, MemoryBB* adr2, BodyBB* adr3) { recognitionBB = adr1; memoryBB = adr2; bodyBB = adr3; }
};

