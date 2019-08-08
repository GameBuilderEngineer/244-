//===================================================================================================================================
//【GameMaster.h】
// [作成者] HAL東京GP12A332 11 菅野 樹
// [作成日] 2019/07/31
// [更新日] 2019/08/04
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "StaticMeshLoader.h"
#include "Player.h"

namespace gameMasterNS {
	const float GAME_TIME = (60.0f * 0.5f);	//4分

	const float COUNT_DOWN_TIME = 3.0f;		//3秒

	enum PLAYER_TYPE
	{
		PLAYER_CHARACTER,
		NON_PLAYER_CHARACTER,
		TYPE_NUM
	};

	enum RESULT_LIST
	{
		WIN_1P,
		WIN_2P,
		DRAW,
	};

	const int MODEL_ADAM = staticMeshNS::SAMPLE_ROBOT001;
	const int MODEL_EVE = staticMeshNS::SAMPLE_ROBOT002;

}

struct playerTable
{
	int playerType;		//PC|NPC
	int modelType;		//プレイヤーのモデルタイプ
	int wage;			//チンギン
};

//===================================================================================================================================
//【ゲーム管理クラス】
// [用途]	このクラスは、シーンをまたいで情報の橋渡しを行う。
//			更新や設定は、各シーンで行う。
//===================================================================================================================================
class GameMaster :public Base
{
private:
	float gameTimer;										//ゲーム時間
	float countDownTimer;									//カウントダウン時間
	playerTable playerInformation[playerNS::NUM_PLAYER];	//プレイヤー情報

public:
	GameMaster();
	~GameMaster();
	
	//processing
	void initialize();
	void update(float frameTime);

	//operation
	void updateGameTime(float frameTime);					//ゲーム時間の更新
	void resetGameTime();									//ゲーム時間のリセット

	//setter
	void setPlayerCharacter(int playerNo, int playerType, int modelType);	//キャラクター情報をセット
	void addWage(int playerNo, int modelType);								//チンギンを加算
	
	//getter
	playerTable* getPlayerInfomation();
	int getResult();
	float getGameTime();
	bool whetherGameOver();
};

