//===================================================================================================================================
//【MemoryLine.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/07/11
// [更新日]2019/09/03
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "MemoryPile.h"
#include "InstancingBillboard.h"
#include <vector>

namespace memoryLineNS
{
	const float MINIMUM_DISTANCE = 2.0f;
	const float MAXIMUM_DISTANCE = 10.0f;
	const float LOST_TIME = 2.0f;
	const float THICKNESS = 3.0f; // ラインの太さ
	const float UPDATE_TIME = 0.01f;
	enum TYPE
	{
		PENTAGON,
		STAR,
		NUM_TYPE
	};
}


class MemoryLine : public Base
{
	Line* line;							//メモリーラインを描画する線情報(実体ではない)
	InstancingBillboard billboard;		//メモリーラインをビルボードの点で描画する実体
	MemoryPile* joinTarget;				//メモリーラインを形成する元になるメモリーパイルのポインタ情報
	Object* joinPlayer;					//メモリーラインを生成したプレイヤーへのポインタ情報
	D3DXVECTOR3** pointList;			//メモリーパイルごとのメモリーラインを形成する描画する点の位置リスト
	D3DXVECTOR3* renderList;			//メモリーライン全体の描画リスト（インスタンスビルボードが要する位置リストは一つ）
	bool initialized;					//初期化フラグ（メモリーアクセスエラー防止）
	bool disconnected;					//切断フラグ（切断されると、消失処理へ移行する）
	float lostTime;						//消失処理用タイマー
	int pileNum;						//メモリーパイルの最大数（非アクティブを含む）
	int* pointNum;						//各メモリーパイルを始点とするメモリーライン上の点の数のリスト
	int renderNum;						//メモリーライン全体の描画数
	int currentRenderNum;				//現在の描画数
	float updateTimer;					//更新タイマー
public:
	MemoryLine();
	~MemoryLine();

	//proccessing
	void initialize(LPDIRECT3DDEVICE9 device, MemoryPile* memoryPile, int num, Object* player, 
		LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void unInitialize();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void update(LPDIRECT3DDEVICE9 device, float frameTime, int type);

	//operation
	bool collision(D3DXVECTOR3 position, float radius);	//衝突検知
	float calculationDistance(D3DXVECTOR3 point);		//(演算)ある点とラインとの距離を戻す
	D3DXVECTOR3 calculationNearPoint(D3DXVECTOR3 point);//(演算)ある点と最も近い位置を戻す
	void setLine(LPDIRECT3DDEVICE9 device);				//(更新)メモリーパイルの間のラインを設定する
	void setStarLine(LPDIRECT3DDEVICE9 device,float frameTime);			//(更新)リカージョンが完成した時の星形のラインを設定する
	void lost(float frameTime);							//(更新)消失処理
	void disconnect();									//(切替)切断処理
	//setter
	void resetCurrentRenderNum();
	//getter
};