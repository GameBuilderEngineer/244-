//===================================================================================================================================
//【Colony.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/07
//===================================================================================================================================
#include "Colony.h"



Colony::Colony()
{
	activation();
}


Colony::~Colony()
{
}

void Colony::update()
{
}

void Colony::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	device->SetRenderState(D3DRS_LIGHTING, false);
	Object::render(device,view,projection,cameraPositon);
	device->SetRenderState(D3DRS_LIGHTING, true);
}
