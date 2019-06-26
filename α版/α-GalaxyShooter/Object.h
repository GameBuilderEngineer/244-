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

	//描画系変数
	LPD3DXMESH mesh;
	D3DMATERIAL9* meshMaterials;
	LPDIRECT3DTEXTURE9* meshTextures;
	LPDIRECT3DTEXTURE9 textureShade;
	LPDIRECT3DTEXTURE9 textureLine;
	DWORD numMaterials;
	LPD3DXEFFECT effect;

	//ステータス変数
	D3DXVECTOR3 position;		//位置
	D3DXQUATERNION quaternion;	//回転
	D3DXVECTOR3 scale;			//スケール
	float radius;				//衝突半径

	//移動系変数
	D3DXVECTOR3 speed;			//速度
	D3DXVECTOR3 acceleration;	//加速度
	D3DXVECTOR3 gravity;		//重力

	//各種フラグ
	bool onGravity;				//重力有効化フラグ
	bool onActive;				//アクティブ化フラグ
	bool onRender;				//描画有効化フラグ

	//方向6軸
	Ray axisX;
	Ray axisY;
	Ray axisZ;
	Ray reverseAxisX;
	Ray reverseAxisY;
	Ray reverseAxisZ;
	//重力Ray
	Ray gravityRay;

	//行列（位置・回転・ワールド）：スケール追加予定
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
	//取得関数
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
	Ray* getGravityRay() { return &gravityRay; };
	bool getActive() { return onActive; }

	//セット関数
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void addSpeed(D3DXVECTOR3 add) { speed += add; }
	void setGravity(D3DXVECTOR3 source, float power);
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setQuaternion(D3DXQUATERNION _quaternion) { quaternion = _quaternion; }
	void activation();			//活性化
	void inActivation();		//不活化

	//姿勢制御
	void postureControl(D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection,float t)
	{
		Base::postureControl(&quaternion,currentDirection, nextDirection, t);
	}

	//任意軸線型補間回転
	void anyAxisRotationSlerp(D3DXVECTOR3 axis, float radian,float t)
	{
		Base::anyAxisRotationSlerp(&quaternion, axis, radian, t);
	}
	
	//任意軸回転
	void anyAxisRotation(D3DXVECTOR3 axis, float degree)
	{
		Base::anyAxisRotation(&quaternion, axis, degree);
	}


};

