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

enum AI_LEVEL
{
	NORMAL_LEVEL,				// ノーマル
	HARD_LEVEL,					// ハード
	VERY_HARD_LEVEL				// ベリーハード
};

enum MODULE_TYPE
{
	SENSOR,						// センサー
	ENVIRONMENT_ANSLYSIS,		// 環境解析
	PATH_PLANNING,				// 経路探索
	DECISION_MAKING,			// 意思決定
	MOTION_GENERATION,			// 運動生成
	NUM_KNOWLEDGE_SOURCE		// モジュールの数
};

enum BLACK_BOARD_TYPE
{
	ENVIRONMENT_RECOGNITION,	// 環境認識
	BODY,						// 身体
	MEMORY,						// 記憶
	NUM_BLACK_BOARD				// ブラックボードの数
};

enum TARGET_OF_RECOGNITION
{
	OPPONENT,					// 対戦相手
	MISSILE,					// ミサイル
	ETC,						// とか
	NUM_TARGET					// 対象の数
};

enum PATH_TYPE {
	PATH_TO_OPPONENT,			// 相手への経路
	PATH_TO_JUNK,				// ガラクタへの経路
	NUM_PATH_TYPE,				// 経路の数
	INVALID_PATH = -1			// 無効ルート
};