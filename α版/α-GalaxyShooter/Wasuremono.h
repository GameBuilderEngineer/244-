//-----------------------------------------------------------------------------
// �`���M���f�[�^����[Wasuremono.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/8
//-----------------------------------------------------------------------------
#pragma once
#include "Object.h"
#include "ChinginTable.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Wasuremono :public Object
{
private:
	int id;
	ChinginTable* p;

public:
	Wasuremono(void);
	~Wasuremono(void);
	void initialize(LPDIRECT3DDEVICE9 device, LPSTR xFileName, D3DXVECTOR3* _position);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void move(D3DXVECTOR2 moveDirection, D3DXVECTOR3 cameraAxisX, D3DXVECTOR3 cameraAxisZ);
	void jump(void);
};


