#pragma once
#include "Object.h"

class Player : public Object
{
public:


	Player();
	~Player();

	void update();
	void move(D3DXVECTOR2 moveDirection);
	void jump();
};

