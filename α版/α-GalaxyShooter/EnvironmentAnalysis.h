//-----------------------------------------------------------------------------
// 環境解析処理 [EnvironmentAnalysis.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "Fuzzy.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EnvironmentAnalysis:public KnowledgeSourceBase {
private:
	Fuzzy fuzzy;						// ファジー理論処理
	RecognitionBB* recognitionBB;

	

public:
	// Method
	EnvironmentAnalysis(void);
	~EnvironmentAnalysis(void);
	void initialize(void) override;			// 初期化処理
	void uninitialize(void) override;		// 終了処理
	void update(AgentAI* agentAI) override;	// 更新処理
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }

	
};