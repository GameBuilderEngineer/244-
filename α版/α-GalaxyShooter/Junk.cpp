//===================================================================================================================================
//【Junk.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/07
//===================================================================================================================================
#include "Junk.h"

using namespace junkNS;

Junk::Junk()
{
	onGravity = true;
	activation();
	changeAxisRotation();
}


Junk::~Junk()
{
}

void Junk::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
	bodyCollide.initialize(device, &position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
}

void Junk::update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX fieldMatrix,D3DXVECTOR3 fieldPosition)
{
	setSpeed(D3DXVECTOR3(0, 0, 0));

	float difference = 1.0f;


	D3DXVECTOR3 gravityDirection;
	D3DXVec3Normalize(&gravityDirection, &(fieldPosition - position));
	betweenField.update(position, gravityDirection);
	


	//フィールド補正
	if (betweenField.rayIntersect(fieldMesh, fieldMatrix) &&
		radius >= (betweenField.distance - difference))
	{
		//めり込み補正
		setPosition(position + betweenField.normal*(radius - betweenField.distance));
		//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
		//setSpeed(reverseAxisY.slip(speed, reverseAxisY.normal));
		//Ray moveRay;//移動ベクトルを使ってレイを作成
		//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
		//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
		//{//二重チェック
		//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
		//}
		bound();
	}
	else {
		setGravity(gravityDirection, 80.0f);
	}

	roopRotation();

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}

	//位置更新
	position += speed * frameTime;

	//加速度減衰
	acceleration *= 0.9f;
	Object::update();

}

void Junk::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

void Junk::bound()
{
	changeAxisRotation();
	float rate = (float)(rand() % 10);
	rate *= 0.1;
	acceleration += betweenField.normal*(BOUND_FORCE*rate);
}

void Junk::roopRotation()
{
	anyAxisRotation(axisRotation, ROTATION_SPEED);
}

void Junk::changeAxisRotation()
{
	axisRotation = D3DXVECTOR3((float)(rand() % 10), (float)(rand() % 10), (float)(rand() % 10));
	D3DXVec3Normalize(&axisRotation, &axisRotation);
}

void Junk::headPosition(D3DXVECTOR3 headPosition)
{
	D3DXVECTOR3 headDirection;
	float headDistance = between2VectorDirection(&headDirection,position,headPosition);
	//加速度の増加量を近づくほど小さくする。
	acceleration += headDirection*(HEAD_FORCE/headDistance);
}