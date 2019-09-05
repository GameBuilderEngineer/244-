//===================================================================================================================================
//�yObject.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/06/05
// [�X�V��]2019/08/03
//===================================================================================================================================
#pragma once
#include <stdio.h>
#include <windows.h>
#include <d3dx9.h>
#include "Ray.h"
#include "StaticMeshLoader.h"
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include "Animation.h"

namespace objectNS {

}


class Object:public Base
{
protected:
	//Data
	//�X�^�e�B�b�N���b�V��
	StaticMesh* staticMesh;
	Animation* animation;		//	�A�j���[�V����
	AnimationID animationID;	//	�A�j���[�V����ID

	//�X�e�[�^�X�ϐ�
	D3DXVECTOR3 position;		//�ʒu
	D3DXQUATERNION quaternion;	//��]
	D3DXVECTOR3 scale;			//�X�P�[��
	float radius;				//�Փ˔��a
	float alpha;				//���ߒl

	//�ړ��n�ϐ�
	D3DXVECTOR3 speed;			//���x
	D3DXVECTOR3 acceleration;	//�����x
	D3DXVECTOR3 gravity;		//�d��

	//�e��t���O
	bool onGravity;				//�d�͗L�����t���O
	bool onActive;				//�A�N�e�B�u���t���O
	bool onRender;				//�`��L�����t���O
	bool onLighting;			//���������t���O
	bool onTransparent;			//���߃t���O
	bool operationAlpha;		//���ߒl�̑���L���t���O

	//����6��
	Ray axisX;
	Ray axisY;
	Ray axisZ;
	Ray reverseAxisX;
	Ray reverseAxisY;
	Ray reverseAxisZ;
	//�d��Ray
	Ray gravityRay;

	//�s��i�ʒu�E��]�E���[���h�j�F�X�P�[���ǉ��\��
	D3DXMATRIX matrixPosition;
	D3DXMATRIX matrixRotation;
	D3DXMATRIX matrixWorld;

	//�C���X�^���V���O�ϐ�
	//�`�悷�鐔
	int renderNum;
	//�C���X�^���V���O�`�掞�̊e�I�u�W�F�N�g�̈ʒu�o�b�t�@�[
	LPDIRECT3DVERTEXBUFFER9 positionBuffer;
	LPDIRECT3DVERTEXDECLARATION9 declaration;	// ���_�錾

public:
	//Method
	Object();
	~Object();
	
	//processing
	HRESULT initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position);
	void update();
	//�ʏ탌���_�[
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	//�g�D�[�������_�[
	void toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition,
		LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine);
	//���������_�[�i�C���X�^���V���O�j
	void multipleRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition,
		LPD3DXEFFECT effect);

	//getter
	LPD3DXMESH* getMesh() { return &staticMesh->mesh; }
	D3DXMATRIX *getMatrixWorld() { return &matrixWorld; }	
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
	Ray* getGravityRay() { return &gravityRay; };
	bool getActive() { return onActive; }

	//setter
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void addSpeed(D3DXVECTOR3 add) { speed += add; }
	void setGravity(D3DXVECTOR3 source, float power);
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setQuaternion(D3DXQUATERNION _quaternion) { quaternion = _quaternion; }
	void setAlpha(float value);
	void activation();								//������
	void inActivation();							//�s����
	void switchTransparent(bool flag);				//���߂̐؂�ւ�
	void switchOperationAlpha(bool flag);			//���ߒl����t���O�̐؂�ւ�

	//�`�搔���Z�b�g
	//num:�`�悷�鐔���w��
	//positionBuffer:�e�I�u�W�F�N�g�̈ʒu��ۑ������z��̃|�C���^
	void setNumOfRender(LPDIRECT3DDEVICE9 device, int num, D3DXVECTOR3* _positionList);

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

