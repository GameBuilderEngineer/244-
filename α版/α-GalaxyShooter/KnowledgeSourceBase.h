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
	Module::TYPE moduleTag;							// モジュールタイプを示す								
	bool canUpdate;									// 更新可能かを表すフラグ
	static BlackBoardBase* blackBoard[BB::NUM_MAX];	// ブラックボード

public:
	KnowledgeSourceBase(void);
	~KnowledgeSourceBase(void);
	// 初期化処理
	virtual void initialize(void);
	// 終了処理
	virtual void uninitialize(void);
	// 更新処理
	virtual void update(void) = 0;
	// 更新許可を設定
	void setUpdatePermission(bool setting) { canUpdate = setting; }	
	// 更新許可を取得
	bool getUpdatePermission(void) { return canUpdate; }
	// ブラックボードのページ読み込み
	template<typename dataType> const dataType& read(int type, int page);
	// ブラックボードのページコピー
	template<typename dataType> dataType copy(int type, int page);
	// ブラックボードにページ書き込み
	template<typename dataType> void write(int type, int page, dataType src);
	// モジュールとブラックボードを接続
	friend void setBlackBoard(int type, BlackBoardBase* p);
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// モジュールとブラックボードを接続
void setBlackBoard(int type, BlackBoardBase* p);


//=============================================================================
// ブラックボードのページ読み込み
//=============================================================================
template<typename dataType> 
const dataType& KnowledgeSourceBase::read(int type, int page)
{
	if (blackBoard[type]->getAccessPermission(moduleTag) == false)
	{
		MessageBox(NULL, "モジュールのアクセス違反\n>読み込み", "Error", MB_OK);
	}

	dataType *out = (dataType*)(blackBoard[type]->getPage(page));
	return *out;
}


//=============================================================================
// ブラックボードのページコピー
//=============================================================================
template<typename dataType> 
dataType KnowledgeSourceBase::copy(int type, int page)
{
	if (blackBoard[type]->getAccessPermission(moduleTag) == false)
	{
		MessageBox(NULL, "モジュールのアクセス違反\n>コピー", "Error", MB_OK);
	}

	dataType *out = (dataType*)(blackBoard[type]->getPage(page));
	return *out;
}


//=============================================================================
// ブラックボードにページ書き込み
//=============================================================================
template<typename dataType>
void KnowledgeSourceBase::write(int type, int page, dataType src)
{
	if (blackBoard[type]->getAccessPermission(moduleTag))
	{
		dataType *dest = (dataType*)(blackBoard[type]->getPage(page));
		*dest = src;
	}
	else
	{
		MessageBox(NULL, "モジュールのアクセス違反\n>書き込み", "Error", MB_OK);
	}
}

