//-----------------------------------------------------------------------------
// チンギンデータ処理[Wasuremono.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"

//*****************************************************************************
// グローバル変数　(※静的メンバ変数)
//*****************************************************************************
LPDIRECT3DDEVICE9 Wasuremono::device;	// デバイス
WasuremonoTable* Wasuremono::table;		// ワスレモノテーブルを指すポインタ


//=============================================================================
// コンストラクタ
//=============================================================================
Wasuremono::Wasuremono(void)
{

}

Wasuremono::Wasuremono(int typeID, D3DXVECTOR3 *position)
{
	initialize(typeID, position);
}


//=============================================================================
// 初期化処理
//=============================================================================
void Wasuremono::initialize(int typeID, D3DXVECTOR3 *position)
{
	this->typeID = typeID;
	Object::initialize(device, table->getStaticMesh(typeID), position);
	bodyCollide.initialize(device, position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
}


//=============================================================================
// 更新処理
//=============================================================================
void Wasuremono::update()
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


//*****************************************************************************
// 各ワスレモノの更新処理
//*****************************************************************************
//=============================================================================
// チューイングガム
//=============================================================================
void ChewingGum::update(void)
{
	Wasuremono::update();
}

//=============================================================================
// 扇風機
//=============================================================================
void ElectricFan::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// 縄跳び
//=============================================================================
void JumpRope::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// テレビ
//=============================================================================
void Television::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// けんだま
//=============================================================================
void Kendama::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// サッカーボール
//=============================================================================
void SoccerBall::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// クリスマスツリー
//=============================================================================
void ChristmasTree::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// 自転車
//=============================================================================
void Bicycle::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// 黒電話
//=============================================================================
void DialPhone::update(void)
{
	Wasuremono::update();
}


//=============================================================================
// ウサギのぬいぐるみ
//=============================================================================
void StuffedBunny::update(void)
{
	Wasuremono::update();
}
