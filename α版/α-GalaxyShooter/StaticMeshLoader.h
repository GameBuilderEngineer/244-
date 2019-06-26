#pragma once
#include "Base.h"

namespace staticMeshNS {
	enum MODEL_NUMBER {

		MAX_NUM = 1,
	};
}

struct StaticMesh
{
	LPD3DXMESH						mesh;		// メッシュ情報へのポインタ
	D3DMATERIAL9*					materials;	// マテリアル情報格納先
	LPD3DXBUFFER					bufferMaterial;	// メッシュのマテリアル情報を格納
	LPDIRECT3DTEXTURE9*				g_pD3DXTextures;	// テクスチャ情報格納先
	DWORD							g_nNumMaterial;		// マテリアル情報の数

};

class StaticMeshLoader :public Base
{
private:
	const char* staticMeshName[staticMeshNS::MAX_NUM];
	StaticMesh	staticMesh[staticMeshNS::MAX_NUM];
public:
	StaticMeshLoader();
	~StaticMeshLoader();

	HRESULT load(LPDIRECT3DDEVICE9 device);
	void release(void);


};