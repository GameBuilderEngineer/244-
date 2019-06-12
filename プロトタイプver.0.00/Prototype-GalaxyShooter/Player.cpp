#include "Player.h"
#include "Game.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::update()
{
	Player player[gameNS::NUM_PLAYER];

	D3DXQUATERNION qtnDelta;
	if (GetKeyState('W') & 0x80)
	{
		player[gameNS::PLAYER1].setDirection(player[gameNS::PLAYER1].getDirection() + player[gameNS::PLAYER1].getAxisZ()*0.05);

	}
	if (GetKeyState('S') & 0x80)
	{
		player[gameNS::PLAYER1].getDirection() += -player[gameNS::PLAYER1].getAxisZ()*0.05;
	}
	if (GetKeyState('A') & 0x80)
	{//sin(1/2θ)*(0,1,0)
		qtnDelta.x = 0;
		qtnDelta.y = sin(-DELTA_ANGLE / 2.0f);
		qtnDelta.z = 0;
		qtnDelta.w = cos(-DELTA_ANGLE / 2.0f);
		player[gameNS::PLAYER1].setQuaternion(player[gameNS::PLAYER1].getQuaternion() * qtnDelta);
	}
	if (GetKeyState('D') & 0x80)
	{//sin(1/2θ)*(0,1,0)
		qtnDelta.x = 0;
		qtnDelta.y = sin(DELTA_ANGLE / 2.0f);
		qtnDelta.z = 0;
		qtnDelta.w = cos(DELTA_ANGLE / 2.0f);
		player[gameNS::PLAYER1].setQuaternion(player[gameNS::PLAYER1].getQuaternion() * qtnDelta);
	}


	//ロボット　位置更新
	player[gameNS::PLAYER1].setPosition(player[gameNS::PLAYER1].getPosition() + player[gameNS::PLAYER1].getDirection());

}


