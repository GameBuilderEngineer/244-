//-----------------------------------------------------------------------------
// �e���X�����m�ʂ̏���[Wasuremono.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/14
//-----------------------------------------------------------------------------
#pragma once
#include "Wasuremono.h"

//*****************************************************************************
// �`���[�C���O�K��
//*****************************************************************************
class ChewingGum : public Wasuremono
{
public:
	ChewingGum(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// ��@
//*****************************************************************************
class ElectricFan : public Wasuremono
{
public:
	ElectricFan(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// �꒵��
//*****************************************************************************
class JumpRope : public Wasuremono
{
public:
	JumpRope(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// �e���r
//*****************************************************************************
class Television : public Wasuremono
{
public:
	Television(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// ���񂾂�
//*****************************************************************************
class Kendama : public Wasuremono
{
public:
	Kendama(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// �T�b�J�[�{�[��
//*****************************************************************************
class SoccerBall : public Wasuremono
{
public:
	SoccerBall(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// �N���X�}�X�c���[
//*****************************************************************************
class ChristmasTree : public Wasuremono
{
public:
	ChristmasTree(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// ���]��
//*****************************************************************************
class Bicycle : public Wasuremono
{
public:
	Bicycle(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// ���d�b
//*****************************************************************************
class DialPhone : public Wasuremono
{
public:
	DialPhone(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};

//*****************************************************************************
// �E�T�M�̂ʂ������
//*****************************************************************************
class StuffedBunny : public Wasuremono
{
public:
	StuffedBunny(LPDIRECT3DDEVICE9 device, int id, D3DXVECTOR3 *position) : Wasuremono(device, id, position) {}
	void update(float frameTime, LPD3DXMESH fieldMesh, D3DXMATRIX matrix, D3DXVECTOR3 fieldPosition);
};


