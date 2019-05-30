#pragma once
#include <stdio.h>
#include <windows.h>
#include <d3dx9.h>

namespace objectNS {
	enum {
		PLAYER1,
		PLAYER2,
		PLANET,
		OBJECT_NUM,
	};
}


class Object
{
protected:
	LPD3DXMESH mesh;
	D3DMATERIAL9* meshMaterials;
	LPDIRECT3DTEXTURE9* meshTextures;
	DWORD numMaterials;

	D3DXVECTOR3 position;
	D3DXQUATERNION quaternion;

	D3DXVECTOR3 axisZ;
	D3DXVECTOR3 axisY;
	D3DXVECTOR3 axisX;

	D3DXVECTOR3 direction;//方向ベクトル
	D3DXMATRIX matrixPosition;
	D3DXMATRIX matrixRotation;
	D3DXMATRIX matrixWorld;

	D3DXVECTOR3 gravity;//重力ベクトル
	D3DXVECTOR3 normal;//レイが衝突したポリゴンの法線
	float distance;//レイが衝突したポリゴンとの距離

public:
	Object();
	~Object();
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position);
	VOID render(LPDIRECT3DDEVICE9 device);

	LPD3DXMESH getMesh() { return mesh; }
	D3DXMATRIX getMatrixWorld() { return matrixWorld; }
	D3DXVECTOR3 getPosition() { return position; };
	D3DXVECTOR3 getGravity() { return gravity; };
	D3DXVECTOR3 getDirection() { return direction; };
	D3DXVECTOR3 getNormal() { return normal; }
	float getDistance() { return distance; }
	D3DXVECTOR3 getAxisX() { return axisX; };
	D3DXVECTOR3 getAxisY() { return axisY; };
	D3DXVECTOR3 getAxisZ() { return axisZ; };
	D3DXQUATERNION getQuaternion() { return quaternion; };
	

	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setDirection(D3DXVECTOR3 _direction) { direction = _direction; }
	void setGravity(D3DXVECTOR3 _gravity) { gravity = _gravity; }
	void setQuaternion(D3DXQUATERNION _quaternion) { quaternion = _quaternion; }
	void setDistance(float _distance) { distance = _distance; }
	void setNormal(D3DXVECTOR3 _normal) { normal = _normal; }
};

