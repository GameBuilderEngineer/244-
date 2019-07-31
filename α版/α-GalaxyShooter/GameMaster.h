#pragma once
#include "Base.h"

namespace gameMasterNS {
	const float GAME_TIME = 60.0f * 4.0f;	//4分

	enum PLAYER_TYPE
	{
		PLAYER_1P,
		PLAYER_2P,
		PLAYER_NUM,
	};


}

struct playerTable
{
	int playerType;		//1P|2P|NPC
	int wage;			//チンギン
};

class GameMaster :public Base
{
private:
	float gameTimer;							//ゲーム時間
	playerTable playerInformation[gameMasterNS::PLAYER_NUM];	//プレイヤー情報


public:
	GameMaster();
	~GameMaster();
	
	//processing
	void initialize();
	void update(float frameTime);

	//operation
	void updateGameTime(float frameTime);
	
	//setter
	void setWage(int playerNo, int wage);
	
	//getter
	int getWinnerPlayer();
	int getLoserPlayer();

};

