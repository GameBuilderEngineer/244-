//-----------------------------------------------------------------------------
// AI共用ヘッダ [AICommon.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/23
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"

//*****************************************************************************
// AI一般
//*****************************************************************************
namespace STDAI
{
#define opponent					(recognitionBB->getOpponentPlayer())

	// 定数
	static const int NUM_RECURSION_RECOGNITION = 3;	// リカージョン認識の数
}
using namespace STDAI;


//*****************************************************************************
// ビヘイビアツリー
//*****************************************************************************
// BehaviorNodeBase.hに記述してもinclude順はOKだが毎回開くのが面倒なのでここで
namespace BehaviorTreeNS
{
	// ノードタグ定義
	enum NODE_TAG
	{
		//---------------------------------------------------------------------
		// ルールノード
		//---------------------------------------------------------------------
		_RULE_NODE_,
		PRIORITY,					// 優先順位リスト法
		ON_OFF,						// オン・オフ法
		RANDOM,						// ランダム法
		SEQUENCE,					// シークエンス法
		PARARELL,					// パラレル法

		//---------------------------------------------------------------------
		// 条件ノード
		//---------------------------------------------------------------------
		_CONDITIONAL_NODE_,
		IF_OPPONENT_NEAR,
		IF_FIVE_SECONDS_LATER,
		IF_THREE_SECONDS_LATER,

		//---------------------------------------------------------------------
		// アクションノード
		//---------------------------------------------------------------------
		_ACTION_NODE_,
		ACTION_MOVE,
		ACTION_JUMP,
		ACTION_SHOOT,
		ACTION_PILE,

		//---------------------------------------------------------------------
		// 副処理ノード
		//---------------------------------------------------------------------
		_SUBPROCEDURE_NODE_,
		SET_DESTINATION_OPPONENT,
		SET_DESTINATION_RANDOM,
		SET_TARGET_OPPONENT,

		// タグの数
		NUM_NODE_TAG
	};

	// ノードタイプ定義
	enum NODE_TYPE
	{
		RULE_NODE,					// ルールノード
		CONDITIONAL_NODE,			// 条件ノード
		ACTION_NODE,				// アクションノード
		SUBPROCEDURE_NODE,			// 副処理ノード
	};

	// ツリータイプ定義
	enum TREE
	{
		TREE_INDEX,					//  = 0
		OFFENSE = 0,				// サンプルツリー1
		DEFFENSE,					// サンプルツリー2
		NUM_TREE					// ビヘイビアツリーの数
	};

	// ノードの実行結果
	enum NODE_STATUS
	{
		SUCCESS,					// 実行成功
		FAILED,						// 実行失敗
		RUNNING,					// 実行中
		_NOT_FOUND = -1				// ノードが存在しない
	};

	const int PARENT_IS_NOT_EXIST = -1;		// 親ノードが存在しないことを示す（ルートのみ）
}


//*****************************************************************************
// ステートマシン
//*****************************************************************************
namespace StateTransition
{
	enum
	{
		OFFENSE,
		DEFFENSE,
		STATE_MAX,
		INVALID = -1
	};

}


//*****************************************************************************
// ブラックボードアーキテクチャ
//*****************************************************************************
namespace Module
{
	enum TYPE
	{
		SENSOR,						// センサー
		ENVIRONMENT_ANSLYSIS,		// 環境解析
		PATH_PLANNING,				// 経路探索
		DECISION_MAKING,			// 意思決定
		MOTION_GENERATION,			// 運動生成
		NUM_MAX						// モジュールの数
	};
}

namespace BB
{
	enum TYPE
	{
		ENVIRONMENT_RECOGNITION,	// 環境認識
		MEMORY,						// 記憶
		BODY,						// 身体
		NUM_MAX						// ブラックボードの数
	};
}