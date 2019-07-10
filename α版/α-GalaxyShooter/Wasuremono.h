//-----------------------------------------------------------------------------
// ƒƒXƒŒƒ‚ƒmˆ—[Wasuremono.h]
// AuthorFGP12A332 32 ’†ž˜a‹P
// ì¬“úF2019/7/8
//-----------------------------------------------------------------------------
#pragma once
#include "Object.h"
#include "BoundingSphere.h"
#include "WasuremonoTable.h"

//*****************************************************************************
// ƒNƒ‰ƒX’è‹`
//*****************************************************************************
class Wasuremono :public Object
{
private:
	int id;
	int typeID;
	static LPDIRECT3DDEVICE9 device;
	static WasuremonoTable* table;

public:
	Wasuremono(void);
	Wasuremono(int id, D3DXVECTOR3 *position);
	void initialize(int id, D3DXVECTOR3 *position);
	virtual void update(void);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

	int getAmount(void) { return table->getAmount(typeID); }
	void addAmount(int &dest) { table->addAmount(dest, typeID); }
	void subAmount(int &dest) { table->subAmount(dest, id); }
	static void setDevice(LPDIRECT3DDEVICE9 _device) { device = _device; }
	static void setTable(WasuremonoTable* _table) { table = _table; }

	BoundingSphere bodyCollide;
	Ray betweenField;
};


class ChewingGum : public Wasuremono
{
public:
	ChewingGum(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class ElectricFan : public Wasuremono
{
public:
	ElectricFan(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class JumpRope : public Wasuremono
{
public:
	JumpRope(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class Television : public Wasuremono
{
public:
	Television(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class Kendama : public Wasuremono
{
public:
	Kendama(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class SoccerBall : public Wasuremono
{
public:
	SoccerBall(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class ChristmasTree : public Wasuremono
{
public:
	ChristmasTree(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class Bicycle : public Wasuremono
{
public:
	Bicycle(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class DialPhone : public Wasuremono
{
public:
	DialPhone(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};

class StuffedBunny : public Wasuremono
{
public:
	StuffedBunny(int id, D3DXVECTOR3 *position) : Wasuremono(id, position) {}
	void update(void);
};


