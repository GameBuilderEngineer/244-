//===================================================================================================================================
//�yColony .h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/09/12
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

