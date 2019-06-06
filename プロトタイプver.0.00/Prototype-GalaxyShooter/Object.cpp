#include "Object.h"
#include "Base.h"
Object::Object()
{
	ZeroMemory(this, sizeof(Object));
	D3DXMatrixIdentity(&matrixRotation);
	quaternion = D3DXQUATERNION(0, 0, 0, 1);
	gravity = D3DXVECTOR3(0, 0, 0);
	axisX = D3DXVECTOR3(1, 0, 0);
	axisY = D3DXVECTOR3(1, 0, 0);
	axisZ = D3DXVECTOR3(0, 0, 1);
}

Object::~Object()
{
}

HRESULT Object::initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position)
{
	// ���b�V���̏����ʒu
	memcpy(position, _position, sizeof(D3DXVECTOR3));
	// X�t�@�C�����烁�b�V�������[�h����	
	LPD3DXBUFFER materialBuffer = NULL;
	setVisualDirectory();
	if (FAILED(D3DXLoadMeshFromX(xFileName, D3DXMESH_SYSTEMMEM,
		device, NULL, &materialBuffer, NULL,
		&numMaterials, &mesh)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", xFileName, MB_OK);
		return E_FAIL;
	}
	D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
	meshMaterials = new D3DMATERIAL9[numMaterials];
	meshTextures = new LPDIRECT3DTEXTURE9[numMaterials];

	for (DWORD i = 0; i < numMaterials; i++)
	{
		meshMaterials[i] = materials[i].MatD3D;
		meshMaterials[i].Ambient = meshMaterials[i].Diffuse;
		meshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL &&
			lstrlen(materials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(device,
				materials[i].pTextureFilename,
				&meshTextures[i])))
			{
				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
			}
		}
	}
	materialBuffer->Release();

	return S_OK;
}

VOID Object::render(LPDIRECT3DDEVICE9 device)
{
	//���[���h�g�����X�t�H�[���i���[�J�����W�����[���h���W�ւ̕ϊ��j	
	D3DXMatrixTranslation(&matrixPosition, position.x, position.y, position.z);

	//�N�H�[�^�j�I���iqtnAttitude�j����]�ʃp�����[�^�[�Ɏg�p����
	{
		D3DXMatrixRotationQuaternion(&matrixRotation, &quaternion);
	}
	D3DXMatrixMultiply(&matrixWorld, &matrixRotation, &matrixPosition);

	device->SetTransform(D3DTS_WORLD, &matrixWorld);

	//��]�ɂ��A���[�J�������Ȃ���
	D3DXVec3TransformCoord(&axisX, &D3DXVECTOR3(1, 0, 0), &matrixRotation);
	D3DXVec3TransformCoord(&axisY, &D3DXVECTOR3(0, 1, 0), &matrixRotation);
	D3DXVec3TransformCoord(&axisZ, &D3DXVECTOR3(0, 0, 1), &matrixRotation);

	// �����_�����O			
	for (DWORD i = 0; i < numMaterials; i++)
	{
		device->SetMaterial(&meshMaterials[i]);
		device->SetTexture(0, meshTextures[i]);
		mesh->DrawSubset(i);
	}
}