//===================================================================================================================================
//【ShockWave.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/08/07
// [更新日]2019/09/02
//===================================================================================================================================
#include "ShockWave.h"
using namespace shockWaveNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
ShockWave::ShockWave()
{
	ZeroMemory(this, sizeof(ShockWave));
	existenceTimer = 0.0f;
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
ShockWave::~ShockWave()
{

}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
void ShockWave::initialize(LPDIRECT3DDEVICE9 device,D3DXVECTOR3 initialPosition,float radius, LPDIRECT3DTEXTURE9 _texture, LPD3DXEFFECT _effect)
{
	//テクスチャをセット
	texture = _texture;

	//シェーダーをセット
	effect = _effect;

	this->device = device;
	existenceTimer = 0.0f;
	//初期極座標を初期直交座標から算出
	initialPolar = UtilityFunction::fromRectangular3D(initialPosition);
	D3DXVECTOR3 p = UtilityFunction::fromTransformationPolar3D(initialPolar.radius, initialPolar.theta, initialPolar.phi);
	initialPolar.radius = radius;
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		float rate = (float)i / (float)VERTEX_NUM;
		height[i] = HEIGHT+HEIGHT/2*sinf((float)i);
		//動径の設定
		topPolar[i].radius = radius + height[i];
		bottomPolar[i].radius = radius;
		//極角の設定
		topPolar[i].theta =
		bottomPolar[i].theta = 0.0f;
		//偏角の設定
		topPolar[i].phi =
		bottomPolar[i].phi = UtilityFunction::lerp(0,2.0f*D3DX_PI,rate);
	}
	updateVertexCoord();	//極座標から頂点座標を算出
	createVertexBuffer();	//頂点バッファを作成
	createUVBuffer();		//ＵＶバッファを作成
	createIndexBuffer();	//インデックスバッファを作成

	//頂点宣言
	D3DVERTEXELEMENT9 vertexElement[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//頂点座標
		{ 1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//UV
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(vertexElement, &declation);
}

//===================================================================================================================================
//【頂点バッファの作成】
//===================================================================================================================================
void ShockWave::createVertexBuffer()
{
	D3DXVECTOR3 vertex[VERTEX_NUM * 2];
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		vertex[i] = bottomVertex[i];
		vertex[i+VERTEX_NUM] = topVertex[i];
	}
	//頂点バッファの作成
	device->CreateVertexBuffer(sizeof(vertex), 0, 0, D3DPOOL_MANAGED, &vertexBuffer, 0);//サイズ確保
	copyVertexBuffer(sizeof(vertex), &vertex, vertexBuffer);

}

//===================================================================================================================================
//【UVバッファの作成】
//===================================================================================================================================
void ShockWave::createUVBuffer()
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		float rate = (float)i / (float)VERTEX_NUM;
		topUV[i].x =
		bottomUV[i].x = rate;
		topUV[i].y = 0.0f;
		bottomUV[i].y = 1.0f;
	}
	topUV[VERTEX_NUM].x =
	bottomUV[VERTEX_NUM].x = 1.0f;
	topUV[VERTEX_NUM].y = 0.0f;
	bottomUV[VERTEX_NUM].y = 1.0f;
	D3DXVECTOR2 uv[(VERTEX_NUM+1)*2];
	for (int i = 0; i < VERTEX_NUM+1; i++)
	{
		uv[i] = bottomUV[i];
		uv[i + VERTEX_NUM+1] = topUV[i];
	}
	//UVバッファの作成
	device->CreateVertexBuffer(sizeof(uv), 0, 0, D3DPOOL_MANAGED, &uvBuffer, 0);
	copyVertexBuffer(sizeof(uv), &uv, uvBuffer);

}

//===================================================================================================================================
//【インデックスバッファの作成】
//===================================================================================================================================
void ShockWave::createIndexBuffer()
{
	WORD index[POLYGON_NUM*3];
	WORD topNumber[VERTEX_NUM];
	WORD bottomNumber[VERTEX_NUM];
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		topNumber[i] = i+VERTEX_NUM;
		bottomNumber[i] = i;
	}

	for (int i = 0; i < POLYGON_NUM; i++)
	{
		int j = (int)i / 2;
		int k = UtilityFunction::wrap(j + 1, 0, VERTEX_NUM);
		switch (i % 2)
		{
		case 0:
			index[i * 3 + 0] = bottomNumber[k];
			index[i * 3 + 1] = bottomNumber[j];
			index[i * 3 + 2] = topNumber[j];
			break;
		case 1:
			index[i * 3 + 0] = topNumber[j];
			index[i * 3 + 1] = topNumber[k];
			index[i * 3 + 2] = bottomNumber[k];
			break;
		}
	}
	//インデックスバッファの作成
	device->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, 0);
	void* p = 0;
	indexBuffer->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuffer->Unlock();
}

//===================================================================================================================================
//【頂点座標の更新】
//===================================================================================================================================
void ShockWave::updateVertexCoord()
{
	D3DXMATRIX xRotation;
	D3DXMATRIX yRotation;
	D3DXMATRIX rotation;
	D3DXMatrixRotationX(&xRotation, initialPolar.theta);
	D3DXMatrixRotationY(&yRotation, -initialPolar.phi+D3DX_PI/2);
	D3DXMatrixMultiply(&rotation, &xRotation, &yRotation);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		topVertex[i] = UtilityFunction::fromTransformationPolar3D(topPolar[i].radius,topPolar[i].theta,topPolar[i].phi);
		D3DXVec3TransformCoord(&topVertex[i], &topVertex[i], &rotation);
		bottomVertex[i] = UtilityFunction::fromTransformationPolar3D(bottomPolar[i].radius,bottomPolar[i].theta,bottomPolar[i].phi);
		D3DXVec3TransformCoord(&bottomVertex[i], &bottomVertex[i], &rotation);
	}
}
//===================================================================================================================================
//【更新】
//===================================================================================================================================
void ShockWave::update(float frameTime)
{
	if (!whetherActive())return;
	existenceTimer = min(existenceTimer + frameTime,EXISTENCE_TIME);
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		float rate = existenceTimer / EXISTENCE_TIME;
		topPolar[i].theta = 
		bottomPolar[i].theta = UtilityFunction::lerp(0.0f, D3DX_PI, rate);
	}
	updateVertexCoord();
	createVertexBuffer();
}

//===================================================================================================================================
//【描画】
//===================================================================================================================================
void ShockWave::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	// αブレンドを行う
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	// αソースカラーの指定
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// カリングはしない
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//頂点宣言を追加
	device->SetVertexDeclaration(declation);

	//デバイスデータストリームにメッシュの頂点バッファをバインド
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex3D));
	device->SetStreamSource(1, uvBuffer, sizeof(Vertex3D), sizeof(UV));


	//インデックスバッファをセット
	device->SetIndices(indexBuffer);

	//シェーダー操作
	effect->SetTechnique("main");
	effect->SetMatrix("matrixProjection", &projection);
	effect->SetMatrix("matrixView", &view);
	effect->SetTexture("textureDecal", texture);

	effect->Begin(0, 0);
	effect->BeginPass(0);

	//描画
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, VERTEX_NUM, 0, POLYGON_NUM);

	effect->EndPass();
	effect->End();

	//後始末
	// カリングを有効にする
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

//===================================================================================================================================
//【距離計算】
//===================================================================================================================================
float ShockWave::calculationDistance(D3DXVECTOR3 point)
{
	float result = WIDTH;
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		int k = UtilityFunction::wrap(i + 1, 0, VERTEX_NUM);
		Line line;
		line.start	= topVertex[i];
		line.end	= topVertex[k];
		D3DXVECTOR3 nearPoint = nearestPointOnLine(line.start, line.end, point);//ライン上の最も近い点を算出
		float distance = D3DXVec3Length(&(point - nearPoint));//最も近い点との距離を測定する

		if (i == 0)result = distance;//0番は必ずアクティブであり、初回に代入する必要がある。
		else result = min(result, distance);//より近い方を代入
	}
	return result;
}

//===================================================================================================================================
//【衝突判定】
//（引数１）measurementPosition：測定位置
//（引数２）radius：半径
//===================================================================================================================================
bool ShockWave::collision(D3DXVECTOR3 measurementPosition, float radius)
{
	if (calculationDistance(measurementPosition) > shockWaveNS::WIDTH)	return false;
	//太さ+対象の半径より近い位置にいた場合衝突
	else return true;
}

//===================================================================================================================================
//【getter】
//===================================================================================================================================
bool ShockWave::whetherActive(){return existenceTimer < EXISTENCE_TIME;}
