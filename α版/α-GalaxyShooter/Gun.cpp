//============================================================================================================================================
// Document
//============================================================================================================================================
// Gun.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/09/11
//============================================================================================================================================
#include "Gun.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace gunNS;
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
Gun::Gun(void)
{
	onLighting = false;
	activation();

	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
Gun::~Gun(void)
{
	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
void Gun::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
	
	return;
}
//============================================================================================================================================
// release
// ���
//============================================================================================================================================
void Gun::release(void)
{
	return;
}
//============================================================================================================================================
// update
// �X�V
//============================================================================================================================================
void Gun::update(float _frameTime, D3DXVECTOR3 _position)
{
	//// ���W
	//setPosition(_position);

	////// �p������
	////postureControl(axisY.direction, -gravityRay.direction, 3.0f * _frameTime);

	//Object::update();

	return;
}
//============================================================================================================================================
// render
// �`��
//============================================================================================================================================
void Gun::render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPositon, D3DXMATRIX _matrixPlayer, D3DXMATRIX _matrixAnimation)
{
	//D3DXMATRIXA16 matrix;																		//	���[�J���}�g���N�X
	//UINT matrixIndex = NULL;																	//	�}�g���N�X�C���f�b�N�X
	//D3DXMeshContainerDerived* meshContainer = (D3DXMeshContainerDerived*)_baseMeshContainer;	//	���b�V���R���e�i�|�C���^

	//if (meshContainer->pSkinInfo != NULL)
	//{
	//	LPD3DXBONECOMBINATION boneCombination = NULL;	//	�{�[���̑g�ݍ��킹

	//	boneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(meshContainer->boneCombinationBuffer->GetBufferPointer());

	//	for (DWORD j = 0; j < meshContainer->boneWeightMax; ++j)
	//	{
	//		// ������0
	//		matrixIndex = boneCombination[0].BoneId[j];

	//		if (matrixIndex != UINT_MAX)
	//		{
	//			D3DXMatrixMultiply(&matrix, &meshContainer->boneOffsetMatrix[matrixIndex], meshContainer->boneMatrix[matrixIndex]);
	//			_device->SetTransform(D3DTS_WORLDMATRIX(j), &matrix);
	//		}
	//	}
	//}

	D3DXMatrixIdentity(&matrixWorld);
	D3DXMatrixMultiply(&matrixWorld, &_matrixPlayer, &_matrixAnimation);

	Object::render(_device, _view, _projection, _cameraPositon);

	return;
}
////============================================================================================================================================
//// render
//// �`��
////============================================================================================================================================
//void Gun::render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPositon, LPD3DXMESHCONTAINER _baseMeshContainer)
//{
//	//D3DXMATRIXA16 matrix;																		//	���[�J���}�g���N�X
//	//UINT matrixIndex = NULL;																	//	�}�g���N�X�C���f�b�N�X
//	//D3DXMeshContainerDerived* meshContainer = (D3DXMeshContainerDerived*)_baseMeshContainer;	//	���b�V���R���e�i�|�C���^
//
//	//if (meshContainer->pSkinInfo != NULL)
//	//{
//	//	LPD3DXBONECOMBINATION boneCombination = NULL;	//	�{�[���̑g�ݍ��킹
//
//	//	boneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(meshContainer->boneCombinationBuffer->GetBufferPointer());
//
//	//	for (DWORD j = 0; j < meshContainer->boneWeightMax; ++j)
//	//	{
//	//		// ������0
//	//		matrixIndex = boneCombination[0].BoneId[j];
//
//	//		if (matrixIndex != UINT_MAX)
//	//		{
//	//			D3DXMatrixMultiply(&matrix, &meshContainer->boneOffsetMatrix[matrixIndex], meshContainer->boneMatrix[matrixIndex]);
//	//			_device->SetTransform(D3DTS_WORLDMATRIX(j), &matrix);
//	//		}
//	//	}
//	//}
//
//	matrixWorld = matrix;
//
//	Object::render(_device, _view, _projection, _cameraPositon);
//
//	return;
//}