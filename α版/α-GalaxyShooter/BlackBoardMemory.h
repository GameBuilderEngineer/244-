//-----------------------------------------------------------------------------
// 記憶ブラックボード処理 [BlackBoardMemory.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "BlackBoardBase.h"
#include <unordered_map>
#include "Map.h"


// 前方宣言
class BehaviorNodeBase;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MemoryBB : public BlackBoardBase {
private:
	std::unordered_map<BehaviorNodeBase*, int> onOffRecord;	// ONOFFノードの記録
	std::unordered_map<BehaviorNodeBase*, int> timer;		// タイマー
	// ●アロケータだけにする初期化をねんのためいれておくよてい

	std::vector<MapNode*> memorizedMap;


public:
	// Method
	MemoryBB(void);
	void initialize(void) override;				// 初期化処理

	std::unordered_map<BehaviorNodeBase*, int>& getOnOffRecord(void) { return onOffRecord; }
	std::unordered_map<BehaviorNodeBase*, int>& getTimer(void) { return timer; }
	std::vector<MapNode*>& getMemorizedMap(void) { return memorizedMap; }

};