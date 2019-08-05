//===================================================================================================================================
//�yBoudingSphere.h�z
// �쐬�ҁFHAL����GP12A332 11 ���� ��
// �쐬���F2019/06/12
// �X�V���F2019/08/03
//===================================================================================================================================
#pragma once
#include "Base.h"
class BoundingSphere : public Base
{
private:
	//Data
	D3DXVECTOR3*	position;	//�ʒu
	float			radius;		//���a
	D3DXVECTOR3		center;		//���S
	LPD3DXMESH		mesh;		//���b�V��
public:
	//Method
	BoundingSphere();
	~BoundingSphere();

	//processing
	void initialize(LPDIRECT3DDEVICE9 device,D3DXVECTOR3* position, LPD3DXMESH ownerMesh);
	void initialize(LPDIRECT3DDEVICE9 device, float _raidus);
	void render(LPDIRECT3DDEVICE9 device,D3DXMATRIX owner);
	bool collide(D3DXVECTOR3 targetCenter,float targetRadius, D3DXMATRIX ownerMatrix, D3DXMATRIX targetMatrix);

	//getter
	float getRadius();
	D3DXVECTOR3 getCenter();
	LPD3DXMESH	getMesh();
};