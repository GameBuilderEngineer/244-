//===================================================================================================================================
//�yPointSprite.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/07
//===================================================================================================================================
#pragma once
#include "Base.h"

namespace pointSpriteNS
{
	const float WIDTH = 256.0f;
	const float HEIGHT = 256.0f;
	const int POINT_NUM = 256;
}
inline DWORD GET_ADDRESS(float f) { return *((DWORD*)&f); }
//��`
struct COLOR_VERTEX
{
	D3DXVECTOR3 coord;
	FLOAT scale;
	DWORD color;
};

class PointSprite :public Base
{
	COLOR_VERTEX vertex[pointSpriteNS::POINT_NUM];
	LPDIRECT3DTEXTURE9 pTexture;
	float size[pointSpriteNS::POINT_NUM];

public:
	PointSprite();
	~PointSprite();
	HRESULT initilaize(LPDIRECT3DDEVICE9 device);
	void render(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 cameraPositon);
};

