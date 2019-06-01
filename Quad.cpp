//=============================================================================
// 2D矩形処理 [quad.cpp]
//
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成日 : 2019/6/1
//=============================================================================
//*****************************************************************************
// インクルード
//*****************************************************************************
#include "Main.h"
#include "Quad.h"


//=============================================================================
// 2D矩形のサイズ設定
//=============================================================================
void Quad::setSize(int sizeX, int sizeY)
{
	centralAngle = atan2f((float)sizeY / 2, (float)sizeX / 2);				// 中心座標から頂点への角度を初期化
	D3DXVECTOR2 vec = D3DXVECTOR2((float)sizeX / 2, (float)sizeY / 2);		// 中心座標から頂点へのベクトルを求める
	originalRadius = radius = D3DXVec2Length(&vec);							// 半径の初期化
}


//=============================================================================
// 2D矩形の頂点座標の設定
//=============================================================================
void Quad::setVertex(void)
{
	// アフィン変換
	vertexWk[0].vtx.x = position.x - cosf(centralAngle + rotation.z) * radius;
	vertexWk[0].vtx.y = position.y - sinf(centralAngle + rotation.z) * radius;
	vertexWk[1].vtx.x = position.x + cosf(centralAngle - rotation.z) * radius;
	vertexWk[1].vtx.y = position.y - sinf(centralAngle - rotation.z) * radius;
	vertexWk[2].vtx.x = position.x - cosf(centralAngle - rotation.z) * radius;
	vertexWk[2].vtx.y = position.y + sinf(centralAngle - rotation.z) * radius;
	vertexWk[3].vtx.x = position.x + cosf(centralAngle + rotation.z) * radius;
	vertexWk[3].vtx.y = position.y + sinf(centralAngle + rotation.z) * radius;
}


//=============================================================================
// 2D矩形の頂点カラーの設定
//=============================================================================
void Quad::setColor(D3DCOLOR setColor)
{
	// 一括設定
	vertexWk[0].diffuse = setColor;
	vertexWk[1].diffuse = setColor;
	vertexWk[2].diffuse = setColor;
	vertexWk[3].diffuse = setColor;
}


//=============================================================================
// テクスチャUV座標の設定
//=============================================================================
void Quad::setTexture(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3)
{
	vertexWk[0].tex = v0;
	vertexWk[1].tex = v1;
	vertexWk[2].tex = v2;
	vertexWk[3].tex = v3;
}


//=============================================================================
// 2D矩形の初期化
//=============================================================================
void Quad::initQuad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color)
{
	setSize(sizeX, sizeY);		// サイズ
	this->position = position;	// 座標
	this->rotation = rotation;	// 座標
	setVertex();				// 頂点座標の設定
	setColor(color);			// 頂点カラーの設定

	// テクスチャ座標の設定
	setTexture(D3DXVECTOR2(0.0, 0.0), D3DXVECTOR2(1.0, 0.0), D3DXVECTOR2(0.0, 1.0), D3DXVECTOR2(1.0, 1.0));

	// rhwの設定
	vertexWk[0].rhw = vertexWk[1].rhw = vertexWk[2].rhw = vertexWk[3].rhw = 1.0f;
}


//=============================================================================
// コンストラクタ
//=============================================================================
Quad::Quad(void)
{
}

Quad::Quad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color)
{
	// 宣言と同時に初期化できる
	initQuad(sizeX, sizeY, position, rotation, color);
}


//=============================================================================
// デストラクタ
//=============================================================================
Quad::~Quad(void)
{
}
