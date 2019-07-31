#include "TextManager.h"
using namespace textManagerNS;

TextManager::TextManager()
{
	//�t�H���g�f�[�^���\�[�X�̖��O
	//dataName[FUTURA_BLACK] = { "unicode.futurabb.ttf" };
	dataName[NEW_RODIN] = { "FOT-NewRodinPro-UB.otf" };

	//�t�H���g�̖��O
	//fontName[FUTURA_BLACK] = { "Futura-Black" };
	fontName[NEW_RODIN] = { "FOT-�j���[���_�� Pro UB" };


	setDataDirectory();
	// fontData�ǂݍ���
	for (int i = 0; i < FONT_NUM; i++)
	{
		AddFontResourceEx(dataName[i], FR_PRIVATE, NULL);
	}

	futura = new Text();
}

TextManager::~TextManager()
{
	// fontData�I������
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