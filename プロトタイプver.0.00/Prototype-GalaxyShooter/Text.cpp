#include "Text.h"

Text::Text()
{
	font = NULL;
}


Text::~Text()
{
}

void Text::initialize(LPDIRECT3DDEVICE9 device)
{
	//�����񃌃��_�����O�̏�����
	D3DXCreateFont(device, 0, 10, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "tahome", &font);
}

void Text::print(float x,float y, const char* string, ...)
{
	TCHAR str[MAX_PATH];
	va_list _ArgList;
	__crt_va_start(_ArgList, string);

	_vsprintf_l(str, string, NULL, _ArgList);

	__crt_va_end(_ArgList);

	RECT rect = { x,y,0,0 };
	//������̃T�C�Y���v�Z
	font->DrawTextA(NULL, str, -1, &rect, DT_CALCRECT, NULL);
	//���̃T�C�Y�Ń����_�����O
	font->DrawTextA(NULL, str, -1, &rect, DT_LEFT | DT_BOTTOM, 0xff00ff00);
}