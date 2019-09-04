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
	// バトル状況解析
	const float	LENGTH_OPPONENT_IS_NEAR = 30.0f;		// 相手が近い判断するベクトルの長さ
	const int	BULLET_TWO_VECTOR_ANGLE_DEGREE = 4;		// バレット⇔自分ベクトルとバレットスピードベクトルの角度差
	const float LENGHT_BULLET_IS_NEAR = 8.0f;			// バレットが近いと判断するベクトルの長さ
	const float LOSING_WAGE_DEFFERENSE = -600;			// チンギン額で差をつけられていると見なすチンギンの相手との差額

	const int	VIRTUAL_RECURSION_FPS = 20;				// 仮想リカージョン更新FPS

	// 仮想リカージョン試行回数関係
	const int	NUM_NEARLEST_NODE = 3;					// リカージョン範囲を調べるマップノードの候補数
	const int	NUM_TEST_SIZE = 3;						// リカージョンの大きさ（BSのサイズ）の数
	const int	NUM_TEST_ARROUND = 5;					// １つのノードの周囲でBSを当てる箇所の数
	const int	NUM_TEST_ZONE = NUM_TEST_ARROUND + 1;	// ノード自体の座標も含めてBSを当てる箇所の総数
	const int	NUM_TEST_CASES_PER_NODE = NUM_TEST_SIZE * NUM_TEST_ZONE;// 一つのノードについて衝突検知の試行回数

	// リカージョンエリア判定用バウンディングスフィア
	const float	TEST_SIZE_RADIUS_BASE = 10.0f;			// 基本半径
	const float	TEST_SIZE_RADIUS_ADD = 10.0f;			// 追加半径
	const float  TEST_SIZE_RADIUS_FUZZY_ADJUST = 10.0f;	// サイズ集合が各1.0のときに含む実際のBS半径の最小最大との差
	const float  AXIS_TILT_ANGLE_FOR_SMALL_BS = 0.22f;	// サイズに応じた配置半径を作るためレイを傾ける角度
	const float  AXIS_TILT_ANGLE_FOR_MIDDLE_BS = 0.3f;	// サイズに応じた配置半径を作るためレイを傾ける角度
	const float  AXIS_TILT_ANGLE_FOR_BIG_BS = 0.42f;		// サイズに応じた配置半径を作るためレイを傾ける角度

	// ※ファジー入力値算出にあたっての定数は直接selectRecursionArea()をいじる方が早いのでここには記載しない
}


//*****************************************************************************
// クラス定義
//*****************************************************************************
class EnvironmentAnalysis:public KnowledgeSourceBase {
private:
	//------
	// Data
	//------
	RecognitionBB* recognitionBB;			// 環境認識ブラックボード
	std::vector<Wasuremono*>* wasuremono;	// ワスレモノ
	Fuzzy fuzzy;							// ファジー理論処理
	Ray ray;								// 汎用レイ

	// バトル状況関係
	bool isOpponentNear;					// 敵が違い
	bool isOpponentOffensive;				// 敵が攻撃的である
	bool isBulletNear;						// バレットが近い
	bool isChinginLow;						// チンギンが低い

	// 仮想リカージョン関係
	int vRecursionFrameCount;				// 更新カウント
	BoundingSphere* recursionSphere;		// リカージョン候補座標算出用BSポインタ

	// 記憶処理関係
	int mapTimeCount;						// マップ記憶フレームカウンタ
	int forgettingTimeMap;					// マップ記憶維持フレーム数
	int bulletTimeCount;					// バレット記憶フレームカウンタ
	int forgettingTimeBullet;				// バレット記憶維持フレーム数

	//--------
	// Method
	//--------
	// バトル状況を解析
	void analyzeBattle(AgentAI* agentAI);
	// メモリーライン切断座標を算出
	void makeCoordForCut(AgentAI* agentAI);
	// 仮想リカージョン
	void virtualRecursion(AgentAI* agentAI);
	//（仮想リカージョンステップその１）近いマップノードで候補を絞る
	void selectMapNode(MapNode* nearestNode[], int* numNearestNode, AgentAI* agentAI);
	//（仮想リカージョンステップその２）リカージョン場所の認識をストックする
	void recognizeRecursionArea(RecursionRecognition recursionRecognition[], MapNode* nearestNode[],
		int numNearestNode, AgentAI* agentAI);
	//（仮想リカージョンステップその３）リカージョン認識の数を絞る
	void selectRecursionArea(int selectionRecognition[], RecursionRecognition recursionRecognition[],
		MapNode* nearestNode[], int numNearestNode, AgentAI* agentAI);
	//（仮想リカージョンステップその４）メモリーパイルを打ち込む座標を作る
	void makeCoordForPile(int selectionRecognition[], RecursionRecognition recursionRecognition[], AgentAI* agentAI);
	// リカージョン認識への代入処理（スフィアとワスレモノの衝突判定）
	void hitCheckAndAssign(AgentAI* agentAI, D3DXVECTOR3* checkPosition,
		RecursionRecognition* recursionRecognition, int index, float circumscribedRadius);
	// 記憶事項を忘却
	void forgetMemorizedMatter(void);

public:
	EnvironmentAnalysis(std::vector<Wasuremono*>* _wasuremono);
	~EnvironmentAnalysis(void);
	void setBlackBoard(RecognitionBB* adr) { recognitionBB = adr; }
	void initialize(void) override;			// 初期化処理
	void uninitialize(void) override;		// 終了処理
	void update(AgentAI* agentAI) override;	// 更新処理
	void debugRender(AgentAI* agentAI);		// デバッグ描画処理
};