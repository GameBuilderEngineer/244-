//-----------------------------------------------------------------------------
// チンギンデータ処理[ChinginTable.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#include "ChinginTable.h"
using namespace ChinginNS;

//=============================================================================
// コンストラクタ
//=============================================================================
ChinginTable::ChinginTable(void)
{
	data[0].id = 0;
	data[0].name = "チューイングガム";
	data[0].amount = 5;

	data[1].id = 1;
	data[1].name = "扇風機";
	data[1].amount = 20;

	data[2].id = 2;
	data[2].name = "なわとび";
	data[2].amount = 10;

	data[3].id = 3;
	data[3].name = "テレビ";
	data[3].amount = 50;

	data[4].id = 4;
	data[4].name = "けん玉";
	data[4].amount = 25;

	data[5].id = 5;
	data[5].name = "サッカーボール";
	data[5].amount = 20;

	data[6].id = 6;
	data[6].name = "クリスマスツリー";
	data[6].amount = 75;

	data[7].id = 7;
	data[7].name = "自転車";
	data[7].amount = 50;

	data[8].id = 8;
	data[8].name = "黒電話";
	data[8].amount = 75;

	data[9].id = 9;
	data[9].name = "ウサギのぬいぐるみ";
	data[9].amount = 200;

	data[10].id = 10;
	data[10].name = "ニンゲン（対戦相手）";
	data[10].amount = 1000;
}


//=============================================================================
// デストラクタ
//=============================================================================
ChinginTable::~ChinginTable(void)
{

}


//=============================================================================
// 名前を取得
//=============================================================================
std::string ChinginTable::getName(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			break;
		}
	}
	return out->name;
}


//=============================================================================
// 金額を取得
//=============================================================================
int ChinginTable::getAmount(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			break;
		}
	}
	return out->amount;
}

int ChinginTable::getAmount(std::string name)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->name == name)
		{
			break;
		}
	}
	return out->amount;
}


//=============================================================================
// 金額を加える
//=============================================================================
void ChinginTable::addAmount(int &dest, int id)
{
	dest += getAmount(id);
}

void ChinginTable::addAmount(int &dest, std::string name)
{
	dest += getAmount(name);
}


//=============================================================================
// 金額を引く
//=============================================================================
void ChinginTable::subAmount(int &dest, int id)
{
	dest -= getAmount(id);
}

void ChinginTable::subAmount(int &dest, std::string name)
{
	dest -= getAmount(name);
}


//=============================================================================
// 要素のアドレスを取得
//=============================================================================
ChinginData* ChinginTable::find(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			return out;
		}
	}
	return NULL;
}

ChinginData* ChinginTable::find(std::string name)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->name == name)
		{
			return out;
		}
	}
	return NULL;
}

ChinginData* ChinginTable::find(int amount)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->amount == amount)
		{
			return out;
		}
	}
	return NULL;
}

// 先頭要素を取得
ChinginData* ChinginTable::begin(void)
{
	return data;
}


//=============================================================================
// 存在するか検索
//=============================================================================
bool ChinginTable::exists(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			return true;
		}
	}
	return false;
}

bool ChinginTable::exists(std::string name)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->name == name)
		{
			return true;
		}
	}
	return false;
}

bool ChinginTable::exists(int amount)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->amount == amount)
		{
			return true;
		}
	}
	return false;
}



