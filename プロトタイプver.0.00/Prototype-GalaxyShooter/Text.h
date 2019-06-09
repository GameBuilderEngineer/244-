#pragma once
#include "Base.h"
#include <string>

class Text : public Base
{
public:
	LPD3DXFONT font;

	Text();
	~Text();
	void initialize(LPDIRECT3DDEVICE9 device);
	void print(float x, float y, const char* string, ...);
};

