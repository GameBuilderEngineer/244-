//===================================================================================================================================
//yMemoryPile.cppz
// [์ฌา]HALGP12A332 11 ์ ๗
// [์ฌ๚]2019/05/16
// [XV๚]2019/08/04
//===================================================================================================================================
#include "MemoryPile.h"
using namespace memoryPileNS;

//===================================================================================================================================
//yRXgN^z
//===================================================================================================================================
MemoryPile::MemoryPile()
{
	lostTime = 0;
	onLost = false;
	inActivation();
}

//===================================================================================================================================
//yfXgN^z
//===================================================================================================================================
MemoryPile::~MemoryPile()
{

}

//===================================================================================================================================
//y๚ปz
//===================================================================================================================================
void MemoryPile::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
}

//===================================================================================================================================
//yXVz
//===================================================================================================================================
void MemoryPile::update(float frameTime)
{
	lost(frameTime);

	Object::update();
}

//===================================================================================================================================
//y`ๆz
//===================================================================================================================================
void MemoryPile::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
}

//===================================================================================================================================
//yมธz
//[]tOช
//===================================================================================================================================
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