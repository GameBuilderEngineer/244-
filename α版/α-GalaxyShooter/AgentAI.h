//-----------------------------------------------------------------------------
// エージェントAI処理 [AgentAI.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "arbiter.h"
#include "Sensor.h"
#include "EnvironmentAnalysis.h"
#include "PathPlanning.h"
#include "DecisionMaking.h"
#include "MotionGeneration.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardBody.h"
#include "BlackBoardMemory.h"



//*****************************************************************************
// クラス定義
//*****************************************************************************
class AgentAI {
private:
	// アービター：各モジュールのタイミングや切り替えを制御
	Arbiter *arbiter;								// 調停者（Arbiter）

	// AIモジュール（ナレッジソース）：ブラックボードを読み書きしながらAIを動かす
	Sensor					*sensor; 				// センサー 
	EnvironmentAnalysis		*environmentAnalysis; 	// 環境解析
	PathPlanning			*pathPlanning;			// 経路探索
	DecisionMaking			*decisionMaking;		// 意思決定　
	MotionGeneration		*motionGeneration;		// 運動生成

	// ブラックボード：AIの記憶や身体状態を記録する黒板的概念
	RecognitionBB			*recognitionBB; 		// 環境認識
	BodyBB					*bodyBB; 				// 身体状態
	MemoryBB				*memoryBB; 				// 記憶

	// Playerクラスに必要だと思われる
	//bool isNPC;
	//int characterID;

	// Data
	int aiID;							// AIの固有識別番号

public:
	// Method
	AgentAI(void);
	~AgentAI(void);
	void initialize(void);				// 初期化処理
	void uninitialize(void);			// 終了処理
	void run(void);						// 実行
};