//-----------------------------------------------------------------------------
// 環境認識ブラックボード処理 [BlackBoardRecognition.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardBase.h"
#include "BlackBoardMemory.h"
#include "Player.h"
#include "Map.h"
#include "RecursionRecognition.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RecognitionBB : public BlackBoardBase
{
private:
	MemoryBB* memoryBB;							// 記憶領域ブラックボード
	Player* opponentPlayer;						// 対戦相手
	D3DXVECTOR3 *myPosition;					// 自分の座標
	bool inAir;									// true 空中にいる  false 地上にいる
	bool isDown;								// ダウン中か

	float distanceBetweenPlayers;				// プレイヤー間の距離

	RecursionRecognition recursionRecognition[NUM_RECURSION_RECOGNITION];// リカージョン認識

public:
	RecognitionBB(Player* _opponentPlayer);
	void setMemoryBB(MemoryBB* _memoryBB) { memoryBB = _memoryBB; }
	void initialize(void) override;								// 初期化処理
	Player* getOpponentPlayer(void) { return opponentPlayer; }	// 対戦相手を取得

	D3DXVECTOR3* getMyPosition(void) { return myPosition; }		// 自分の座標
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }
	bool getWhetherInAir(void) { return inAir; }				// 自分が空中にいるか？
	void setWhetherInAir(bool setting) { inAir = setting; }
	bool getIsDown(void) { return isDown; }						// 自分がダウン中か？
	void setIsDown(bool setting) { isDown = setting; }
	RecursionRecognition* getRecursionRecognition(void) { return recursionRecognition; }// リカージョン認識を取得

	// 相手の情報
	bool getIsOpponentFall(void) { return opponentPlayer->whetherFall(); }				// 落下中か？
	bool getIsOpponentSky(void) { return opponentPlayer->whetherSky(); }				// 上空モードか？
	bool getIsOpponentDown(void) { return opponentPlayer->whetherDown(); }				// ダウン中か？
	void setDistanceBetweenPlayers(float setting) { distanceBetweenPlayers = setting; }	// 距離設定
	float getDistanceBetweenPlayers(void) { return distanceBetweenPlayers; }			// 距離取得

	// マップ情報
	std::list<MapNode*>& getMemorizedMap(void) { return memoryBB->getMemorizedMap(); }

	// バレットの情報
	std::list<Bullet*>& getMemorizedBullet(void) { return memoryBB->getMemorizedBullet(); }
};