#include "MemoryLine.h"

MemoryLine::MemoryLine()
{
	initialized = false;
}

MemoryLine::~MemoryLine()
{

}

void MemoryLine::initialize(MemoryPile* memoryPile, int num, Player* player)
{
	pileNum = num;
	joinTarget = memoryPile;
	joinPlayer = player;
	initialized = true;
}

void MemoryLine::unInitialize()
{

}

void MemoryLine::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	if (initialized == false)return;			//�������ς݂łȂ���ΏI��

}
void MemoryLine::update(float frameTime)
{
	if (initialized == false)return;			//�������ς݂łȂ���ΏI��
	for (int i = 0; i < pileNum; i++)
	{
		if (joinTarget[i].getActive())
		{

		}
	}
}
