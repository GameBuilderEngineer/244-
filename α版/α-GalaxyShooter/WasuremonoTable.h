//-----------------------------------------------------------------------------
// ワスレモノデータベース[WasuremonoTable.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include <string>
#include "StaticMeshLoader.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace WasuremonoNS
{
	// ワスレモノの種類
	enum WASUREMONO_TYPE
	{
		CHEWING_GUM,		// チューイングガム
		ELECTRIC_FAN,		// 扇風機
		JUMP_ROPE,			// 縄跳び
		TELEVISION,			// テレビ
		KENDAMA,			// けんだま
		SOCCER_BALL,		// サッカーボール
		CHRISTMAS_TREE,		// クリスマスツリー
		BICYCLE,			// 自転車
		DIAL_PHONE,			// 黒電話
		STUFFED_BUNNY,		// うさぎのぬいぐるみ
		NUM_WASUREMONO,		// ワスレモノ種類の数

		// 人間（対戦相手）はテーブル上にデータのみ存在する
		// テーブル上以外でワスレモノとしては数えない
		HUMAN = NUM_WASUREMONO,

		NUM_TABLE_ELEMENT	// ワスレモノテーブルの要素数
	};
}


//*****************************************************************************
// クラス定義
//*****************************************************************************
struct WasuremonoData
{
	int typeID;				// ワスレモノの固有番号
	std::string name;		// ワスレモノの名前
	int amount;				// ワスレモノのチンギン
	StaticMesh* staticMesh;	// メッシュ情報
};

class WasuremonoTable
{
private:
	StaticMeshLoader* staticMeshLoader;						// メッシュローダー
	WasuremonoData data[WasuremonoNS::NUM_TABLE_ELEMENT];	// テーブル本体

public:
	WasuremonoTable(StaticMeshLoader* p);
	~WasuremonoTable(void);

	// 要素のアドレス取得
	WasuremonoData* find(int typeID);
	WasuremonoData* find(std::string name);
	WasuremonoData* begin(void);
	// 存在するか検索　true……存在する/false……存在しない
	bool exists(int typeID);
	bool exists(std::string name);
	// 名前を取得
	std::string getName(int typeID);
	// 金額を取得
	int getAmount(int typeID);
	int getAmount(std::string name);
	// メッシュ情報を取得
	StaticMesh* getStaticMesh(int typeID);
	StaticMesh* getStaticMesh(std::string name);
	// 金額を加える
	void addAmount(int &dest, int typeID);
	void addAmount(int &dest, std::string name);
	// 金額を引く
	void subAmount(int &dest, int typeID);
	void subAmount(int &dest, std::string name);

	// メッシュローダーをセット
	void setStaticMeshLoader(StaticMeshLoader* staticMeshLoader) { this->staticMeshLoader = staticMeshLoader; }
};


