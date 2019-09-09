//===================================================================================================================================
//【Player.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/09/08
//===================================================================================================================================
#include "Player.h"
#include "UIRevival.h"

using namespace playerNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Player::Player()
{
	ZeroMemory(&keyTable, sizeof(OperationKeyTable));
	hp = MAX_HP;
	revivalPoint = 0;
	onGravity = true;
	radius = 5.0f;
	activation();

	state = GROUND;

	recoveryTimer = 0.0f;					//自動回復時間
	invincibleTimer = 0.0f;					//無敵時間
	fallTimer = 0.0f;						//落下時間
	skyTimer = 0.0f;						//上空モード時間
	decreaseRevivalTimer = 0.0f;			//ダウンタイマー[体力が切れるorメモリーラインを切断される]

	onGround = false;						//接地判定

	skyHeight = 0.0f;
	modelType = staticMeshNS::CHILD;
	reverseValueXAxis = CAMERA_SPEED;		//操作Ｘ軸
	reverseValueYAxis = CAMERA_SPEED;		//操作Ｙ軸
	onJump = false;							//ジャンプフラグ
	onRecursion = false;					//リカージョン生成フラグ
	for (int i = 0; i < NUM_SHOCK_WAVE; i++)
	{
		onShockWave[i] = false;
	}//衝撃波発動フラグ
	canShockWave = false;
	collidedOpponentMemoryLine = false;		//相手のメモリーラインとの衝突フラグ
	disconnectOpponentMemoryLine = false;	//敵メモリーライン切断メッセージフラグ
	elementBullet = 0;						//弾アクセス要素数
	elementMemoryPile = 0;					//メモリーパイル要素数
	intervalBullet = 0;						//発弾間隔
	difference = DIFFERENCE_FIELD;			//フィールド補正差分
	recursion = NULL;						//リカージョンNULL
	recursionTimer = 0.0f;					//リカージョンの生存時間
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
Player::~Player()
{

}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
//プレイヤータイプごとに初期化内容を変更
void Player::initialize(int playerType,int modelType, LPDIRECT3DDEVICE9 _device, StaticMeshLoader* staticMeshLoader, TextureLoader* textureLoader, ShaderLoader* shaderLoader) {
	device = _device;
	type = playerType;
	npc = false;
	this->modelType = modelType;
	this->textureLoader = textureLoader;
	this->shaderLoader = shaderLoader;
	this->sound = NULL;
	switch (type)
	{
	case PLAYER1:
		keyTable = KEY_TABLE_1P;
		break;
	case PLAYER2:
		keyTable = KEY_TABLE_2P;
		break;
	case TITLE_PLAYER:
		keyTable = NON_CONTOROL;
		break;
	}
	Object::initialize(device, &staticMeshLoader->staticMesh[staticMeshNS::CHILD], &(D3DXVECTOR3)START_POSITION[type]);
	bodyCollide.initialize(device, &position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
	
	//弾の初期化
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].initialize(device, &staticMeshLoader->staticMesh[staticMeshNS::BULLET], &D3DXVECTOR3(0, 0, 0));
	}
	//メモリーパイルの初期化
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].initialize(device, &staticMeshLoader->staticMesh[staticMeshNS::MEMORY_PILE], &D3DXVECTOR3(0, 0, 0));
	}

	//メモリーラインの初期化
	memoryLine.initialize(device, memoryPile, NUM_MEMORY_PILE, this,
		*shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::LIGHT_001));
	//スターラインの初期化
	starLine.initialize(device, memoryPile, NUM_MEMORY_PILE, this,
		*shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::LIGHT_001));

	// 弾エフェクト初期化
	bulletEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// ダウンエフェクト初期化
	downEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// アップエフェクト初期化
	upEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// ラインエフェクト初期化
	lineEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	return;
}

//===================================================================================================================================
//【更新】
//[処理内容1]回復処理
//[処理内容2]移動処理
//[処理内容3]ジャンプ処理
//[処理内容4]重力処理
//[処理内容5]接地処理
//[処理内容6]メモリーパイル・メモリーライン・リカージョンの処理
//===================================================================================================================================
void Player::update(float frameTime)
{

#ifdef _DEBUG
	//調整用
	if (input->getController()[type]->wasButton(virtualControllerNS::UP))
		difference += 0.01f;
	if (input->getController()[type]->wasButton(virtualControllerNS::DOWN))
		difference -= 0.01f;
#endif // _DEBUG

	//前処理
	setSpeed(D3DXVECTOR3(0, 0, 0));	//速度（移動量）の初期化
	onJump = false;					//ジャンプフラグ

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
	case GROUND:	updateGround(frameTime,onJump);	break;
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
	position += speed*frameTime;
	
	//===========
	//【姿勢制御】
	//===========
	postureControl(axisY.direction, -gravityRay.direction,3.0f * frameTime);
	
	//===========
	//【オブジェクト：更新】
	//===========
	Object::update();

	//===========
	//【弾の更新】
	//===========
	updateBullet(frameTime);

	//===========
	//【カメラの操作】
	//===========
	controlCamera(frameTime);

	//===========
	//【メモリーパイル・メモリーライン・リカージョンの更新】
	//===========
	updateMemoryItem(frameTime);

	//===========
	//【衝撃波の更新】
	//===========
	for (int i = 0; i < NUM_SHOCK_WAVE; i++)
	{
		updateShockWave(frameTime,i);
	}

	//===========
	//【アップエフェクトの更新】
	//===========
	updateUpEffect(frameTime);
}

//===================================================================================================================================
//【描画】
//===================================================================================================================================
//======================
//【トゥーンレンダー】
//======================
void Player::toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition,
	LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine)
{
	Object::toonRender(device,view,projection, cameraPosition,effect,textureShade,textureLine);
	//他のオブジェクトの描画
	//otherRender(device,view,projection,cameraPosition);
}
//======================
//【通常描画】
//======================
void Player::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	Object::render(device,view,projection, cameraPosition);
	//他のオブジェクトの描画
	otherRender(device,view,projection,cameraPosition);
}
//======================
//【本体以外の他のオブジェクト描画】
//======================
void Player::otherRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// 弾エフェクトの描画
	bulletEffect.render(device, view, projection, cameraPosition);

	// ダウンエフェクトの描画
	downEffect.render(device, view, projection, cameraPosition);

	// アップエフェクトの描画
	upEffect.render(device, view, projection, cameraPosition);

	// ラインエフェクトの描画
	lineEffect.render(device, view, projection, cameraPosition);

	//バレットの描画
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].render(device, view, projection, cameraPosition);
	}
	//メモリーパイルの描画
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].render(device, view, projection, cameraPosition);
	}
	//リカージョンの描画
	if (onRecursion) recursion->render(device, view, projection, cameraPosition);
	//メモリーラインの描画
	memoryLine.render(device, view, projection, cameraPosition);
	//スターラインの描画
	starLine.render(device, view, projection, cameraPosition);
	//衝撃波の描画
	for(int i = 0;i<NUM_SHOCK_WAVE;i++)
		if (onShockWave[i])
			shockWave[i]->render(device, view, projection, cameraPosition);
	//メモリーラインの切断ガイドの表示
	if (collidedOpponentMemoryLine)
	{

	}

	//デバッグ時描画
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//【回復処理】
// [処理内容]自動回復を行う
//===================================================================================================================================
void Player::recorvery(float frameTime)
{
	if (whetherDown())return; 

	invincibleTimer = max(invincibleTimer - frameTime, 0);
	recoveryTimer += frameTime;
	if (!whetherInvincible() && recoveryTimer < INTERVAL_RECOVERY)return;
	recoveryHp(AMOUNT_RECOVERY);//自動HP回復
	recoveryTimer = 0.0f;
}

//===================================================================================================================================
//【移動操作】
// [処理内容1]入力された２次元ベクトルに応じてカメラ情報に基づき、速度へ加算処理を行う。
//===================================================================================================================================
void Player::moveOperation()
{
	if (whetherDown())return;
	//キーによる移動
	//前へ進む
	if (input->isKeyDown(keyTable.front)) {
		move(D3DXVECTOR2(0, -1), camera->getDirectionX(), camera->getDirectionZ());
	}
	//後ろへ進む
	if (input->isKeyDown(keyTable.back)) {
		move(D3DXVECTOR2(0, 1), camera->getDirectionX(), camera->getDirectionZ());
	}
	//左へ進む
	if (input->isKeyDown(keyTable.left)) {
		move(D3DXVECTOR2(-1, 0), camera->getDirectionX(), camera->getDirectionZ());
	}
	//右へ進む
	if (input->isKeyDown(keyTable.right))
	{
		move(D3DXVECTOR2(1, 0), camera->getDirectionX(), camera->getDirectionZ());
	}
	//リセット
	if (input->wasKeyPressed(keyTable.reset))
	{
		reset();
	}
	//コントローラスティックによる移動
	if (input->getController()[type]->checkConnect()) {
		move(input->getController()[type]->getLeftStick()*0.001f, camera->getDirectionX(), camera->getDirectionZ());
	}
}
//===================================================================================================================================
//【移動】
// [処理内容1]入力された２次元ベクトルに応じてカメラ情報に基づき、速度へ加算処理を行う。
// [処理内容2]移動後の姿勢制御を行う。
//===================================================================================================================================
void Player::move(D3DXVECTOR2 operationDirection,D3DXVECTOR3 cameraAxisX,D3DXVECTOR3 cameraAxisZ)
{
	if (operationDirection.x == 0 && operationDirection.y == 0)return;//入力値が0以下ならば移動しない
	//Y軸方向への成分を削除する
	D3DXVECTOR3 front = slip(cameraAxisZ, axisY.direction);
	D3DXVECTOR3 right = slip(cameraAxisX, axisY.direction);
	D3DXVec3Normalize(&front, &front);//正規化
	D3DXVec3Normalize(&right, &right);//正規化

	//操作方向をカメラのXZ方向に準拠した移動ベクトルへ変換する
	D3DXVECTOR3 moveDirection = operationDirection.x*right + -operationDirection.y*front;
	if (onGround) {
		addSpeed(moveDirection*SPEED);
	}
	else {
		addSpeed(moveDirection*SPEED/10);
	}
	postureControl(getAxisZ()->direction, moveDirection, 0.1f);
}

//===================================================================================================================================
//【ジャンプ】
// [処理内容]加速度へ加算処理を行う
//===================================================================================================================================
void Player::jump()
{
	if (whetherDown())return;
	acceleration += axisY.direction * JUMP_FORCE+speed/0.9f;
	onGround = false;
	// サウンドの再生
	sound->play(soundNS::TYPE::SE_JUMP, soundNS::METHOD::PLAY);
}

//===================================================================================================================================
//【リセット】
//===================================================================================================================================
void Player::reset()
{
	position = START_POSITION[type];
	quaternion = D3DXQUATERNION(0, 0, 0, 1);
	axisX.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 0, 0));
	axisY.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0));
	axisZ.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 1));
	reverseAxisX.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(-1, 0, 0));
	reverseAxisY.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, -1, 0));
	reverseAxisZ.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, -1));
	Object::update();
}

//===================================================================================================================================
//【状態切替】
//===================================================================================================================================
void Player::changeState(int _state)
{
	if (state == _state)return;//同じ状態なら処理しない
	state = _state;
	//【切替時初期化処理】
	switch (state)
	{
	case GROUND:	changeGround();		break;
	case FALL:		changeFall();		break;
	case DOWN:		changeDown();		break;
	case SKY:		changeSky();		break;
	case REVIVAL:	changeRevival();	break;
	default:							break;
	}
}

//===================================================================================================================================
//【地上モード 切替処理】
//===================================================================================================================================
void Player::changeGround()
{
	onGround = true;
	triggerShockWave();//衝撃波を発生させる
}
//===================================================================================================================================
//【地上モード 更新処理】
//===================================================================================================================================
void Player::updateGround(float frameTime, bool _onJump)
{
	//===========
	//【接地処理】
	//===========
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//重力方向を算出
	gravityRay.initialize(position, gravityDirection);								//重力レイの初期化
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//重力発生源との距離
	if (radius + attractorRadius >= distanceToAttractor - difference)
	{
		//相互半径合計値より引力発生源との距離が短いと接地
		onGround = true;
		onGravity = false;
		//めり込み補正
		//現在位置+ 垂直方向*(めり込み距離)
		setPosition(position + axisY.direction * (radius + attractorRadius - distanceToAttractor));
		//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
		setSpeed(reverseAxisY.slip(speed, axisY.direction));
		acceleration *= 0;
		if (_onJump)jump();//ジャンプ
	}
	else {
		//空中
		onGround = false;
		onGravity = true;
	}
	setGravity(gravityDirection, GRAVITY_FORCE*frameTime);//重力処理

}

//===================================================================================================================================
//【落下モード 切替処理】
//===================================================================================================================================
void Player::changeFall()
{
	fallTimer = FALL_TIME;//落下時間のセット
	onGround = false;
}
//===================================================================================================================================
//【落下モード 更新処理】
//===================================================================================================================================
void Player::updateFall(float frameTime)
{
	//===========
	//【接地処理】
	//===========
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//重力方向を算出
	gravityRay.initialize(position, gravityDirection);								//重力レイの初期化
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//重力発生源との距離
	D3DXVECTOR3 fallPosition;
	D3DXVECTOR3 groundPosition;
	D3DXVECTOR3 skyPosition;
	float rate;
	fallTimer -= frameTime;
	rate = fallTimer / FALL_TIME;
	groundPosition = axisY.direction * (radius + attractorRadius);
	skyPosition = axisY.direction * (radius + attractorRadius + skyHeight);
	D3DXVec3Lerp(&fallPosition, &groundPosition, &skyPosition, rate);
	setPosition(fallPosition);
	//【地上】モードへ切替
	if (!whetherFall())changeState(REVIVAL);
}

//===================================================================================================================================
//【ダウン時 切替処理】
//===================================================================================================================================
void Player::changeDown()
{
	elementMemoryPile = 0;
	revivalPoint = 0;
	decreaseRevivalTimer = DECREASE_REVIVAL_TIME;//復活ポイント減少時間のセット
	canShockWave = true;
	// ダウンエフェクト発生
	downEffect.generateDownEffect(200, position, downVec());

}
//===================================================================================================================================
//【ダウン時 更新処理】
//===================================================================================================================================
void Player::updateDown(float frameTime)
{
	// ダウンエフェクトの更新
	downEffect.update(frameTime);

	decreaseRevivalTimer -= frameTime;

	if (revivalPoint > 0 && decreaseRevivalTimer <= 0)
	{
		decreaseRevivalTimer = DECREASE_REVIVAL_TIME;
		revivalPoint -= DECREASE_REVIVAL_POINT;
		if (revivalPoint < 0)revivalPoint = 0;
	}
	if (input->wasKeyPressed(keyTable.revival)|| input->getController()[type]->wasButton(BUTTON_REVIVAL))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_REVIVAL_POINT, soundNS::METHOD::PLAY);
		revivalPoint += INCREASE_REVIVAL_POINT;
		// アップエフェクト発生
		upEffect.generateUpEffect(200, position, upVec());
		if (whetherRevival())changeState(REVIVAL);
	}

	updateGround(frameTime, false);
}
//===================================================================================================================================
//【ダウン時 更新処理】
//===================================================================================================================================
void Player::updateUpEffect(float frameTime)
{
	// アップエフェクトの更新
	upEffect.update(frameTime);
}
//===================================================================================================================================
//【上空モード 切替処理】
//===================================================================================================================================
void Player::changeSky()
{
	skyTimer = SKY_TIME;//上空モード時間のセット
	skyHeight = 0.0f;
	hp = MAX_HP;
	onGround = true;
	canShockWave = true;
	deleteMemoryItem();
}

//===================================================================================================================================
//【上空モード 更新処理】
//===================================================================================================================================
void Player::updateSky(float frameTime)
{
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//重力方向を算出
	gravityRay.initialize(position, gravityDirection);								//重力レイの初期化
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//重力発生源との距離
	skyTimer -= frameTime;
	skyHeight = min(skyHeight + 80.0f * frameTime, SKY_HEIGHT);
	if (radius + attractorRadius + skyHeight >= distanceToAttractor - difference)
	{
		//めり込み補正
		//現在位置+ 垂直方向*(めり込み距離)
		setPosition(position + axisY.direction * (radius + attractorRadius + skyHeight - distanceToAttractor));
		//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
		setSpeed(reverseAxisY.slip(speed, axisY.direction));
	}
	else {
		//空中
		//onGround = false;
		setGravity(gravityDirection, GRAVITY_FORCE);//重力処理
	}

	//【落下】モードへ切替
	if (!whetherSky())changeState(FALL);
}

//===================================================================================================================================
//【復活時 切替処理】
//===================================================================================================================================
void Player::changeRevival()
{
	// サウンドの再生
	sound->play(soundNS::TYPE::SE_REVIVAL, soundNS::METHOD::PLAY);

	invincibleTimer = INVINCIBLE_TIME;//無敵時間のセット
	changeState(GROUND);
	triggerShockWave();//衝撃波を発生させる
}
//===================================================================================================================================
//【復活時 更新処理】
//===================================================================================================================================
void Player::updateRevival(float frameTime)
{
	updateGround(frameTime,false);
}

//===================================================================================================================================
//【重力設定】
//[内容]重力源の位置情報で重力を設定する
//[引数]
//D3DXVECTOR3* attractorPosition：引力発生地点
//===================================================================================================================================
void Player::configurationGravity(D3DXVECTOR3* _attractorPosition,float _attractorRadius)
{
	//重力処理を行うために必要な要素をセット
	attractorPosition = _attractorPosition;
	attractorRadius = _attractorRadius;
	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//重力レイの初期化
	setGravity(gravityDirection, GRAVITY_FORCE);
	postureControl(axisY.direction, gravityDirection, 1.0f);
}

//===================================================================================================================================
//【重力設定(レイ)】
//[内容]レイを使用して重力源のメッシュの法線を取りだし、その法線を重力方向とする
//[引数]
// D3DXVECTOR3* attractorPosition	：引力発生地点
// LPD3DXMESH _attractorMesh		：（レイ処理用）引力発生メッシュ
// D3DXMATRIX _attractorMatrix		：（レイ処理用）引力発生行列
//[戻値]なし
//===================================================================================================================================
void Player::configurationGravityWithRay(D3DXVECTOR3* attractorPosition, LPD3DXMESH _attractorMesh, D3DXMATRIX* _attractorMatrix)
{
	//レイ判定を行うために必要な要素をセット
	attractorMesh =_attractorMesh;
	attractorMatrix = _attractorMatrix;

	//重力線を作成
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//重力レイの初期化
	
	//レイ判定
	if (gravityRay.rayIntersect(attractorMesh, *attractorMatrix))
	{//重力線上にポリゴンが衝突していた場合、ポリゴン法線を重力方向とし、姿勢を法線と一致させる。
		postureControl(axisY.direction, gravityRay.normal, 1.0f);
		setGravity(-gravityRay.normal, GRAVITY_FORCE);
	}
	else
	{//衝突ポリゴンが存在しない場合は、重力線をそのまま重力方向とし、姿勢を重力線と一致させる。
		postureControl(axisY.direction, gravityDirection, 1.0f);
		setGravity(gravityDirection, GRAVITY_FORCE);
	}
}

//===================================================================================================================================
//【弾の更新】
//===================================================================================================================================
void Player::updateBullet(float frameTime)
{
	intervalBullet = max(intervalBullet - frameTime, 0);//インターバルの更新
	//バレットの更新
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].update(frameTime);
	}

	// 弾エフェクトの更新
	bulletEffect.update(frameTime);

	//バレットの発射
	if (whetherDown())return;//ダウン時：発射不可
	if (((npc && input->wasKeyPressed(BUTTON_BULLET)) || (!npc && input->getMouseLButton()) || input->getController()[type]->isButton(BUTTON_BULLET))
		&& intervalBullet == 0)
	{
		// バレットエフェクト
		bulletEffect.generateBulletEffect(20, position, bulletVec());

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
		bullet[elementBullet].configurationGravity(attractorPosition,attractorRadius);
		bullet[elementBullet].Object::update();
		elementBullet++;
		if (elementBullet >= NUM_BULLET)elementBullet = 0;
		intervalBullet = INTERVAL_BULLET;
	}
}

//===================================================================================================================================
//【カメラの操作/更新】
//===================================================================================================================================
void Player::controlCamera(float frameTime)
{
	//操作軸反転操作
	if (input->wasKeyPressed(keyTable.cameraX))reverseValueXAxis *= -1;
	if (input->wasKeyPressed(keyTable.cameraY))reverseValueYAxis *= -1;
	//マウス操作
	camera->rotation(D3DXVECTOR3(0, 1, 0), (float)(input->getMouseRawX() * reverseValueXAxis));
	camera->rotation(camera->getHorizontalAxis(), (float)(input->getMouseRawY() * reverseValueYAxis));
	//コントローラ操作
	if (input->getController()[type]->checkConnect()) {
		camera->rotation(D3DXVECTOR3(0, 1, 0), input->getController()[type]->getRightStick().x*0.1f*frameTime*reverseValueXAxis);
		camera->rotation(camera->getHorizontalAxis(), input->getController()[type]->getRightStick().y*0.1f*frameTime*reverseValueYAxis);
	}

	//相手をロックオン(未完)
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
		//camera[PLAYER1].lockOn(*player[PLAYER2].getPosition(), frameTime);
	}

	camera->setUpVector(axisY.direction);
	camera->update();
}

//===================================================================================================================================
//【メモリーアイテムの操作/更新】
//===================================================================================================================================
void Player::updateMemoryItem(float frameTime)
{
	//ダウン状態ならば全てのメモリアイテムを削除
	if (whetherDown())
	{
		deleteMemoryItem();
	}

	if (onRecursion)recursionTimer -= frameTime;

	//リカージョン時間がなくなった場合リカージョンを削除する
	if (recursionTimer < 0)
	{
		if(onRecursion)SAFE_DELETE(recursion);
		onRecursion = false;
	}

	//接地有効距離かどうか
	bool whetherInstallationEffectiveDistance = false;
	int k = elementMemoryPile -1;
	if (k < 0)
	{
 		k = 0;
	}

	float length = D3DXVec3Length(&(position - *memoryPile[k].getPosition()));

	if(elementMemoryPile == 0)
	{
		whetherInstallationEffectiveDistance = true;
	}
	else if(	length	<= memoryLineNS::MAXIMUM_DISTANCE	//最大距離以下
			&&	length	>= memoryLineNS::MINIMUM_DISTANCE)	//最小距離以上
	{
		whetherInstallationEffectiveDistance = true;
	}
	
	if (length < memoryLineNS::MINIMUM_DISTANCE)	//最小距離未満
	{
		memoryLine.changeColor(device, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if (length > memoryLineNS::MAXIMUM_DISTANCE-5.0f)	//最大距離超過
	{
		memoryLine.changeColor(device, D3DXCOLOR(0.8f, 0.2f, 0.1f, 1.0f));
	}
	else {
		memoryLine.changeColor(device, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
	if (!whetherSky()&&
		elementMemoryPile != 0 &&//２本目以降の設置を行う状態
		D3DXVec3Length(&(position - *memoryPile[k].getPosition())) 
		> memoryLineNS::MAXIMUM_DISTANCE//最大距離超過
		)
	{
		//メモリーパイル・メモリーラインが消失し、プレイヤーはダウン状態になる。
		changeState(STATE::DOWN);
	}

	if (elementMemoryPile == NUM_MEMORY_PILE-1) {
		//最後のメモリーパイルの手前の場合
		memoryPile[elementMemoryPile].setPosition(position);
		memoryPile[elementMemoryPile].setQuaternion(quaternion);
		memoryPile[elementMemoryPile].activation();
		memoryPile[elementMemoryPile].setRenderFlag(false);
		memoryPile[elementMemoryPile].Object::update();
	}

	//メモリーパイルのセット
	if (!whetherDown()&&
		!whetherSky()&&
		whetherInstallationEffectiveDistance &&
		onGround && 
		memoryPile[elementMemoryPile].ready() &&
		((npc && input->wasKeyPressed(BUTTON_PILE)) || (!npc && input->getMouseRButtonTrigger()) || input->getController()[type]->wasButton(virtualControllerNS::L1)))
	{
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
			memoryLine.update(device, frameTime,memoryLineNS::PENTAGON);//メモリーラインの更新
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
			starLine.disconnect();
			//メモリーパイルとメモリーラインの消失
			for (int i = 0; i < NUM_MEMORY_PILE; i++)
			{
				memoryPile[i].switchLost();//消失
				memoryLine.disconnect();//切断
			}
		}
	}

	//[メッセージ]敵のメモリーパイルを切断する
	if (((npc && input->wasKeyPressed(BUTTON_CUT)) ||			//キーボード操作（AI用）
		input->getController()[type]->wasButton(BUTTON_CUT) ||	//コントローラ操作
		 (!npc && input->getMouseWheelState()==inputNS::DOWN)||	//マウスホイール操作
		 (GetAsyncKeyState(VK_RSHIFT) & 0x8000))				//キーボード操作（仮）
			&& state == GROUND) 								//地上モード時
	{
		disconnectOpponentMemoryLine = true;
		// ラインエフェクト発生
		lineEffect.generateLineEffect(200, collideMemoryLinePosition, upVec());
	}
	else
	{ disconnectOpponentMemoryLine = false;}

	//メモリーパイルの更新
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}
	
	//メモリーラインの更新
	memoryLine.update(device, frameTime,memoryLineNS::PENTAGON);

	// ラインエフェクトの更新
	lineEffect.update(frameTime);

	//スターラインの更新
	starLine.update(device, frameTime,memoryLineNS::STAR);//スターラインの更新
	
	//リカージョンの更新
	if (onRecursion)
	{
		recursion->update(frameTime);
	}
}
//===================================================================================================================================
//【メモリーアイテムの削除処理】
//===================================================================================================================================
void Player::deleteMemoryItem()
{
	elementMemoryPile = 0;
	//スターラインのリセット
	starLine.resetCurrentRenderNum();
	//メモリーパイルとメモリーラインの消失
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].switchLost();//消失
		memoryLine.disconnect();//切断
	}
	//リカージョンの削除
	if (onRecursion)SAFE_DELETE(recursion);
	onRecursion = false;
	recursionTimer = 0;
}
//===================================================================================================================================
//【弾ベクトル取得】
//===================================================================================================================================
D3DXVECTOR3 Player::bulletVec()
{
	//Y軸方向への成分を削除する
	D3DXVECTOR3 front = slip(camera->getDirectionZ(), axisY.direction);
	D3DXVec3Normalize(&front, &front);//正規化

	return front;
}
//===================================================================================================================================
//【ダウンベクトル取得】
//===================================================================================================================================
D3DXVECTOR3 Player::downVec()
{
	D3DXVECTOR3 downVec = reverseAxisY.direction;
	D3DXVec3Normalize(&downVec, &downVec);//正規化

	return downVec;
}
//===================================================================================================================================
//【アップベクトル取得】
//===================================================================================================================================
D3DXVECTOR3 Player::upVec()
{
	D3DXVECTOR3 upVec = axisY.direction;
	D3DXVec3Normalize(&upVec, &upVec);//正規化

	return upVec;
}
//===================================================================================================================================
//【メモリーラインの切断処理】
// [処理内容]呼び出されるとこのプレイヤーのメモリーラインが切断され、ダウン状態になる。
//===================================================================================================================================
void Player::disconnectMemoryLine()
{
	if (onRecursion)return;
	//メモリーパイルとメモリーラインの消失
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].switchLost();//消失
		memoryLine.disconnect();//切断
	}
	// サウンドの再生
	sound->play(soundNS::TYPE::SE_CUT_MEMORY_LINE, soundNS::METHOD::PLAY);
	changeState(playerNS::DOWN);
}

//===================================================================================================================================
//【衝撃波を発動】
//===================================================================================================================================
void Player::triggerShockWave()
{
	if (!canShockWave)return;	//使用可能か
	for (int i = 0;i < NUM_SHOCK_WAVE; i++)
	{
		if(onShockWave[i])continue;		//生成されているか
		shockWave[i] = new ShockWave();
		shockWave[i]->initialize(device, position, attractorRadius, *textureLoader->getTexture(textureLoaderNS::SHOCKWAVE), *shaderLoader->getEffect(shaderNS::SHOCK_WAVE));
		shockWave[i]->update(0.05*(float)i);
		onShockWave[i] = true;		//生成中にする
	}
	// サウンドの再生
	sound->play(soundNS::TYPE::SE_SHOCK_WAVE, soundNS::METHOD::PLAY);
	canShockWave = false;	//使用不可能にする
}

//===================================================================================================================================
//【衝撃波を削除】
//===================================================================================================================================
void Player::deleteShockWave(int n)
{
	delete shockWave[n];
	onShockWave[n] = false;
}

//===================================================================================================================================
//【衝撃波の更新処理】
//===================================================================================================================================
void Player::updateShockWave(float frameTime,int n)
{
	if (!onShockWave[n])return;//生成されていなければ更新しない
	if (!shockWave[n]->whetherActive())//衝撃波はアクティブでない
	{
		deleteShockWave(n);//削除
		return;
	}
	shockWave[n]->update(frameTime);//更新
}

//===================================================================================================================================
//【衝撃波の更新処理】
//===================================================================================================================================
bool Player::collideShockWave(D3DXVECTOR3 point,float radius)
{
	if (!onShockWave[1])return false;
	return (shockWave[1]->collision(point,radius));
}

//===================================================================================================================================
//【setter】
//===================================================================================================================================
void Player::setInput(Input* _input) { input = _input; }
void Player::setCamera(Camera* _camera) { camera = _camera; }
void Player::setSound(Sound* _sound) { sound = _sound; }
void Player::damgae(int value) { 
	hp = max(hp - value, 0);
	if (whetherDeath())changeState(DOWN);
}
void Player::recoveryHp(int value) { hp = min(hp + value, MAX_HP); }
void Player::setCollidedMemoryLine(bool frag) { collidedOpponentMemoryLine = frag; }
void Player::setCollideMemoryLinePosition(D3DXVECTOR3 value){ 
	collideMemoryLinePosition = value; }

//===================================================================================================================================
//【getter】
//===================================================================================================================================
int Player::getHp() { return hp; }
int Player::getRevivalPoint() { return revivalPoint; }
int Player::getState() { return state; }
int Player::getWage() { return wage; }
bool Player::whetherDown() { return state == DOWN; }
bool Player::whetherRevival() { return revivalPoint >= (uiRevivalNS::MAX_REVIVAL_POINT); }
bool Player::whetherDeath() {return hp <= 0;}
bool Player::whetherInvincible() {return invincibleTimer > 0;}
bool Player::whetherSky() { return skyTimer > 0; }
bool Player::whetherFall() { return fallTimer > 0; }
bool Player::whetherGenerationRecursion() { return onRecursion; }
bool Player::whetherCollidedOpponentMemoryLine() { return collidedOpponentMemoryLine; }
bool Player::messageDisconnectOpponentMemoryLine() { return disconnectOpponentMemoryLine; }
int Player::getElementMemoryPile() { return elementMemoryPile; }
Recursion* Player::getRecursion() { return recursion; }
MemoryPile* Player::getMemoryPile() { return memoryPile; }
MemoryLine*  Player::getMemoryLine() { return &memoryLine; }