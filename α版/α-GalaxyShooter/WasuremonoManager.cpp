//-----------------------------------------------------------------------------
// ワスレモノ管理処理[WasuremonoManager.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/9
//-----------------------------------------------------------------------------
#include "Base.h"
#include "WasuremonoManager.h"
#include "WasuremonoSeries.h"
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
void WasuremonoManager::initialize(LPDIRECT3DDEVICE9 device, std::vector<Wasuremono*> *wasuremono, StaticMeshLoader* staticMeshLoader, Planet*)
{
	if (table == NULL)
	{	// インスタンス生成時のみ
		table = new WasuremonoTable(staticMeshLoader);	// テーブル生成
		Wasuremono::setTable(table);					// テーブル→ワスレモノに設定
		this->device = device;
	}

	this->wasuremono = wasuremono;
	wasuremono->reserve(WASUREMONO_MAX);	// vectorのメモリのみ先に確保
	setUp();								// ワスレモノ初期配備
	timeCnt = 0.0f;
	respawnMode = 0;
}


//=============================================================================
// 終了処理
//=============================================================================
void WasuremonoManager::uninitialize(void)
{
	clear();// ワスレモノ一斉破棄
}


//=============================================================================
// 更新処理
//=============================================================================
void WasuremonoManager::update(float frameTime)
{
	// 更新間隔を調整
	timeCnt += frameTime;
	if (timeCnt < RESPAWN_SURBEY_INTERVAL) { return; }
	timeCnt = 0.0f;

	// 非表示のワスレモノを解放
	for (int i = 0; i < wasuremono->size(); i++)
	{
		if ((*wasuremono)[i]->getActive() == false)
		{
			SAFE_DELETE((*wasuremono)[i])
			wasuremono->erase(wasuremono->begin() + i);
		}
	}

	// 条件に当てはまればリスポーン
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
	// 仮
	if (wasuremono->size() < size_t(INITIAL_PLACEMENT_NUMBER * 0.8f))
	{
		respawnMode = RANDOM;
		return true;
	}
	return false;
}


//=============================================================================
// 自動リスポーン処理
//=============================================================================
void WasuremonoManager::autoRespawn(void)
{
	D3DXVECTOR3 newPosition;

	switch (respawnMode)
	{
	case RANDOM:
		positionRand(newPosition);
		create(rand() % NUM_WASUREMONO, &newPosition);
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
			wasuremono->emplace_back(new ChewingGum(device, typeID, position));
			break;

		case ELECTRIC_FAN:
			wasuremono->emplace_back(new ElectricFan(device, typeID, position));
			break;

		case JUMP_ROPE:
			wasuremono->emplace_back(new JumpRope(device, typeID, position));
			break;

		case TELEVISION:
			wasuremono->emplace_back(new Television(device, typeID, position));
			break;

		case KENDAMA:
			wasuremono->emplace_back(new Kendama(device, typeID, position));
			break;

		case SOCCER_BALL:
			wasuremono->emplace_back(new SoccerBall(device, typeID, position));
			break;

		case CHRISTMAS_TREE:
			wasuremono->emplace_back(new ChristmasTree(device, typeID, position));
			break;

		case BICYCLE:
			wasuremono->emplace_back(new Bicycle(device, typeID, position));
			break;

		case DIAL_PHONE:
			wasuremono->emplace_back(new DialPhone(device, typeID, position));
			break;

		case STUFFED_BUNNY:
			wasuremono->emplace_back(new StuffedBunny(device, typeID, position));
			break;
		
		default:
			break;
	}

	return wasuremono->back();
}


//=============================================================================
// ワスレモノを破棄
//=============================================================================
void WasuremonoManager::destroy(int id)
{
	delete (*wasuremono)[id];
	wasuremono->erase(wasuremono->begin() + id);
}


//=============================================================================
// ワスレモノ初期配備
//=============================================================================
void WasuremonoManager::setUp(void)
{
	std::vector<int> type(INITIAL_PLACEMENT_NUMBER);
	setUpInitialType(type);

	std::vector<D3DXVECTOR3> position(INITIAL_PLACEMENT_NUMBER);
	setUpInitialPosition(position);

	for (int i = 0; i < INITIAL_PLACEMENT_NUMBER; i++)
	{
		(*wasuremono)[i] = create(type[i], &position[i]);
	}
}


//=============================================================================
// ワスレモノ一斉破棄
//=============================================================================
void WasuremonoManager::clear(void)
{
	for (size_t i = 0; i < wasuremono->size(); i++)
	{
		delete (*wasuremono)[i];
	}
	(*wasuremono).clear();
}


//=============================================================================
// ゲームスタート時にワスレモノのタイプを決めるアルゴリズム
//=============================================================================
void WasuremonoManager::setUpInitialType(std::vector<int> &type)
{
	for (int i = 0; i < type.size(); i++)
	{
		type[i] = rand() % NUM_WASUREMONO;	// 仮
	}
}


//=============================================================================
// ゲームスタート時にワスレモノを配置するアルゴリズム
//=============================================================================
void WasuremonoManager::setUpInitialPosition(std::vector<D3DXVECTOR3> &position)
{
	for (int i = 0; i < position.size(); i++)
	{
		positionRand(position[i]);	// 仮
	}
}

//=============================================================================
// ランダム配置
//=============================================================================
D3DXVECTOR3 WasuremonoManager::positionRand(D3DXVECTOR3 &out)
{
	// 仮
	float x = (float)(rand() % 100);
	if (rand() % 2) x = -x;
	float y = (float)(rand() % 100);
	if (rand() % 2) y = -y;
	float z = (float)(rand() % 100);
	if (rand() % 2) z = -z;
	D3DXVECTOR3 setPos = D3DXVECTOR3(x, y, z);
	D3DXVec3Normalize(&setPos, &setPos);
	setPos.x *= 200.0f;
	setPos.y *= 200.0f;
	setPos.z *= 200.0f;
	
	out = setPos;
	return setPos;
}

