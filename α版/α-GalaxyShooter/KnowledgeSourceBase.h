//-----------------------------------------------------------------------------
// ナレッジソース基底処理 [KnowledgeSourceBase.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardBase.h"
#include "BlackBoardRecognition.h"
#include "BlackBoardMemory.h"
#include "BlackBoardBody.h"

// 前方宣言(AgentAIクラスと相互参照のため)
class AgentAI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class KnowledgeSourceBase {
protected:
	// Data
	Module::TYPE moduleTag;							// モジュールタイプを示す								
	bool canUpdate;									// 更新可能かを表すフラグ

public:
	KnowledgeSourceBase(void);
	~KnowledgeSourceBase(void);
	// 初期化処理
	virtual void initialize(void) = 0;
	// 終了処理
	virtual void uninitialize(void) = 0;
	// 更新処理
	virtual void update(AgentAI* agentAI) = 0;
	// 更新許可を設定
	void setUpdatePermission(bool setting) { canUpdate = setting; }	
	// 更新許可を取得
	bool getUpdatePermission(void) { return canUpdate; }

};
