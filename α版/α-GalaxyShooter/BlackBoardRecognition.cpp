//-----------------------------------------------------------------------------
// 環境認識ブラックボード処理 [BlackBoardRecognition.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "BlackBoardRecognition.h"

//=============================================================================
// コンストラクタ
//=============================================================================
RecognitionBB::RecognitionBB(Player* _opponentPlayer): opponentPlayer(_opponentPlayer)
{
	// No Process
}


//=============================================================================
// 初期化処理
//=============================================================================
void RecognitionBB::initialize(void)
{
	memoryBB = NULL;
	// opponentPlayer = コンストラクタで設定済
	myPosition = NULL;
	inAir = false;
	distanceBetweenPlayers = 0.0f;
	D3DXVECTOR3 lineCutCoord = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isDestinationDecided = false;
	bulletSwitch = false;

	isOpponentNear = false;
	isOpponentOffensive = false;
	isBulletNear = false;
	isChinginLow = false;

	ZeroMemory(recursionRecognition, sizeof(RecursionRecognition) * NUM_RECURSION_RECOGNITION);
	ZeroMemory(&recursionRecognitionForOpponent, sizeof(RecursionRecognition));
	recursionPolicy = RECURSION_PERSONALITY::LARGEST_WEIGHT;// ●リカージョンの方針を設定
	isStartRecursion = false;
	isStartRecursionForOpponent = false;
	ZeroMemory(&runningRecursion, sizeof(RecursionRecognition));
	isRecursionRunnning = false;
}