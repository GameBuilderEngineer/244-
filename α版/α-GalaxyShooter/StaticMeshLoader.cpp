//===================================================================================================================================
//�yStaticMeshLoader.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/17
//===================================================================================================================================
#include "StaticMeshLoader.h"
using namespace staticMeshNS;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
StaticMeshLoader::StaticMeshLoader()
{
	fileName[CHILD] = { "Character_Eve.x" };
	fileName[BULLET] = { "bullet.x" };
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
	fileName[MEMORY_PILE] = { "memoryPile.x" };
	fileName[WASUREMONO_BALL] = { "ball.x" };
	fileName[WASUREMONO_PHONE] = { "phone.X" };
	fileName[WASUREMONO_BUNNY] = { "toybunny.x" };
	fileName[WASUREMONO_FAN] = { "Fan.x" };
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
StaticMeshLoader::~StaticMeshLoader()
{
	release();
}

//===================================================================================================================================
//�y�Ǎ������z
//===================================================================================================================================
HRESULT StaticMeshLoader::load(LPDIRECT3DDEVICE9 device)
{
	setVisualDirectory();
	// X�t�@�C�����烁�b�V�������[�h����
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

		//�C���f�b�N�X�o�b�t�@�̎擾
		staticMesh[i].mesh->GetIndexBuffer(&staticMesh[i].indexBuffer);
		
		//�����e�[�u���T�C�Y���擾
		staticMesh[i].mesh->GetAttributeTable(NULL, &staticMesh[i].attributeTableSize);

		//�T�C�Y���̃������̈�m��
		staticMesh[i].attributeTable = new D3DXATTRIBUTERANGE[staticMesh[i].attributeTableSize];

		//�����e�[�u���̎擾
		staticMesh[i].mesh->GetAttributeTable(staticMesh[i].attributeTable, &staticMesh[i].attributeTableSize);

		//���_�����̎擾�E�ݒ�
		D3DVERTEXELEMENT9 vertexElement[65];
		staticMesh[i].mesh->GetDeclaration(vertexElement);
		for (int num = 0; num < 65;num++)
		{
			staticMesh[i].vertexElement[num] = vertexElement[num];
		}
		device->CreateVertexDeclaration(vertexElement, &staticMesh[i].declaration);

		staticMesh[i].numBytesPerVertex = staticMesh[i].mesh->GetNumBytesPerVertex();
		
		//���_�o�b�t�@�̎擾
		staticMesh[i].mesh->GetVertexBuffer(&staticMesh[i].vertexBuffer);
	}

	return S_OK;
}

//===================================================================================================================================
//�y��������z
//===================================================================================================================================
void StaticMeshLoader::release(void)
{

}