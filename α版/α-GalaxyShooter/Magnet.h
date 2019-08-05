//===================================================================================================================================
//yMagnet.hz
// [ì¬Ò]HAL“Œ‹GP12A332 11 ›–ì ÷
// [ì¬“ú]2019/06/15
// [XV“ú]2019/08/04
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "Object.h"

namespace magnetNS
{

}

class Magnet :public Object
{
private:
	//Data
	int type;
	float amount;	//¥‹C—Ê
	StaticMeshLoader* staticMeshLoader;

public:
	//Method
	Magnet();
	~Magnet();

	//proseccing
	void initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* _staticMeshLoader,float amount);
	void update();

	//operation
	void reverseAmount();
	void calculationMagneticeForce(Magnet target);

};

