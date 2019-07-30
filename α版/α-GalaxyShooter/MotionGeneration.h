//-----------------------------------------------------------------------------
// 運動生成処理 [MotionGeneration.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MotionGeneration:public KnowledgeSourceBase {
private:
	MemoryBB* memoryBB;
	BodyBB* bodyBB;

public:
	// Method
	MotionGeneration(void);
	~MotionGeneration(void);
	void initialize(void) override;		// 初期化処理
	void uninitialize(void) override;	// 終了処理
	void update(AgentAI* agentAI) override;// 更新処理
	void setBlackBoard(MemoryBB* adr1, BodyBB* adr2) { memoryBB = adr1; bodyBB = adr2; }

	void move(AgentAI* agentAI, D3DXVECTOR3 targetCoordinates);

};