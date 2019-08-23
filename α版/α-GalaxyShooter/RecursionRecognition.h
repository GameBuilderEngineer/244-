//-----------------------------------------------------------------------------
// リカージョンのAI認識 [RecursionRecognition.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/8/22
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "Wasuremono.h"
#include <vector>

//*****************************************************************************
// リカージョン認識クラス
//*****************************************************************************
struct RecursionRecognition
{
	// Data
	float totalHit;								// 認識範囲内のワスレモノ数
	float totalAmount;							// 認識範囲の総チンギン額
	D3DXVECTOR3 center;							// 認識範囲の中心座標
	float radius;								// 認識範囲の半径
	std::vector<Wasuremono*> wasuremonoInArea;	// ワスレモノへのポインタ
	D3DXVECTOR3 pilePosition[5];				// メモリーパイルの設置座標
	float fuzzySelectionWeight;					// この認識をリカージョンに採用するかどうかの重みづけ 

	// Method
	RecursionRecognition();
	~RecursionRecognition();
};
