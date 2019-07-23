#pragma once
#include "Base.h"
#include "MemoryPile.h"
#include "Player.h"
#include "InstancingBillboard.h"
#include <vector>

namespace memoryLineNS
{
	const float MINIMUM_DISTANCE = 2.0f;
	const float MAXIMUM_DISTANCE = 10.0f;
	const float LOST_TIME = 2.0f;
	const float THICKNESS = 3.0f; // ラインの太さ
}


class MemoryLine : public Base
{
	Line* line;							//メモリーラインを描画する線情報(実体ではない)
	InstancingBillboard billboard;		//メモリーラインをビルボードの点で描画する実体
	MemoryPile* joinTarget;				//メモリーラインを形成する元になるメモリーパイルのポインタ情報
	Player* joinPlayer;					//メモリーラインを生成したプレイヤーへのポインタ情報
	D3DXVECTOR3** pointList;			//メモリーパイルごとのメモリーラインを形成する描画する点の位置リスト
	D3DXVECTOR3* renderList;			//メモリーライン全体の描画リスト（インスタンスビルボードが要する位置リストは一つ）
	bool initialized;					//初期化フラグ（メモリーアクセスエラー防止）
	bool disconnected;					//切断フラグ（切断されると、消失処理へ移行する）
	float lostTime;						//消失処理用タイマー
	int pileNum;						//メモリーパイルの最大数（非アクティブを含む）
	int* pointNum;						//各メモリーパイルを始点とするメモリーライン上の点の数のリスト
	int renderNum;						//メモリーライン全体の描画数
public:
	MemoryLine();
	~MemoryLine();

	void initialize(LPDIRECT3DDEVICE9 device, MemoryPile* memoryPile, int num, Player* player, 
		LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void unInitialize();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void update(LPDIRECT3DDEVICE9 device, float frameTime);
	//衝突検知
	bool collision(D3DXVECTOR3 position);

	float calculationDistance(D3DXVECTOR3 point);	//(演算)ある点とラインとの距離を戻す
	void setLine(LPDIRECT3DDEVICE9 device);			//(更新)メモリーパイルの間のラインを設定する
	void lost(float frameTime);						//(更新)消失処理
	void disconnect();								//(切替)切断処理
};