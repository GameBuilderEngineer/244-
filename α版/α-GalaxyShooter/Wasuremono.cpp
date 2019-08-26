//-----------------------------------------------------------------------------
// ワスレモノ処理[Wasuremono.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"
#include "Map.h"
using namespace wasuremonoNS;
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
WasuremonoTable* Wasuremono::table;		// ワスレモノテーブルを指すポインタ


//=============================================================================
// コンストラクタ
//=============================================================================
Wasuremono::Wasuremono(void)
{

}

Wasuremono::Wasuremono(LPDIRECT3DDEVICE9 device, int typeID, D3DXVECTOR3 *position)
{
	this->typeID = typeID;
	Object::initialize(device, table->getStaticMesh(typeID), position);
	bodyCollide.initialize(device, position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
	onGravity = true;
	activation();
	difference = DIFFERENCE_FIELD;
	configurationGravity(Map::getField()->getPosition(), Map::getField()->getRadius());
}


//=============================================================================
// 初期化処理
//=============================================================================
void Wasuremono::initialize(LPDIRECT3DDEVICE9 device, int typeID, D3DXVECTOR3 *position)
{
	Wasuremono(device, typeID, position);
}


//=============================================================================
// 更新処理
//=============================================================================
void Wasuremono::update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition)
{
	if (!onActive) { return; }

	setSpeed(D3DXVECTOR3(0, 0, 0));

	//===========
	//【接地処理】
	//===========
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//重力方向を算出
	gravityRay.initialize(position, gravityDirection);								//重力レイの初期化
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//重力発生源との距離
	if (radius + attractorRadius >= distanceToAttractor - difference)
	{
		//相互半径合計値より引力発生源との距離が短いと接地
		onGround = true;
		onGravity = false;
		//めり込み補正
		//現在位置+ 垂直方向*(めり込み距離)
		setPosition(position + axisY.direction * (radius + attractorRadius - distanceToAttractor));
		//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
		setSpeed(reverseAxisY.slip(speed, axisY.direction));
		acceleration *= 0;
	}
	else {
		//空中
		onGround = false;
		onGravity = true;
	}
	setGravity(gravityDirection, GRAVITY_FORCE*frameTime);//重力処理


	if (D3DXVec3Length(&acceleration) > 0.05f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}

	//位置更新
	position += speed * frameTime;

	//加速度減衰
	//acceleration *= 0.9f;

	// 姿勢制御……重力方向レイを当てたフィールドの法線と自分Y軸を使用
	postureControl(axisY.direction, betweenField.normal, 3.0f * frameTime);

	Object::update();
}


//=============================================================================
// 描画処理
//=============================================================================
void Wasuremono::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif
}

//===================================================================================================================================
//【重力設定】
//[内容]重力源の位置情報で重力を設定する
//[引数]
//D3DXVECTOR3* attractorPosition：引力発生地点
//===================================================================================================================================
void Wasuremono::configurationGravity(D3DXVECTOR3* _attractorPosition, float _attractorRadius)
{
	//重力処理を行うために必要な要素をセット
	attractorPosition = _attractorPosition;
	attractorRadius = _attractorRadius;
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//重力レイの初期化
	setGravity(gravityDirection, GRAVITY_FORCE);
	postureControl(axisY.direction, gravityDirection, 1.0f);
}
