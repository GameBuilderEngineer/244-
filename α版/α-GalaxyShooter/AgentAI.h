//-----------------------------------------------------------------------------
// エージェントAI処理 [AgentAI.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "Camera.h"
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
#include "Sound.h"

//*****************************************************************************
// エージェントAI
//*****************************************************************************
class AgentAI: public Player
{
private:
	//------
	// Data
	//------
	static int				numAgent;				// AIの数  
	int						aiID;					// AIの固有識別番号
	float					frameTime;				// 1フレームあたりの時間
	float					virticalTime;			// オートカメラの縦首振り時間
	float					horizontalTime;			// オートカメラの横首振り時間

	// アービター：			各モジュールのタイミングや切り替えを制御
	Arbiter					*arbiter;

	// ナレッジソース：		ブラックボードを読み書きしながらAIを動かす
	Sensor					*sensor; 				// センサー *マップや相手の情報を収集
	EnvironmentAnalysis		*environmentAnalysis; 	// 環境解析 *リカージョン座標決めなど
	PathPlanning			*pathPlanning;			// 経路探索 *ほぼ処理なし
	DecisionMaking			*decisionMaking;		// 意思決定 *ビヘイビアツリーによる行動決定
	MotionGeneration		*motionGeneration;		// 運動生成 *各アクションのフラグ管理

	// ブラックボード：		AIの記憶や身体状態を記録する黒板的概念
	RecognitionBB			*recognitionBB; 		// 環境認識
	MemoryBB				*memoryBB; 				// 記憶
	BodyBB					*bodyBB; 				// 身体状態


	//--------
	// Method
	//--------
	// プレイヤー処理の事前更新
	void updatePlayerBefore(float frameTime);
	// プレイヤー処理の事後更新
	void updatePlayerAfter(float frameTime);
	// プレイヤー自己情報→AIに送信 
	void updateAgentSelfData(void);
	// オートカメラ操作
	void autoCamera(void);
	// 水平ロックオン
	void lockOnHorizontally(D3DXVECTOR3 lockOnTarget, float frameTime);
	// 3次元ロックオン（未完）
	void lockOn3D(D3DXVECTOR3 lockOnTarget, float frameTime);

public:
	AgentAI(Player* opponentPlayer, Camera* camera, std::vector<Wasuremono*>* wasuremono);
	~AgentAI(void);
	// 初期化処理
	void initialize(int playerType, int modelType, PDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader,
		TextureLoader* textureLoader, ShaderLoader* shaderLoader) override;
	// 終了処理
	void uninitialize(void);
	// 更新処理
	void update(float frameTime) override;
	// 描画処理
	void debugRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	// バレットの発射
	void shootBullet(D3DXVECTOR3 targetDirection);
	// メモリーパイルの設置
	void locateMemoryPile(void);
	// メモリーライン切断
	void cutMemoryLine(void);
	// 復活ポイント増加
	void increaseRevivalPoint(void);
};