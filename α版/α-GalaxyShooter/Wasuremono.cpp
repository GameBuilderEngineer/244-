//-----------------------------------------------------------------------------
// ワスレモノ処理[Wasuremono.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"

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


	D3DXVECTOR3 gravityDirection;
	D3DXVec3Normalize(&gravityDirection, &(fieldPosition - position));
	betweenField.update(position, gravityDirection);



	//フィールド補正
	if (betweenField.rayIntersect(fieldMesh, matrix) &&
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
		//bound();
	}
	else {
		setGravity(gravityDirection, 80.0f);
	}


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
