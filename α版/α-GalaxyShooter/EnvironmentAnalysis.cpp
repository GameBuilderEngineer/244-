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
#if 0
#define DUMP_RECUASION_AREA		// リカージョンエリアデータをダンプする
static FILE* fp = NULL;
#endif 

#if 0
#define DUMP_FUZZY_RECOGNITION	// リカージョン認識の数を絞るファジーデータをエリア別にダンプする
static FILE* fp2 = NULL;
#endif

#if 1	// デバッグ描画する場合は1（更新処理を描画処理で実行することになるので注意）					
#define AI_RENDER_MODE
#endif

// デバッグ描画が有効の場合
#ifdef AI_RENDER_MODE

#if 1
#define RENDER_LINE_CUT_POINT	// メモリーライン切断座標を描画する
static LPD3DXMESH cutPoint = NULL;
static D3DMATERIAL9 cutPointMat;
#endif

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

	battleAnalysisFrameCount = 0;
	vRecursionFrameCount = 0;

#ifdef RENDER_RECUASION_AREA
	spherePoint.initialize(device, 1.0f);
#endif

#ifdef RENDER_PILE_POINT
	D3DXCreateSphere(device, 1.0f, 5, 5, &pilePoint, NULL);
	// ノードの表示マーク用メッシュのマテリアル
	// ライトは切るのでDiffuse, Ambientは不透明だけでよい
	pointMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	pointMat.Emissive = { 1.0f, 0.0f, 1.0f, 1.0f };	// 紫
#endif

#ifdef RENDER_LINE_CUT_POINT
	D3DXCreateSphere(device, 1.0f, 5, 5, &cutPoint, NULL);
	// ノードの表示マーク用メッシュのマテリアル
	// ライトは切るのでDiffuse, Ambientは不透明だけでよい
	cutPointMat.Diffuse = { 0.0f, 0.0f, 0.0f, 1.0f };
	cutPointMat.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	cutPointMat.Emissive = { 1.0f, 1.0f, 0.0f, 1.0f };// 黄
#endif
}


//=============================================================================
// 終了処理
//=============================================================================
void EnvironmentAnalysis::uninitialize(void)
{

#ifdef RENDER_PILE_POINT
	SAFE_RELEASE(pilePoint)
#endif
#ifdef RENDER_LINE_CUT_POINT
	SAFE_RELEASE(cutPoint)
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

	if (++battleAnalysisFrameCount % BATTLE_ANALYSIS_FPS/**/)
	{
		analyzeBattle(agentAI);			// バトル状況を解析
		battleAnalysisFrameCount = 0;
	}

	makeCoordForCut(agentAI);			// メモリーライン切断座標を算出

	if (++vRecursionFrameCount % VIRTUAL_RECURSION_FPS == 0)
	{
		virtualRecursion(agentAI);		// 仮想リカージョン
		vRecursionFrameCount = 0;
	}

	forgetMemorizedMatter();			// 記憶事項を忘却
}


//=============================================================================
// バトル状況を解析
//=============================================================================
void EnvironmentAnalysis::analyzeBattle(AgentAI* agentAI)
{
	//------
	// 相手
	//------
	//距離
	// センサーで視界に入ったときの距離で判定
	float opponentNearSet = 
		fuzzy.reverseGrade(recognitionBB->getDistanceBetweenPlayers(), 0.0f, LENGTH_OPPONENT_IS_NEAR);
	if (opponentNearSet > 0.5f/*調整*/)
	{
		recognitionBB->setIsOpponentNear(true);
	}
	else
	{
		recognitionBB->setIsOpponentNear(false);
	}

	// 衝撃波
	recognitionBB->setMayHappenShockWave(false);
	if (recognitionBB->getIsOpponentInCamera())
	{
		if (opponent->getState() == playerNS::SKY || opponent->getState() == playerNS::FALL)
		{
			recognitionBB->setMayHappenShockWave(true);
		}
	}

	//----------------
	// バレットの解析
	//----------------
	std::list<Bullet*> bulletList = recognitionBB->getMemorizedBullet();
	std::list<Bullet*>::iterator itr;
	int cntHostileBullet = 0;				// 敵性バレットの数
	int cntCloseDistanceBullet = 0;			// 敵性至近距離バレットの数	

	for (itr = bulletList.begin(); itr != bulletList.end(); itr++)
	{
		D3DXVECTOR3 vecBulletToAgent;		// バレット⇔自分のベクトル
		D3DXVECTOR3 slipVecBulletToAgent;	// バレット⇔自分の滑りベクトル
		D3DXVECTOR3 slipVecBulletSpeed;		// バレットのスピードの滑りベクトル
		float dintanceToBullet;				// バレットとの距離
		bool isHostile = false;				// 敵性バレットであるか

		// 自分⇔バレットのベクトルを算出し滑りベクトルにして正規化
		vecBulletToAgent = *agentAI->getPosition() - *(*itr)->getPosition();
		dintanceToBullet = D3DXVec3Length(&vecBulletToAgent);	// 長さを保管
		slipVecBulletToAgent = slip(vecBulletToAgent, (*itr)->getAxisY()->direction);
		D3DXVec3Normalize(&slipVecBulletToAgent, &slipVecBulletToAgent);

		// バレットのスピードも滑りベクトルにしてを正規化
		slipVecBulletSpeed = slip((*itr)->getSpeed(), (*itr)->getAxisY()->direction);
		D3DXVec3Normalize(&slipVecBulletSpeed, &slipVecBulletSpeed);

		// 自分の方向に向かってくるなら敵性バレットである
		float dot = D3DXVec3Dot(&slipVecBulletSpeed, &slipVecBulletToAgent);
		float angleDifferenceForHit = acosf(dot);
		if (angleDifferenceForHit < D3DXToRadian(BULLET_TWO_VECTOR_ANGLE_DEGREE))
		{
			isHostile = true;
			cntHostileBullet++;
		}

		// 距離の近い敵性バレットを調べる
		if (isHostile && dintanceToBullet < LENGHT_BULLET_IS_NEAR)
		{
			cntCloseDistanceBullet++;
		}
	}

	// 至近距離の敵性バレットがあるか設定する
	if (cntCloseDistanceBullet > 0)
	{ 
		recognitionBB->setIsBuletNear(true);
	}
	else
	{
		recognitionBB->setIsBuletNear(false);
	}

	float hostileBulletSet = fuzzy.grade((float)cntHostileBullet, 0.0f, 3.0f);


	//----------------
	// 相手の攻撃意欲
	//----------------
	if (fuzzy.OR(opponentNearSet, hostileBulletSet) > 0.65f/*こんなもんか？*/)
	{
		recognitionBB->setIsOpponentOffensive(true);
	}
	else
	{
		recognitionBB->setIsOpponentOffensive(false);
	}


	//----------------
	// 獲得チンギン数
	//----------------
	int wageDifference = agentAI->getWage() - opponent->getWage();
	if (wageDifference < LOSING_WAGE_DEFFERENSE/*相手との差額*/)
	{
		recognitionBB->setIsChinginLow(true);
	}
	else
	{
		recognitionBB->setIsChinginLow(false);
	}
}


//=============================================================================
// メモリーライン切断座標を算出
//=============================================================================
void EnvironmentAnalysis::makeCoordForCut(AgentAI* agentAI)
{
	// メモリーラインが引かれていなければ終了
	if (opponent->getElementMemoryPile() == 0) { return; }
	
	int numPile = opponent->getElementMemoryPile() + 1; // パイルの数（次に打ち込むパイルを加える）
	float length[5 + 1] = { 0.0f };						// パイルとの距離を昇順にソートして格納
	MemoryPile* pile[5 + 1] = { NULL };					// パイルとの距離で昇順にソートしたメモリーパイル
	MemoryPile pileBeforeHitting;						// 次に打ち込むパイル（対戦相手座標を格納）

	//--------------------------------------------
	// 近距離のパイルを取得して近さ順にソートする
	//--------------------------------------------
	for (int i = 0; i < numPile; i++)
	{
		// ５つ打ち切る前は次に打ち込むパイルも加える
		if (i == opponent->getElementMemoryPile() && i != 5/*5本目の次のパイルは無いので*/)
		{
			length[i] = D3DXVec3Length(&(*opponent->getPosition() - *agentAI->getPosition()));
			pileBeforeHitting.setPosition(*opponent->getPosition());
			pileBeforeHitting.getAxisY()->initialize(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), opponent->getAxisY()->direction);
			pile[i] = &pileBeforeHitting;
		}

		// 次に打ち込むパイル以降はパス
		if (i >= opponent->getElementMemoryPile()) { continue; }

		length[i] = D3DXVec3Length(&(*opponent->getMemoryPile()[i].getPosition() - *agentAI->getPosition()));
		pile[i] = &opponent->getMemoryPile()[i];
	}

	// バブルソート
	for (int i = 0; i < numPile - 1; i++)
	{
		for (int k = numPile - 1; k > i; k--)
		{
			if (length[i] > length[k])
			{
				if (pile[i] == NULL || pile[k] == NULL) { continue; }

				float tempLen = length[k];
				MemoryPile* tempPile = pile[k];
				length[k] = length[i];
				pile[k] = pile[i];
				length[i] = tempLen;
				pile[i] = tempPile;
			}
		}
	}

	//------------------------
	// 以下で使用するデータ２
	//------------------------
	D3DXVECTOR3 vecLine0to1;		// 最短パイル⇔第2最短パイルのベクトル（正規化済）
	D3DXVECTOR3 orthogonal0to1;		// このメモリーラインに直交するベクトル（正規化済）
	D3DXVECTOR3 vecLine0to2;		// 最短パイル⇔第3最短パイルのベクトル（正規化済）
	D3DXVECTOR3 orthogonal0to2;		// このメモリーラインに直交するベクトル（正規化済）
	//D3DXVECTOR3 vecLine1to2;		// 第2最短パイル⇔第3最短パイルのベクトル（正規化済）
	//D3DXVECTOR3 orthogonal1to2;		// このメモリーラインに直交するベクトル（正規化済）
	// ベクトルの中身を埋める
	vecLine0to1 = *pile[1]->getPosition() - *pile[0]->getPosition();
	D3DXVec3Normalize(&vecLine0to1, &vecLine0to1);
	D3DXVec3Cross(&orthogonal0to1, &vecLine0to1, &pile[0]->getAxisY()->direction);
	D3DXVec3Normalize(&orthogonal0to1, &orthogonal0to1);
	if (opponent->getElementMemoryPile() > 1/*メモリーラインが2本以上*/)
	{
		vecLine0to2 = *pile[2]->getPosition() - *pile[0]->getPosition();
		D3DXVec3Normalize(&vecLine0to2, &vecLine0to2);
		D3DXVec3Cross(&orthogonal0to2, &vecLine0to2, &pile[0]->getAxisY()->direction);
		D3DXVec3Normalize(&orthogonal0to2, &orthogonal0to2);
		//vecLine1to2 = *pile[2]->getPosition() - *pile[1]->getPosition();
		//D3DXVec3Normalize(&vecLine1to2, &vecLine1to2);
		//D3DXVec3Cross(&orthogonal1to2, &vecLine1to2, &pile[1]->getAxisY()->direction);
		//D3DXVec3Normalize(&orthogonal1to2, &orthogonal1to2);
	}
	D3DXVECTOR3 posLine0to1;		// 最短パイル⇔第2最短パイルのラインを切断する座標
	D3DXVECTOR3 posLine0to2;		// 最短パイル⇔第3最短パイルのラインを切断する座標


	//----------------
	// 座標を算出する
	//----------------
	// ここでやっていること
	// (1)平面の方程式を求めてエージェントの座標との距離を求める
	// (2)距離を利用して平面との交点を求める
	// (3)フィールド座標から交点までのベクトルをフィールド半径まで伸長し座標とする

	{// 最短パイル⇔第2最短パイルのラインを切断する座標を求める
		float d = -(orthogonal0to1.x * pile[0]->getPosition()->x
			+ orthogonal0to1.y * pile[0]->getPosition()->y
			+ orthogonal0to1.z * pile[0]->getPosition()->z);

		float distance = (orthogonal0to1.x * agentAI->getPosition()->x
			+ orthogonal0to1.y * agentAI->getPosition()->y
			+ orthogonal0to1.z * agentAI->getPosition()->z + d);

		D3DXVECTOR3 intersection = (-orthogonal0to1 * distance) + *agentAI->getPosition();
		D3DXVECTOR3 vecFieldToMemoryLine = intersection - *Map::getField()->getPosition();
		D3DXVec3Normalize(&vecFieldToMemoryLine, &vecFieldToMemoryLine);
		posLine0to1 = vecFieldToMemoryLine * Map::getField()->getRadius();
	}

	if(opponent->getElementMemoryPile() > 1/*メモリーラインが2本以上*/)
	{// 最短パイル⇔第3最短パイルのラインを切断する座標を求める
		float d = -(orthogonal0to2.x * pile[0]->getPosition()->x
			+ orthogonal0to2.y * pile[0]->getPosition()->y
			+ orthogonal0to2.z * pile[0]->getPosition()->z);

		float distance = (orthogonal0to2.x * agentAI->getPosition()->x
			+ orthogonal0to2.y * agentAI->getPosition()->y
			+ orthogonal0to2.z * agentAI->getPosition()->z + d);

		D3DXVECTOR3 intersection = (-orthogonal0to2 * distance) + *agentAI->getPosition();
		D3DXVECTOR3 vecFieldToMemoryLine = intersection - *Map::getField()->getPosition();
		D3DXVec3Normalize(&vecFieldToMemoryLine, &vecFieldToMemoryLine);
		posLine0to2 = vecFieldToMemoryLine * Map::getField()->getRadius();
	}


	//----------------
	// 座標を決定する
	//----------------
#define DIFFERENSE_BETWEEN_GROUND	(2.5f)

	D3DXVECTOR3 slipVecPile0ToAgent = slip(
		*agentAI->getPosition() - *pile[0]->getPosition(),
		pile[0]->getReverseAxisY()->direction);
	D3DXVec3Normalize(&slipVecPile0ToAgent, &slipVecPile0ToAgent);
	float radian0and1 = acosf(D3DXVec3Dot(&vecLine0to1, &slipVecPile0ToAgent));
	float radian0and2 = acosf(D3DXVec3Dot(&vecLine0to2, &slipVecPile0ToAgent));


	//if (opponent->getElementMemoryPile() == 1/*メモリーラインが1本のときだけ*/)
	//{
	//	if (radian0and1 < D3DX_PI * 0.5f)
	//	{
	//		recognitionBB->setLineCutCoord(posLine0to1);
	//	}
	//	else
	//	{
	//		recognitionBB->setLineCutCoord(
	//			*pile[0]->getPosition() + pile[0]->getReverseAxisY()->direction * DIFFERENSE_BETWEEN_GROUND);
	//	}
	//}


		// エージェント⇔最短パイルのベクトルがパイル同士のベクトル２つに対して
		// どの程度角度が開いているかにより座標を３つから選択する
		if (radian0and1 > D3DX_PI * 0.5f && radian0and2 > D3DX_PI * 0.5f)
		{// 両方のベクトルに対し鈍角
			recognitionBB->setLineCutCoord(
				*pile[0]->getPosition() + pile[0]->getReverseAxisY()->direction * DIFFERENSE_BETWEEN_GROUND);
		}
		else if (radian0and1 < D3DX_PI * 0.5f)
		{
			recognitionBB->setLineCutCoord(posLine0to1);
		}
		else if (radian0and2 < D3DX_PI * 0.5f)
		{
			recognitionBB->setLineCutCoord(posLine0to2);
		}


#ifdef RENDER_LINE_CUT_POINT
	D3DXMATRIX pointWorldMatrix;
	D3DXMatrixIdentity(&pointWorldMatrix);
	//D3DXMatrixTranslation(&pointWorldMatrix,
	//	pile[0]->getPosition()->x,
	//	pile[0]->getPosition()->y,
	//	pile[0]->getPosition()->z);
	D3DXMatrixTranslation(&pointWorldMatrix,
		recognitionBB->getLineCutCoord().x,
		recognitionBB->getLineCutCoord().y,
		recognitionBB->getLineCutCoord().z);
	D3DMATERIAL9 matDef;
	device->GetMaterial(&matDef);
	device->LightEnable(0, false);
	device->SetMaterial(&cutPointMat);
	device->SetTransform(D3DTS_WORLD, &pointWorldMatrix);
	cutPoint->DrawSubset(0);
	device->LightEnable(0, true);
	device->SetMaterial(&matDef);
#endif// RENDER_LINE_CUT_POINT
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

	//リカージョン場所の認識をストックする
	RecursionRecognition* recursionRecognition = new RecursionRecognition[numNearestNode * NUM_TEST_CASES_PER_NODE];
	recognizeRecursionArea(recursionRecognition, nearestNode, numNearestNode, agentAI);

	// リカージョン認識の数を絞る
	int selectionRecognition[NUM_RECURSION_RECOGNITION] = { -1, -1, -1 };
	selectRecursionArea(selectionRecognition, recursionRecognition, nearestNode, numNearestNode, agentAI);

	// メモリーパイルを打ち込む座標を作る
	makeCoordForPile(selectionRecognition, recursionRecognition, agentAI);

	// 環境認識ブラックボードに保管
	for (int i = 0; i < NUM_RECURSION_RECOGNITION; i++)
	{
		if (selectionRecognition[i] == -1)
		{	// リカージョン認識が選択されていない場合は非活性化
			recognitionBB->setIsActiveRecursionRecognition(i, false);
		}
		else
		{	// リカージョン認識が選択されている場合は活性化してコピーする
			recognitionBB->setIsActiveRecursionRecognition(i, true);
			recognitionBB->getRecursionRecognition()[i] = recursionRecognition[selectionRecognition[i]];
		}
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
//（仮想リカージョンステップその２）リカージョン場所の認識をストックする
//=============================================================================
void EnvironmentAnalysis::recognizeRecursionArea(
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
			// パイルを打つ座標算出に使用（外接円）
			float circumscribedRadius = TEST_SIZE_RADIUS_BASE + cntSize * TEST_SIZE_RADIUS_ADD;
			// 衝突判定判定スフィアの半径（内接円）正五角形の内接円の半径の定数で算出
			float inscribedRadius = circumscribedRadius * 0.25f * (1 + 2.236f);
			// 衝突判定用スフィアの生成
			recursionSphere = new BoundingSphere;
			recursionSphere->initialize(device, inscribedRadius);

			// まずノードの位置ぴったりで衝突判定
			hitCheckAndAssign(agentAI, nearestNode[cntNode]->getPosition(), &recursionRecognition[index], index, circumscribedRadius);
			index++;

			// 次にノードの周囲を回しながら衝突判定を行いたいが
			// そのために惑星中心⇔ノード間のレイを少し傾ける
			ray.update(*Map::getField()->getPosition(), *nearestNode[cntNode]->getPosition() - *Map::getField()->getPosition());
			D3DXVECTOR3 axisToMakeDegree = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			axisToMakeDegree = slip(axisToMakeDegree, ray.direction);// 回転軸をレイに直交するベクトルにする
			switch (cntSize)
			{// 傾く角度をスフィアサイズによって変える
			case 0:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, AXIS_TILT_ANGLE_FOR_SMALL_BS);
				break;
			case 1:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, AXIS_TILT_ANGLE_FOR_MIDDLE_BS);
				break;
			case 2:
				D3DXQuaternionRotationAxis(&quaternion, &axisToMakeDegree, AXIS_TILT_ANGLE_FOR_BIG_BS);
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
				hitCheckAndAssign(agentAI, &ray.direction, &recursionRecognition[index], index, circumscribedRadius);
				index++;
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
	setDataDirectory();
	fp2 = fopen("DumpFuzzyRecognition.txt", "w");
	fprintf(fp2, "リカージョン認識ファジーデータ\n出力元：EnvironmentAnalysis.cpp/selectRecursionArea()\n");
#endif// DUMP_FUZZY_RECOGNITION

	//--------------------------------------------
	// ファジー理論でどの認識を採用するか重みづけ
	//--------------------------------------------
	for (int i = 0; i < numNearestNode * NUM_TEST_CASES_PER_NODE; i++)
	{
		// 距離の近さ⇔遠さをファジー入力化
		float lenAgentBetweenArea = D3DXVec3Length(&(recursionRecognition[i].center - *agentAI->getPosition()));
		float distanceNear = fuzzy.reverseGrade(lenAgentBetweenArea, 0.0f, 25.0f);
		float distanceFar = fuzzy.grade(lenAgentBetweenArea, 22.0f, 36.0f);
		// リカージョン範囲の小ささ⇔大きさをファジー入力化
		float radiusSizeSmall = fuzzy.reverseGrade(recursionRecognition[i].radius,
			TEST_SIZE_RADIUS_BASE - TEST_SIZE_RADIUS_FUZZY_ADJUST, TEST_SIZE_RADIUS_BASE + 2 * TEST_SIZE_RADIUS_ADD);
		float radiusSizeBig = fuzzy.grade(recursionRecognition[i].radius,
			TEST_SIZE_RADIUS_BASE, TEST_SIZE_RADIUS_BASE + 2 * TEST_SIZE_RADIUS_ADD + TEST_SIZE_RADIUS_FUZZY_ADJUST);
		// 範囲内チンギン額の少なさ⇔多さをファジー入力化
		float littleAmount = fuzzy.reverseGrade(recursionRecognition[i].totalAmount, 5.0f, 150.0f);
		float lotAmount = fuzzy.grade(recursionRecognition[i].totalAmount, 130.0f, 550.0f);

		// ファジー論理演算等でメリットを算出する
		float leastMerit, largestMerit, finalMerit;
		leastMerit = fuzzy.AND(distanceNear, radiusSizeSmall);
		leastMerit = fuzzy.AND(leastMerit, lotAmount);
		largestMerit = fuzzy.OR(distanceNear, radiusSizeSmall);
		largestMerit = fuzzy.OR(largestMerit, lotAmount * 1.8f/*チンギン額の評価ウェイトを上げる*/);
		finalMerit = (largestMerit + leastMerit) / 2;
		// ファジー論理演算等でデメリットを算出する
		float leastDemerit, largestDemerit, finalDemerit;
		leastDemerit = fuzzy.AND(distanceFar, radiusSizeBig);
		leastDemerit = fuzzy.AND(leastDemerit, littleAmount);
		largestDemerit = fuzzy.OR(distanceFar * 1.1f/*距離の評価ウェイトを上げる*/, radiusSizeBig);
		largestDemerit = fuzzy.OR(largestDemerit, littleAmount);
		finalDemerit = (largestDemerit + leastDemerit) / 2;

		// 最終的な重みをファジー出力として吐き出す
		recursionRecognition[i].fuzzySelectionWeight = fuzzy.grade(fuzzy.NOT(finalDemerit) + finalMerit, 0.0f, 2.0f);

		//----------------------------------------------------------------------
		// 以下に該当する認識は選択しない
		if (recursionRecognition[i].totalAmount == 0.0f) { continue; }
		if (recursionRecognition[i].fuzzySelectionWeight == 0.0f) { continue; }
		//----------------------------------------------------------------------

		// 重みの大きい認識から選択していく
		if (recursionRecognition[i].fuzzySelectionWeight > largestWeight)
		{
			largestWeight = recursionRecognition[i].fuzzySelectionWeight;
			selectionRecognition[selectionIndex] = i;
			if (++selectionIndex >= NUM_RECURSION_RECOGNITION) selectionIndex = 0;
		}

#ifdef DUMP_FUZZY_RECOGNITION
		fprintf(fp2, "%d\n", recursionRecognition[i].uniqueID);
		fprintf(fp2, "距離lenAgentBetweenArea = %.3f\n", lenAgentBetweenArea);
		fprintf(fp2, "距離distanceNear = %.3f\n", distanceNear);
		fprintf(fp2, "距離distanceFar = %.3f\n", distanceFar);
		fprintf(fp2, "サイズradiusSizeSmall = %.3f\n", radiusSizeSmall);
		fprintf(fp2, "サイズradiusSizeBig = %.3f\n", radiusSizeBig);
		fprintf(fp2, "チンギンlotAmount = %.3f\n", lotAmount);
		fprintf(fp2, "チンギンlittleAmount = %.3f\n", littleAmount);
		fprintf(fp2, "largestMerit = %.3f leastMerit = %.3f, finalMerit = %.3f\n", largestMerit, leastMerit, finalMerit);
		fprintf(fp2, "largestDemrit = %.3f leastDemerit = %.3f, finalDemerit = %.3f\n", largestDemerit, leastDemerit, finalDemerit);
		fprintf(fp2, "fuzzySelectWeight = %.3f\n\n", recursionRecognition[i].fuzzySelectionWeight);
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
		//-----------------------------------------------
		// 選択されていない認識はパスする
		if (selectionRecognition[i] == -1) { continue; }
		//-----------------------------------------------

		// 弧度法では中心角 = 弦長÷半径（使うのは中心角÷2なので予め2で割っておく）
		float angle = recursionRecognition[selectionRecognition[i]].radius / Map::getField()->getRadius();

		// 惑星中心⇔リカージョン認識中心座標のレイを求めた中心角分だけ傾ける
		D3DXQuaternionIdentity(&quaternion);
		D3DXMatrixIdentity(&worldMatrix);
		D3DXVECTOR3 axisForTilt = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		ray.update(*Map::getField()->getPosition(),
			recursionRecognition[selectionRecognition[i]].center - *Map::getField()->getPosition());
		axisForTilt = slip(axisForTilt, ray.direction);	// 回転軸をレイに直交するベクトルにする
		D3DXQuaternionRotationAxis(&quaternion, &axisForTilt, angle);
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
// リカージョン認識への代入（スフィアとワスレモノの衝突判定）
//=============================================================================
void EnvironmentAnalysis::hitCheckAndAssign(AgentAI* agentAI,
	D3DXVECTOR3* checkPosition, RecursionRecognition* recursionRecognition, int index, float circumscribedRadius)
{
	recursionRecognition->uniqueID = index;
	recursionRecognition->center = *checkPosition;
	recursionRecognition->totalHit = 0;
	recursionRecognition->totalAmount = 0;
	recursionRecognition->radius = circumscribedRadius;

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
	fprintf(fp, "%d\n", recursionRecognition->uniqueID);
	fprintf(fp, "recursionRecognition->center = (%.2f, %.2f,%.2f) \n",
		recursionRecognition->center.x, recursionRecognition->center.y, recursionRecognition->center.z);
	fprintf(fp, "recursionRecognition->totalHit = %d\n", (int)recursionRecognition->totalHit);
	fprintf(fp, "recursionRecognition->totalAmount = %d\n", (int)recursionRecognition->totalAmount);
	fprintf(fp, "recursionRecognition->radius = %.2f\n", recursionRecognition->radius);
#endif// DUMP_RECUASION_AREA

#ifdef RENDER_RECUASION_AREA
	if (recursionRecognition->uniqueID == 2 /*|| recursionRecognition->uniqueID == 3*/)
	{
		spherePoint.render(device, recursionWorldMatrix);	// スフィア座標の描画

		BoundingSphere bs;
		bs.initialize(device, 15.0f);
		bs.render(device, recursionWorldMatrix);			// サイズ調整用のスフィア描画
	}
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
		forgettingTimeMap = 60/*FPS*/ * 8/*秒*/ / recognitionBB->getMemorizedMap().size();
		if (mapTimeCount > forgettingTimeMap)
		{
			recognitionBB->getMemorizedMap().pop_front();
			mapTimeCount = 0;
		}
	}

	if (recognitionBB->getMemorizedBullet().size() != 0)
	{
		bulletTimeCount++;
		forgettingTimeBullet = 60/*FPS*/ * 3/*秒*/ / recognitionBB->getMemorizedBullet().size();
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

	analyzeBattle(agentAI);			// バトル状況を解析

	makeCoordForCut(agentAI);		// メモリーライン切断座標を算出

	static int cnt = 0;// ●仮
	if (++cnt % 5 == 0)
	{
		cnt = 0;
		virtualRecursion(agentAI);// 仮想リカージョン

	}

	forgetMemorizedMatter();		// 記憶事項を忘却

#endif
}