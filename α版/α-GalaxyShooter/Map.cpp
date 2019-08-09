//-----------------------------------------------------------------------------
// �}�b�v���� [Map.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/27
//-----------------------------------------------------------------------------
#include "Map.h"
using namespace MapNS;

#if 0	// �}�b�v�m�[�h�̃R���W������\������ꍇ��1
#define MAP_COLLISION_VIEW
#endif
#if 1	// �}�b�v�m�[�h�̃}�[�N��\������ꍇ��1
#define MAP_MARK_VIEW
#endif 

//*****************************************************************************
// �ÓI�����o
//*****************************************************************************
int MapNode::instanceCount = -1;
std::vector<MapNode*> Map::mapNode;
Planet* Map::field;// �������̑[�u



//=============================================================================
// ����������
//=============================================================================
void Map::initialize(LPDIRECT3DDEVICE9 device, Planet* _field)
{
	field = _field;

	// D3DXCreateSphere(�f�o�C�X, ���̔��a, �X���C�X��, �X�^�b�N��, ���b�V��, �אڐ��f�[�^)
	// �m�[�h�̃o�E���f�B���O�X�t�B�A�p���b�V��
	D3DXCreateSphere(device, 28.0f, 9, 9, &sphere, NULL);
	// �m�[�h�̕\���}�[�N�p���b�V��
	D3DXCreateSphere(device, 1.0f, 5, 5, &mapCoodMark, NULL);

	// �m�[�h�̕\���}�[�N�p���b�V���̃}�e���A��
	// ���C�g�͐؂�̂�Diffuse, Ambient�͕s���������ł悢
	mapCoodMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	mapCoodMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mapCoodMat.Emissive = { 0.0f, 1.0f, 1.0f, 1.0f };
	targetCoodMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	targetCoodMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	targetCoodMat.Emissive = { 1.0f, 0.0f, 0.0f, 1.0f };

	// �t�B�[���h�̔��a�𑪂�
	ruler.start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ruler.direction = D3DXVECTOR3(0.0f, 10000.0f, 0.0f);
	float radius = 0.0f;
	if (ruler.rayIntersect(*field->getMesh(), *field->getMatrixWorld()))
	{
		radius = ruler.distance;
	}

	//---------------
	// �m�[�h��z�u
	//---------------
	// �k�ɓ_�ɔz�u
	ruler.direction = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Scale(&ruler.direction, &ruler.direction, ruler.distance);
	createNode(device);

	// ���C����]�����Ȃ�����̈ܓx�o�x���Ƃɔz�u
	D3DXMATRIX rotationMatrix;
	for (int i = 0; i < STACKS; i++)
	{
		ruler.direction = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Scale(&ruler.direction, &ruler.direction, ruler.distance);

		// Z����]
		D3DXMatrixIdentity(&rotationMatrix);
		D3DXMatrixRotationZ(&rotationMatrix, (i + 1) * D3DX_PI / (float)STACKS);
		D3DXVec3TransformCoord(&ruler.direction, &ruler.direction, &rotationMatrix);

		for (int j = 0; j < SLICES; j++)
		{
			// Y����]
			D3DXMatrixIdentity(&rotationMatrix);
			D3DXMatrixRotationY(&rotationMatrix, j * 2.0f * D3DX_PI / (float)SLICES);
			D3DXVec3TransformCoord(&ruler.direction, &ruler.direction, &rotationMatrix);

			createNode(device);
		}
	}

	// ��ɓ_�ɔz�u
	ruler.direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Scale(&ruler.direction, &ruler.direction, ruler.distance);
	createNode(device);


// �m�[�h���ϓ��ɎU�炻���Ƃ������ł��Ȃ������c�[
//D3DXVECTOR2 tempVector(ruler.direction.x, ruler.direction.z);
//float tempRadius = D3DXVec2Length(&tempVector);
//float tempCircumference = tempRadius * 2.0f * D3DX_PI;
//float percentage = tempCircumference / circumference;
//int slices = (int)(SLICES * percentage + 0.9f);
//int slices;
//switch (i)
//{
//case 1:	slices = 6; break;
//case 2:	slices = 8; break;
//case 3:	slices = 10; break;
//case 4:	slices = 12; break;
//case 5:	slices = 10; break;
//case 6:	slices = 8; break;
//case 7:	slices = 6; break;
//}
}


//=============================================================================
// �I������
//=============================================================================
void Map::uninitialize(void)
{
	for (size_t i = 0; i < mapNode.size(); i++)
	{
		delete mapNode[i];
	}
	mapNode.clear();
}


//=============================================================================
// �`�揈��
//=============================================================================
void Map::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
#ifdef _DEBUG

// �R���W�����̕`��
#ifdef MAP_COLLISION_VIEW
	for (size_t i = 0; i < mapNode.size(); i++)
	{
		mapNode[i]->boundingSphere.render(device, *mapNode[i]->getWorldMatrix());
	}
#endif// MAP_COLLISION_VIEW

// �}�[�N�̕`��
#ifdef MAP_MARK_VIEW

	D3DMATERIAL9 matDef;
	device->GetMaterial(&matDef);
	device->LightEnable(0, false);
	for (size_t i = 0; i < mapNode.size(); i++)
	{
		if (i == 5)
		{
			device->SetMaterial(&targetCoodMat);
		}
		else
		{
			device->SetMaterial(&mapCoodMat);
		}
		device->SetTransform(D3DTS_WORLD, mapNode[i]->getWorldMatrix());
		mapCoodMark->DrawSubset(0);
	}
	device->LightEnable(0, true);
	device->SetMaterial(&matDef);
#endif// MAP_MARK_VIEW

#endif// _DEBUG
}


//=============================================================================
// �m�[�h����
//=============================================================================
void Map::createNode(LPDIRECT3DDEVICE9 device)
{
	MapNode *newNode = new MapNode;
	newNode->setNumber(newNode->getInstanceCount());
	newNode->setPosition(ruler.direction);
	D3DXMatrixIdentity(newNode->getWorldMatrix());
	D3DXMatrixTranslation(newNode->getWorldMatrix(),
		newNode->getPosition()->x, newNode->getPosition()->y, newNode->getPosition()->z);
	newNode->setWasuremonoCount(0);
	newNode->boundingSphere.initialize(device, newNode->getPosition(), sphere);
	mapNode.emplace_back(newNode);
}