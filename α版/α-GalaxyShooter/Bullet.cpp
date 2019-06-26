#include "Bullet.h"
using namespace bulletNS;

Bullet::Bullet()
{
	onGravity = true;
	inActivation();
	existenceTimer = 0.0f;
}


Bullet::~Bullet()
{
}

void Bullet::initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position)
{
	Object::initialize(device, xFileName, _position);
	bodyCollide.initialize(device, &position, mesh);
	radius = bodyCollide.getRadius();
}

void Bullet::update(float frameTime, LPD3DXMESH fieldMesh,D3DXMATRIX matrix)
{
	if (onActive == false)return;

	existenceTimer += frameTime;
	if (existenceTimer >= EXISTENCE_TIME)
	{
		existenceTimer = 0.0f;
		inActivation();
		return;
	}
	float difference = 1.0f;

	setSpeed(D3DXVECTOR3(0, 0, 0));
	addSpeed(getAxisZ()->direction*50.0);//自動移動

	//anyAxisRotation(axisY.direction, (rand() % 10) - 5);

	//フィールド補正
	if (reverseAxisY.rayIntersect(fieldMesh, matrix) &&
		radius+2.0f >= (reverseAxisY.distance - difference))
	{
		//めり込み補正
		setPosition(position + axisY.direction*(radius + 2.0f - reverseAxisY.distance));
		//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
		setSpeed(reverseAxisY.slip(speed, reverseAxisY.normal));
		//Ray moveRay;//移動ベクトルを使ってレイを作成
		//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
		//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
		//{//二重チェック
		//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
		//}
		
	}
	else {
		setGravity(-axisY.direction, 80.0f);
	}

	D3DXVECTOR3 moveDirection;

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}

	//位置更新
	position += speed * frameTime;

	//加速度減衰
	acceleration *= 0.9f;

	//姿勢制御
	postureControl(axisY.direction, reverseAxisY.normal, 3.0f * frameTime);


	Object::update();
}

void Bullet::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
	bodyCollide.render(device, matrixWorld);
}
