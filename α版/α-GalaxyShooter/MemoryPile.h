//===================================================================================================================================
//【MemoryLine.h】
// 作成者：HAL東京GP12A332 11 菅野 樹
// 作成日：2019/07/04
// 更新日：2019/09/03
//===================================================================================================================================
#pragma once
#include "Object.h"
#include "Lambert.h"

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
	//Method
	MemoryPile();
	~MemoryPile();

	//processing
	void initialize(LPDIRECT3DDEVICE9 device, StaticMesh*_staticMesh, D3DXVECTOR3* _position);
	void update(float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

	//operation
	void lost(float frameTime);
	void reset();
	void switchLost();
	bool ready();

	//setter
	//getter
};