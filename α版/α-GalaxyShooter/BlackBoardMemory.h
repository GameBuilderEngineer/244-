//-----------------------------------------------------------------------------
// 記憶ブラックボード処理 [BlackBoardMemory.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "BlackBoardBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MemoryBB : public BlackBoardBase {
private:

public:
	// Method
	MemoryBB(void);
	~MemoryBB(void);
	void initialize(void) override;				// 初期化処理
	void uninitialize(void) override;			// 終了処理
};