//============================================================================================================================================
// Document
//============================================================================================================================================
// TextManager.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/02
//============================================================================================================================================
#pragma once
#include "Base.h"
#include "Text.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace textManagerNS
{
	enum TYPE
	{
		NEW_RODIN,
		FUTURA,
		TYPE_MAX
	};
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class TextManager : public Base
{
private:
	const char* dataName[textManagerNS::TYPE::TYPE_MAX];	//	リソースデータ名
	const char* fontName[textManagerNS::TYPE::TYPE_MAX];	//	フォント名
public:
	Text* text[textManagerNS::TYPE::TYPE_MAX];				//	テキスト
	TextManager(void);
	~TextManager(void);
	void initialize(LPDIRECT3DDEVICE9 _device);
};