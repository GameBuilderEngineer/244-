#pragma once
#include "Object.h"
class MemoryPile :public Object
{
public:
	MemoryPile();
	~MemoryPile();

	void initialize(LPDIRECT3DDEVICE9 device, StaticMesh*_staticMesh, D3DXVECTOR3* _position);
	void update(float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

};

