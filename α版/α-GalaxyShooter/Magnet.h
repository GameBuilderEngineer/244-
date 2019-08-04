#pragma once
#include "Base.h"
#include "Object.h"

namespace magnetNS
{

}

class Magnet :public Object
{
private:
	int type;
	float amount;	//Ž¥‹C—Ê
	StaticMeshLoader* staticMeshLoader;

public:
	Magnet();
	~Magnet();
	void initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* _staticMeshLoader,float amount);
	void reverseAmount();
	void calculationMagneticeForce(Magnet target);
	void update();
};

