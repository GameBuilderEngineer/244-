#include "Base.h"
char rootPath[1124]={0};

void initializeDirectory(char* root)
{
	strcpy(rootPath, root);//�p�X(root)��rootPath�փR�s�[
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

//�p������
void Base::postureControl(D3DXQUATERNION* quaternion, D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection, float t)
{
	D3DXVECTOR3 controlAxis;
	//�@���ƃL�����N�^�[�Ƃ̊O�ς����߂�i���ʂɒ������邽�߂̉�]���ƂȂ�j
	D3DXVec3Cross(&controlAxis, &currentDirection, &nextDirection);
	D3DXVec3Normalize(&controlAxis, &controlAxis);
	float rotationRadian;
	if (formedRadianAngle(&rotationRadian, currentDirection, nextDirection))
	{
		anyAxisRotationSlerp(quaternion, controlAxis, rotationRadian, t);
	}
}

//�C�ӎ����^��ԉ�]
void Base::anyAxisRotationSlerp(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float radian, float t)
{
	D3DXQUATERNION deltaRotation(0, 0, 0, 1);
	D3DXQuaternionRotationAxis(&deltaRotation, &axis, radian);
	deltaRotation = *quaternion * deltaRotation;
	D3DXQuaternionSlerp(quaternion, quaternion, &deltaRotation, t);
}

//�C�ӎ���]
void Base::anyAxisRotation(D3DXQUATERNION* quaternion,D3DXVECTOR3 axis, float degree)
{
	D3DXQUATERNION rotationQ(0, 0, 0, 1);
	float radian = D3DXToRadian(degree);
	D3DXQuaternionRotationAxis(&rotationQ, &axis, radian);

	//����*��]�Ώ�*��]�N�H�[�^�j�I��
	*quaternion *= rotationQ;
}

//��̃x�N�g���̂Ȃ��p���v�Z
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

D3DXVECTOR3 Base::slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //����x�N�g���i��������j

	//����x�N�g�� S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (pow(D3DXVec3Length(&N), 2)))*N;

	return S;
}

float Base::between2VectorLength(D3DXVECTOR3 position1, D3DXVECTOR3 position2)
{
	return D3DXVec3Length(&(position1 - position2));
}

float Base::between2VectorDirection(D3DXVECTOR3* out, D3DXVECTOR3 position1, D3DXVECTOR3 position2)
{
	D3DXVECTOR3 direction = position2 - position1;
	D3DXVec3Normalize(out, &direction);
	return D3DXVec3Length(&direction);
}
void Base::copyVertexBuffer(unsigned size, void *sorce, IDirect3DVertexBuffer9 *buffer) {
	void *p = 0;
	buffer->Lock(0, 0, &p, 0);
	memcpy(p, sorce, size);
	buffer->Unlock();
}
