#pragma once
#include "Base.h"

struct PlaneVertex
{
	D3DXVECTOR2 coord;
	D3DXVECTOR2 uv;
};

class Plane : public Base
{
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	LPDIRECT3DVERTEXBUFFER9 positionBuffer;
	IDirect3DVertexDeclaration9* declation;
	LPD3DXEFFECT effect;
	D3DXVECTOR3* position;
	LPDIRECT3DTEXTURE9 texture;
	int num;
public:
	Plane();
	~Plane();

	HRESULT initialize(LPDIRECT3DDEVICE9 device);

	//球状にランダム配置表示する
	void createPositionSpherical(int _num, float radius);

	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

};