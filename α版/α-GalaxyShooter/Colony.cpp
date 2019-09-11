//===================================================================================================================================
//yColony.cppz
// [ì¬ŽÒ]HAL“Œ‹žGP12A332 11 ›–ì Ž÷
// [ì¬“ú]2019/05/16
// [XV“ú]2019/08/07
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
