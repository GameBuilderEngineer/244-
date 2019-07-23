//-----------------------------------------------------------------------------
// 記憶ブラックボード処理 [BlackBoardMemory.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "BlackBoardBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class MemoryBB : public BlackBoardBase {
private:
	// Data
	enum {
		INDEX,
		NUM_DATA
	};



public:
	// Method
	MemoryBB(void);
	~MemoryBB(void);
	void initialize(void) override;				// 初期化処理
	void uninitialize(void) override;			// 終了処理
	bool getAccessPermission(int tag) override;	// モジュールにアクセス許可を返す
};