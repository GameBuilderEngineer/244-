//-----------------------------------------------------------------------------
// 記憶ブラックボード処理 [BlackBoardMemory.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "BlackBoardBase.h"
#include "Map.h"
#include "Bullet.h"
#include <unordered_map>
#include <list>


// 前方宣言
class BehaviorNodeBase;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MemoryBB : public BlackBoardBase {
private:
	std::list<MapNode*> memorizedMap;						// マップ記憶リスト
	std::list<Bullet*> memorizedBullet;						// バレット記憶リスト
	std::unordered_map<BehaviorNodeBase*, int> onOffRecord;	// ONOFFノードの記録（ビヘイビアツリーで使用）
	std::unordered_map<BehaviorNodeBase*, int> timer;		// タイマー（ビヘイビアツリーで使用）
	std::unordered_map<BehaviorNodeBase*, bool> flag;		// フラグ（ビヘイビアツリーで使用）

public:
	// Method
	MemoryBB(void);
	void initialize(void) override;
	std::unordered_map<BehaviorNodeBase*, int>& getOnOffRecord(void) { return onOffRecord; }// ONOFFノード記録を取得
	std::unordered_map<BehaviorNodeBase*, int>& getTimer(void) { return timer; }// タイマー取得
	std::list<MapNode*>& getMemorizedMap(void) { return memorizedMap; }			// マップ記憶リストを取得
	std::list<Bullet*>& getMemorizedBullet(void) { return memorizedBullet; }	// バレット記憶リストを取得
};