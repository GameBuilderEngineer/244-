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
	canChangeCameraSkyMode = true;
	D3DXQuaternionIdentity(&cameraRotPreservation);
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
	npc = true;

	// アービター初期化
	arbiter->initialize();

	// モジュール初期化
	KnowledgeSourceBase::setDevice(device);
	sensor->initialize();
	environmentAnalysis->initialize();
	decisionMaking->initialize();
	pathPlanning->initialize();
	motionGeneration->initialize(input, keyTable);

	// ブラックボード初期化
	recognitionBB->initialize();
	memoryBB->initialize();
	bodyBB->initialize();

	// 初期設定項目を埋める
	recognitionBB->setMemoryBB(memoryBB);
	recognitionBB->setMyPosition(&position);
	recognitionBB->setFrameTimePointer(&frameTime);
	recognitionBB->setElementMemoryPilePointer(&elementMemoryPile);
	recognitionBB->setPointerWhetherInstallationEffectiveDistance(&whetherInstallationEffectiveDistance);
	recognitionBB->setSkyHeightPointer(&skyHeight);
	motionGeneration->setAnimationPlayerPointer(animationPlayer);
	bodyBB->configMovingDestination(opponent->getPosition());// ●
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

	// AI記憶忘却

	// AI用オートカメラ操作
	autoCamera();

	// プレイヤー処理の事後更新
	updatePlayerAfter(frameTime);

	// プレイヤー自己情報→AIに送信 
	updateAgentSelfData();

#ifdef _DEBUG
	//●
 	if (input->wasKeyPressed('Q'))
	{
		//input->clearKeyPress('Q');
		recognitionBB->setIsStartRecursion(true);
	}
	if (input->wasKeyPressed('O'))
	{
		recognitionBB->setIsStartRecursionForOpponent(true);
	}
#endif
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
	//===========
	//【回復】
	//===========
	recorvery(frameTime);

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

	//仮
	if (input->wasKeyPressed('H'))
	{
		changeState(SKY);
	}
	//仮
	if (input->wasKeyPressed(keyTable.provisional))
	{
		triggerShockWave();
	}

	switch (state)
	{
	case FALL:		updateFall(frameTime);			break;
	case SKY:		updateSky(frameTime);			break;
	case GROUND:	updateGround(frameTime, onJump);break;
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

	// アニメーションの更新
	animationPlayer->update(input, state);

	//===========
	//【弾の更新】
	//===========
	updateBullet(frameTime);

	//===========
	//【カメラの操作】
	//===========
	camera->setUpVector(axisY.direction);
	camera->update();

	//===========
	//【メモリーパイル・メモリーライン・リカージョンの更新】
	//===========
	updateMemoryItem(frameTime);

	//===========
	//【衝撃波の更新】
	//===========
	for (int i = 0; i < NUM_SHOCK_WAVE; i++)
	{
		updateShockWave(frameTime, i);
	}

	//===========
	//【アップエフェクトの更新】
	//===========
	updateUpEffect(frameTime);
}


//=============================================================================
// プレイヤー自己情報→AIに送信 
//=============================================================================
void AgentAI::updateAgentSelfData(void)
{
	recognitionBB->setWhetherInAir(!onGround);							// 空中にいるか
	bodyBB->setShootingInterval(intervalBullet);						// バレット発射インターバル
	bodyBB->setIsReadyForPile(memoryPile[elementMemoryPile].ready());	// パイル設置可能か
	recognitionBB->setPlayerState(state);								// ステートを設定
}


//=============================================================================
// 復活ポイント増加
//=============================================================================
void AgentAI::increaseRevivalPoint(void)
{
	revivalPoint += INCREASE_REVIVAL_POINT;

	// サウンドの再生
	sound->play(soundNS::TYPE::SE_REVIVAL_POINT, soundNS::METHOD::PLAY);
	revivalPoint += INCREASE_REVIVAL_POINT;
	// アップエフェクト発生
	upEffect.generateUpEffect(200, position, upVec());
	if (whetherRevival())changeState(REVIVAL);
}

//=============================================================================
// オートカメラ操作
//=============================================================================
void AgentAI::autoCamera(void)
{
	//------------
	// 上空＆落下
	//------------
	if (state == SKY || state == FALL)
	{
		if (canChangeCameraSkyMode)
		{
			cameraRotPreservation = camera->relativeQuaternion;
			camera->setRelative(SKY_RELATIVE_QUATERNION);
			canChangeCameraSkyMode = false;
		}
		return;
	}

	//------
	// 地上
	//------
	if (canChangeCameraSkyMode == false)
	{
		camera->setRelative(cameraRotPreservation);
		canChangeCameraSkyMode = true;
	}

	if (D3DXVec3Length(&(*opponent->getPosition() - position)) < 70.0f/*こんなもんか？*/&&
		recognitionBB->getIsOpponentInCamera())
	{// 相手プレイヤーとの距離が近くかつカメラに相手プレイヤーが映っていればロック音
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
