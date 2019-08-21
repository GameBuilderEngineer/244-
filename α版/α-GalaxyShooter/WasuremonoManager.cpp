//-----------------------------------------------------------------------------
// ワスレモノ管理処理[WasuremonoManager.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/9
//-----------------------------------------------------------------------------
#include "Base.h"
#include "WasuremonoManager.h"
#include "WasuremonoSeries.h"

Wasuremono* unko;
D3DXVECTOR3 unkoList[] = {
		D3DXVECTOR3(100,50,50),
		D3DXVECTOR3(-100,-100,-50),
		D3DXVECTOR3(100,-50,10),
		D3DXVECTOR3(100,50,10),
		D3DXVECTOR3(100,0,100),
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(-100,100,100),
		D3DXVECTOR3(-100,-100,100),
		D3DXVECTOR3(-100,100,0),
		D3DXVECTOR3(-100,100,-100),
};


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
	wasuremono->reserve(WASUREMONO_MAX);				// vectorのメモリのみ先に確保
	ZeroMemory(typeCount, sizeof(int) * NUM_WASUREMONO);// ワスレモノタイプのカウントを初期化

	// ワスレモノ初期配備
	setUp();

	timeCnt = 0.0f;
	respawnMode = 0;

	unko = create(CHEWING_GUM, &D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	// GameSceneで解放するように一旦変更
	//// 非表示のワスレモノを解放
	//for (int i = 0; i < wasuremono->size(); i++)
	//{
	//	if ((*wasuremono)[i]->getActive() == false)
	//	{
	//		SAFE_DELETE((*wasuremono)[i])
	//		wasuremono->erase(wasuremono->begin() + i);
	//	}
	//}

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

	typeCount[typeID]++;		// タイプごとのカウントを増やす
	return wasuremono->back();
}


//=============================================================================
// ワスレモノを破棄
//=============================================================================
void WasuremonoManager::destroy(int id)
{
	typeCount[(*wasuremono)[id]->getType()]--;	// タイプごとのカウント減らす
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
	std::vector<Wasuremono*> temp;
	(*wasuremono).swap(temp);	// メモリアロケータに戻す
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


//=============================================================================
// インスタンシング描画
//=============================================================================
void WasuremonoManager::instancingRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon, LPD3DXEFFECT effect)
{
	int listAddCount[NUM_WASUREMONO] = { 0 };		// 各リストの要素カウンタ
	int representative[NUM_WASUREMONO] = { -1 };	// 各クラスの代表インスタンス番号

	// 各クラスの座標リスト
	D3DXVECTOR3* chewingGumList		= new D3DXVECTOR3[typeCount[CHEWING_GUM]];
	D3DXVECTOR3* electricFanList	= new D3DXVECTOR3[typeCount[ELECTRIC_FAN]];
	D3DXVECTOR3* jumpRopeList		= new D3DXVECTOR3[typeCount[JUMP_ROPE]];
	D3DXVECTOR3* televisionList		= new D3DXVECTOR3[typeCount[TELEVISION]];
	D3DXVECTOR3* kendamaList		= new D3DXVECTOR3[typeCount[KENDAMA]];
	D3DXVECTOR3* soccerBallList		= new D3DXVECTOR3[typeCount[SOCCER_BALL]];
	D3DXVECTOR3* christmasTreeList	= new D3DXVECTOR3[typeCount[CHRISTMAS_TREE]];
	D3DXVECTOR3* bicycleList		= new D3DXVECTOR3[typeCount[BICYCLE]];
	D3DXVECTOR3* dialPhoneList		= new D3DXVECTOR3[typeCount[DIAL_PHONE]];
	D3DXVECTOR3* stuffedBunnyList	= new D3DXVECTOR3[typeCount[STUFFED_BUNNY]];

	// 座標リストを埋める
	for (int i = 0; i < wasuremono->size(); i++)
	{
		switch ((*wasuremono)[i]->getType())
		{
		case CHEWING_GUM:
			chewingGumList[listAddCount[CHEWING_GUM]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[CHEWING_GUM] == 1)
			{
				representative[CHEWING_GUM] = i;
			}
			break;

		case ELECTRIC_FAN:
			electricFanList[listAddCount[ELECTRIC_FAN]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[ELECTRIC_FAN] == 1)
			{
				representative[ELECTRIC_FAN] = i;
			}
			break;

		case JUMP_ROPE:
			jumpRopeList[listAddCount[JUMP_ROPE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[JUMP_ROPE] == 1)
			{
				representative[JUMP_ROPE] = i;
			}
			break;

		case TELEVISION:
			televisionList[listAddCount[TELEVISION]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[TELEVISION] == 1)
			{
				representative[TELEVISION] = i;
			}
			break;

		case KENDAMA:
			kendamaList[listAddCount[KENDAMA]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[KENDAMA] == 1)
			{
				representative[KENDAMA] = i;
			}
			break;

		case SOCCER_BALL:
			soccerBallList[listAddCount[SOCCER_BALL]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[SOCCER_BALL] == 1)
			{
				representative[SOCCER_BALL] = i;
			}
			break;

		case CHRISTMAS_TREE:
			christmasTreeList[listAddCount[CHRISTMAS_TREE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[CHRISTMAS_TREE] == 1)
			{
				representative[CHRISTMAS_TREE] = i;
			}
			break;

		case BICYCLE:
			bicycleList[listAddCount[BICYCLE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[BICYCLE] == 1)
			{
				representative[BICYCLE] = i;
			}
			break;

		case DIAL_PHONE:
			dialPhoneList[listAddCount[DIAL_PHONE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[DIAL_PHONE] == 1)
			{
				representative[DIAL_PHONE] = i;
			}
			break;

		case STUFFED_BUNNY:
			stuffedBunnyList[listAddCount[STUFFED_BUNNY]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[STUFFED_BUNNY] == 1)
			{
				representative[STUFFED_BUNNY] = i;
			}
			break;
		}
	}
	
	unko->setNumOfRender(device, 10, unkoList);
	unko->multipleRender(device, view, projection, cameraPositon, effect);

	//// インスタンシング描画に座標リストを渡す
	//(*wasuremono)[representative[CHEWING_GUM]]->setNumOfRender(device, typeCount[CHEWING_GUM], chewingGumList);
	//(*wasuremono)[representative[ELECTRIC_FAN]]->setNumOfRender(device, typeCount[ELECTRIC_FAN], electricFanList);
	//(*wasuremono)[representative[JUMP_ROPE]]->setNumOfRender(device, typeCount[JUMP_ROPE], jumpRopeList);
	//(*wasuremono)[representative[TELEVISION]]->setNumOfRender(device, typeCount[TELEVISION], televisionList);
	//(*wasuremono)[representative[KENDAMA]]->setNumOfRender(device, typeCount[KENDAMA], kendamaList);
	//(*wasuremono)[representative[SOCCER_BALL]]->setNumOfRender(device, typeCount[SOCCER_BALL], soccerBallList);
	//(*wasuremono)[representative[CHRISTMAS_TREE]]->setNumOfRender(device, typeCount[CHRISTMAS_TREE], christmasTreeList);
	//(*wasuremono)[representative[BICYCLE]]->setNumOfRender(device, typeCount[BICYCLE], bicycleList);
	//(*wasuremono)[representative[DIAL_PHONE]]->setNumOfRender(device, typeCount[DIAL_PHONE], dialPhoneList);
	//(*wasuremono)[representative[STUFFED_BUNNY]]->setNumOfRender(device, typeCount[STUFFED_BUNNY], stuffedBunnyList);

	//// インスタンシング描画
	//(*wasuremono)[representative[CHEWING_GUM]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[ELECTRIC_FAN]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[JUMP_ROPE]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[TELEVISION]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[KENDAMA]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[SOCCER_BALL]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[CHRISTMAS_TREE]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[BICYCLE]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[DIAL_PHONE]]->multipleRender(device, view, projection, cameraPositon, effect);
	//(*wasuremono)[representative[STUFFED_BUNNY]]->multipleRender(device, view, projection, cameraPositon, effect);

	// リスト解放
	SAFE_DELETE_ARRAY(chewingGumList)
	SAFE_DELETE_ARRAY(electricFanList)
	SAFE_DELETE_ARRAY(jumpRopeList)
	SAFE_DELETE_ARRAY(televisionList)
	SAFE_DELETE_ARRAY(kendamaList)
	SAFE_DELETE_ARRAY(soccerBallList)
	SAFE_DELETE_ARRAY(christmasTreeList)
	SAFE_DELETE_ARRAY(bicycleList)
	SAFE_DELETE_ARRAY(dialPhoneList)
	SAFE_DELETE_ARRAY(stuffedBunnyList)
}