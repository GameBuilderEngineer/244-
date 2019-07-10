#pragma once
#include "Base.h"
#include "MemoryPile.h"
class MemoryLine : public Base
{
	MemoryPile* joinTarget;
	
public:
	MemoryLine();
	~MemoryLine();

	void initialize(MemoryPile* memoryPile);
	void unInitialize();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void update(float frameTime);
	
};

