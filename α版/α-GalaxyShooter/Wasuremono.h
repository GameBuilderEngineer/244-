//-----------------------------------------------------------------------------
// ワスレモノ処理[Wasuremono.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/8
//-----------------------------------------------------------------------------
#pragma once
#include "Object.h"
#include "BoundingSphere.h"
#include "WasuremonoTable.h"

namespace wasuremonoNS
{
	const float GRAVITY_FORCE = 9.8f*7.0;			//重力
	const float DIFFERENCE_FIELD = 0.2f;		//フィールド補正差分

}

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Wasuremono :public Object
{
private:
	int typeID;
	static WasuremonoTable* table;
	D3DXVECTOR3 *attractorPosition;
	float attractorRadius;
	float difference;
	bool onGround;

public:
	Wasuremono(void);
	Wasuremono(LPDIRECT3DDEVICE9 device, int typeID, D3DXVECTOR3 *position);
	void initialize(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position);
	virtual void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	
	int getType(void) { return typeID; }
	int getAmount(void) { return table->getAmount(typeID); }
	void addAmount(int &dest) { table->addAmount(dest, typeID); }
	void subAmount(int &dest) { table->subAmount(dest, typeID); }
	static void setTable(WasuremonoTable* _table) { table = _table; }

	BoundingSphere bodyCollide;
	Ray betweenField;
	
	void configurationGravity(D3DXVECTOR3* _attractorPosition, float _attractorRadius);

};

