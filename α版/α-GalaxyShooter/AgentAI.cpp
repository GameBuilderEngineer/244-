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
AgentAI::AgentAI(Player* opponentPlayer, D3DXVECTOR3* cameraPosition, float fieldOfView)
{
	aiID = numAgent++;

	// アービター
	arbiter = new Arbiter;

	// モジュール
	sensor = new Sensor(cameraPosition, fieldOfView);
	environmentAnalysis = new EnvironmentAnalysis;
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
	PDIRECT3DDEVICE9 device,
	StaticMeshLoader* staticMeshLoader,
	TextureLoader* textureLoader,
	ShaderLoader* shaderLoader)
{
	Player::initialize(playerType, device, staticMeshLoader, textureLoader, shaderLoader);

	// アービター初期化
	arbiter->initialize();

	// モジュール初期化
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
	recognitionBB->setMyPosition(&position);
	bodyBB->configMovingDestination(opponent->getPosition());
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

	// プレイヤー処理の事後更新
	updatePlayerAfter(frameTime);

	// プレイヤー自己情報→AIに送信 
	updateAgentSelfData();
}


//=============================================================================
// プレイヤー処理の事前更新
//=============================================================================
void AgentAI::updatePlayerBefore(float frameTime)
{
	setSpeed(D3DXVECTOR3(0, 0, 0));	// 速度（移動量）の初期化
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
	bool onJump = false;
	if (input->wasKeyPressed(keyTable.jump) ||
		input->getController()[type]->wasButton(playerNS::BUTTON_JUMP))
	{
		onJump = true;
	}
#endif

	//===========
	//【接地処理】
	//===========
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//重力レイの初期化
	if (radius + attractorRadius >= (between2VectorLength(position, *attractorPosition) - difference))
	{
		onGround = true;
		//めり込み補正
		//現在位置+ 垂直方向*(めり込み距離)
		setPosition(position + axisY.direction * (radius + attractorRadius - between2VectorLength(position, *attractorPosition)));
		//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
		setSpeed(reverseAxisY.slip(speed, axisY.direction));
#ifdef _DEBUG
		if (onJump)jump();//ジャンプ
#endif
	}
	else {
		onGround = false;
		setGravity(gravityDirection, playerNS::GRAVITY_FORCE);//重力処理
	}

	//===========
	//【加速度処理】
	//===========
	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}
	acceleration *= 0.9f;//加速度減衰

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
	controlCamera(frameTime);

	//==========================
	//【メモリーアイテムの更新】
	//==========================
	// メモリーパイルの更新3
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}

	// メモリーラインの更新
	memoryLine.update(device, frameTime);
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

	memoryPile[elementMemoryPile].setPosition(position);
	memoryPile[elementMemoryPile].setQuaternion(quaternion);
	memoryPile[elementMemoryPile].activation();
	memoryPile[elementMemoryPile].Object::update();
	elementMemoryPile++;

	//メモリーパイルを全て設置することに成功
	if (elementMemoryPile >= NUM_MEMORY_PILE)
	{
		elementMemoryPile = 0;//セットする対象を0番のメモリパイルに切替
		//リカージョンによるワスレモノから賃金への変換が終わるまでは、メモリーパイルをセットできない状態にする
		onRecursion = true;
		//設置されたメモリーパイル5点を用いてリカージョン用のポリゴンを生成する。
		D3DXVECTOR3 vertex[NUM_MEMORY_PILE];
		for (int i = 0; i < NUM_MEMORY_PILE; i++)
		{
			vertex[i] = *memoryPile[i].getPosition();
		}
		//リカージョンの生成
		recursion = new Recursion;
		recursion->initialize(device, vertex, *textureLoader->getTexture(textureLoaderNS::RECURSION), *shaderLoader->getEffect(shaderNS::RECURSION));
		//メモリーパイルとメモリーラインの消失
		for (int i = 0; i < NUM_MEMORY_PILE; i++)
		{
			memoryPile[i].switchLost();//消失
			memoryLine.disconnect();//切断
		}
	}

	//メモリーパイルの切断処理
	//if (input->getController()[type]->wasButton(virtualControllerNS::A)
	//	|| (GetAsyncKeyState(VK_RSHIFT) & 0x8000))
	//{
	//	if (collitionMemoryLine && !onRecursion1P)
	//	{//[条件判定]1Pのメモリーラインと2Pが衝突
	//		for (int i = 0; i < NUM_1P_MEMORY_PILE; i++)
	//		{//メモリーパイルとメモリーラインの消失
	//			memoryPile[i].switchLost();//消失
	//			memoryLine.disconnect();//切断
	//		}
	//		player[PLAYER2].changeState(playerNS::DOWN);
	//	}
	//}
}
