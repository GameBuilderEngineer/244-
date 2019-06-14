#include "Camera.h"

Camera::Camera()
{
	ZeroMemory(this, sizeof(Camera));
	D3DXQuaternionIdentity(&relativeQuaternion);
	posture = D3DXQUATERNION(0, 0, 0, 1);
	D3DXMatrixRotationQuaternion(&world, &posture);
}

Camera::~Camera()
{

}

HRESULT Camera::initialize(DWORD _windowWidth, DWORD _windowHeight)
{
	setAspect(_windowWidth,_windowHeight);
	return S_OK;
}

void Camera::update()
{
	if (target != NULL) {
		gazePosition = *target;
		position = *target;
	}
	else {
		position = (D3DXVECTOR3)relativeQuaternion;
	}

	D3DXVECTOR3 axisY(world._21, world._22, world._23);
	if(targetY != NULL)Base::postureControl(&posture,axisY,*targetY ,0.1f);

	//姿勢クォータニオンから姿勢行列を作成する
	D3DXMatrixRotationQuaternion(&world, &posture);
	position +=
		relativeQuaternion.x*D3DXVECTOR3(world._11,world._12,world._13)+
		relativeQuaternion.y*D3DXVECTOR3(world._21,world._22,world._23)+
		relativeQuaternion.z*D3DXVECTOR3(world._31,world._32,world._33);


	setViewProjection();
}

D3DXVECTOR3 Camera::getHorizontalAxis()
{
	D3DXVECTOR3 axis;
	D3DXVec3Cross(&axis,&D3DXVECTOR3(0,1,0),&D3DXVECTOR3(relativeQuaternion.x, relativeQuaternion.y, relativeQuaternion.z));
	if (isnan(axis.x)||isnan(axis.y)||isnan(axis.z))return D3DXVECTOR3(1,0,0);	
	return axis;
}

void Camera::rotation(D3DXVECTOR3 axis,float degree)
{
	D3DXQUATERNION conjugateQ;
	D3DXQUATERNION rotationQ(0,0,0,1);
	float radian = D3DXToRadian(degree);
	D3DXQuaternionRotationAxis(&rotationQ, &axis, radian);
	D3DXQuaternionConjugate(&conjugateQ, &rotationQ);

	//共役*回転対象*回転クォータニオン
	relativeQuaternion = conjugateQ * relativeQuaternion * rotationQ;
}

void Camera::setAspect(DWORD _windowWidth, DWORD _windowHeight)
{
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
	aspect = (FLOAT)windowWidth / (FLOAT)windowHeight;

}

HRESULT Camera::setViewProjection()
{
	D3DXMatrixLookAtLH(&view, &position, &gazePosition, &upVector);

	// プロジェクション
	D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI / 4, aspect, 0.1f, 1000.0f);

	return S_OK;
}