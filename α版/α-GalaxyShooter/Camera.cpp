//===================================================================================================================================
//【Camera.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/05
//===================================================================================================================================
#include "Camera.h"

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Camera::Camera()
{
	ZeroMemory(this, sizeof(Camera));
	D3DXQuaternionIdentity(&relativeQuaternion);
	posture = D3DXQUATERNION(0, 0, 0, 1);
	D3DXMatrixRotationQuaternion(&world, &posture);
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
Camera::~Camera()
{

}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
HRESULT Camera::initialize(DWORD _windowWidth, DWORD _windowHeight)
{
	setAspect(_windowWidth,_windowHeight);
	return S_OK;
}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
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
	gazePosition += 
		relativeGaze.x*D3DXVECTOR3(world._11,world._12,world._13)+
		relativeGaze.y*D3DXVECTOR3(world._21,world._22,world._23)+
		relativeGaze.z*D3DXVECTOR3(world._31,world._32,world._33);

	
	setViewProjection();
}


//
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


void Camera::lockOn(D3DXVECTOR3 lockOnTarget,float frameTime)
{
	D3DXVECTOR3 axis(0, 1, 0);
	float radian;

	//プレイヤーとロックオン対象の方向ベクトル
	D3DXVECTOR3 lockOnTargetDirection;
	between2VectorDirection(&lockOnTargetDirection, *target, lockOnTarget);
	lockOnTargetDirection = slip(lockOnTargetDirection, getDirectionY());
	D3DXVec3Normalize(&lockOnTargetDirection, &lockOnTargetDirection);
	D3DXVECTOR3 front = slip(getDirectionZ(), getDirectionY());
	D3DXVec3Normalize(&front, &front);
	if (formedRadianAngle(&radian, front, lockOnTargetDirection))
	{
		rotation(axis, D3DXToDegree(radian));
	}

}

//===================================================================================================================================
//【setter】
//===================================================================================================================================
//ウィンドウサイズによるアスペクト比の設定
void Camera::setAspect(DWORD _windowWidth, DWORD _windowHeight)
{
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
	aspect = (FLOAT)windowWidth / (FLOAT)windowHeight;
}

//プロジェクション行列とビュー行列の設定
HRESULT Camera::setViewProjection()
{
	D3DXMatrixLookAtLH(&view, &position, &gazePosition, &upVector);
	// プロジェクション
	//D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI / 2.5, aspect, 0.1f, 1000.0f);
	D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI / 2.5, aspect, 0.1f, 10000.0f);

	return S_OK;
}

//===================================================================================================================================
//【getter】
//===================================================================================================================================
D3DXVECTOR3 Camera::getAxisZ()
{
	return D3DXVECTOR3(world._31, world._32, world._33);
}
D3DXVECTOR3 Camera::getAxisY()
{
	return D3DXVECTOR3(world._21, world._22, world._23);
}
D3DXVECTOR3 Camera::getHorizontalAxis()
{
	D3DXVECTOR3 axis;
	D3DXVec3Cross(&axis,&D3DXVECTOR3(0,1,0),&D3DXVECTOR3(relativeQuaternion.x, relativeQuaternion.y, relativeQuaternion.z));
	if (isnan(axis.x)||isnan(axis.y)||isnan(axis.z))return D3DXVECTOR3(1,0,0);	
	return axis;
}
