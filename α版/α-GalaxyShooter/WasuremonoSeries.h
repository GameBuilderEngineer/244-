//-----------------------------------------------------------------------------
// 各ワスレモノ個別の処理[Wasuremono.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/14
//-----------------------------------------------------------------------------
#pragma once
#include "Wasuremono.h"

//*****************************************************************************
// チューイングガム
//*****************************************************************************
class ChewingGum : public Wasuremono
{
public:
	ChewingGum(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// 扇風機
//*****************************************************************************
class ElectricFan : public Wasuremono
{
public:
	ElectricFan(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// 縄跳び
//*****************************************************************************
class JumpRope : public Wasuremono
{
public:
	JumpRope(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// テレビ
//*****************************************************************************
class Television : public Wasuremono
{
public:
	Television(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// けんだま
//*****************************************************************************
class Kendama : public Wasuremono
{
public:
	Kendama(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// サッカーボール
//*****************************************************************************
class SoccerBall : public Wasuremono
{
public:
	SoccerBall(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// クリスマスツリー
//*****************************************************************************
class ChristmasTree : public Wasuremono
{
public:
	ChristmasTree(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// 自転車
//*****************************************************************************
class Bicycle : public Wasuremono
{
public:
	Bicycle(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// 黒電話
//*****************************************************************************
class DialPhone : public Wasuremono
{
public:
	DialPhone(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// ウサギのぬいぐるみ
//*****************************************************************************
class StuffedBunny : public Wasuremono
{
public:
	StuffedBunny(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};


