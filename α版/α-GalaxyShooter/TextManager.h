#pragma once
#include "Base.h"
#include "Text.h"

namespace textManagerNS
{
	enum
	{
		NEW_RODIN,
		FONT_NUM
	};
}

class TextManager :	public Base
{
private:
	const char* dataName[textManagerNS::FONT_NUM];
	const char* fontName[textManagerNS::FONT_NUM];
public:
	
	Text* futura;

	TextManager();
	~TextManager();
	void initialize(LPDIRECT3DDEVICE9 device);
};