//===================================================================================================================================
//【Bullet.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/07/31
// [更新日]2019/08/04
//===================================================================================================================================
#include "Bullet.h"
using namespace bulletNS;

Bullet::Bullet()
{
	onLighting = false;
	onGravity = true;
	inActivation();
	existenceTimer = 0.0f;
}


Bullet::~Bullet()
{
}

void Bullet::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
	bodyCollide.initialize(device, &position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
}

void Bullet::update(float frameTime)
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
	addSpeed(getAxisZ()->direction*SPEED);//自動移動

	//===========
	//【接地処理】
	//===========
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//重力レイの初期化
	if (radius + attractorRadius >= (between2VectorLength(position, *attractorPosition) - difference))
	{
		//めり込み補正
		//現在位置+ 垂直方向*(めり込み距離)
		setPosition(position + -gravityDirection * (radius + attractorRadius - between2VectorLength(position, *attractorPosition)));
		//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
		setSpeed(reverseAxisY.slip(speed, -gravityDirection));
	}
	else {
		setGravity(gravityDirection, GRAVITY_FORCE);
	}

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}

	//位置更新
	position += speed * frameTime;

	//加速度減衰
	acceleration *= 0.9f;

	//姿勢制御
	postureControl(axisY.direction, -gravityRay.direction, 3.0f * frameTime);

	Object::update();
}

void Bullet::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//【重力設定】
//[内容]重力源の位置情報で重力を設定する
//[引数]
//D3DXVECTOR3* attractorPosition：引力発生地点
//===================================================================================================================================
void Bullet::configurationGravity(D3DXVECTOR3* _attractorPosition, float _attractorRadius)
{
	//重力処理を行うために必要な要素をセット
	attractorPosition = _attractorPosition;
	attractorRadius = _attractorRadius;
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//重力レイの初期化
	setGravity(gravityDirection, GRAVITY_FORCE);
	//postureControl(axisY.direction, gravityDirection, 1.0f);
}
