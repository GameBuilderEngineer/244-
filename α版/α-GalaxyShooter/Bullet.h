//===================================================================================================================================
//【Bullet.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/07/31
// [更新日]2019/08/04
//===================================================================================================================================
#pragma once
#include "Object.h"
#include "BoundingSphere.h"

namespace bulletNS
{
	const float EXISTENCE_TIME = 3.0f;		//存在時間
	const float GRAVITY_FORCE = 60.0f;		//重力
	const float SPEED = 70.0f;

}

class Bullet :	public Object
{
private:
	float existenceTimer;
	D3DXVECTOR3* attractorPosition;						//重力（引力）発生位置
	float attractorRadius;								//重力（引力）発生オブジェクト半径

public:
	BoundingSphere bodyCollide;

	//Method
	Bullet();
	~Bullet();
	
	//processing
	void initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position);
	void update(float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	
	//operation
	void configurationGravity(D3DXVECTOR3* attractorPosition, float _attractorRadius);
	
	//setter

	//getter
};

