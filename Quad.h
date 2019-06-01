//=============================================================================
// 2D矩形処理 [quad.h]
//
// Author : HAL東京昼間部 2年制ゲーム学科 GP12A332 32 中込和輝
// 作成日 : 2019/6/1
//=============================================================================
//*****************************************************************************
// インクルード
//*****************************************************************************
#pragma once
#include "Main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	NUM_VERTEX		(4)			// 頂点数
#define	NUM_POLYGON		(2)			// ポリゴン数


//*****************************************************************************
// 構造体定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3			vtx;		// 頂点座標
	float				rhw;		// テクスチャのパースペクティブコレクト用
	D3DCOLOR			diffuse;	// 反射光
	D3DXVECTOR2			tex;		// テクスチャ座標
} VERTEX_2D;


//*****************************************************************************
// クラス定義
//*****************************************************************************
class Quad {
protected:
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	D3DXVECTOR3		position;					// 位置
	D3DXVECTOR3		rotation;					// 回転
	float			centralAngle;				// 中心座標から４頂点への角度
	float			radius;						// 半径
	float			originalRadius;				// 元の半径

public:
	void setSize(int sizeX, int sizeY);			// 2D矩形のサイズ設定
	void setVertex(void);						// 2D矩形の頂点座標の設定
	void setColor(D3DCOLOR setColor);			// 2D矩形頂点カラーの設定
												// テクスチャUV座標の設定
	void setTexture(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3);
												// 2D矩形の初期化
	void initQuad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color);

	// コンストラクタ・デストラクタ
	Quad(void);
	Quad(int sizeX, int sizeY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DCOLOR color);
	~Quad(void);

	// アクセサ
	D3DXVECTOR3 getPosition(void) { return position; }
	D3DXVECTOR3 getRotation(void) { return rotation; }
	D3DXVECTOR3 setPosition(void) { return position; }
	D3DXVECTOR3 setRotation(void) { return rotation; }
};
