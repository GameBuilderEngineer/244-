//-----------------------------------------------------------------------------
// ワスレモノ管理処理[WasuremonoManager.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/7/9
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include "StaticMeshLoader.h"
#include "WasuremonoTable.h"
#include "Wasuremono.h" 
#include "Planet.h"
using namespace WasuremonoNS;

// インクルードは
// WasuremonoTable→Wasuremono, WasuremonoSeries, WasuremonoManager
// Wasuremono→WasuremonoSeries, WasuremonoManager
// WasuremonoSeries→WasuremonoManager

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace WasuremonoNS
{
	// リスポーンモード
	enum RESPAWN_MODE
	{
		RANDOM		// ランダム
	};

	const static int WASUREMONO_MAX = 200;
	const static int INITIAL_PLACEMENT_NUMBER = 100;
	const static float RESPAWN_SURBEY_INTERVAL = 3.0f;
}



//*****************************************************************************
// クラス定義
//*****************************************************************************
class WasuremonoManager
{
private:
	// Data
	WasuremonoTable* table;					// ワスレモノ表（名称やチンギンを参照可能）
	std::vector<Wasuremono*>* wasuremono;	// ワスレモノ
	float timeCnt;							// 時間カウント
	int respawnMode;						// リスポーンのモード
	LPDIRECT3DDEVICE9 device;				// デバイス
	Planet *field;							// フィールド情報
	int typeCount[NUM_WASUREMONO];			// ワスレモノごとの数

	// タイプ初期化
	void setUpInitialType(std::vector<int> &type);
	// 座標初期化
	void setUpInitialPosition(std::vector<D3DXVECTOR3> &position);
	// リスポーン条件を調べる
	bool surbeyRespawnCondition(void);
	// 自動リスポーン処理
	void autoRespawn(void);
	// ランダム配置
	D3DXVECTOR3 positionRand(D3DXVECTOR3 &out);


public:
	WasuremonoManager(void);
	~WasuremonoManager(void);							
	void initialize(LPDIRECT3DDEVICE9 device, std::vector<Wasuremono*> *wasuremono, StaticMeshLoader* staticMeshLoader, Planet*);
	void uninitialize(void);
	void update(float frameTime);

	// ワスレモノを生成
	Wasuremono* create(int typeID, D3DXVECTOR3 *position);
	// ワスレモノを破棄
	void destroy(int id);
	// ワスレモノ初期配備
	void setUp(void);
	// ワスレモノ一斉破棄
	void clear(void);

	void instancingRender(LPDIRECT3DDEVICE9 device,
		D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon, LPD3DXEFFECT effect);
};


