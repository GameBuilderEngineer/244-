//-----------------------------------------------------------------------------
// AI共用ヘッダ [AICommon.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/23
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
#define OPPONENT(p)				()

namespace Agent
{
	enum LEVEL
	{
		NORMAL_LEVEL,				// ノーマル
		HARD_LEVEL,					// ハード
		VERY_HARD_LEVEL				// ベリーハード
	};
}

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

namespace Target
{
	enum TYPE
	{
		OPPONENT,					// 対戦相手
		MISSILE,					// ミサイル
		ETC,						// とか
		NUM_MAX						// 対象の数
	};
}

namespace Path
{
	enum TYPE
	{
		TO_OPPONENT,				// 相手への経路
		TO_JUNK,					// ガラクタへの経路
		NUM_MAX,					// 経路の数
		INVALID = -1				// 無効ルート
	};
}

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

namespace BehaviorTreeNS
{
	// ビヘイビアツリー
	enum TREE
	{
		TREE_INDEX,					// 0
		SAMPLE = 0,					// サンプルツリー
		NUM_TREE					// ビヘイビアツリーの数
	};

	// ノードタイプ
	enum NODE_TYPE
	{
		RULE_NODE,					// ルールノード
		CONDITIONAL_NODE,			// 条件ノード
		ACTION_NODE,				// アクションノード
		SUBPROCEDURE_NODE,			// 副処理ノード
	};

	// ノードのタグ
	enum NODE_TAG
	{
		// ルールノード
		_RULE_NODE_,
		PRIORITY,					// 優先順位リスト法
		ON_OFF,						// オン・オフ法
		RANDOM,						// ランダム法
		SEQUENCE,					// シークエンス法
		PARARELL,					// パラレル法

		// 条件ノード
		_CONDITIONAL_NODE_,	
		IF_OPPONENT_NEAR,

		// アクションノード
		_ACTION_NODE_,
		ACTION_MOVE,

		// 副処理ノード
		_SUBPROCEDURE_NODE_,
		SET_TARGET_OPPONENT,

		NUM_NODE_TAG				// タグの数
	};

	// ノードの実行結果
	enum NODE_STATUS
	{
		SUCCESS,					// 実行成功
		FAILED,						// 実行失敗
		RUNNING,					// 実行中
		_NOT_FOUND = -1				// ノードが存在しない
	};

	const int PARENT_IS_NOT_EXIST = -1;
}

