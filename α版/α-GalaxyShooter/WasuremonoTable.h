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
		HUMAN,				// 人間（対戦相手）

		NUM_WASUREMONO,		// ワスレモノ種類の数
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
	StaticMeshLoader* staticMeshLoader;
	WasuremonoData data[WasuremonoNS::NUM_WASUREMONO];	// テーブル本体

public:
	WasuremonoTable(StaticMeshLoader* staticMeshLoader);
	~WasuremonoTable(void);

	// 要素のアドレス取得
	WasuremonoData* find(int id);
	WasuremonoData* find(std::string name);
	WasuremonoData* find(int amount);
	WasuremonoData* begin(void);
	// 存在するか検索　true……存在する/false……存在しない
	bool exists(int id);
	bool exists(std::string name);
	bool exists(int amount);
	// 名前を取得
	std::string getName(int id);
	// 金額を取得
	int getAmount(int id);
	int getAmount(std::string name);
	// 金額を加える
	void addAmount(int &dest, int id);
	void addAmount(int &dest, std::string name);
	// 金額を引く
	void subAmount(int &dest, int id);
	void subAmount(int &dest, std::string name);

	// その他アクセサ
	void setStaticMeshLoader(StaticMeshLoader* staticMeshLoader) { this->staticMeshLoader = staticMeshLoader; }
	StaticMesh* getStaticMesh(int id) { return data[id].staticMesh; }
};


