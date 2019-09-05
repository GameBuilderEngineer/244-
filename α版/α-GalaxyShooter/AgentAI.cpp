//-----------------------------------------------------------------------------
// エージェントAI処理 [AgentAI.cpp]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"
using namespace playerNS;

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int AgentAI::numAgent = 0;


//=============================================================================
// コンストラクタ
//=============================================================================
AgentAI::AgentAI(Player* opponentPlayer, Camera* camera, std::vector<Wasuremono*>* wasuremono)
{
	aiID = numAgent++;
	virticalTime = 0.0f;
	horizontalTime = 0.0f;

	// アービター
	arbiter = new Arbiter;

	// モジュール
	sensor = new Sensor(camera);
	environmentAnalysis = new EnvironmentAnalysis(wasuremono);
	pathPlanning = new PathPlanning;
	decisionMaking = new DecisionMaking;
	motionGeneration = new MotionGeneration;

	// ブラックボード
	recognitionBB = new RecognitionBB(opponentPlayer);
	bodyBB = new BodyBB;
	memoryBB = new MemoryBB;

	// アービターにモジュールを接続
	arbiter->setModule(Module::SENSOR, sensor);
	arbiter->setModule(Module::ENVIRONMENT_ANSLYSIS, environmentAnalysis);
	arbiter->setModule(Module::PATH_PLANNING, pathPlanning);
	arbiter->setModule(Module::DECISION_MAKING, decisionMaking);
	arbiter->setModule(Module::MOTION_GENERATION, motionGeneration);

	// モジュールにブラックボードを接続
	sensor->setBlackBoard(recognitionBB);
	environmentAnalysis->setBlackBoard(recognitionBB);
	pathPlanning->setBlackBoard(recognitionBB, memoryBB);
	decisionMaking->setBlackBoard(recognitionBB, memoryBB, bodyBB);
	motionGeneration->setBlackBoard(memoryBB, bodyBB);
}


//=============================================================================
// デストラクタ
//=============================================================================
AgentAI::~AgentAI(void)
{
	// モジュールとブラックボード破棄
	SAFE_DELETE(arbiter)
	SAFE_DELETE(sensor)
	SAFE_DELETE(environmentAnalysis)
	SAFE_DELETE(pathPlanning)
	SAFE_DELETE(decisionMaking)
	SAFE_DELETE(motionGeneration)
	SAFE_DELETE(recognitionBB)
	SAFE_DELETE(bodyBB)
	SAFE_DELETE(memoryBB)

	--numAgent;
}


//=============================================================================
// 初期化処理
//=============================================================================
void AgentAI::initialize(
	int playerType, 
	int modelType,
	PDIRECT3DDEVICE9 device,
	StaticMeshLoader* staticMeshLoader,
	TextureLoader* textureLoader,
	ShaderLoader* shaderLoader)
{
	Player::initialize(playerType, modelType,device, staticMeshLoader, textureLoader, shaderLoader);

	// アービター初期化
	arbiter->initialize();

	// モジュール初期化
	KnowledgeSourceBase::setDevice(device);
	sensor->initialize();
	environmentAnalysis->initialize();
	decisionMaking->initialize();
	pathPlanning->initialize();
	motionGeneration->initialize();

	// ブラックボード初期化
	recognitionBB->initialize();
	memoryBB->initialize();
	bodyBB->initialize();

	// 初期設定項目を埋める
	recognitionBB->setMemoryBB(memoryBB);
	recognitionBB->setMyPosition(&position);
	recognitionBB->setFrameTimePointer(&frameTime);
	bodyBB->configMovingDestination(opponent->getPosition()); // ●
}


//=============================================================================
// 終了処理
//=============================================================================
void AgentAI::uninitialize(void)
{
	// モジュール終了
	sensor->uninitialize();
	environmentAnalysis->uninitialize();
	decisionMaking->uninitialize();
	pathPlanning->uninitialize();
	motionGeneration->uninitialize();
}


//=============================================================================
// 更新処理
//=============================================================================
void AgentAI::update(float frameTime)
{
	// プレイヤー処理の事前更新
	updatePlayerBefore(frameTime);

	// AIの更新
	arbiter->update();
	if (sensor->getUpdatePermission())
	{
		sensor->update(this);
	}
	if (environmentAnalysis->getUpdatePermission())
	{
		environmentAnalysis->update(this);
	}
	if (pathPlanning->getUpdatePermission())
	{
		pathPlanning->update(this);
	}
	if (decisionMaking->getUpdatePermission())
	{
		decisionMaking->update(this);
	}
	if (motionGeneration->getUpdatePermission())
	{
		motionGeneration->update(this);
	}

	// AI用オートカメラ操作
	autoCamera();

	// プレイヤー処理の事後更新
	updatePlayerAfter(frameTime);

	// プレイヤー自己情報→AIに送信 
	updateAgentSelfData();

	//●
	if (input->isKeyDown('Q'))
	{
		recognitionBB->flag = true;
	}
}


//=============================================================================
// プレイヤー処理の事前更新
//=============================================================================
void AgentAI::updatePlayerBefore(float frameTime)
{
	setSpeed(D3DXVECTOR3(0, 0, 0));	// 速度（移動量）の初期化
	onJump = false;
	disconnectOpponentMemoryLine = false;
	this->frameTime = frameTime;	// frameTime記録
}


//=============================================================================
// プレイヤー処理の事後更新
//=============================================================================
void AgentAI::updatePlayerAfter(float frameTime)
{
#ifdef _DEBUG
	// 調整用
	if (input->getController()[type]->wasButton(virtualControllerNS::UP))
		difference += 0.01f;
	if (input->getController()[type]->wasButton(virtualControllerNS::DOWN))
		difference -= 0.01f;
#endif

	//===========
	//【回復】
	//===========
	recorvery(frameTime);

#ifdef _DEBUG
	// デバッグモードのときはコントローラの入力を一部受け付ける
	// 特段理由はない　せっかくだから

		//===========
		//【移動処理】
		//===========
	moveOperation();

	//===========
	//【ジャンプ】
	//===========
	if (input->wasKeyPressed(keyTable.jump) ||
		input->getController()[type]->wasButton(BUTTON_JUMP))
	{
		onJump = true;
	}
#endif

	switch (state)
	{
	case FALL:		updateFall(frameTime);			break;
	case SKY:		updateSky(frameTime);			break;
	case GROUND:	updateGround(frameTime, onJump); break;
	case DOWN:		updateDown(frameTime);			break;
	case REVIVAL:	updateRevival(frameTime);		break;
	}

	//===========
	//【加速度処理】
	//===========
	if (D3DXVec3Length(&acceleration) > 0.05f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}
	//acceleration *= 0.9f;//加速度減衰


	//===========
	//【位置更新】
	//===========
	position += speed * frameTime;

	//===========
	//【姿勢制御】
	//===========
	postureControl(axisY.direction, -gravityRay.direction, 3.0f * frameTime);

	//===========
	//【オブジェクト：更新】
	//===========
	Object::update();

	//===========
	//【弾の更新】
	//===========
	//インターバルの更新
	intervalBullet = max(intervalBullet - frameTime, 0);
	//バレットの更新
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].update(frameTime);
	}

	//===========
	//【カメラの操作】
	//===========
	camera->setUpVector(axisY.direction);
	camera->update();

	//==========================
	//【メモリーアイテムの更新】
	//==========================
	if (whetherDown())
	{
		deleteMemoryItem();//ダウン状態ならば全てのメモリアイテムを削除
	}
	if (onRecursion)recursionTimer -= frameTime;
	if (recursionTimer < 0)
	{
		if (onRecursion)SAFE_DELETE(recursion);
		onRecursion = false;
	}

	// メモリーパイルのセットはビヘイビアツリーから

	// メモリーラインの切断もビヘイビアツリーから

	// メモリーパイルの更新
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}

	// メモリーラインの更新
	memoryLine.update(device, frameTime, memoryLineNS::PENTAGON);

	//スターラインの更新
	starLine.update(device, frameTime, memoryLineNS::STAR);//スターラインの更新

	//リカージョンの更新
	if (onRecursion)
	{
		recursion->update(frameTime);
	}

	//===========
	//【衝撃波の更新】
	//===========
	for (int i = 0; i < NUM_SHOCK_WAVE; i++)
	{
		updateShockWave(frameTime, i);
	}
}


//=============================================================================
// プレイヤー自己情報→AIに送信 
//=============================================================================
void AgentAI::updateAgentSelfData(void)
{
	recognitionBB->setWhetherInAir(!onGround);							// 空中にいるか
	recognitionBB->setIsDown(whetherDown());							// ダウン中か
	bodyBB->setShootingInterval(intervalBullet);						// バレット発射インターバル
	bodyBB->setIsReadyForPile(memoryPile[elementMemoryPile].ready());	// パイル設置可能か
}


//=============================================================================
// バレットの発射
//=============================================================================
void AgentAI::shootBullet(D3DXVECTOR3 targetDirection)
{
	// この条件判定はビヘイビアツリーでも行っている
	// if (whetherDown())return;//ダウン時：発射不可
	// if (intervalBullet == 0)


	//バレットの発射
	if (whetherDown())return;//ダウン時：発射不可
	if (intervalBullet == 0)
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_ATTACK, soundNS::METHOD::PLAY);

		bullet[elementBullet].setPosition(position);
		//Y軸方向への成分を削除する
		D3DXVECTOR3 front = slip(camera->getDirectionZ(), axisY.direction);
		D3DXVec3Normalize(&front, &front);//正規化
		bullet[elementBullet].addSpeed(front*0.2);//速度を加算
		bullet[elementBullet].setQuaternion(quaternion);
		bullet[elementBullet].postureControl(axisZ.direction, front, 1.0f);
		bullet[elementBullet].activation();
		bullet[elementBullet].configurationGravity(attractorPosition, attractorRadius);
		bullet[elementBullet].Object::update();
		elementBullet++;
		if (elementBullet >= NUM_BULLET)elementBullet = 0;
		intervalBullet = INTERVAL_BULLET;
	}
}


//=============================================================================
// メモリーパイルの設置
//=============================================================================
void AgentAI::locateMemoryPile(void)
{
	// この辺の条件判定はビヘイビアツリーで行っている
	// onGround &&
	// memoryPile[elementMemoryPile].ready()

	// サウンドの再生
	sound->play(soundNS::TYPE::SE_INSTALLATION_MEMORY_PILE, soundNS::METHOD::PLAY);

	memoryPile[elementMemoryPile].setPosition(position);
	memoryPile[elementMemoryPile].setQuaternion(quaternion);
	memoryPile[elementMemoryPile].activation();
	memoryPile[elementMemoryPile].Object::update();
	elementMemoryPile++;

	//メモリーパイルを全て設置することに成功
	if (elementMemoryPile >= NUM_MEMORY_PILE)
	{
		memoryLine.update(device, frameTime, memoryLineNS::PENTAGON);//メモリーラインの更新
		elementMemoryPile = 0;//セットする対象を0番のメモリパイルに切替
		//リカージョンによるワスレモノから賃金への変換が終わるまでは、メモリーパイルをセットできない状態にする
		onRecursion = true;
		recursionTimer = RECURSION_TIME;
		//設置されたメモリーパイル5点を用いてリカージョン用のポリゴンを生成する。
		D3DXVECTOR3 vertex[NUM_MEMORY_PILE];
		for (int i = 0; i < NUM_MEMORY_PILE; i++)
		{
			vertex[i] = *memoryPile[i].getPosition();
		}
		//リカージョンの生成
		recursion = new Recursion;
		recursion->initialize(device, vertex, *textureLoader->getTexture(textureLoaderNS::RECURSION), *shaderLoader->getEffect(shaderNS::RECURSION));
		//スターラインのリセット
		starLine.resetCurrentRenderNum();
		//メモリーパイルとメモリーラインの消失
		for (int i = 0; i < NUM_MEMORY_PILE; i++)
		{
			memoryPile[i].switchLost();//消失
			memoryLine.disconnect();//切断
		}
	}

}


//=============================================================================
// メモリーライン切断
//=============================================================================
void AgentAI::cutMemoryLine(void)
{
	disconnectOpponentMemoryLine = true;
}


//=============================================================================
// 復活ポイント増加
//=============================================================================
void AgentAI::increaseRevivalPoint(void)
{
	revivalPoint += INCREASE_REVIVAL_POINT;
}

//=============================================================================
// オートカメラ操作
//=============================================================================
void AgentAI::autoCamera(void)
{

	if (D3DXVec3Length(&(*opponent->getPosition() - position)) < 90.0f/*こんなもんか？*/)
	{// 相手に近ければロックオン
		lockOnHorizontally(*opponent->getPosition(), frameTime);
	}
	else
	{// それ以外は首振り

		// 垂直方向回転
		static const float ROTATION_VIRTICAL = 0.12;
		static const float VIRTICAL_UNIT_TIME = 5.0f;
		virticalTime += frameTime;
		if (virticalTime < VIRTICAL_UNIT_TIME)
		{
			camera->rotation(camera->getHorizontalAxis(), -ROTATION_VIRTICAL);
		}
		else if(virticalTime >= VIRTICAL_UNIT_TIME && virticalTime < VIRTICAL_UNIT_TIME * 2)
		{
			camera->rotation(camera->getHorizontalAxis(), ROTATION_VIRTICAL);
		}
		else
		{
			virticalTime = 0.0f;
		}

		// 水平方向回転
		static const float ROTATION_HORIZONTAL = 0.15;
		static const float HORIZONTAL_UNIT_TIME = 3.0f;
		horizontalTime += frameTime;
		if (horizontalTime < HORIZONTAL_UNIT_TIME)
		{
			camera->rotation(D3DXVECTOR3(0, 1, 0), -ROTATION_HORIZONTAL);
		}
		else if (horizontalTime >= HORIZONTAL_UNIT_TIME && horizontalTime < HORIZONTAL_UNIT_TIME * 3)
		{
			camera->rotation(D3DXVECTOR3(0, 1, 0), ROTATION_HORIZONTAL);
		}
		else if(horizontalTime >= HORIZONTAL_UNIT_TIME * 3 && horizontalTime < HORIZONTAL_UNIT_TIME * 4)
		{
			camera->rotation(D3DXVECTOR3(0, 1, 0), -ROTATION_HORIZONTAL);
		}
		else
		{
			horizontalTime = 0.0f;
		}
	}
}


//=============================================================================
// 水平ロックオン
//=============================================================================
void AgentAI::lockOnHorizontally(D3DXVECTOR3 lockOnTarget, float frameTime)
{
	float radian;						// 回転角度
	D3DXVECTOR3 axis(0, 1, 0);			// 回転軸
	D3DXVECTOR3 lockOnTargetDirection;	// ターゲット方向ベクトル

	// プレイヤー→ターゲットのベクトルにする
	between2VectorDirection(&lockOnTargetDirection, *camera->target, lockOnTarget);

	// カメラ位置と注視点を含む平面の左右どちらにターゲットがあるか
	// 平面の方程式にターゲットの座標を代入して調べる
	bool isRight = false;
	D3DXVECTOR3 planeN = camera->getDirectionX();
	float d = -(planeN.x * camera->position.x + planeN.y * camera->position.y + planeN.z * camera->position.z);
	if (planeN.x * lockOnTarget.x + planeN.y * lockOnTarget.y + planeN.z * lockOnTarget.z + d > 0)
	{
		isRight = true;
	}

	// カメラの注視方向ベクトルとターゲット方向ベクトルをカメラのXZ平面と平行になるようスリップ
	lockOnTargetDirection = slip(lockOnTargetDirection, camera->getDirectionY());
	D3DXVec3Normalize(&lockOnTargetDirection, &lockOnTargetDirection);
	D3DXVECTOR3 front = slip(camera->getDirectionZ(), camera->getDirectionY());
	D3DXVec3Normalize(&front, &front);

	// 回転させる
	if (formedRadianAngle(&radian, front, lockOnTargetDirection))
	{
		if (isRight)
		{// 回転向きそのまま
		}
		else//(isLeft)
		{// 回転向き変える
			radian = -radian;
		}
		camera->rotation(axis, D3DXToDegree(radian * frameTime));
	}
}


//=============================================================================
// 3次元ロックオン（未完）
//=============================================================================
// ターゲットとの位置関係によって（おそらく）ターゲット方向の逆方向を向くよう回転
// 見下ろしでなく見上げる方向になってしまう
// よくわからん！
void AgentAI::lockOn3D(D3DXVECTOR3 lockOnTarget, float frameTime)
{
	float radian;						// 回転角度
	D3DXVECTOR3 axis;					// 回転軸
	D3DXVECTOR3 lockOnTargetDirection;	// ターゲット方向ベクトル

	// 外積を回転軸に
	D3DXVec3Cross(&axis, &camera->getDirectionZ(), &(lockOnTarget - camera->position));

	// プレイヤー→ターゲットのベクトルにする
	between2VectorDirection(&lockOnTargetDirection, *camera->target, lockOnTarget);

	// カメラを回転させる
	D3DXVECTOR3 front = camera->getDirectionZ();
	if (formedRadianAngle(&radian, front, lockOnTargetDirection))
	{
		camera->rotation(axis, D3DXToDegree(radian* frameTime));
	}

	//// フィールドの下にカメラが潜り込んだら
	//if (D3DXVec3Dot(&camera->getDirectionZ(), &getReverseAxisY()->direction) < 0)
	//{
	//	isOpponentLockOn = false;
	//}
}


//=============================================================================
// デバッグ描画
//=============================================================================
void AgentAI::debugRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	environmentAnalysis->debugRender(this);	// デバッグ描画が有効になっていれば仮想リカージョンを描画
}
