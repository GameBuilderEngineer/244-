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

//----------
// 定数定義
//----------
namespace EnvilonmentAnalysisNs
{
	static const int	NUM_NEARLEST_NODE = 3;					// リカージョン範囲を調べるマップノードの候補数
	static const int	NUM_TEST_SIZE = 3;						// リカージョンの大きさ（BSのサイズ）の数
	static const int	NUM_TEST_ARROUND = 5;					// １つのノードの周囲でBSを当てる箇所の数
	static const int	NUM_TEST_ZONE = NUM_TEST_ARROUND + 1;	// ノード自体の座標も含めてBSを当てる箇所の総数
	static const int	NUM_TEST_CASES_PER_NODE = NUM_TEST_SIZE * NUM_TEST_ZONE;// 一つのノードについて衝突検知の試行回数
	static const float	TEST_SIZE_RADIUS_BASE = 15.0f;			// リカージョンエリア判定用BSの基本半径
	static const float	TEST_SIZE_RADIUS_ADD = 10.0f;			// リカージョンエリア判定用BSの追加半径
}

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

	void selectMapNode(MapNode* nearestNode[], int* numNearestNode, AgentAI* agentAI);
	void checkRecursionArea(RecursionRecognition recursionRecognition[], MapNode* nearestNode[],
		int numNearestNode, AgentAI* agentAI);
	void selectRecursionArea(int selectionRecognition[], RecursionRecognition recursionRecognition[],
		MapNode* nearestNode[], int numNearestNode, AgentAI* agentAI);
	void makeCoordForPile(int selectionRecognition[], RecursionRecognition recursionRecognition[], AgentAI* agentAI);

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
	void debugRender(AgentAI* agentAI);		// デバッグ描画処理
};