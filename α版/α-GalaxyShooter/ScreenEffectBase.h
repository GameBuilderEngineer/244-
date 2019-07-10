//=============================================================================
// エフェクト処理 [ScreenEffectBase.h]
//
//=============================================================================

#pragma once
#include "Base.h"
#include <d3dx9.h>
#include "StaticMeshLoader.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace ScreenEffectNS
{
	const  int	NUM_VERTEX = 4;			// 頂点数
	const  int	NUM_POLYGON = 2;		// ポリゴン数

	// エフェクト原点（回転軸）
	enum F_PIVOT {
		F_CENTER,
		F_TOP_LEFT,
		F_PIVOT_MAX
	};
}

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_2D_F
{
	D3DXVECTOR3			vtx;		// 頂点座標
	float				rhw;		// テクスチャのパースペクティブコレクト用
	D3DCOLOR			diffuse;	// 反射光
	D3DXVECTOR2			uv;			// テクスチャ座標
};

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_3D_F
{
	D3DXVECTOR3			vtx;		// 頂点座標
	D3DXVECTOR3			nor;		// 法線ベクトル
	D3DCOLOR			diffuse;	// 反射光
	D3DXVECTOR2			tex;		// テクスチャ座標
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ScreenEffectBase
{
protected:
	VERTEX_2D_F			vertexWk[ScreenEffectNS::NUM_VERTEX];	// 頂点情報格納ワーク
	VERTEX_3D_F			vertexWk3D[ScreenEffectNS::NUM_VERTEX];	// 頂点情報格納ワーク
	LPDIRECT3DTEXTURE9	texture;						// テクスチャへのポインタ
	int					pivot;							// 原点（回転軸）
	int					width;							// 横幅
	int					height;							// 高さ
	D3DXVECTOR3			position;						// 位置
	D3DXVECTOR3			rotation;						// 回転
	float				centralAngle;					// 中心座標から４頂点への角度
	float				radius;							// 半径
	float				originalRadius;					// 元の半径
	float				alpha;							// アルファ値
	int					settingFrame;					// エフェクト生存時間
	int					cntFrame;						// エフェクト生存時間加算

	//スタティックメッシュ
	StaticMesh* staticMesh;
	//行列（位置・回転・ワールド）：スケール追加予定
	D3DXMATRIX matrixPosition;
	D3DXMATRIX matrixRotation;
	D3DXMATRIX matrixWorld;

public:
	ScreenEffectBase();
	~ScreenEffectBase();

	virtual void initialize(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 _texture, int _pivot, int _width, int _height, D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DCOLOR color);
	virtual void uninitialize(void);
	virtual void render2D(LPDIRECT3DDEVICE9 device);
	virtual void render3D(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	virtual void activate(int second);
	virtual void inactivate(void);
	HRESULT setTexture(LPDIRECT3DDEVICE9 device, LPSTR fileName);		// テクスチャの設定
	void setTexture(LPDIRECT3DTEXTURE9 _texture);						// テクスチャの設定　ポインタ代入Ver
	void setUVCoordinates(D3DXVECTOR2 v0, D3DXVECTOR2 v1, D3DXVECTOR2 v2, D3DXVECTOR2 v3);// テクスチャUV座標の設定
	void setSize(int sizeX, int sizeY);									// サイズ設定
	void setVertex(void);												// 頂点座標の設定
	void setColor(D3DCOLOR v0, D3DCOLOR v1, D3DCOLOR v2, D3DCOLOR v3);	// カラーの設定
	void setColor(D3DCOLOR color);										// カラーの設定　４頂点一括設定Ver
	void setAlpha(D3DCOLOR color);
	void setPosition2(D3DXVECTOR3 _position);

	D3DXVECTOR3 getPosition(void) { return position; }
	D3DXVECTOR3 getRotation(void) { return rotation; }
	D3DXVECTOR3 setPosition(void) { return position; }
	D3DXVECTOR3 setRotation(void) { return rotation; }
	void setPivot(int _pivot) { pivot = _pivot; }
	bool isActive;

};
