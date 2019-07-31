#include "MemoryPile.h"

using namespace memoryPileNS;

MemoryPile::MemoryPile()
{
	lostTime = 0;
	onLost = false;
	inActivation();
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
	lost(frameTime);

	Object::update();
}

void MemoryPile::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
}

void MemoryPile::lost(float frameTime)
{
	if (!onLost)return;
	lostTime += frameTime;
	alpha -= frameTime;
	if (lostTime > LOST_TIME)
	{
		inActivation();
		reset();
	}
}

void MemoryPile::reset()
{
	lostTime = 0.0f;
	alpha = 1.0f;
	onLost = false;
}


void MemoryPile::switchLost()
{
	onLost = true;
	switchTransparent(true);
	switchOperationAlpha(true);
}

bool MemoryPile::ready()
{
	return !onLost;
}