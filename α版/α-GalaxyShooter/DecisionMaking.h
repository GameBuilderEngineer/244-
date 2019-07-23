//-----------------------------------------------------------------------------
// 意思決定処理 [DecisionMaking.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"
#include "StateMachine.h"
#include "BehaviorTree.h"
#include "BehaviorNodeBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class DecisionMaking: public KnowledgeSourceBase {
private:
	// Data
	RecognitionBB* recognitionBB;	// 環境認識
	MemoryBB* memoryBB;				// 記憶
	BodyBB* bodyBB;					// 身体状態
	StateMachine* stateMachine;		// ステートマシン
	BehaviorTree* behaviorTree;		// ビヘイビアツリー

	State* currentState;											// 現在のステート
	std::vector<BehaviorRecord> record[BehaviorTreeNS::NUM_TREE];	// ビヘイビアツリーのノード情報



public:
	// Method
	DecisionMaking(void);
	~DecisionMaking(void);
	void initialize(void) override;			// 初期化処理
	void uninitialize(void) override;		// 終了処理
	void update(void) override;				// 更新処理
	void setBlackBoard(RecognitionBB* adr1, MemoryBB* adr2, BodyBB* adr3) { recognitionBB = adr1; memoryBB = adr2; bodyBB = adr3; }
	void setStateMachine(StateMachine* adr) { stateMachine = adr; }
	void setBehaviorTree(BehaviorTree* adr) { behaviorTree = adr; }
};

