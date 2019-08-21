//-----------------------------------------------------------------------------
// マップ処理 [Map.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/27
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "Ray.h"
#include "BoundingSphere.h"
#include "Planet.h"
#include "Wasuremono.h"
#include <vector>

namespace MapNS
{
	const int SLICES = 8;			// 主軸に平行な方向の分割数
	const int STACKS = 8;			// 主軸に垂直な方向の分割数
}


//*****************************************************************************
// マップノード
//*****************************************************************************
class MapNode
{
private:
	// Data
	int number;						// ノード番号
	static int instanceCount;		// ノード数カウンタ
	D3DXVECTOR3	position;			// ワールド座標
	D3DXMATRIX worldMatrix;			// ワールドマトリクス
	int wasuremonoCount;			// バウンディングスフィア内のワスレモノの数

public:
	BoundingSphere boundingSphere;	// バウンディングスフィア
#ifdef _DEBUG
	bool isRed;						// ノードのデバッグ表示が赤色
#endif

	// Method
	MapNode(void) { instanceCount++; }
	int getInstanceCount(void) { return instanceCount; }	// Getter
	D3DXVECTOR3* getPosition(void) { return &position; }
	D3DXMATRIX* getWorldMatrix(void) { return &worldMatrix; }
	void setNumber(int _number) { number = _number; }		// Setter
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setWasuremonoCount(int _set) { wasuremonoCount = wasuremonoCount; }
};


//*****************************************************************************
// マップ
//*****************************************************************************
class Map
{
private:
	static Planet* field;
	LPD3DXMESH sphere;						// バウンディングスフィア用球形メッシュ
	LPD3DXMESH mapCoodMark;					// マップノード座標マーク用メッシュ
	D3DMATERIAL9 mapCoodMat;				// マップノード座標マーク用のマテリアルその１
	D3DMATERIAL9 targetCoodMat;				// マップノード座標マーク用のマテリアルその２
	static std::vector<MapNode*> mapNode;	// マップノード
	Ray ruler;								// ノード配置につかうレイ

public:
	void initialize(LPDIRECT3DDEVICE9 device, Planet* planet);
	void uninitialize(void);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void createNode(LPDIRECT3DDEVICE9 device);	// ノード生成
	static std::vector<MapNode*>& getMapNode(void) { return mapNode; }
	static Planet* getField(void) { return field; }
};
