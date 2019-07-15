#pragma once
#include "Base.h"
#include "MemoryPile.h"
#include "Player.h"
#include "InstancingBillboard.h"
#include <vector>

namespace memoryLineNS
{
	const float MINIMUM_DISTANCE = 2.0f;
	const float MAXIMUM_DISTANCE = 10.0f;
}

struct Line
{
	D3DXVECTOR3 start;
	D3DXVECTOR3 end;
};

class MemoryLine : public Base
{
	Line* line;
	InstancingBillboard billboard;
	MemoryPile* joinTarget;
	Player* joinPlayer;
	D3DXVECTOR3** pointList;
	D3DXVECTOR3* renderList;
	bool initialized;
	int pileNum;
	int* pointNum;
	int renderNum;
public:
	MemoryLine();
	~MemoryLine();

	void initialize(LPDIRECT3DDEVICE9 device, MemoryPile* memoryPile, int num, Player* player);
	void unInitialize();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void update(LPDIRECT3DDEVICE9 device, float frameTime);

	void setLine(LPDIRECT3DDEVICE9 device);
	
};

