//-----------------------------------------------------------------------------
// チンギンデータ処理[Wasuremono.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#include "Wasuremono.h"

//=============================================================================
// コンストラクタ
//=============================================================================
Wasuremono::Wasuremono(void)
{

}


//=============================================================================
// デストラクタ
//=============================================================================
Wasuremono::~Wasuremono(void)
{

}


//=============================================================================
// 初期化処理
//=============================================================================
void Wasuremono::initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position)
{
	Object::initialize(device, xFileName, _position);
	bodyCollide.initialize(device, &position, mesh);
}


//=============================================================================
// 更新処理
//=============================================================================
void Wasuremono::update()
{
	if (D3DXVec3Length(&acceleration) > 0.01f)
	{
		speed += acceleration;
	}
	position += speed;

	acceleration *= 0.9f;


	postureControl(axisY.direction, reverseAxisY.normal, 0.05f);

	Object::update();
}


//=============================================================================
// 描画処理
//=============================================================================
void Wasuremono::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device, view, projection, cameraPositon);
	bodyCollide.render(device, matrixWorld);

}


//=============================================================================
// 移動
//=============================================================================
void Wasuremono::jump()
{
	acceleration += axisY.direction;
}


void Wasuremono::move(D3DXVECTOR2 operationDirection, D3DXVECTOR3 cameraAxisX, D3DXVECTOR3 cameraAxisZ)
{
	if (operationDirection.x == 0 && operationDirection.y == 0)return;//入力値が0以下ならば移動しない
	//Y軸方向への成分を削除する
	D3DXVECTOR3 front = slip(cameraAxisZ, axisY.direction);
	D3DXVECTOR3 right = slip(cameraAxisX, axisY.direction);
	D3DXVec3Normalize(&front, &front);//正規化
	D3DXVec3Normalize(&right, &right);//正規化

	//操作方向をカメラのXZ方向に準拠した移動ベクトルへ変換する
	D3DXVECTOR3 moveDirection = operationDirection.x*right + -operationDirection.y*front;
	addSpeed(moveDirection*0.0007);
	postureControl(getAxisZ()->direction, moveDirection, 0.1f);
}


