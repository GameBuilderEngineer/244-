#include "MemoryPile.h"



MemoryPile::MemoryPile()
{
}


MemoryPile::~MemoryPile()
{
}

void MemoryPile::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);

}

void MemoryPile::update(float frameTime)
{
	Object::update();
}

void MemoryPile::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
}