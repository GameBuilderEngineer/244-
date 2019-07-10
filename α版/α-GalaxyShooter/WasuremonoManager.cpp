//-----------------------------------------------------------------------------
// ワスレモノ管理処理[WasuremonoManager.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/9
//-----------------------------------------------------------------------------
#include "Base.h"
#include "WasuremonoManager.h"
using namespace WasuremonoNS;

//=============================================================================
// コンストラクタ
//=============================================================================
WasuremonoManager::WasuremonoManager(void)
{
	table = NULL;
}


//=============================================================================
// デストラクタ
//=============================================================================
WasuremonoManager::~WasuremonoManager(void)
{
	SAFE_DELETE(table);
}


//=============================================================================
// 初期化処理
//=============================================================================
void WasuremonoManager::initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader)
{
	if (table == NULL)
	{// 初回の実行の場合
		table = new WasuremonoTable(staticMeshLoader);
		// デストラクタで破棄（ゲームシーンをリプレイする場合の初期化など破棄不要なケースを想定）

		Wasuremono::setDevice(device);
		Wasuremono::setTable(table);
	}

	frameCnt = 0;
	respawnMode = 0;
}


//=============================================================================
// 終了処理
//=============================================================================
void WasuremonoManager::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void WasuremonoManager::update(void)
{
	// 更新頻度を調整
	if (frameCnt++ < SECOND(3)) { return; }
	frameCnt = 0;

	// 状況を取得しリスポーンを判断する
	if (surbeyRespawnCondition() == true)
	{
		autoRespawn();
	}
}


//=============================================================================
// リスポーン条件を調べる
//=============================================================================
bool WasuremonoManager::surbeyRespawnCondition(void)
{
	// 仮の条件
	if (wasuremono.size() < size_t(INITIAL_PLACEMENT_NUMBER * 0.8f))
	{
		respawnMode = FEW_WASUREMONO;
		return true;
	}

	return false;
}


//=============================================================================
// 自動リスポーン処理
//=============================================================================
void WasuremonoManager::autoRespawn(void)
{
	switch (respawnMode)
	{
	case FEW_WASUREMONO:
		break;

	default:
		break;
	}
}


//=============================================================================
// ワスレモノを生成
//=============================================================================
Wasuremono* WasuremonoManager::create(int typeID, D3DXVECTOR3 *position)
{
	switch (typeID)
	{
		case CHEWING_GUM:
			wasuremono.push_back(new ChewingGum(typeID, position));
			break;

		case ELECTRIC_FAN:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case JUMP_ROPE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case TELEVISION:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case KENDAMA:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case SOCCER_BALL:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case CHRISTMAS_TREE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case BICYCLE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case DIAL_PHONE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case STUFFED_BUNNY:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;
		
		default:
			break;
	}
	return wasuremono.back();
}


//=============================================================================
// ワスレモノを破棄
//=============================================================================
void WasuremonoManager::destroy(int id)
{
	delete wasuremono[id];
	wasuremono.erase(wasuremono.begin() + id);
}


//=============================================================================
// ゲーム開始時のワスレモノ初期生成
//=============================================================================
void WasuremonoManager::startWork(void)
{
	wasuremono.reserve(INITIAL_PLACEMENT_NUMBER);		// ポインタ確保

	int typeID[INITIAL_PLACEMENT_NUMBER];				// 種類生成
	setUpInitialType(typeID);

	D3DXVECTOR3 position[INITIAL_PLACEMENT_NUMBER];		// 座標生成
	setUpInitialPosition(position);

	for (int i = 0; i < INITIAL_PLACEMENT_NUMBER; i++)
	{
		wasuremono[i] = create(typeID[i], &position[i]);
	}
}


//=============================================================================
// ゲーム終了時のワスレモノ一斉破棄
//=============================================================================
void WasuremonoManager::finishWork(void)
{
	for (size_t i = 0; i < wasuremono.size(); i++)
	{
		delete wasuremono[i];
	}
	wasuremono.clear();
}


//=============================================================================
// ゲームスタート時にワスレモノのタイプを決めるアルゴリズム
//=============================================================================
void WasuremonoManager::setUpInitialType(int typeID[])
{

}


//=============================================================================
// ゲームスタート時にワスレモノを配置するアルゴリズム
//=============================================================================
void WasuremonoManager::setUpInitialPosition(D3DXVECTOR3 position[])
{
	
}