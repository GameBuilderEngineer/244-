//-----------------------------------------------------------------------------
// ワスレモノ処理[Wasuremono.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"
#include "Map.h"

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

	float difference = 1.0f;

	//// 重力方向のベクトル&レイを作成（グラヴィティレイにおきかえできる？）
	//D3DXVECTOR3 gravityDirection;
	//D3DXVec3Normalize(&gravityDirection, &(fieldPosition - position));
	//betweenField.update(position, gravityDirection);

	////フィールド補正
	//if (betweenField.rayIntersect(fieldMesh, matrix) &&
	//	radius >= (betweenField.distance - difference))
	//{
	//	//めり込み補正
	//	setPosition(position + betweenField.normal*(radius - betweenField.distance));
	//	//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
	//	//setSpeed(reverseAxisY.slip(speed, reverseAxisY.normal));
	//	//Ray moveRay;//移動ベクトルを使ってレイを作成
	//	//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
	//	//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
	//	//{//二重チェック
	//	//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
	//	//}
	//	//bound();

	//}
	//else {
	//	setGravity(gravityDirection, 80.0f);
	//}

	//===========
	//【接地処理】
	//===========
	D3DXVECTOR3 *attractorPosition = Map::getField()->getPosition();
	float attractorRadius = Map::getField()->getRadius();
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//重力方向を算出
	gravityRay.initialize(position, gravityDirection);								//重力レイの初期化
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//重力発生源との距離
	if (radius + attractorRadius >= distanceToAttractor - difference)
	{
		//相互半径合計値より引力発生源との距離が短いと接地
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
		onGravity = true;
	}
	setGravity(gravityDirection, 80.0f);//重力処理


	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}

	//位置更新
	position += speed * frameTime;

	//加速度減衰
	acceleration *= 0.9f;

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
