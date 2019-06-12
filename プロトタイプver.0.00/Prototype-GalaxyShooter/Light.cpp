#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

void Light::initialize(Direct3D9* direct3D9) {

	// ƒ‰ƒCƒg‚ð‚ ‚Ä‚é ”’F‚ÅŒõ‘ò”½ŽË‚ ‚è‚ÉÝ’è
	D3DXVECTOR3 vDirection(0, -1, 1);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.5f;
	light.Diffuse.g = 1.5f;
	light.Diffuse.b = 1.5f;
	light.Diffuse.a = 1.0f;
	light.Specular = light.Diffuse;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vDirection);
	light.Range = 20.0f;
	direct3D9->device->SetLight(0, &light);
	direct3D9->device->LightEnable(0, true);
}

