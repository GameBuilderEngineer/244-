//===================================================================================================================================
//【Colony .h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/09/12
//===================================================================================================================================
#pragma once
#include "Object.h"
class Colony :public Object
{
public:
	Colony();
	~Colony();
	void update();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

};

