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
	//-------------
	// Data - 一般
	//-------------
	MemoryBB* memoryBB;							// 記憶領域ブラックボード
	Player* opponentPlayer;						// 対戦相手
	D3DXVECTOR3 *myPosition;					// 自分の座標
	float *frameTime;							// フレーム時間へのポインタ
	bool inAir;									// true 空中にいる  false 地上にいる
	bool isDown;								// ダウン中か
	float distanceBetweenPlayers;				// プレイヤー間の距離
	D3DXVECTOR3 lineCutCoord;					// メモリーライン切断座標

public://●
	//-----------------------------
	// Data - リカージョン認識関係
	//-----------------------------
	bool flag = false;

	// リカージョン認識（環境認識モジュールで調べたリカージョン場所候補）
	RecursionRecognition recursionRecognition[NUM_RECURSION_RECOGNITION];

	// リカージョン認識の活性状態（上記リカージョン認識が実際に使用できるか否かをフラグ管理）
	bool isActiveRecursionRecognition[NUM_RECURSION_RECOGNITION];

	// 実行リカージョン認識
	//（上記リカージョン認識は環境認識モジュール実行毎に書き換わる）
	//（そのため実際に実行するリカージョンは実行中に書き換わらないよう別に保管する）
	RecursionRecognition runningRecursion;

	// リカージョンの方針
	//（上記リカージョン認識から実行リカージョン認識をさらに選定するための方針）
	//（ウェイト重視, チンギン額重視, 半径サイズ重視の３方針）
	int recursionPolicy;

	bool isRecursionRunnning;					// リカージョンが実行中であるかどうか
	int pileCount;								// メモリーパイル打ち込みをカウント

public:
	//--------
	// Method
	//--------
	RecognitionBB(Player* _opponentPlayer);
	void initialize(void) override;								// 初期化処理
	void setMemoryBB(MemoryBB* _memoryBB) { memoryBB = _memoryBB; }

	// frameTime
	float getFrameTime(void) { return *frameTime; }				// フレーム時間を取得
	void setFrameTimePointer(float* adr) { frameTime = adr; }	// フレーム時間へポインタ設定

	// 自分の情報
	D3DXVECTOR3* getMyPosition(void) { return myPosition; }		// 自分の座標
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }
	bool getWhetherInAir(void) { return inAir; }				// 自分が空中にいるか？
	void setWhetherInAir(bool setting) { inAir = setting; }
	bool getIsDown(void) { return isDown; }						// 自分がダウン中か？
	void setIsDown(bool setting) { isDown = setting; }
	D3DXVECTOR3 getLineCutCoord(void) { return lineCutCoord; }				// メモリーライン切断座標を取得
	void setLineCutCoord(D3DXVECTOR3 setting) { lineCutCoord = setting; }	// メモリーライン切断座標を設定
	RecursionRecognition* getRecursionRecognition(void) { return recursionRecognition; }// リカージョン認識を取得
	bool getIsActiveRecursionRecognition(int i) { return isActiveRecursionRecognition[i]; }// リカージョン認識の活性状態を取得
	void setIsActiveRecursionRecognition(int i, bool setting) { isActiveRecursionRecognition[i] = setting; }// リカージョン認識の活性状態を設定
	bool getIsRecursionRunning(void) { return isRecursionRunnning; }
	void setIsRecursionRunning(bool setting) { isRecursionRunnning = setting; }
	int getRecursionPolicy(void) { return recursionPolicy; }
	void setRecursionPolicy(int setting) { recursionPolicy = setting; }
	RecursionRecognition* getRunningRecursion(void) { return &runningRecursion; }
	int* getPileCount(void) { return &pileCount; }

	// 相手の情報
	Player* getOpponentPlayer(void) { return opponentPlayer; }							// 対戦相手を取得
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