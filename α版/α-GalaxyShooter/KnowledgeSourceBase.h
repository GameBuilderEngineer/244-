//-----------------------------------------------------------------------------
// ナレッジソース基底処理 [KnowledgeSourceBase.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class KnowledgeSourceBase {
protected:
	// Data
	bool canUpdate;													// 更新可能か
	BlackBoardBase* bb[NUM_BLACK_BOARD];							// ブラックボード

public:
	// Method
	KnowledgeSourceBase(void);
	~KnowledgeSourceBase(void);
	virtual void initialize(void);									// 初期化処理
	virtual void uninitialize(void);								// 終了処理
	virtual void update(void) = 0;									// 更新処理

	void setUpdatePermission(bool setting) { canUpdate = setting; }	// 更新許可を設定
	bool getUpdatePermission(void) { return canUpdate; }			// 更新許可を取得

	// ブラックボードのページ読み込み
	template<typename dataType> const dataType* read( BlackBoardBase* blackBoard, int page)
	{
		return (dataType*)(blackBoard->getPage(page));
	}
	// ブラックボードのページコピー
	template<typename dataType> dataType copy(BlackBoardBase* blackBoard, int page)
	{
		dataType *out = (dataType*)(blackBoard->getPage(page));
		return *out;
	}
	// ブラックボードにページ書き込み
	template<typename dataType> void write(BlackBoardBase* blackBoard, int page, dataType src)
	{
		dataType *dest = (dataType*)(blackBoard->getPage(page));
		*dest = src;
	}
};


