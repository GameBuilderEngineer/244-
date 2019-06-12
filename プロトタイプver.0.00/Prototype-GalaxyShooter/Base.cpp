#include "Base.h"
char rootPath[1124]={0};

void initializeDirectory(char* root)
{
	strcpy(rootPath, root);//パス(root)をrootPathへコピー
}

void setRootDirectory()
{
	SetCurrentDirectory(rootPath);
}

void setDataDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\01 Data File");
	SetCurrentDirectory(tmporary);
}

void setVisualDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\02 Visual File");
	SetCurrentDirectory(tmporary);
}

void setShaderDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\03 Shader File");
	SetCurrentDirectory(tmporary);
}

void setSoundDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\04 Sound File");
	SetCurrentDirectory(tmporary);
}

//姿勢制御
void Base::postureControl(D3DXQUATERNION* quaternion, D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection, float t)
{
	D3DXVECTOR3 controlAxis;
	//法線とキャラクターとの外積を求める（平面に直立するための回転軸となる）
	D3DXVec3Cross(&controlAxis, &currentDirection, &nextDirection);
	D3DXVec3Normalize(&controlAxis, &controlAxis);
	float rotationRadian;
	if (formedRadianAngle(&rotationRadian, currentDirection, nextDirection))
	{
		anyAxisRotationSlerp(quaternion, controlAxis, rotationRadian, t);
	}
}

//任意軸線型補間回転
void Base::anyAxisRotationSlerp(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float radian, float t)
{
	D3DXQUATERNION deltaRotation(0, 0, 0, 1);
	D3DXQuaternionRotationAxis(&deltaRotation, &axis, radian);
	deltaRotation = *quaternion * deltaRotation;
	D3DXQuaternionSlerp(quaternion, quaternion, &deltaRotation, t);
}

//任意軸回転
void Base::anyAxisRotation(D3DXQUATERNION* quaternion,D3DXVECTOR3 axis, float degree)
{
	D3DXQUATERNION rotationQ(0, 0, 0, 1);
	float radian = D3DXToRadian(degree);
	D3DXQuaternionRotationAxis(&rotationQ, &axis, radian);

	//共役*回転対象*回転クォータニオン
	*quaternion *= rotationQ;
}

//二つのベクトルのなす角を計算
bool Base::formedRadianAngle(float* out, D3DXVECTOR3 v1, D3DXVECTOR3 v2) {
	float dot = D3DXVec3Dot(&v1, &v2);
	if (isnan(dot))return false;

	float v1Length = D3DXVec3Length(&v1);
	float v2Length = D3DXVec3Length(&v2);
	if (v1Length == 0 || v2Length == 0)return false;

	*out = acosf(dot / (v1Length*v2Length));
	if (isnan(*out))return false;
	return true;
}


//仮置き
D3DXVECTOR3 Base::slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //滑りベクトル（滑る方向）

	//滑りベクトル S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (pow(D3DXVec3Length(&N), 2)))*N;

	return S;
}