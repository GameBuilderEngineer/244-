//===================================================================================================================================
//�yStaticMeshLoader.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/12
//===================================================================================================================================
#pragma once
#include "Base.h"

namespace staticMeshNS {
	enum MESH_NUMBER {
		GUN,
		BULLET,
		CUBE,
		SAMPLE_HIERARCHY_MESH,
		MAGNET_S,
		MAGNET_N,
		PLANET,
		SAMPLE_ROBOT001,
		SAMPLE_ROBOT002,
		SAMPLE_SKINNED_MESH,
		STAR,
		STAR_REGULAR_POLYHEDRON,
		STAR_REGULAR_POLYHEDRON_X10,
		STAR_REGULAR_POLYHEDRON_X100,
		SAMPLE_STATIC_MESH,
		SAMPLE_TOON_MESH,
		MEMORY_PILE,
		WASUREMONO_BUNNY,
		WASUREMONO_PAPER,
		WASUREMONO_REDBULL,
		WASUREMONO_SHOES,
		WASUREMONO_TEAPOT,
		WASUREMONO_LIGHT,
		WASUREMONO_BALL,
		WASUREMONO_SCISSORS,
		WASUREMONO_PLAYSTATION,
		WASUREMONO_HAT,
		MESH_NUM,
	};
}

struct StaticMesh
{
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;		//���_���o�b�t�@
	LPDIRECT3DINDEXBUFFER9			indexBuffer;		//�C���f�b�N�X�o�b�t�@
	LPD3DXMESH						mesh;				// ���b�V�����
	D3DMATERIAL9*					materials;			// �}�e���A�����i�[��
	LPD3DXBUFFER					bufferMaterial;		// ���b�V���̃}�e���A���o�b�t�@
	LPDIRECT3DTEXTURE9*				textures;			// �e�N�X�`�����i�[��
	DWORD							numMaterial;		// �}�e���A�����̐�
	D3DVERTEXELEMENT9				vertexElement[65];	// ���_����
	LPDIRECT3DVERTEXDECLARATION9	declaration;		// ���_�錾
	DWORD							numBytesPerVertex;	// ���_�T�C�Y
	D3DXATTRIBUTERANGE*				attributeTable;		// �����e�[�u��
	DWORD							attributeTableSize;
};

class StaticMeshLoader :public Base
{
private:
	const char* fileName[staticMeshNS::MESH_NUM];
public:
	StaticMesh	staticMesh[staticMeshNS::MESH_NUM];
	StaticMeshLoader();
	~StaticMeshLoader();

	HRESULT load(LPDIRECT3DDEVICE9 device);
	void release(void);
};