#pragma once
#include "Base.h"
#include "MemoryPile.h"
#include "Player.h"
#include "InstancingBillboard.h"
#include <vector>

namespace memoryLineNS
{
}

class MemoryLine : public Base
{
	InstancingBillboard billboard;
	std::vector<D3DXVECTOR3> positionList;
	MemoryPile* joinTarget;
	Player* joinPlayer;
	int pileNum;
	bool initialized;
public:
	MemoryLine();
	~MemoryLine();

	void initialize(MemoryPile* memoryPile, int num, Player* player);
	void unInitialize();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void update(float frameTime);
	
};

