#pragma once
#include "Base.h"

namespace staticMeshNS {
	enum MODEL_NUMBER {

		MAX_NUM = 1,
	};
}

struct StaticMesh
{
	LPD3DXMESH						mesh;		// ���b�V�����ւ̃|�C���^
	D3DMATERIAL9*					materials;	// �}�e���A�����i�[��
	LPD3DXBUFFER					bufferMaterial;	// ���b�V���̃}�e���A�������i�[
	LPDIRECT3DTEXTURE9*				g_pD3DXTextures;	// �e�N�X�`�����i�[��
	DWORD							g_nNumMaterial;		// �}�e���A�����̐�

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