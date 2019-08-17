//===================================================================================================================================
//【ShockWave.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/04
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "UtilityFunction.h"

namespace shockWaveNS
{
	const int VERTEX_NUM = 24;
	const int POLYGON_NUM = VERTEX_NUM*2;
	const float EXISTENCE_TIME = 2.0f;
	const float HEIGHT = 7.0f;
}

class ShockWave :public Base
{
private:
	LPDIRECT3DDEVICE9 device;								//directX9デバイス
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;					//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 uvBuffer;						//ＵＶバッファ
	LPDIRECT3DINDEXBUFFER9 indexBuffer;						//インデックスバッファ
	IDirect3DVertexDeclaration9* declation;					//頂点宣言
	LPDIRECT3DTEXTURE9 texture;								//テクスチャ
	LPD3DXEFFECT effect;									//シェーダーエフェクト

	utility::Polar3D initialPolar;							//初期極座標
	utility::Polar3D topPolar[shockWaveNS::VERTEX_NUM];		//上部極座標
	utility::Polar3D bottomPolar[shockWaveNS::VERTEX_NUM];	//下部極座標

	D3DXVECTOR3 topVertex[shockWaveNS::VERTEX_NUM];			//上部頂点座標
	D3DXVECTOR3 bottomVertex[shockWaveNS::VERTEX_NUM];		//下部頂点座標
	D3DXVECTOR2 topUV[shockWaveNS::VERTEX_NUM+1];			//上部ＵＶ座標
	D3DXVECTOR2 bottomUV[shockWaveNS::VERTEX_NUM+1];		//下部ＵＶ座標

	float height[shockWaveNS::VERTEX_NUM];					//下部から上部への高さ
	float existenceTimer;									//存在時間
	float deltaTheta;										//θ増加量



public:
	//Method
	ShockWave();
	~ShockWave();

	//processing
	void initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 initialPosition, float radius, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect);
	void createUVBuffer();
	void createVertexBuffer();
	void createIndexBuffer();
	void updateVertexCoord();
	void update(float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);

	//getter
	bool whetherActive();
};
