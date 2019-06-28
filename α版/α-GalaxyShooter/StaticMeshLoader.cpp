#include "StaticMeshLoader.h"
using namespace staticMeshNS;

StaticMeshLoader::StaticMeshLoader()
{
	fileName[BULLET] = { "bullet.x" };
	fileName[FIELD001] = { "field001.x" };
	fileName[SAMPLE_HIERARCHY_MESH] = { "HierarchyMesh.x" };
	fileName[MAGNET_S] = { "magnetS.x" };
	fileName[MAGNET_N] = { "magnetN.x" };
	fileName[PLANET] = { "planet.x" };
	fileName[SAMPLE_ROBOT001] = { "RobotB.x" };
	fileName[SAMPLE_ROBOT002] = { "robotB_still_back.x" };
	fileName[SAMPLE_SKINNED_MESH] = { "SkinnedMesh.x" };
	fileName[STAR] = { "star.x" };
	fileName[STAR_REGULAR_POLYHEDRON] = { "starRegularPolyhedron.x" };
	fileName[STAR_REGULAR_POLYHEDRON_X10] = { "x10starRegularPolyhedron.x" };
	fileName[STAR_REGULAR_POLYHEDRON_X100] = { "x100starRegularPolyhedron.x" };
	fileName[SAMPLE_STATIC_MESH] = { "StaticMesh.x" };
	fileName[SAMPLE_TOON_MESH] = { "Toon_6Color.x" };
}

StaticMeshLoader::~StaticMeshLoader()
{
	release();
}

HRESULT StaticMeshLoader::load(LPDIRECT3DDEVICE9 device)
{
	setVisualDirectory();
	// Xファイルからメッシュをロードする
	for (int i = 0; i < MESH_NUM; i++)
	{
		staticMesh[i].bufferMaterial = NULL;
		D3DXLoadMeshFromX(
			(LPCSTR)fileName[i],
			D3DXMESH_SYSTEMMEM,
			device,
			NULL,
			&staticMesh[i].bufferMaterial,
			NULL,
			&staticMesh[i].numMaterial,
			&staticMesh[i].mesh);

		D3DXMATERIAL* materials = (D3DXMATERIAL*)staticMesh[i].bufferMaterial->GetBufferPointer();
		staticMesh[i].materials = new D3DMATERIAL9[staticMesh[i].numMaterial];
		staticMesh[i].textures = new LPDIRECT3DTEXTURE9[staticMesh[i].numMaterial];

		for (DWORD num = 0; num < staticMesh[i].numMaterial; num++)
		{
			staticMesh[i].materials[num] = materials[num].MatD3D;
			staticMesh[i].materials[num].Ambient = staticMesh[i].materials[num].Diffuse;
			staticMesh[i].textures[num] = NULL;
			if (materials[num].pTextureFilename != NULL && lstrlen(materials[num].pTextureFilename) > 0)
			{
				D3DXCreateTextureFromFile(device,materials[num].pTextureFilename,&staticMesh[i].textures[num]);
			}
		}

		//頂点バッファの取得
		staticMesh[i].mesh->GetVertexBuffer(&staticMesh[i].vertexBuffer);

		//インデックスバッファの取得
		staticMesh[i].mesh->GetIndexBuffer(&staticMesh[i].indexBuffer);

		//
		staticMesh[i].mesh->GetFVF();

	}


	return S_OK;
}

void StaticMeshLoader::release(void)
{

}