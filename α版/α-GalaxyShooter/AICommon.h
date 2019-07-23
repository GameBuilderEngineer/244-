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
