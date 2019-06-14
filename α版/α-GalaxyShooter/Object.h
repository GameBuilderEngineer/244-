#pragma once
#include <stdio.h>
#include <windows.h>
#include <d3dx9.h>
#include "Ray.h"

namespace objectNS {

}


class Object:public Base
{
protected:
	//Data

	//�`��n�ϐ�
	LPD3DXMESH mesh;
	D3DMATERIAL9* meshMaterials;
	LPDIRECT3DTEXTURE9* meshTextures;
	LPDIRECT3DTEXTURE9 textureShade;
	LPDIRECT3DTEXTURE9 textureLine;
	DWORD numMaterials;
	LPD3DXEFFECT effect;

	//�X�e�[�^�X�ϐ�
	D3DXVECTOR3 position;		//�ʒu
	D3DXQUATERNION quaternion;	//��]
	D3DXVECTOR3 scale;			//�X�P�[��
	float radius;				//�Փ˔��a

	//�ړ��n�ϐ�
	D3DXVECTOR3 speed;			//���x
	D3DXVECTOR3 acceleration;	//�����x
	D3DXVECTOR3 gravity;		//�d��

	//�e��t���O
	bool onGravity;				//�d�͗L�����t���O

	//����6��
	Ray axisX;
	Ray axisY;
	Ray axisZ;
	Ray reverseAxisX;
	Ray reverseAxisY;
	Ray reverseAxisZ;

	//�s��i�ʒu�E��]�E���[���h�j�F�X�P�[���ǉ��\��
	D3DXMATRIX matrixPosition;
	D3DXMATRIX matrixRotation;
	D3DXMATRIX matrixWorld;

public:
	//Method
	Object();
	~Object();
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position);
	void update();
	VOID render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	VOID toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	//�擾�֐�
	LPD3DXMESH* getMesh() { return &mesh; }
	D3DXMATRIX getMatrixWorld() { return matrixWorld; }
	
	D3DXVECTOR3* getPosition() { return &position; };
	D3DXQUATERNION getQuaternion() { return quaternion; };
	float getRadius() { return radius; }
	
	D3DXVECTOR3 getSpeed() { return speed; }
	D3DXVECTOR3 getAcceleration() { return acceleration; }
	D3DXVECTOR3 getGravity() { return gravity; };
	
	Ray* getAxisX() { return &axisX; };
	Ray* getAxisY() { return &axisY; };
	Ray* getAxisZ() { return &axisZ; };
	Ray* getReverseAxisX() { return &reverseAxisX; };
	Ray* getReverseAxisY() { return &reverseAxisY; };
	Ray* getReverseAxisZ() { return &reverseAxisZ; };

	//�Z�b�g�֐�
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void addSpeed(D3DXVECTOR3 add) { speed += add; }
	void setGravity(D3DXVECTOR3 source, float power);
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setQuaternion(D3DXQUATERNION _quaternion) { quaternion = _quaternion; }
	
	//�p������
	void postureControl(D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection,float t)
	{
		Base::postureControl(&quaternion,currentDirection, nextDirection, t);
	}

	//�C�ӎ����^��ԉ�]
	void anyAxisRotationSlerp(D3DXVECTOR3 axis, float radian,float t)
	{
		Base::anyAxisRotationSlerp(&quaternion, axis, radian, t);
	}
	
	//�C�ӎ���]
	void anyAxisRotation(D3DXVECTOR3 axis, float degree)
	{
		Base::anyAxisRotation(&quaternion, axis, degree);
	}


};

