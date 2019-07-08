//-----------------------------------------------------------------------------
// チンギンデータ処理[ChinginTable.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include <string>

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace ChinginNS
{
	const static int NUM_CHINGIN = 5;
}


//*****************************************************************************
// クラス定義
//*****************************************************************************
struct ChinginData
{
	int id;							// チンギンの固有番号
	std::string name;				// チンギンの名前
	int amount;						// チンギン金額
};

class ChinginTable
{
private:
	ChinginData data[NUM_CHINGIN];	// テーブル本体

public:
	ChinginTable(void);
	~ChinginTable(void);
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
	// 要素のアドレス取得
	ChinginData* find(int id);
	ChinginData* find(std::string name);
	ChinginData* find(int amount);
	ChinginData* begin(void);
	// 存在するか検索　true……存在する/false……存在しない
	bool exists(int id);
	bool exists(std::string name);
	bool exists(int amount);
};


