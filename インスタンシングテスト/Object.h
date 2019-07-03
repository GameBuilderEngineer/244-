#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"

namespace ObjectNS{
	const int WIDTH_NUM = 100;
	const int DEPTH_NUM = 100;
}

class Object
{
	LPD3DXMESH pMesh = NULL;
	D3DMATERIAL9* pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	DWORD dwNumMaterials = 0;
	LPD3DXEFFECT g_pEffect = NULL;
	IDirect3DVertexBuffer9* vtxBuf;
	IDirect3DVertexBuffer9* worldPosBuf;
	IDirect3DVertexDeclaration9* decl;
public:
	Object();
	~Object();
	HRESULT initialize(LPDIRECT3DDEVICE9 pDevice);
	void update();
	void render(LPDIRECT3DDEVICE9 pDevice);
	void unInitialize();
};