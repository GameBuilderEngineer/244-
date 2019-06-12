#pragma once
#include "Base.h"
#include "Object.h"

class Magnet :public Object
{
public:
	Magnet();
	~Magnet();

	void initialize(LPDIRECT3DDEVICE9 device);

};

