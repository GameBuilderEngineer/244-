//-----------------------------------------------------------------------------
// リカージョンのAI認識 [RecursionRecognition.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/8/22
//-----------------------------------------------------------------------------
#include "RecursionRecognition.h"

//=============================================================================
// コンストラクタ
//=============================================================================
RecursionRecognition::RecursionRecognition(void)
{
	uniqueID = -1;
	totalHit = 0;
	totalAmount = 0;
	center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	radius = 0.0f;
	wasuremonoInArea.reserve(15);	// 適度にキャパシティーを増やしておく
	ZeroMemory(pilePosition, sizeof(D3DXVECTOR3) * 5);
	fuzzySelectionWeight = 0.0f;
}


//=============================================================================
// デストラクタ
//=============================================================================
RecursionRecognition::~RecursionRecognition()
{
	// ベクターは自動で解放される
}
