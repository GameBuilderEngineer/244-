//-----------------------------------------------------------------------------
// ワスレモノデーターベース[WasuremonoTable.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/7
//-----------------------------------------------------------------------------
#include "WasuremonoTable.h"
#include "cassert"
using namespace WasuremonoNS;

//=============================================================================
// コンストラクタ
//=============================================================================
WasuremonoTable::WasuremonoTable(StaticMeshLoader* p): staticMeshLoader(p)
{
	// テーブルの構築
	data[CHEWING_GUM].typeID = CHEWING_GUM;
	data[CHEWING_GUM].name = "チューイングガム";
	data[CHEWING_GUM].amount = 5;
	data[CHEWING_GUM].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[CHEWING_GUM].appearanceProbability = PROBABILITY_UNIT * 5;

	data[ELECTRIC_FAN].typeID = ELECTRIC_FAN;
	data[ELECTRIC_FAN].name = "扇風機";
	data[ELECTRIC_FAN].amount = 20;
	data[ELECTRIC_FAN].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[ELECTRIC_FAN].appearanceProbability = PROBABILITY_UNIT * 4;

	data[JUMP_ROPE].typeID = JUMP_ROPE;
	data[JUMP_ROPE].name = "なわとび";
	data[JUMP_ROPE].amount = 10;
	data[JUMP_ROPE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[JUMP_ROPE].appearanceProbability = PROBABILITY_UNIT * 5;

	data[TELEVISION].typeID = TELEVISION;
	data[TELEVISION].name = "テレビ";
	data[TELEVISION].amount = 50;
	data[TELEVISION].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[TELEVISION].appearanceProbability = PROBABILITY_UNIT * 3;

	data[KENDAMA].typeID = KENDAMA;
	data[KENDAMA].name = "けん玉";
	data[KENDAMA].amount = 25;
	data[KENDAMA].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[KENDAMA].appearanceProbability = PROBABILITY_UNIT * 4;

	data[SOCCER_BALL].typeID = SOCCER_BALL;
	data[SOCCER_BALL].name = "サッカーボール";
	data[SOCCER_BALL].amount = 20;
	data[SOCCER_BALL].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[SOCCER_BALL].appearanceProbability = PROBABILITY_UNIT * 4;

	data[CHRISTMAS_TREE].typeID = CHRISTMAS_TREE;
	data[CHRISTMAS_TREE].name = "クリスマスツリー";
	data[CHRISTMAS_TREE].amount = 75;
	data[CHRISTMAS_TREE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[CHRISTMAS_TREE].appearanceProbability = PROBABILITY_UNIT * 2;

	data[BICYCLE].typeID = BICYCLE;
	data[BICYCLE].name = "自転車";
	data[BICYCLE].amount = 50;
	data[BICYCLE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[BICYCLE].appearanceProbability = PROBABILITY_UNIT * 3;

	data[DIAL_PHONE].typeID = DIAL_PHONE;
	data[DIAL_PHONE].name = "黒電話";
	data[DIAL_PHONE].amount = 75;
	data[DIAL_PHONE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[DIAL_PHONE].appearanceProbability = PROBABILITY_UNIT * 2;
	//

	data[STUFFED_BUNNY].typeID = STUFFED_BUNNY;
	data[STUFFED_BUNNY].name = "ウサギのぬいぐるみ";
	data[STUFFED_BUNNY].amount = 200;
	data[STUFFED_BUNNY].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::WASUREMONO_PHONE]);
	data[STUFFED_BUNNY].appearanceProbability = PROBABILITY_UNIT;

	data[HUMAN].typeID = HUMAN;
	data[HUMAN].name = "ニンゲン（対戦相手）";
	data[HUMAN].amount = 1000;
	data[HUMAN].staticMesh = NULL;				// 未使用
	data[HUMAN].appearanceProbability = -1.0f;	// 未使用

	//------------------------------
	// 出現確率についてアサーション
	//------------------------------
	{
		float sum = 0.0f;
		for (int i = 0; i < NUM_WASUREMONO; i++)
		{
			sum += data[i].appearanceProbability;
		}
		// 合計値が100%になっていない
		assert(sum > 99.9f && sum < 100.1);
	}
}


//=============================================================================
// デストラクタ
//=============================================================================
WasuremonoTable::~WasuremonoTable(void)
{

}


//=============================================================================
// 要素のアドレスを取得
//=============================================================================
WasuremonoData* WasuremonoTable::find(int typeID)
{
	if (typeID < NUM_WASUREMONO && typeID > -1)
	{
		return &data[typeID];
	}
	return NULL;
}

WasuremonoData* WasuremonoTable::find(std::string name)
{
	WasuremonoData* out = data;
	for (int i = 0; i < NUM_WASUREMONO; i++)
	{
		out++;
		if (out->name == name)
		{
			return out;
		}
	}
	return NULL;
}

// 先頭要素を取得
WasuremonoData* WasuremonoTable::begin(void)
{
	return data;
}


//=============================================================================
// 存在するか検索
//=============================================================================
bool WasuremonoTable::exists(int typeID)
{
	if (typeID < NUM_WASUREMONO && typeID > -1) return true;
	else return false;
}

bool WasuremonoTable::exists(std::string name)
{
	WasuremonoData *p = find(name);
	if (p != NULL)
	{
		return 	true;
	}
	return false;
}


//=============================================================================
// 名前を取得
//=============================================================================
std::string WasuremonoTable::getName(int typeID)
{
	if (typeID < NUM_WASUREMONO && typeID > -1)
	{
		return data[typeID].name;
	}
	return "不正なIDだよ";
}


//=============================================================================
// 金額を取得
//=============================================================================
int WasuremonoTable::getAmount(int typeID)
{
	if (typeID < NUM_WASUREMONO && typeID > -1)
	{
		return data[typeID].amount;
	}
	return -1;
}

int WasuremonoTable::getAmount(std::string name)
{
	WasuremonoData *p = find(name);
	if (p != NULL)
	{
		return 	p->amount;
	}
	return -1;
}


//=============================================================================
// メッシュ情報を取得
//=============================================================================
StaticMesh* WasuremonoTable::getStaticMesh(int typeID)
{ 
 	if (typeID < NUM_WASUREMONO && typeID > -1)
	{
		return data[typeID].staticMesh;
	}
	return NULL;
}

StaticMesh* WasuremonoTable::getStaticMesh(std::string name)
{
	WasuremonoData *p = find(name);
	if (p != NULL)
	{
		return 	p->staticMesh;
	}
	return NULL;
}


//=============================================================================
// 出現確率を取得
//=============================================================================
float WasuremonoTable::getProbability(int typeID)
{
	if (typeID < NUM_WASUREMONO && typeID > -1)
	{
		return data[typeID].appearanceProbability;
	}
	return -1.0f;
}


//=============================================================================
// 金額を加える
//=============================================================================
void WasuremonoTable::addAmount(int &dest, int typeID)
{
	dest += getAmount(typeID);
}

void WasuremonoTable::addAmount(int &dest, std::string name)
{
	dest += getAmount(name);
}


//=============================================================================
// 金額を引く
//=============================================================================
void WasuremonoTable::subAmount(int &dest, int typeID)
{
	dest -= getAmount(typeID);
}

void WasuremonoTable::subAmount(int &dest, std::string name)
{
	dest -= getAmount(name);
}

