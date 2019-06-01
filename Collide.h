#pragma once

#include <d3dx9.h>
#include "Object.h"

BOOL Collide(D3DXVECTOR3, D3DXVECTOR3, Object*, FLOAT*, D3DXVECTOR3*);
VOID RenderRay(LPDIRECT3DDEVICE9, D3DXVECTOR3, D3DXVECTOR3);
