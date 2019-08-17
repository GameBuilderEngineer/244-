//===================================================================================================================================
//【Recursion.h】
// 作成者：HAL東京GP12A332 11 菅野 樹
// 作成日：2019/07/17
// 更新日：2019/08/05
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "BoundingSphere.h"

namespace recursionNS
{
	const float EXISTENCE_TIME = 3.0f;
}

class Recursion:public Base
{
private:
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;		//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 uvBuffer;			//ＵＶバッファ
	LPDIRECT3DINDEXBUFFER9 indexBuffer;			//インデックスバッファ
	LPDIRECT3DVERTEXDECLARATION9 declation;		//頂点宣言
	LPDIRECT3DTEXTURE9 texture;					//テクスチャ
	LPD3DXEFFECT effect;						//シェーダーエフェクト

	D3DXVECTOR3 weightCenter;					//重心
	BoundingSphere boundingSphere;				//おおよその衝突検知用範囲（高速化＆誤った衝突検知防止）
	D3DMATRIX worldMatrix;						//重心をもとにしたワールド行列
	D3DXVECTOR3* vertexArray;					//リカージョンが構成されるメモリーパイル位置

	bool onRender;								//描画フラグ
	float existenceTimer;						//存在時間

public:
	Recursion();
	~Recursion();

	//processing
	HRESULT initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3* vertexArray,LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void update(float frameTime);

	//================================================================
	//【重心位置の算出】
	//vertex	：メモリーパイルの頂点位置配列ポインタ
	//vertexNum	：頂点の数
	//================================================================
	void calculationCenter(D3DXVECTOR3* vertex, int vertexNum);

	//================================================================
	//【リカージョンとの衝突検知関数】
	//targetPosition：リカージョンを構成するポリゴンとの衝突判定する位置
	//targetCenter	：対象オブジェクトの球コリジョンの中心位置
	//targetRadius	：対象オブジェクトの球コリジョンの半径
	//targetMatrix	：対象オブジェクトのワールド行列
	//================================================================
	bool collide(D3DXVECTOR3 targetPosition, D3DXVECTOR3 targetCenter, float targetRadius, D3DXMATRIX targetMatrix);


};