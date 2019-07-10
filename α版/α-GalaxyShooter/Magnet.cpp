#include "Magnet.h"

Magnet::Magnet()
{
	activation();
}


Magnet::~Magnet()
{
}

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

void Magnet::calculationMagneticeForce(Magnet target)
{
	speed = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveDirection = target.position - position;
	float distance = D3DXVec3Length(&moveDirection);
	float magneticeForce = (target.amount*amount) / distance;
	D3DXVec3Normalize(&moveDirection,&moveDirection);
	speed += moveDirection * magneticeForce;
}

void Magnet::reverseAmount()
{
	amount *= -1.0f;
}

void Magnet::update()
{
	position += speed;
	Object::update();
}