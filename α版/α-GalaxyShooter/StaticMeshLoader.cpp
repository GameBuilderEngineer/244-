#include "StaticMeshLoader.h"
using namespace staticMeshNS;

StaticMeshLoader::StaticMeshLoader()
{
	fileName[BULLET] = { "bullet.x" };
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
	fileName[MEMORY_PILE] = { "memoryPile.x" };
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

		

		//インデックスバッファの取得
		staticMesh[i].mesh->GetIndexBuffer(&staticMesh[i].indexBuffer);

		//ULONG addref = staticMesh[i].mesh->AddRef();
		//
		//DWORD Options;
		//const D3DVERTEXELEMENT9* pDeclaration;
		//LPDIRECT3DDEVICE9 pD3DDevice;
		//LPD3DXMESH* ppCloneMesh;
		//staticMesh[i].mesh->CloneMesh(Options,pDeclaration,pD3DDevice,ppCloneMesh );
		//
		//
		//DWORD FVF;
		//staticMesh[i].mesh->CloneMeshFVF(Options, FVF, pD3DDevice, ppCloneMesh);
		//
		//const DWORD* pAdjacency;
		//DWORD* pPRep;
		//staticMesh[i].mesh->ConvertAdjacencyToPointReps(pAdjacency, pPRep);
		
		//staticMesh[i].mesh->ConvertPointRepsToAdjacency(pPRep, (DWORD*)pAdjacency);
		//
		//DWORD Attribld;
		//staticMesh[i].mesh->DrawSubset(Attribld);
		
		//属性テーブルサイズを取得
		staticMesh[i].mesh->GetAttributeTable(NULL, &staticMesh[i].attributeTableSize);
		//サイズ分のメモリ領域確保
		staticMesh[i].attributeTable = new D3DXATTRIBUTERANGE[staticMesh[i].attributeTableSize];
		//属性テーブルの取得
		staticMesh[i].mesh->GetAttributeTable(staticMesh[i].attributeTable, &staticMesh[i].attributeTableSize);


		//
		D3DVERTEXELEMENT9 vertexElement[65];
		staticMesh[i].mesh->GetDeclaration(vertexElement);
		for (int num = 0; num < 65;num++)
		{
			staticMesh[i].vertexElement[num] = vertexElement[num];
		}
		device->CreateVertexDeclaration(vertexElement, &staticMesh[i].declaration);

		//FVF = staticMesh[i].mesh->GetFVF();

		staticMesh[i].numBytesPerVertex = staticMesh[i].mesh->GetNumBytesPerVertex();

		//
		//staticMesh[i].mesh->GetFVF();
		
		//頂点バッファの取得
		staticMesh[i].mesh->GetVertexBuffer(&staticMesh[i].vertexBuffer);
		//DWORD dwStride = staticMesh[i].mesh->GetNumBytesPerVertex();
		//BYTE *pbVertices = NULL;
		//DWORD maxVertices = staticMesh[i].mesh->GetNumVertices();
		//if (SUCCEEDED(staticMesh[i].vertexBuffer->Lock(0, 0, (VOID**)&pbVertices, 0)))
		//{
		//	D3DXVECTOR3* position;
		//	D3DXVECTOR3* normal;
		//	for (int n = 0; n < maxVertices + 10; n++)
		//	{
		//		position = (D3DXVECTOR3*)&pbVertices[n*dwStride];
		//		normal = (D3DXVECTOR3*)&pbVertices[n*dwStride + sizeof(D3DXVECTOR3)];
		//	}
		//	staticMesh[i].vertexBuffer->Unlock();
		//}
	}


	return S_OK;
}

void StaticMeshLoader::release(void)
{

}