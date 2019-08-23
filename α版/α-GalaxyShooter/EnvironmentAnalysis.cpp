//-----------------------------------------------------------------------------
// 環境解析処理 [EnvironmentAnalysis.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "EnvironmentAnalysis.h"
#include "AgentAI.h"
#include "Map.h"

//=============================================================================
// コンストラクタ
//=============================================================================
EnvironmentAnalysis::EnvironmentAnalysis(std::vector<Wasuremono*>* _wasuremono): wasuremono(_wasuremono)
{
	recursionSphere = NULL;
}


//=============================================================================
// デストラクタ
//=============================================================================
EnvironmentAnalysis::~EnvironmentAnalysis(void)
{
	SAFE_DELETE(recursionSphere)
}


//=============================================================================
// 初期化処理
//=============================================================================
void EnvironmentAnalysis::initialize(void)
{
	mapTimeCount = 0;
	forgettingTimeMap = 0;
	bulletTimeCount = 0;
	forgettingTimeBullet = 0;
}


//=============================================================================
// 終了処理
//=============================================================================
void EnvironmentAnalysis::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void EnvironmentAnalysis::update(AgentAI* agentAI)
{
	//static int cnt = 0;// ●仮
	//if (++cnt % 10 == 0)
	//{
	//	cnt = 0;
	//	virtualRecursion(agentAI);
	//}

	forgetMemorizedMatter();
}


//=============================================================================
// 仮想リカージョン
//=============================================================================
void EnvironmentAnalysis::virtualRecursion(AgentAI* agentAI)
{
	static const int NUM_NEARLEST_NODE = 3;					// リカージョン範囲を調べるマップノードの候補数
	static const int NUM_TEST_SIZE = 3;						// リカージョンの大きさ（BSのサイズ）の数
	static const int NUM_TEST_ARROUND = 5;					// １つのノードの周囲でBSを当てる箇所の数
	static const int NUM_TEST_ZONE = NUM_TEST_ARROUND + 1;	
	static const int NUM_TEMP_RECOGNITION = NUM_NEARLEST_NODE * NUM_TEST_SIZE* NUM_TEST_ZONE;

	// 以下の処理でベクトルをいろいろ回転させるのに使用
	D3DXQUATERNION quaternion;
	D3DXQuaternionIdentity(&quaternion);
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

	//------------------------------
	// 近いマップノードで候補を絞る
	//------------------------------
	std::list<MapNode*> nodeList = recognitionBB->getMemorizedMap();
	std::list<MapNode*>::iterator itr;
	float shortestLen = 1000.0f;
	std::list<MapNode*>::iterator nearestNode[NUM_NEARLEST_NODE]; // イテレータ配列
	int element = 0;		// イテレータ配列index
	int numNearestNode = 0;	// イテレータ配列がいくつ埋まったかカウント
	for (itr = nodeList.begin(); itr != nodeList.end(); itr++)
	{
		D3DXVECTOR3* nodePosition = (*itr)->getPosition();
		float tempLen = D3DXVec3LengthSq(&(*nodePosition - *agentAI->getPosition()));
		if (tempLen < shortestLen)
		{
			shortestLen = tempLen;
			nearestNode[element] = itr;
			if (++element == NUM_NEARLEST_NODE) element = 0;
			if (++numNearestNode > NUM_NEARLEST_NODE) numNearestNode = NUM_NEARLEST_NODE;
		}
	}

	//------------------------------------------------------------------------
	// 候補のノード付近にサイズを変えながらバウンディングスフィアを当てまくり
	// ワスレモノや想定チンギン額とそのときのスフィアのパラメータを保管する
	//------------------------------------------------------------------------
	RecursionRecognition recursionRecognition[NUM_TEMP_RECOGNITION];	// 保管先
	int index = 0;														// 保管先配列index
	for (int cntNode = 0; cntNode < numNearestNode; cntNode++)
	{
		for (int cntSize = 0; cntSize < NUM_TEST_SIZE; cntSize++)
		{
			// リカージョンチェック用スフィアを生成
			recursionRadius = 10.0f + cntSize * 8.0f;// ←ここは調整 
			recursionSphere = new BoundingSphere;
			recursionSphere->initialize(device, recursionRadius);

			// まずノードの位置ぴったりで衝突判定
			recognizeRecursionArea(agentAI, (*nearestNode[cntNode])->getPosition(), &recursionRecognition[index++]);
			
			// 次にノードの周囲を回しながら衝突判定を行いたいが
			// そのために惑星中心⇔ノード間のレイを少し傾ける
			ray.update(*Map::getField()->getPosition(), *(*nearestNode[cntNode])->getPosition() - *Map::getField()->getPosition());
			D3DXVECTOR3 axisToMakeDegree = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.1f);// ←ここは調整
			D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
			D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);

			// 傾けてあるレイを回転軸で回しながらレイの先端でBSの衝突判定
			D3DXVECTOR3 rotationAxis = *(*nearestNode[cntNode])->getPosition() - *Map::getField()->getPosition();
			D3DXQuaternionIdentity(&quaternion);
			D3DXMatrixIdentity(&worldMatrix);
			for (int cntZone = 0; cntZone < NUM_TEST_ARROUND; cntZone++)
			{
				D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI * 2 / NUM_TEST_ARROUND);
				D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
				D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);
				recognizeRecursionArea(agentAI, &ray.direction, &recursionRecognition[index++]);
			}
			SAFE_DELETE(recursionSphere);
		}
	}
	
	//----------------------------
	// リカージョン認識の数を絞る
	//----------------------------
	int selectionRecognition[NUM_RECURSION_RECOGNITION] = { 0 };
	float largestWeight = 0.0f;
	int selectionIndex = 0;
	for (int i = 0; i < NUM_TEMP_RECOGNITION; i++)
	{
		// ファジー理論でどの認識を採用するか重みづけ
		float radiusSizeSmall = fuzzy.reverseGrade(recursionRecognition->radius, 3.0f, 15.0f);
		float littleAmount = fuzzy.reverseGrade(recursionRecognition->totalAmount, 5.0f, 70.0f);
		float demerit = fuzzy.OR(radiusSizeSmall, littleAmount);
		float radiusSizeBig = fuzzy.grade(recursionRecognition->radius, 12.0f, 34.0f);
		float lotAmount = fuzzy.grade(recursionRecognition->totalAmount, 50.0f, 300.0f);
		float merit = fuzzy.OR(radiusSizeBig, lotAmount);
		recursionRecognition->fuzzySelectionWeight = fuzzy.grade(fuzzy.NOT(demerit) + merit, 0.0f, 2.0f);// 最終的な重み

		// 重みの大きい認識から選択していく
		for (int k = 0; k < NUM_RECURSION_RECOGNITION; k++)
		{
			if (recursionRecognition->fuzzySelectionWeight > largestWeight)
			{
				largestWeight = recursionRecognition->fuzzySelectionWeight;
				selectionRecognition[selectionIndex] = i;
				if (selectionIndex++ >= NUM_RECURSION_RECOGNITION) element = 0;
			}
		}
	}

	//------------------------------------
	// メモリーパイルを打ち込む座標を作る
	//------------------------------------
	// アルゴリズム考案中
	// 今は思いつかないのでとりあえず正五角形にしとく
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		// 弧度法では中心角 = 弦長÷半径
		float angle = recursionRecognition[selectionRecognition[i]].radius / Map::getField()->getRadius();

		// 惑星中心⇔リカージョン認識中心座標のレイを求めた中心角分だけ傾ける
		D3DXQuaternionIdentity(&quaternion);
		D3DXMatrixIdentity(&worldMatrix);
		D3DXVECTOR3 axisForTilt = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXQuaternionRotationAxis(&quaternion, &axisForTilt, angle);
		ray.update(*Map::getField()->getPosition(),
			recursionRecognition[selectionRecognition[i]].center - *Map::getField()->getPosition());
		D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
		D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);

		// 傾けてあるレイを回転軸で回しながらレイの先端の座標をパイルを打つ座標として記録する
		D3DXQuaternionIdentity(&quaternion);
		D3DXMatrixIdentity(&worldMatrix);
		D3DXVECTOR3 rotationAxis = recursionRecognition[selectionRecognition[i]].center - *Map::getField()->getPosition();
		D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI * 2 / 5/*パイルの数だから5*/);
		D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
		for (int k = 0; k < 5; k++)
		{
			D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);
			recursionRecognition[selectionRecognition[i]].pilePosition[k] = ray.direction;
		}
	}

	// 環境認識ブラックボードにフィードバック
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		recognitionBB->getRecursionRecognition()[i] = recursionRecognition[selectionRecognition[i]];
	}
}


//=============================================================================
// リカージョン認識への代入（スフィアとワスレモノの衝突判定が主）
//=============================================================================
void EnvironmentAnalysis::recognizeRecursionArea(AgentAI* agentAI, D3DXVECTOR3* checkPosition, RecursionRecognition* recursionRecognition)
{
	recursionRecognition->center = *checkPosition;
	recursionRecognition->totalHit = 0;
	recursionRecognition->totalAmount = 0;
	recursionRecognition->radius = recursionSphere->getRadius();

	D3DXMATRIX recursionWorldMatrix;
	D3DXMatrixIdentity(&recursionWorldMatrix);
	D3DXMatrixTranslation(&recursionWorldMatrix, checkPosition->x, checkPosition->y, checkPosition->z);

	// フィールド半径の二乗
	float radius2 = Map::getField()->getRadius() * Map::getField()->getRadius();

	// バウンディングスフィアとワスレモノの衝突判定
	for (size_t i = 0; i < wasuremono->size(); i++)
	{
		// 自分の反対側の半球にあるワスレモノは飛ばしてちょっと高速化
		D3DXVECTOR3 vec = *(*wasuremono)[i]->getPosition() - *agentAI->getPosition();
		float len = D3DXVec3LengthSq(&vec);
		if (len > radius2/*三平方の定理*/) { continue; }

		if (recursionSphere->collide(*(*wasuremono)[i]->getPosition(),
			(*wasuremono)[i]->getRadius(), recursionWorldMatrix, *(*wasuremono)[i]->getMatrixWorld()))
		{
			recursionRecognition->totalHit++;
			recursionRecognition->totalAmount += (float)(*wasuremono)[i]->getAmount();
			recursionRecognition->wasuremonoInArea.push_back((*wasuremono)[i]);
		}
	}
}


//=============================================================================
// 記憶事項を忘却
//=============================================================================
void EnvironmentAnalysis::forgetMemorizedMatter(void)
{
	if (recognitionBB->getMemorizedMap().size() != 0)
	{
		mapTimeCount++;
		forgettingTimeMap = 60/*FPS*/ * 15/*秒*/ / recognitionBB->getMemorizedMap().size();
		if (mapTimeCount > forgettingTimeMap)
		{
			recognitionBB->getMemorizedMap().pop_front();
			mapTimeCount = 0;
		}
	}

	if (recognitionBB->getMemorizedBullet().size() != 0)
	{
		bulletTimeCount++;
		forgettingTimeBullet = 60/*FPS*/ * 4/*秒*/ / recognitionBB->getMemorizedBullet().size();
		if (bulletTimeCount > forgettingTimeBullet)
		{
			recognitionBB->getMemorizedBullet().pop_front();
			bulletTimeCount = 0;
		}
	}
}

