#include "TextManager.h"
using namespace textManagerNS;

TextManager::TextManager()
{
	//フォントデータリソースの名前
	//dataName[FUTURA_BLACK] = { "unicode.futurabb.ttf" };
	dataName[NEW_RODIN] = { "FOT-NewRodinPro-EB.otf" };

	//フォントの名前
	//fontName[FUTURA_BLACK] = { "Futura-Black" };
	fontName[NEW_RODIN] = { "FOT-ニューロダン Pro UB" };

	setDataDirectory();

	// fontData読み込み
	for (int i = 0; i < FONT_NUM; i++)
	{
		AddFontResourceEx(dataName[i], FR_PRIVATE, NULL);
	}

	futura = new Text();
}

TextManager::~TextManager()
{
	// fontData終了処理
	for (int i = 0; i < FONT_NUM; i++)
	{
		RemoveFontResourceEx(dataName[i], FR_PRIVATE, NULL);
	}

	SAFE_DELETE(futura);
}

void TextManager::initialize(LPDIRECT3DDEVICE9 device)
{
	//futura->initialize(device, 48, 27, 0xffffffff,fontName[FUTURA_BLACK]);
	futura->initialize(device, 48, 27, 0xffffffff, fontName[NEW_RODIN]);
}