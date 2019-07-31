#pragma once
#include "Object.h"

namespace memoryPileNS
{
	const float LOST_TIME = 2.0f;
}

class MemoryPile :public Object
{
private:
	float lostTime;
	bool onLost;
public:
	MemoryPile();
	~MemoryPile();

	void initialize(LPDIRECT3DDEVICE9 device, StaticMesh*_staticMesh, D3DXVECTOR3* _position);
	void update(float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void lost(float frameTime);
	void reset();
	void switchLost();
	bool ready();
};