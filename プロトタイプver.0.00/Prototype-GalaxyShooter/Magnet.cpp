#include "Magnet.h"



Magnet::Magnet()
{
}


Magnet::~Magnet()
{
}

void Magnet::initialize(LPDIRECT3DDEVICE9 device)
{
	Object::initialize(device, (LPSTR)"magnetS.x", &D3DXVECTOR3(0, 10, 0));
}