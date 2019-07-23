//-----------------------------------------------------------------------------
// ブラックボード基底処理 [BlackBoardBase.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BlackBoardBase {
protected:
	// Data
	void** index;

public:
	// Method
	BlackBoardBase(void);
	~BlackBoardBase(void);
	virtual void initialize(void);					// 初期化処理
	virtual void uninitialize(void);				// 終了処理
	virtual bool getAccessPermission(int tag) = 0;	// モジュールにアクセス許可を返す
	void* getPage(int page) { return index[page]; }	// ページを取得
};