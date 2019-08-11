//-----------------------------------------------------------------------------
// エージェントAI処理 [AgentAI.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "Player.h"
#include "arbiter.h"
#include "Sensor.h"
#include "EnvironmentAnalysis.h"
#include "PathPlanning.h"
#include "DecisionMaking.h"
#include "MotionGeneration.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardBody.h"
#include "BlackBoardMemory.h"
#include "StateMachine.h"
#include "BehaviorTree.h"


//*****************************************************************************
// クラス定義
//*****************************************************************************
class AgentAI: public Player
{
private:
	static int				numAgent;				// AIの数  
	int						aiID;					// AIの固有識別番号
	Player*					opponentPlayer;			// 対戦相手
	float					frameTime;				// 1フレームあたりの時間

	// アービター：			各モジュールのタイミングや切り替えを制御
	Arbiter					*arbiter;

	// ナレッジソース：		ブラックボードを読み書きしながらAIを動かす
	Sensor					*sensor; 				// センサー 
	EnvironmentAnalysis		*environmentAnalysis; 	// 環境解析
	PathPlanning			*pathPlanning;			// 経路探索
	DecisionMaking			*decisionMaking;		// 意思決定　
	MotionGeneration		*motionGeneration;		// 運動生成

	// ブラックボード：		AIの記憶や身体状態を記録する黒板的概念
	RecognitionBB			*recognitionBB; 		// 環境認識
	MemoryBB				*memoryBB; 				// 記憶
	BodyBB					*bodyBB; 				// 身体状態

	// プレイヤー処理の事前更新
	void updatePlayerBefore(float frameTime);
	// プレイヤー処理の事後更新
	void updatePlayerAfter(float frameTime);
	// プレイヤー自己情報→AIに送信 
	void updateAgentSelfData(void);

public:
	AgentAI(Player* opponentPlayer);
	~AgentAI(void);

	// 初期化処理
	void initialize(int playerType, PDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader,
		TextureLoader* textureLoader, ShaderLoader* shaderLoader) override;
	// 終了処理
	void uninitialize(void);
	// 更新処理
	void update(float frameTime) override;
	// バレットの発射
	void shootBullet(D3DXVECTOR3 targetDirection);
	// メモリーパイルの設置
	void locateMemoryPile(void);
};