//===================================================================================================================================
//yMagnet.cppz
// ์ฌาFHALGP12A332 11 ์ ๗
// ์ฌ๚F2019/06/15
// XV๚F2019/08/04
//===================================================================================================================================
#include "Magnet.h"
using namespace magnetNS;
//===================================================================================================================================
//yRXgN^z
//===================================================================================================================================
Magnet::Magnet()
{
	activation();
}

//===================================================================================================================================
//yfXgN^z
//===================================================================================================================================
Magnet::~Magnet()
{
}

//===================================================================================================================================
//y๚ปz
//===================================================================================================================================
void Magnet::initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* _staticMeshLoader,float _amount)
{
	amount = _amount;
	staticMeshLoader = _staticMeshLoader;
	int radius = 150;
	if (_amount > 0) {
		Object::initialize(device,  &staticMeshLoader->staticMesh[staticMeshNS::MAGNET_N],
			&D3DXVECTOR3((float)((rand() % radius) - radius / 2), (float)((rand() % radius) - radius / 2), (float)((rand() % radius) - radius / 2)));
	}
	else {
		Object::initialize(device, &staticMeshLoader->staticMesh[staticMeshNS::MAGNET_N],
			&D3DXVECTOR3((float)((rand() % radius) - radius / 2), (float)((rand() % radius) - radius / 2), (float)((rand() % radius) - radius / 2)));
	}
}

//===================================================================================================================================
//yฅอvZz
//===================================================================================================================================
void Magnet::calculationMagneticeForce(Magnet target)
{
	speed = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveDirection = target.position - position;
	float distance = D3DXVec3Length(&moveDirection);
	float magneticeForce = (target.amount*amount) / distance;
	D3DXVec3Normalize(&moveDirection,&moveDirection);
	speed += moveDirection * magneticeForce;
}

//===================================================================================================================================
//yฅCสฝ]z
//===================================================================================================================================
void Magnet::reverseAmount()
{
	amount *= -1.0f;
}

//===================================================================================================================================
//yXVz
//===================================================================================================================================
void Magnet::update()
{
	position += speed;
	Object::update();
}