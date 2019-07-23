//-----------------------------------------------------------------------------
// ビヘイビアレコード [BehaviorRecord.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/17
//-----------------------------------------------------------------------------
#pragma once

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BehaviorRecord
{
private:
	int step;	// 子ノード何番目を実行中かを記録

public:
	BehaviorRecord(void);
	~BehaviorRecord();
	int getStep(void) { return step; }
	void setStep(int step) { this->step = step; }
};

