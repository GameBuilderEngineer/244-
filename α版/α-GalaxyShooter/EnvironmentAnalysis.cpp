//-----------------------------------------------------------------------------
// 環境解析処理 [EnvironmentAnalysis.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/19
//-----------------------------------------------------------------------------
#include "EnvironmentAnalysis.h"
#include "AgentAI.h"
#include "Map.h"
using namespace EnvilonmentAnalysisNs;

//----------------
// ビルドスイッチ
//----------------
#ifdef _DEBUG
#if 1
#define DUMP_RECUASION_AREA		// リカージョンエリアデータをダンプする
static FILE* fp = NULL;
static int areaLabel = 0;
#endif 

#if 1
#define DUMP_FUZZY_RECOGNITION	// リカージョン認識の数を絞るファジーデータをエリア別にダンプする
static FILE* fp2 = NULL;
static int	areaLabel2 = 0;
#endif

#if 1	// デバッグ描画する場合は1（更新処理を描画処理で実行することになるので注意）					
#define AI_RENDER_MODE
#endif

// デバッグ描画が有効の場合
#ifdef AI_RENDER_MODE

#if 0
#define RENDER_RECUASION_AREA	// リカージョンエリア検出スフィアを描画する
static BoundingSphere spherePoint;
#endif

#if 0
#define RENDER_PILE_POINT		// パイル設置座標を描画する
static LPD3DXMESH pilePoint = NULL;
static D3DMATERIAL9 pointMat;
#endif

#endif// AI_RENDER_MODE
#endif// _DEBUG


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

#ifdef RENDER_RECUASION_AREA
	spherePoint.initialize(device, 1.0f);
#endif

#ifdef RENDER_PILE_POINT
	D3DXCreateSphere(device, 1.0f, 5, 5, &pilePoint, NULL);
	// ノードの表示マーク用メッシュのマテリアル
	// ライトは切るのでDiffuse, Ambientは不透明だけでよい
	pointMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Emissive = { 1.0f, 0.0f, 1.0f, 1.0f };
#endif
}


//=============================================================================
// 終了処理
//=============================================================================
void EnvironmentAnalysis::uninitialize(void)
{
#ifdef RENDER_RECUASION_AREA
	SAFE_DELETE(recursionSphere)
#endif
}


//=============================================================================
// 更新処理
//=============================================================================
void EnvironmentAnalysis::update(AgentAI* agentAI)
{
#ifdef AI_RENDER_MODE
	return;
#endif //AI_RENDER_MODE


	static int cnt = 0;// ●仮
	if (++cnt % 10 == 0)
	{
		cnt = 0;
		virtualRecursion(agentAI);// 仮想リカージョン

	}

	forgetMemorizedMatter();		// 記憶事項を忘却
}


//=============================================================================
// 仮想リカージョン
//=============================================================================
void EnvironmentAnalysis::virtualRecursion(AgentAI* agentAI)
{
	// 近いマップノードで候補を絞る
	MapNode* nearestNode[NUM_NEARLEST_NODE] = { NULL };
	int numNearestNode = 0;
	selectMapNode(nearestNode, &numNearestNode, agentAI);
	if (numNearestNode == 0) { return; }

	//リカージョンする場所を決めるための衝突判定
	RecursionRecognition* recursionRecognition = new RecursionRecognition[numNearestNode * NUM_TEST_CASES_PER_NODE];
	checkRecursionArea(recursionRecognition, nearestNode, numNearestNode, agentAI);

	// リカージョン認識の数を絞る
	int selectionRecognition[NUM_RECURSION_RECOGNITION] = { 0 };
	selectRecursionArea(selectionRecognition, recursionRecognition, nearestNode, numNearestNode, agentAI);

	// メモリーパイルを打ち込む座標を作る
	makeCoordForPile(selectionRecognition, recursionRecognition, agentAI);

	// 環境認識ブラックボードにフィードバック
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		recognitionBB->getRecursionRecognition()[i] = recursionRecognition[selectionRecognition[i]];
	}

	SAFE_DELETE_ARRAY(recursionRecognition)
}


//=============================================================================
//（仮想リカージョンステップその１）近いマップノードで候補を絞る
//=============================================================================
void EnvironmentAnalysis::selectMapNode(
	MapNode* nearestNode[],				// 最寄りマップノードポインタ配列を返す
	int* numNearestNode,				// 候補をいくつ見つけたか（=ポインタ配列の要素数）を返す　
	AgentAI* agentAI)
{
	std::list<MapNode*> nodeList = recognitionBB->getMemorizedMap();
	std::list<MapNode*>::iterator itr;
	float shortestLen = 1000.0f;
	int index = 0;

	for (itr = nodeList.begin(); itr != nodeList.end(); itr++)
	{
		D3DXVECTOR3* nodePosition = (*itr)->getPosition();
		float tempLen = D3DXVec3LengthSq(&(*nodePosition - *agentAI->getPosition()));
		if (tempLen < shortestLen)
		{
			shortestLen = tempLen;
			nearestNode[index] = (*itr)->getPointer();
			if (++index == NUM_NEARLEST_NODE) index = 0;
			if (++(*numNearestNode) > NUM_NEARLEST_NODE) *numNearestNode = NUM_NEARLEST_NODE;
		}
	}
}


//=============================================================================
//（仮想リカージョンステップその２）リカージョンする場所を決めるための衝突判定
//=============================================================================
void EnvironmentAnalysis::checkRecursionArea(
	RecursionRecognition recursionRecognition[],	// 認識保管配列
	MapNode* nearestNode[],							// 最寄りマップノードポインタ配列
	int numNearestNode,								// ポインタ配列の要素数
	AgentAI* agentAI)
{
	D3DXQUATERNION quaternion;
	D3DXQuaternionIdentity(&quaternion);
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

#ifdef DUMP_RECUASION_AREA
	areaLabel = 0;
	setDataDirectory();
	fp = fopen("DumpRecuasionArea.txt", "w");
	fprintf(fp, "リカージョンエリアデータ\n出力元：EnvironmentAnalysis.cpp/recognizeRecursionArea()\n");
#endif// DUMP_RECUASION_AREA

	// 候補のノード付近にサイズを変えながらバウンディングスフィアを当てまくり
	// ワスレモノや想定チンギン額とそのときのスフィアのパラメータを保管する
	int index = 0;
	for (int cntNode = 0; cntNode < numNearestNode; cntNode++)
	{
		for (int cntSize = 0; cntSize < NUM_TEST_SIZE; cntSize++)
		{
			// リカージョンチェック用スフィアを生成
			recursionRadius = 15.0f + cntSize * 10.0f;// ←ここは調整（これがBS自体の半径）
			recursionSphere = new BoundingSphere;
			recursionSphere->initialize(device, recursionRadius);

			// まずノードの位置ぴったりで衝突判定
			recognizeRecursionArea(agentAI, nearestNode[cntNode]->getPosition(), &recursionRecognition[index++]);

			// 次にノードの周囲を回しながら衝突判定を行いたいが
			// そのために惑星中心⇔ノード間のレイを少し傾ける
			ray.update(*Map::getField()->getPosition(), *nearestNode[cntNode]->getPosition() - *Map::getField()->getPosition());
			D3DXVECTOR3 axisToMakeDegree = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			switch (cntSize)
			{// 傾く角度をスフィアサイズによって変える
			case 0:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.22f);
				break;
			case 1:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.3f);
				break;
			case 2:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, 0.42f);
				break;
			}
			D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
			D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);

			// 傾けてあるレイを回転軸で回しながらレイの先端でBSの衝突判定
			D3DXVECTOR3 rotationAxis = *nearestNode[cntNode]->getPosition() - *Map::getField()->getPosition();
			D3DXQuaternionIdentity(&quaternion);
			D3DXMatrixIdentity(&worldMatrix);
			for (int cntZone = 0; cntZone < NUM_TEST_ARROUND; cntZone++)
			{
				D3DXQuaternionRotationAxis(&quaternion, &rotationAxis, D3DX_PI * 2 / NUM_TEST_ARROUND);
				D3DXMatrixRotationQuaternion(&worldMatrix, &quaternion);
				D3DXVec3TransformCoord(&ray.direction, &ray.direction, &worldMatrix);
				recognizeRecursionArea(agentAI, &ray.direction, &recursionRecognition[index++]);
			}
			recursionSphere->getMesh()->Release();
			SAFE_DELETE(recursionSphere);
		}
	}

#ifdef DUMP_RECUASION_AREA
	fclose(fp);
#endif// DUMP_RECUASION_AREA
}


//=============================================================================
//（仮想リカージョンステップその３）リカージョン認識の数を絞る
//=============================================================================
void EnvironmentAnalysis::selectRecursionArea(
	int selectionRecognition[],
	RecursionRecognition recursionRecognition[],	// 認識保管配列
	MapNode* nearestNode[],							// 最寄りマップノードポインタ配列
	int numNearestNode,								// ポインタ配列の要素数
	AgentAI* agentAI)
{
	float largestWeight = 0.0f;
	int selectionIndex = 0;

#ifdef DUMP_FUZZY_RECOGNITION
	areaLabel2 = 0;
	setDataDirectory();
	fp2 = fopen("DumpFuzzyRecognition.txt", "w");
	fprintf(fp2, "リカージョン認識ファジーデータ\n出力元：EnvironmentAnalysis.cpp/selectRecursionArea()\n");
#endif// DUMP_FUZZY_RECOGNITION

	for (int i = 0; i < numNearestNode * NUM_TEST_CASES_PER_NODE; i++)
	{
		// ファジー理論でどの認識を採用するか重みづけ
		float radiusSizeBig = fuzzy.grade(recursionRecognition[i].radius, 15.0f, 35.0f);
		float littleAmount = fuzzy.reverseGrade(recursionRecognition[i].totalAmount, 5.0f, 70.0f);
		float demerit = fuzzy.OR(radiusSizeBig, littleAmount);

		float radiusSizeSmall = fuzzy.reverseGrade(recursionRecognition[i].radius, 15.0f, 25.0f);
		float lotAmount = fuzzy.grade(recursionRecognition[i].totalAmount, 50.0f, 300.0f);
		float merit = fuzzy.OR(radiusSizeSmall, lotAmount);

		recursionRecognition[i].fuzzySelectionWeight = fuzzy.grade(fuzzy.NOT(demerit) + merit, 0.0f, 2.0f);// 最終的な重み

		// 重みの大きい認識から選択していく
		for (int k = 0; k < NUM_RECURSION_RECOGNITION; k++)
		{
			if (recursionRecognition[i].fuzzySelectionWeight > largestWeight)
			{
				largestWeight = recursionRecognition[i].fuzzySelectionWeight;
				selectionRecognition[selectionIndex] = i;
				if (++selectionIndex >= NUM_RECURSION_RECOGNITION) selectionIndex = 0;
			}
		}

#ifdef DUMP_FUZZY_RECOGNITION
		fprintf(fp2, "%d\n", areaLabel2++);
		fprintf(fp2, "radiusSizeSmall = %.3f\n", radiusSizeSmall);
		fprintf(fp2, "littleAmount = %.3f\n", littleAmount);
		fprintf(fp2, "demerit = %.3f\n", demerit);
		fprintf(fp2, "radiusSizeBig = %.3f\n", radiusSizeBig);
		fprintf(fp2, "lotAmount = %.3f\n", lotAmount);
		fprintf(fp2, "merit = %.3f\n\n", merit);
#endif// DUMP_FUZZY_RECOGNITION
	}

#ifdef DUMP_FUZZY_RECOGNITION
	fclose(fp2);
#endif// DUMP_FUZZY_RECOGNITION
}


//=============================================================================
//（仮想リカージョンステップその４）メモリーパイルを打ち込む座標を作る
//=============================================================================
void EnvironmentAnalysis::makeCoordForPile(int selectionRecognition[], RecursionRecognition recursionRecognition[], AgentAI* agentAI)
{
	D3DXQUATERNION quaternion;
	D3DXQuaternionIdentity(&quaternion);
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);

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

#ifdef RENDER_PILE_POINT
			static D3DXMATRIX pointWorldMatrix;
			D3DXMatrixIdentity(&pointWorldMatrix);
			D3DXMatrixTranslation(&pointWorldMatrix, ray.direction.x, ray.direction.y, ray.direction.z);
			D3DMATERIAL9 matDef;
			device->GetMaterial(&matDef);
			device->LightEnable(0, false);
			device->SetMaterial(&pointMat);
			device->SetTransform(D3DTS_WORLD, &pointWorldMatrix);
			pilePoint->DrawSubset(0);
			device->LightEnable(0, true);
			device->SetMaterial(&matDef);
#endif// RENDER_PILE_POINT
		}
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

	// バウンディングスフィア用ワールドマトリクス作成
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

		if (recursionSphere->collide((*wasuremono)[i]->bodyCollide.getCenter(),
			(*wasuremono)[i]->bodyCollide.getRadius(), recursionWorldMatrix, *(*wasuremono)[i]->getMatrixWorld()))
		{
			recursionRecognition->totalHit++;
			recursionRecognition->totalAmount += (float)(*wasuremono)[i]->getAmount();
			recursionRecognition->wasuremonoInArea.push_back((*wasuremono)[i]);	
		}
	}

#ifdef DUMP_RECUASION_AREA
	fprintf(fp, "%d\n", areaLabel++);
	fprintf(fp, "recursionRecognition->center = (%.2f, %.2f,%.2f) \n",
		recursionRecognition->center.x, recursionRecognition->center.y, recursionRecognition->center.z);
	fprintf(fp, "recursionRecognition->totalHit = %d\n", (int)recursionRecognition->totalHit);
	fprintf(fp, "recursionRecognition->totalAmount = %d\n", (int)recursionRecognition->totalAmount);
	fprintf(fp, "recursionRecognition->radius = %.2f\n", recursionRecognition->radius);
#endif// DUMP_RECUASION_AREA

#ifdef RENDER_RECUASION_AREA
	if (recursionRecognition->radius == 35.0f)
	{
		spherePoint.render(device, recursionWorldMatrix);	// スフィア座標の描画
	}
	BoundingSphere bs;
	bs.initialize(device, 35.0f);
	bs.render(device, recursionWorldMatrix);				// サイズ調整用のスフィア描画
	bs.getMesh()->Release();
#endif
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


//=============================================================================
// デバッグ描画処理
//=============================================================================
void  EnvironmentAnalysis::debugRender(AgentAI* agentAI)
{
	// 更新処理が描画時にコールされるようになる
#ifdef AI_RENDER_MODE
	//static int cnt = 0;// ●仮
	//if (++cnt % 5 == 0)
	//{
	//	cnt = 0;
		virtualRecursion(agentAI);// 仮想リカージョン

	//}

	forgetMemorizedMatter();		// 記憶事項を忘却

#endif
}

