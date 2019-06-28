#include "Magnet.h"

Magnet::Magnet()
{

}


Magnet::~Magnet()
{
}

void Magnet::initialize(LPDIRECT3DDEVICE9 device,float _amount)
{
	amount = _amount;
	if (_amount > 0) {
		Object::initialize(device, (LPSTR)"magnetS.x", &D3DXVECTOR3(rand()%30,rand()%30,rand()%30));
	}
	else {
		Object::initialize(device, (LPSTR)"magnetN.x", &D3DXVECTOR3(rand()%30,rand()%30,rand()%30));
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