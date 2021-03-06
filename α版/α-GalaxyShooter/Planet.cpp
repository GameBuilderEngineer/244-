//===================================================================================================================================
//�yPlanet.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/06/05
// [�X�V��]2019/08/04
//===================================================================================================================================
#include "Planet.h"

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
Planet::Planet()
{
	onLighting = false;
	activation();
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
Planet::~Planet()
{

}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
void Planet::initilaize(LPDIRECT3DDEVICE9 device, StaticMesh*_staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
	sphereCollide.initialize(device,&position, _staticMesh->mesh);
	radius = sphereCollide.getRadius();
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void Planet::update()
{

}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
void Planet::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
#ifdef _DEBUG
	sphereCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//�ysetter�z
//===================================================================================================================================

//===================================================================================================================================
//�ygetter�z
//===================================================================================================================================
LPD3DXMESH Planet::getSphereMesh()
{
	return sphereCollide.getMesh();
}
