//-----------------------------------------------------------------------------
// 身体ブラックボード処理 [BlackBoardBody.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once;
#include "BlackBoardBase.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BodyBB : public BlackBoardBase {
protected:
	//------
	// Data
	//------
	bool aiMove;							// true 移動する　false 移動しない
	D3DXVECTOR3* movingDestination;			// 移動先座標（ビヘイビアツリー中で切り替わる）
	bool isArrived;							// true 到着した　false 到着していない
	float speed;							// 移動スピード
	bool aiJump;							// true ジャンプする　false ジャンプしない
	bool onceJumped;						// true ジャンプ済み　false　未ジャンプ
											// ※Player::jump()を行ったらtrue
	bool aiShoot;							// true バレットを打つ　false バレットを打たない
	D3DXVECTOR3 target;						// バレットのターゲット座標	
	float shootingInterval;					// バレット発射インターバル
	bool aiLocatePile;						// true パイル設置する　false パイル設置しない
	bool isPileReady;						// true パイル設置可能　false パイル設置不可
	bool aiCutLine;							// true ライン切る　false ライン切らない
	bool onceTriedCut;						// true ライン切断実行済み　false ライン切断実行していない
	bool aiRevivalAction;					// true ダウン復活アクションする　false ダウン復活アクションしない
	float revivalPointInterval;				// 復活ポイントの加算インターバルタイム


public:
	//--------
	// Method
	//--------
	BodyBB(void);
	void initialize(void) override;									// 初期化

	// 移動
	bool getMove(void) { return aiMove; }							// 移動を取得
	void setMove(bool setting) { aiMove = setting; }				// 移動を設定
	D3DXVECTOR3* getMovingDestination(void) { return movingDestination; }// 目的地の座標ポインタを取得
	void configMovingDestination(D3DXVECTOR3* _destnation);			// 目的地座標を新たに設定し関連フラグも設定する
	bool getIsArrived(void) { return isArrived; }					// 目的地到着したか取得
	void setIsArrival(bool setting) { isArrived = setting; }		// 目的地到着したかを設定
	float getSpeed(void) { return speed; }							// 移動スピードを取得
	void setSpeed(const float _speed) { speed = _speed; }			// 移動スピードを設定
	const float MOVING_SPEED = playerNS::SPEED;
	const float MOVING_SLOW_SPEED = playerNS::SPEED / 5.0f;

	// ジャンプ
	bool getJump(void) { return aiJump; }							// ジャンプを取得
	void setJump(bool setting) { aiJump = setting; }				// ジャンプを設定
	bool whetherJumpedOnce(void) { return onceJumped; }				// ジャンプ履歴の取得
	void setJumpedHistory(bool setting) { onceJumped = setting; }	// ジャンプ履歴の設定

	// バレット
	bool getShootingBullet(void) { return aiShoot; }				// バレットを打つか取得
	void setShootingBullet(bool setting) { aiShoot = setting; }		// バレットを打つか設定
	D3DXVECTOR3 getTargetCoordValue(void) { return target; }		// ターゲット座標の取得		※ポインタじゃない！
	void setTargetCoordValue(D3DXVECTOR3 setting) { target = setting; }// ターゲット座標の設定	※ポインタ握るより取り回しが良い気がして
	float getShootingInterval(void) { return shootingInterval; }	// バレット発射インターバルタイムの取得
	void setShootingInterval(float currentValue) { shootingInterval = currentValue; }// バレット発射インターバルタイムの設定

	// メモリーパイル
	bool getLocatingPile(void) { return aiLocatePile; }				// パイル設置するか取得
	void setLocatingPile(bool setting) { aiLocatePile = setting; }	// パイル設置を設定
	bool getIsReadyForPile(void) { return isPileReady; }			// パイル設置可能か取得
	void setIsReadyForPile(bool setting) { isPileReady = setting; }	// パイル設置可能か設定

	// メモリーライン
	bool getCuttingLine(void) { return aiCutLine; }					// メモリーラインを切るか取得
	void setCuttingLine(bool setting) { aiCutLine = setting; }		// メモリーラインを切るか設定
	bool getOnceTriedCut(void) { return onceTriedCut; }				// メモリ―ライン切断を実行済みか取得
	void setOnceTriedCut(bool setting) { onceTriedCut = setting; }	// メモリーライン切断を未実行か取得

	// ダウン復活
	bool getRevivalAction(void) { return aiRevivalAction; }			// ダウン復活アクションをするか取得
	void setRevivalAction(bool setting) { aiRevivalAction = setting; }// ダウン復活アクションをするか設定
	float getRevivalPointInterval(void) { return revivalPointInterval; }// 復活ポイントの加算インターバルタイムを取得
	void setRevivalPointInterval(float setting) { revivalPointInterval = setting; }// 復活ポイントの加算インターバルタイムを設定
};