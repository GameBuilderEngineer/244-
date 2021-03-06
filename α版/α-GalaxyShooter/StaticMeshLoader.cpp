//===================================================================================================================================
//【StaticMeshLoader.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/17
//===================================================================================================================================
#include "StaticMeshLoader.h"
using namespace staticMeshNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
StaticMeshLoader::StaticMeshLoader()
{
	fileName[GUN] = { "Gun.x" };
	fileName[BULLET] = { "Bullet.x" };
	fileName[CUBE] = { "cube.x" };
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
	fileName[MEMORY_PILE] = { "Memory_Pile.x" };
	fileName[WASUREMONO_BUNNY] = { "toybunny.x" };
	fileName[WASUREMONO_PAPER] = { "paper.x" };
	fileName[WASUREMONO_REDBULL] = { "redbull.x" };
	fileName[WASUREMONO_SHOES] = { "shoes.x" };
	fileName[WASUREMONO_TEAPOT] = { "teapot.x" };
	fileName[WASUREMONO_LIGHT] = { "light.x" };
	fileName[WASUREMONO_BALL] = { "soccerball.x" };
	fileName[WASUREMONO_SCISSORS] = { "scissors.x" };
	fileName[WASUREMONO_PLAYSTATION] = { "playstation.x" };
	fileName[WASUREMONO_HAT] = { "hat.x" };
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
StaticMeshLoader::~StaticMeshLoader()
{
	release();
}

//===================================================================================================================================
//【読込処理】
//===================================================================================================================================
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
		
		//属性テーブルサイズを取得
		staticMesh[i].mesh->GetAttributeTable(NULL, &staticMesh[i].attributeTableSize);

		//サイズ分のメモリ領域確保
		staticMesh[i].attributeTable = new D3DXATTRIBUTERANGE[staticMesh[i].attributeTableSize];

		//属性テーブルの取得
		staticMesh[i].mesh->GetAttributeTable(staticMesh[i].attributeTable, &staticMesh[i].attributeTableSize);

		//頂点属性の取得・設定
		D3DVERTEXELEMENT9 vertexElement[65];
		staticMesh[i].mesh->GetDeclaration(vertexElement);
		for (int num = 0; num < 65;num++)
		{
			staticMesh[i].vertexElement[num] = vertexElement[num];
		}
		device->CreateVertexDeclaration(vertexElement, &staticMesh[i].declaration);

		staticMesh[i].numBytesPerVertex = staticMesh[i].mesh->GetNumBytesPerVertex();
		
		//頂点バッファの取得
		staticMesh[i].mesh->GetVertexBuffer(&staticMesh[i].vertexBuffer);
	}

	return S_OK;
}

//===================================================================================================================================
//【解放処理】
//===================================================================================================================================
void StaticMeshLoader::release(void)
{
	for (int i = 0; i < MESH_NUM; i++)
	{
		for (DWORD num = 0; num < staticMesh[i].numMaterial; num++)
		{
			SAFE_RELEASE(staticMesh[i].textures[num])
		}
		SAFE_RELEASE(staticMesh[i].vertexBuffer);
		SAFE_RELEASE(staticMesh[i].indexBuffer);
		SAFE_RELEASE(staticMesh[i].mesh);
		SAFE_RELEASE(staticMesh[i].declaration);
		SAFE_RELEASE(staticMesh[i].bufferMaterial);

		SAFE_DELETE_ARRAY(staticMesh[i].textures);
		SAFE_DELETE_ARRAY(staticMesh[i].materials);
		SAFE_DELETE_ARRAY(staticMesh[i].bufferMaterial);

	}
}