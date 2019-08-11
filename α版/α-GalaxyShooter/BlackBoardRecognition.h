//-----------------------------------------------------------------------------
// 環境認識ブラックボード処理 [BlackBoardRecognition.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "AICommon.h"
#include "BlackBoardBase.h"
#include "Player.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************

class RecognitionBB : public BlackBoardBase
{
private:
	Player* opponentPlayer;						// 対戦相手
	D3DXVECTOR3 *myPosition;					// 自分の座標
	bool inAir;									// true 空中にいる  false 地上にいる
	bool isDown;								// ダウン中か

public:
	RecognitionBB(void);
	void initialize(void) override;				// 初期化処理

	// 対戦相手をセット
	void setOpponentPlayer(Player* _opponentPlayer) { opponentPlayer = _opponentPlayer; }
	// 対戦相手を取得
	Player* getOpponentPlayer(void) { return opponentPlayer; }

	D3DXVECTOR3* getMyPosition(void) { return myPosition; }
	void setMyPosition(D3DXVECTOR3* _position) { myPosition = _position; }
	bool getWhetherInAir(void) { return inAir; }
	void setWhetherInAir(bool setting) { inAir = setting; }
	bool getIsDown(void) { return isDown; }
	void setIsDown(bool setting) { isDown = setting; }
};