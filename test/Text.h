#pragma once
#include "Base.h"
#include <string>

class Text : public Base
{
	D3DXCOLOR color;
	LPD3DXFONT font;
public:

	Text();
	~Text();
	void initialize(LPDIRECT3DDEVICE9 device, int height, int width, D3DXCOLOR _color);
	void print(float x, float y, const char* string, ...);
};

