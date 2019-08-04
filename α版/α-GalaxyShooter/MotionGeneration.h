//-----------------------------------------------------------------------------
// 運動生成処理 [MotionGeneration.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------

#pragma once
#include "KnowledgeSourceBase.h"

namespace MotionGenerationNS
{
	static const float STOP_MOVE_LENGTH = 3.0f;		// 2.0だと止まらない4.0以上だと停止位置のずれが大きい
	static const float LANDING_JUDGE_LENGTH = 3.0f;	// いい塩梅がよくわからないからテキトー
}

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
	void initialize(void) override;
	void uninitialize(void) override;
	void update(AgentAI* agentAI) override;
	void setBlackBoard(MemoryBB* adr1, BodyBB* adr2) { memoryBB = adr1; bodyBB = adr2; }

	void move(AgentAI* agentAI, D3DXVECTOR3* targetCoordinates);	// 移動
	bool autoStop(D3DXVECTOR3* position1, D3DXVECTOR3* position2);	// 自動停止
	void jumpFlagCycle(AgentAI* agentAI);


};