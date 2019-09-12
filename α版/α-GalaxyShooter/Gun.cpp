//============================================================================================================================================
// Document
//============================================================================================================================================
// Gun.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/09/11
//============================================================================================================================================
#include "Gun.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace gunNS;
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
Gun::Gun(void)
{
	onLighting = false;
	activation();

	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
Gun::~Gun(void)
{
	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
void Gun::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
	
	return;
}
//============================================================================================================================================
// release
// 解放
//============================================================================================================================================
void Gun::release(void)
{
	return;
}
//============================================================================================================================================
// update
// 更新
//============================================================================================================================================
void Gun::update(float _frameTime, D3DXVECTOR3 _position)
{
	//// 座標
	//setPosition(_position);

	////// 姿勢制御
	////postureControl(axisY.direction, -gravityRay.direction, 3.0f * _frameTime);

	//Object::update();

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void Gun::render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPositon, D3DXMATRIX _matrixPlayer, D3DXMATRIX _matrixAnimation)
{
	//D3DXMATRIXA16 matrix;																		//	ローカルマトリクス
	//UINT matrixIndex = NULL;																	//	マトリクスインデックス
	//D3DXMeshContainerDerived* meshContainer = (D3DXMeshContainerDerived*)_baseMeshContainer;	//	メッシュコンテナポインタ

	//if (meshContainer->pSkinInfo != NULL)
	//{
	//	LPD3DXBONECOMBINATION boneCombination = NULL;	//	ボーンの組み合わせ

	//	boneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(meshContainer->boneCombinationBuffer->GetBufferPointer());

	//	for (DWORD j = 0; j < meshContainer->boneWeightMax; ++j)
	//	{
	//		// 試しに0
	//		matrixIndex = boneCombination[0].BoneId[j];

	//		if (matrixIndex != UINT_MAX)
	//		{
	//			D3DXMatrixMultiply(&matrix, &meshContainer->boneOffsetMatrix[matrixIndex], meshContainer->boneMatrix[matrixIndex]);
	//			_device->SetTransform(D3DTS_WORLDMATRIX(j), &matrix);
	//		}
	//	}
	//}

	//D3DXMatrixIdentity(&matrixWorld);
	//D3DXMatrixMultiply(&matrixWorld, &_matrixPlayer, &_matrixAnimation);
	matrixWorld = _matrixPlayer;
	Object::render(_device, _view, _projection, _cameraPositon);

	return;
}
////============================================================================================================================================
//// render
//// 描画
////============================================================================================================================================
//void Gun::render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPositon, LPD3DXMESHCONTAINER _baseMeshContainer)
//{
//	//D3DXMATRIXA16 matrix;																		//	ローカルマトリクス
//	//UINT matrixIndex = NULL;																	//	マトリクスインデックス
//	//D3DXMeshContainerDerived* meshContainer = (D3DXMeshContainerDerived*)_baseMeshContainer;	//	メッシュコンテナポインタ
//
//	//if (meshContainer->pSkinInfo != NULL)
//	//{
//	//	LPD3DXBONECOMBINATION boneCombination = NULL;	//	ボーンの組み合わせ
//
//	//	boneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(meshContainer->boneCombinationBuffer->GetBufferPointer());
//
//	//	for (DWORD j = 0; j < meshContainer->boneWeightMax; ++j)
//	//	{
//	//		// 試しに0
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