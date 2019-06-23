//-----------------------------------------------------------------------------
// ファジー理論 [Fuzzy.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/23
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct FuzzyDistance
{
	float	nearSet;
	float	normalSet;
	float	farSet;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// メンバーシップ関数「上昇斜辺」／
float FuzzyGrade(float value, float x0, float x1);

// メンバーシップ関数「下降斜辺」＼
float FuzzyReverseGrade(float value, float x0, float x1);

// メンバーシップ関数「三角形」＿／＼＿
float FuzzyTriangle(float value, float x0, float x1, float x2);

// メンバーシップ関数「台形」＿／￣＼＿
float FuzzyTrapenoid(float value, float x0, float x1, float x2, float x3);

// ヘッジ関数「とても強く」
float HedgeVery(float a);

// ヘッジ関数「とても弱く」
float HedgeNotVery(float a);

// ファジーAND演算
float FuzzyAnd(float a, float b);

// ファジーOR演算
float FuzzyOr(float a, float b);

// ファジーNOT演算
float FuzzyNot(float a);


