#include "Player.h"

Player::Player()
{
	onGravity = true;
	radius = 5.0f;
}

Player::~Player()
{

}


void Player::update()
{
	if (D3DXVec3Length(&acceleration) > 0.01f)
	{
		speed += acceleration;
	}
	position += speed;

	acceleration *= 0.9f;
	

	postureControl(axisY.direction, reverseAxisY.normal,0.05f);

	//法線とキャラクターとの外積を求める（平面に直立するための回転軸となる）
	//D3DXVec3Cross(&rotationAxis, &axisY.direction, &reverseAxisY.normal);
	//D3DXVec3Normalize(&rotationAxis,&rotationAxis);
	//
	//if (!isinf(rotationAxis.x+rotationAxis.y+rotationAxis.z))
	//{
	//	//float dot = D3DXVec3Dot(&axisY.direction, &reverseAxisY.normal);
	//	//float upLength = D3DXVec3Length(&axisY.direction);
	//	//float normalLength = D3DXVec3Length(&reverseAxisY.normal);
	//	//radian = acosf( dot / ( upLength*normalLength ) );
	//
	//	//回転角を求める
	//	//acos(上方向ベクトル・(ドット積)法線ベクトル)
	//	if(formedRadianAngle(&radian, axisY.direction, reverseAxisY.normal))
	//	{
	//		//回転クォータニオンを作成
	//		deltaRotation= D3DXQUATERNION(0, 0, 0, 1);
	//		D3DXQuaternionRotationAxis(&deltaRotation, &rotationAxis, radian);
	//		deltaRotation = quaternion * deltaRotation;
	//
	//		D3DXQuaternionSlerp(&quaternion, &quaternion, &deltaRotation, 0.05f);
	//	}
	//}

	Object::update();
}

void Player::jump()
{
	acceleration += axisY.direction;
}

void Player::move(D3DXVECTOR2 moveDirection)
{

}