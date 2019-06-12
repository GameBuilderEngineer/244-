#include "Text.h"

Text::Text()
{
	font = NULL;
	color = D3DXCOLOR(255, 255, 255, 255);
}


Text::~Text()
{
}

void Text::initialize(LPDIRECT3DDEVICE9 device,int height,int width,D3DXCOLOR _color)
{
	color = _color;
	//�����񃌃��_�����O�̏�����
	D3DXCreateFont(device, height, width, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahome", &font);
}

void Text::print(float x,float y, const char* string, ...)
{
	TCHAR str[2048];
	va_list _ArgList;
	__crt_va_start(_ArgList, string);

	_vsprintf_l(str, string, NULL, _ArgList);

	__crt_va_end(_ArgList);

	RECT rect = { x,y,0,0 };
	//������̃T�C�Y���v�Z
	font->DrawTextA(NULL, str, -1, &rect, DT_CALCRECT, NULL);
	//���̃T�C�Y�Ń����_�����O
	font->DrawTextA(NULL, str, -1, &rect, DT_LEFT | DT_BOTTOM, color);
}