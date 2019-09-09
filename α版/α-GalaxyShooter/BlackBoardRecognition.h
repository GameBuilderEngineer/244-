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
	float *skyHeight;							// 上空モードの高さへのポインタ
	bool inAir;									// true 空中にいる  false 地上にいる

	bool isOpponentInCamera;					// 相手がカメラに映っているか
	float distanceBetweenPlayers;				// プレイヤー間の距離
	D3DXVECTOR3 lineCutCoord;					// メモリーライン切断座標
	bool isDestinationDecided;					// 目的地が決まったか

	// プレイヤーステート
	int playerState;							// プレイヤークラスの状態

	//-----------------------
	// Data - バトル状況関係
	//-----------------------
	bool isOpponentNear;						// 敵が違い
	bool mayHappenShockWave;					// 衝撃波が発生する可能性がある
	bool isOpponentOffensive;					// 敵が攻撃的である
	bool isBulletNear;							// バレットが近い
	bool isChinginLow;							// チンギンが低い

	//-----------------------------
	// Data - リカージョン認識関係
	//-----------------------------
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

	bool isStartRecursion;						// リカージョンを開始するか？
	bool isRecursionRunnning;					// リカージョンが実行中であるかどうか
	int *elementMemoryPile;						// メモリーパイルの要素番号
	int nextElementMemoryPile;					// 次に打つメモリーパイルの要素番号 

public:
	//--------
	// Method
	//--------
	RecognitionBB(Player* _opponentPlayer);
	void initialize(void) override;									// 初期化処理
	void setMemoryBB(MemoryBB* _memoryBB) { memoryBB = _memoryBB; }	// ブラックボードをセット
	float getFrameTime(void) { return *frameTime; }					// フレーム時間を取得
	void setFrameTimePointer(float* p) { frameTime = p; }			// フレーム時間へポインタ設定
	float getSkyHeight(void) { return *skyHeight; }					// 上空モードの高さを取得
	void setSkyHeightPointer(float* adr) { skyHeight = adr; }		// 上空モードの高さへポインタ設定

	// 自分の情報
	D3DXVECTOR3* getMyPosition(void) { return myPosition; }			// 自分の座標を取得
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }// 自分の座標を設定
	bool getWhetherInAir(void) { return inAir; }					// 自分が空中にいるか取得
	void setWhetherInAir(bool setting) { inAir = setting; }			// 自分が空中にいるか設定
	int getPlayerState(void) { return playerState; }				// プレイヤーステートを取得
	void setPlayerState(int setting) { playerState = setting; }		// プレヤーステートを設定

	bool getIsOpponentInCamera(void) { return isOpponentInCamera; }	// 相手がカメラに移っているか取得
	void setIsOpponentInCamera(bool setting) { isOpponentInCamera = setting; }// 相手がカメラに移っているか設定

	D3DXVECTOR3 getLineCutCoord(void) { return lineCutCoord; }				// メモリーライン切断座標を取得
	void setLineCutCoord(D3DXVECTOR3 setting) { lineCutCoord = setting; }	// メモリーライン切断座標を設定

	bool getWhetherDestinationDecided(void) { return isDestinationDecided; }// 目的地が決まったか取得
	void setWhetherDestinationDecided(bool setting) { isDestinationDecided = setting; }// 目的地が決まったか設定

	// リカージョン
	RecursionRecognition* getRecursionRecognition(void) { return recursionRecognition; }// リカージョン認識を取得
	bool getIsActiveRecursionRecognition(int i) { return isActiveRecursionRecognition[i]; }// リカージョン認識の活性状態を取得
	void setIsActiveRecursionRecognition(int i, bool setting) { isActiveRecursionRecognition[i] = setting; }// リカージョン認識の活性状態を設定
	bool getIsStartRecursion(void) { return isStartRecursion; }				// リカージョンを開始するか取得
	void setIsStartRecursion(bool setting)
	{ 
		isStartRecursion = setting;
	}	// リカージョンを開始するか設定
	bool getIsRecursionRunning(void) { return isRecursionRunnning; }
	void setIsRecursionRunning(bool setting) { isRecursionRunnning = setting; }
	int getRecursionPolicy(void) { return recursionPolicy; }
	void setRecursionPolicy(int setting) { recursionPolicy = setting; }
	RecursionRecognition* getRunningRecursion(void) { return &runningRecursion; }

	int getElementMemoryPile(void) { return *elementMemoryPile; }
	void setElementMemoryPilePointer(int* p) { elementMemoryPile = p; }

	int getNextElementMemoryPile(void) { return nextElementMemoryPile; }
	void setNextElementMemoryPile(int element) { nextElementMemoryPile = element; }

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

	// バトル状況関係
	bool getIsOpponentNear(void) { return isOpponentNear; };					// 敵が違いか取得
	void setIsOpponentNear(bool setting) { isOpponentNear = setting; }			// 敵が近いか設定
	bool getMayHappenShockWave(void) { return mayHappenShockWave; }				// 衝撃波が発生する可能性があるか取得
	void setMayHappenShockWave(bool setting) { mayHappenShockWave = setting; }	// 衝撃波が発生する可能性があるか設定
	bool getIsOpponentOffensive(void) { return isOpponentOffensive; }			// 敵が攻撃的であるか取得
	void setIsOpponentOffensive(bool setting) { isOpponentOffensive = setting; }// 敵が攻撃的であるか設定
	bool getIsBulletNear(void) { return isBulletNear; }							// バレットが近いか取得
	void setIsBuletNear(bool setting) { isBulletNear = setting; }				// バレットが近いか設定
	bool getIsChinginLow(void) { return isChinginLow; }							// チンギンが低いか取得
	void setIsChinginLow(bool setting) { isChinginLow = setting; }				// チンギンが低いか設定
};