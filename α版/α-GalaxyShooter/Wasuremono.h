//-----------------------------------------------------------------------------
// チンギンデータ処理[Wasuremono.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/8
//-----------------------------------------------------------------------------
#pragma once
#include "Object.h"
#include "ChinginTable.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
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


