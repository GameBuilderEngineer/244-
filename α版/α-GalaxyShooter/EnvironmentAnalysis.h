//-----------------------------------------------------------------------------
// 環境解析処理 [EnvironmentAnalysis.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"
#include "Fuzzy.h"
#include "BoundingSphere.h"
#include "RecursionRecognition.h"
#include "Ray.h"


//*****************************************************************************
// クラス定義
//*****************************************************************************
class EnvironmentAnalysis:public KnowledgeSourceBase {
private:
	RecognitionBB* recognitionBB;			// 環境認識ブラックボード
	std::vector<Wasuremono*>* wasuremono;	// ワスレモノ
	Fuzzy fuzzy;							// ファジー理論処理
	int mapTimeCount;
	int forgettingTimeMap;
	int bulletTimeCount;
	int forgettingTimeBullet;

	BoundingSphere* recursionSphere;						// リカージョン候補座標算出用BS
	float recursionRadius;
	D3DXVECTOR3 checkPosition;
	D3DXVECTOR3 posCandidate[7/*適当*/][5/*パイルの数*/];	// リカージョン候補座標
	Ray ray;


public:
	// Method
	EnvironmentAnalysis(std::vector<Wasuremono*>* _wasuremono);
	~EnvironmentAnalysis(void);
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }
	void initialize(void) override;			// 初期化処理
	void uninitialize(void) override;		// 終了処理
	void update(AgentAI* agentAI) override;	// 更新処理
	void virtualRecursion(AgentAI* agentAI);
	void recognizeRecursionArea(AgentAI* agentAI, D3DXVECTOR3* checkPosition, RecursionRecognition* recursionRecognition);
	void forgetMemorizedMatter(void);		// 記憶事項を忘却
};