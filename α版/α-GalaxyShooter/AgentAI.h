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
#include "Sound.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class AgentAI: public Player {
private:
	// Data
	static int	numAgent;	// AIの数  
	int			aiID;		// AIの固有識別番号

	// アービター：各モジュールのタイミングや切り替えを制御
	Arbiter *arbiter;

	// AIモジュール（ナレッジソース）：ブラックボードを読み書きしながらAIを動かす
	Sensor					*sensor; 				// センサー 
	EnvironmentAnalysis		*environmentAnalysis; 	// 環境解析
	PathPlanning			*pathPlanning;			// 経路探索
	DecisionMaking			*decisionMaking;		// 意思決定　
	MotionGeneration		*motionGeneration;		// 運動生成

	// ブラックボード：AIの記憶や身体状態を記録する黒板的概念
	RecognitionBB			*recognitionBB; 		// 環境認識
	MemoryBB				*memoryBB; 				// 記憶
	BodyBB					*bodyBB; 				// 身体状態

public:
	// Method
	AgentAI(void);
	~AgentAI(void);
	void initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader, TextureLoader* textureLoader, ShaderLoader* shaderLoader);
	void uninitialize(void);						// 終了処理
	void update(Sound* _sound, float frameTime);	// 更新処理
};