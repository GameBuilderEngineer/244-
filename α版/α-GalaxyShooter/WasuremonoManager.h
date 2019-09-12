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
	const static int WASUREMONO_MAX = 160;				// ワスレモノ最大数	
	const static int INITIAL_PLACEMENT_NUMBER = 120;		// ワスレモノ初期配備数
	const static float RESPAWN_SURBEY_INTERVAL = 1.5f;	// ワスレモノリスポーン間隔(秒)
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
	int typeCount[NUM_WASUREMONO];			// ワスレモノごとの数（インスタンシング描画で使う）
	Planet* field;							// フィールド
	LPDIRECT3DDEVICE9 device;				// デバイス
	float timeCnt;							// 時間カウント


	// 自動リスポーン処理
	void autoRespawn(void);
	// ランダム配置
	D3DXVECTOR3 positionRand(float radiusRatio);
	// タイプを決める
	int decideType(void);

public:
	WasuremonoManager(void);
	~WasuremonoManager(void);							
	void initialize(LPDIRECT3DDEVICE9 device, std::vector<Wasuremono*> *_wasuremono, StaticMeshLoader* staticMeshLoader, Planet* _field);
	void uninitialize(void);
	void update(float frameTime);

	// ワスレモノを１つ生成
	Wasuremono* create(int typeID, D3DXVECTOR3 *position);
	// ワスレモノを１つ破棄
	void destroy(int i);
	// インスタンシング描画
	void instancingRender(LPDIRECT3DDEVICE9 device,
		D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon, LPD3DXEFFECT effect);
};


