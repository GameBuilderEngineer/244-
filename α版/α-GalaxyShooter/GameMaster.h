#pragma once
#include "Base.h"

namespace gameMasterNS {
	const float GAME_TIME = 60.0f * 4.0f;	//4��

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
	int wage;			//�`���M��
};

class GameMaster :public Base
{
private:
	float gameTimer;							//�Q�[������
	playerTable playerInformation[gameMasterNS::PLAYER_NUM];	//�v���C���[���


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

