//===================================================================================================================================
//【MemoryLine.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/04
//===================================================================================================================================
#include "MemoryLine.h"
#include "UtilityFunction.h"
using namespace memoryLineNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
MemoryLine::MemoryLine()
{
	line = NULL;
	joinTarget = NULL;
	joinPlayer = NULL;
	pointList = NULL;
	renderList = NULL;

	disconnected = false;
	lostTime = 0;

	initialized = false;
	
	pileNum = 0;
	pointNum = NULL;
	renderNum = 0;
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
MemoryLine::~MemoryLine()
{
	SAFE_DELETE_ARRAY(line);
	SAFE_DELETE_ARRAY(pointList);
	SAFE_DELETE_ARRAY(renderList);
	SAFE_DELETE_ARRAY(pointNum);
}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
void MemoryLine::initialize(LPDIRECT3DDEVICE9 device, MemoryPile* memoryPile, int num, Object* player
	,LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture)
{
	pileNum = num;
	line = new Line[num];
	for (int i = 0; i < pileNum; i++)
	{
		line[i].start = D3DXVECTOR3(0,0,0);
		line[i].end = D3DXVECTOR3(0, 0, 0);
	}
	pointList = new D3DXVECTOR3*[pileNum];

	//pointList[0] = new D3DXVECTOR3[pileNum];
	//pointList[0][0] = D3DXVECTOR3(0,0,0);

	pointNum = new int[pileNum];

	//ラインの元となるメモリーパイルのセット
	joinTarget = memoryPile;
	//メモリーパイルを設置するプレイヤー
	joinPlayer = player;
	
	setLine(device);
	billboard.initialize(device,effect,texture);

	initialized = true;
}

//===================================================================================================================================
//【終了処理】
//===================================================================================================================================
void MemoryLine::unInitialize()
{

}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void MemoryLine::update(LPDIRECT3DDEVICE9 device, float frameTime)
{
	if (initialized == false)return;			//初期化済みでなければ終了

	if (disconnected) {
		lost(frameTime);
	}
	else {
		setLine(device);
	}
}

//===================================================================================================================================
//【描画】
//===================================================================================================================================
void MemoryLine::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	if (initialized == false)return;			//初期化済みでなければ終了
	billboard.render(device, view, projection, cameraPosition);
}

//===================================================================================================================================
//【描画ラインの設定】
//メモリーパイルのアクティブ状況に応じて変動
//===================================================================================================================================
void MemoryLine::setLine(LPDIRECT3DDEVICE9 device)
{
	renderNum = 0;//全体で描画する点の数を0とする。
	//描画ラインの設定
	for (int i = 0; i < pileNum; i++)
	{
		pointNum[i] = 0;//ライン上の点の描画数を0にする
		{//メモリーラインの始点位置と終点位置を設定する
			if (joinTarget[i].getActive())
			{//[条件判定]接続元メモリーパイルのアクティブ
				line[i].start = *joinTarget[i].getPosition();//接続元をメモリーラインの始点にする
				//次のメモリーパイルの要素数
				int k = UtilityFunction::wrap(i+1,0,pileNum);
				//次のメモリーラインが
				if (joinTarget[k].getActive())
				{//メモリーラインの終点＝次のメモリーライン
					line[i].end = *joinTarget[k].getPosition();
				}
				else 
				{//メモリーラインの終点＝プレイヤー
					line[i].end = *joinPlayer->getPosition();

				}
			}
		}

		float length = D3DXVec3Length(&(line[i].end - line[i].start));//ラインの長さを算出
		pointNum[i] = (int)(length / 1.0f);//ラインの描画点数を確定
		renderNum += pointNum[i];//全体合計点数へ加算
		if (pointNum[i] <= 0)continue;//描画する点が0以下ならば次のメモリーラインへ
		pointList[i] = new D3DXVECTOR3[pointNum[i]];//描画する点の位置情報を新たに生成
		for (int n = 0; n < pointNum[i]; n++)
		{
			//ラインをもとに補間係数を用いて位置情報を作成する。
			//補間係数=描画番号n/全体描画数
			D3DXVec3Lerp(&pointList[i][n], &line[i].start, &line[i].end, (float)(n+1) / (float)pointNum[i]);
		}
	}

	
	if (renderNum > 0)
	{
		renderList = new D3DXVECTOR3[renderNum];
		{//pointListを用いてrenderListへ値を設定する
			int j = 0;
			int k = 0;
			for (int i = 0; i < renderNum; i++)
			{
				renderList[i] = pointList[j][k];
				k++;
				if (k > pointNum[j]) {
					k = 0;
					j++;
				}
			}
		}
		//インスタンスビルボードの描画数と描画位置情報の設定
		billboard.setNumOfRender(device, renderNum, renderList);
		for (int i = 0; i < pileNum; i++)
		{
			if (pointNum[i] <= 0)continue;//描画数が0以下であればスキップ
			delete[]pointList[i];//描画する点のリストの削除
		}
	}

	SAFE_DELETE_ARRAY(renderList);//全体のメモリーラインの点の位置情報リストを削除
}

//===================================================================================================================================
//【切断】
//===================================================================================================================================
void MemoryLine::disconnect()
{
	disconnected = true;
}

//===================================================================================================================================
//【消失】
//===================================================================================================================================
void MemoryLine::lost(float frameTime)
{
	if (!disconnected)return;
	lostTime += frameTime;

	if (lostTime > LOST_TIME)
	{
		disconnected = false;
		renderNum = 0;//全体で描画する点の数を0とする。
		for (int i = 0; i < pileNum; i++)
		{
			line[i].start = D3DXVECTOR3(0, 0, 0);
			line[i].end = D3DXVECTOR3(0, 0, 0);
			//if (pointNum[i] > 0)delete[] pointList[i];
			pointNum[i] = 0;//ライン上の点の描画数を0にする
		}
		billboard.setNumOfRender(NULL, 0, renderList);
	}
}

//===================================================================================================================================
//【距離計算】
//===================================================================================================================================
float MemoryLine::calculationDistance(D3DXVECTOR3 point)
{
	float result = THICKNESS;
	for (int i = 0; i < pileNum; i++)
	{
		if (!joinTarget[i].getActive())continue;//接続元がアクティブでない場合スキップ
		
		D3DXVECTOR3 nearPoint = nearestPointOnLine(line[i].start, line[i].end, point);//ライン上の最も近い点を算出
		float distance = D3DXVec3Length(&(point - nearPoint));//最も近い点との距離を測定する
		
		if (i == 0)result = distance;//0番は必ずアクティブであり、初回に代入する必要がある。
		else result = min(result, distance);//より近い方を代入
	}
	return result;
}

//===================================================================================================================================
//【距離計算】
//（引数１）measurementPosition：測定位置
//（引数２）radius：半径
//===================================================================================================================================
bool MemoryLine::collision(D3DXVECTOR3 measurementPosition,float radius)
{
	if (initialized == false)return false;//初期化されていなければ非衝突
	if (!joinTarget[0].getActive())return false;//メモリーパイルがアクティブでなければ非衝突
	if (calculationDistance(measurementPosition) > THICKNESS)	return false;
	//太さ+対象の半径より近い位置にいた場合衝突
	else return true;
}