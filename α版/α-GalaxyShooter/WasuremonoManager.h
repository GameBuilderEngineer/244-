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
// インクルードは
// WasuremonoTable→Wasuremono, WasuremonoManager
// Wasuremono→WasuremonoManager

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace WasuremonoNS
{
	// リスポーンモード
	enum RESPAWN_MODE
	{
		FEW_WASUREMONO		// ワスレモノの少ない場所にリスポーン
	};


	const static int INITIAL_PLACEMENT_NUMBER = 100;
}

#define SECOND(_s)	(_s * 60/*fps*/)



//*****************************************************************************
// クラス定義
//*****************************************************************************
class WasuremonoManager
{
private:
	DWORD frameCnt;						// フレームカウント

	// ワスレモノ表（名称やチンギンを参照可能）
	WasuremonoTable* table;

	// ワスレモノスロット（生成したワスレモノを管理するポインタvector）
	std::vector<Wasuremono*> wasuremono;

	// 初期化アルゴリズム
	void setUpInitialType(int typeID[]);
	void setUpInitialPosition(D3DXVECTOR3 position[]);

	// リスポーン関係
	int respawnMode;					// リスポーンのモード
	bool surbeyRespawnCondition(void);	// リスポーン条件を調べる
	void autoRespawn(void);				// 自動リスポーン処理

public:
	WasuremonoManager(void);
	~WasuremonoManager(void);
	void initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader);// 初期化
	void uninitialize(void);					// 終了処理
	void update(void);							// 更新処理
	Wasuremono* create(int typeID, D3DXVECTOR3 *position);// ワスレモノを生成
	void destroy(int id);						// ワスレモノを破棄
	void startWork(void);						// ゲーム開始時のワスレモノ初期生成
	void finishWork(void);						// ゲーム終了時のワスレモノ一斉破棄
};


