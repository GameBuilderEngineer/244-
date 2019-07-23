#pragma once
#include "Base.h"

class Recursion:public Base
{
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	LPDIRECT3DVERTEXBUFFER9 uvBuffer;
	LPDIRECT3DINDEXBUFFER9 indexBuffer;
	LPDIRECT3DVERTEXDECLARATION9 declation;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXEFFECT effect;
	D3DXVECTOR3 center;//èdêS
	bool onRender;

public:
	Recursion();
	~Recursion();

	HRESULT initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3* vertexArray,LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void calculationCenter();
};