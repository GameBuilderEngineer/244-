//===================================================================================================================================
//【Player.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/04
//===================================================================================================================================
#include "Player.h"
using namespace playerNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Player::Player()
{
	ZeroMemory(&keyTable, sizeof(OperationKeyTable));
	hp = 100;
	maxHp = 100;
	sp = 100;
	maxSp = 100;
	onGravity = true;
	radius = 5.0f;
	activation();

	state = GROUND;

	recoveryTimer = 0.0f;					//自動回復時間
	invincibleTimer = 0.0f;					//無敵時間
	fallTimer = 0.0f;						//落下時間
	skyTimer = 0.0f;						//上空モード時間
	downTimer = 0.0f;						//ダウンタイマー[体力が切れるorメモリーラインを切断される]

	onGround = false;						//接地判定

	skyHeight = 0.0f;
	modelType = staticMeshNS::ADULT;
	reverseValueXAxis = CAMERA_SPEED;		//操作Ｘ軸
	reverseValueYAxis = CAMERA_SPEED;		//操作Ｙ軸
	onRecursion = false;					//リカージョン生成フラグ
	onShockWave = false;					//衝撃波発動フラグ
	collidedOpponentMemoryLine = false;		//相手のメモリーラインとの衝突フラグ
	disconnectOpponentMemoryLine = false;	//敵メモリーライン切断メッセージフラグ
	elementBullet = 0;						//弾アクセス要素数
	elementMemoryPile = 0;					//メモリーパイル要素数
	intervalBullet = 0;						//発弾間隔
	difference = DIFFERENCE_FIELD;			//フィールド補正差分
	recursion = NULL;						//リカージョンNULL
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
	this->modelType = modelType;
	this->textureLoader = textureLoader;
	this->shaderLoader = shaderLoader;

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
	Object::initialize(device, &staticMeshLoader->staticMesh[staticMeshNS::SAMPLE_TOON_MESH], &(D3DXVECTOR3)START_POSITION[type]);
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
		*shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::LIGHT001));

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
	bool onJump = false;			//ジャンプフラグ

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
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_JUMP, soundNS::METHOD::PLAY);
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
	switch (state)
	{
	case FALL:
		fallTimer -= frameTime;
		rate = fallTimer / FALL_TIME;
		groundPosition = axisY.direction * (radius + attractorRadius);
		skyPosition = axisY.direction * (radius + attractorRadius + skyHeight);
		D3DXVec3Lerp(&fallPosition, &groundPosition, &skyPosition, rate);
		setPosition(fallPosition);
		if (!whetherFall())changeState(GROUND);
		break;
	case SKY:
		skyTimer -= frameTime;
		skyHeight = min(skyHeight + 80.0f * frameTime, SKY_HEIGHT);
		if (radius + attractorRadius + skyHeight >= distanceToAttractor - difference)
		{
			//相互半径合計値より引力発生源との距離が短いと接地
			//相互半径合計値より引力発生源との距離が短いと接地
			onGround = true;
			//めり込み補正
			//現在位置+ 垂直方向*(めり込み距離)
			setPosition(position + axisY.direction * (radius + attractorRadius + skyHeight - distanceToAttractor));
			//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
			setSpeed(reverseAxisY.slip(speed, axisY.direction));
		}
		else {
			//空中
			onGround = false;
			setGravity(gravityDirection, GRAVITY_FORCE);//重力処理
		}
		if (!whetherSky())changeState(FALL);
		break;
	case GROUND:
		if (radius + attractorRadius >= distanceToAttractor - difference)
		{
			//相互半径合計値より引力発生源との距離が短いと接地
			onGround = true;
			//めり込み補正
			//現在位置+ 垂直方向*(めり込み距離)
			setPosition(position + axisY.direction * (radius + attractorRadius - distanceToAttractor));
			//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
			setSpeed(reverseAxisY.slip(speed, axisY.direction));
			if (onJump)jump();//ジャンプ
		}
		else {
			//空中
			onGround = false;
			setGravity(gravityDirection, GRAVITY_FORCE);//重力処理
		}
		break;
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
	updateShockWave(frameTime);
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
	otherRender(device,view,projection,cameraPosition);
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
	//メモリーラインの描画
	memoryLine.render(device, view, projection, cameraPosition);
	//リカージョンの描画
	if (onRecursion) recursion->render(device, view, projection, cameraPosition);
	//衝撃波の描画
	if (onShockWave) shockWave->render(device, view, projection, cameraPosition);
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
	if (whetherDown()) {
		downTimer = max(downTimer - frameTime,0);
		if (!whetherDown())changeState(REVIVAL);
		return;
	}
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
	addSpeed(moveDirection*SPEED);
	postureControl(getAxisZ()->direction, moveDirection, 0.1f);
}

//===================================================================================================================================
//【ジャンプ】
// [処理内容]加速度へ加算処理を行う
//===================================================================================================================================
void Player::jump()
{
	if (whetherDown())return;
	acceleration += axisY.direction*JUMP_FORCE;
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
	case GROUND:	ground();	break;
	case FALL:		fall();		break;
	case DOWN:		down();		break;
	case SKY:		sky();		break;
	case REVIVAL:	revival();	break;
	default:					break;
	}
}

//===================================================================================================================================
//【地上モード 切替処理】
//===================================================================================================================================
void Player::ground()
{
	triggerShockWave();//衝撃波を発生させる
}

//===================================================================================================================================
//【落下モード 切替処理】
//===================================================================================================================================
void Player::fall()
{
	fallTimer = FALL_TIME;//落下時間のセット
	// サウンドの再生
	sound->play(soundNS::TYPE::SE_LANDING, soundNS::METHOD::PLAY);
}

//===================================================================================================================================
//【ダウン時 切替処理】
//===================================================================================================================================
void Player::down()
{
	downTimer = DOWN_TIME;//ダウン時間のセット
}

//===================================================================================================================================
//【上空モード 切替処理】
//===================================================================================================================================
void Player::sky()
{
	skyTimer = SKY_TIME;//上空モード時間のセット
	skyHeight = 0.0f;
}

//===================================================================================================================================
//【復活時 切替処理】
//===================================================================================================================================
void Player::revival()
{
	invincibleTimer = INVINCIBLE_TIME;//無敵時間のセット
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

	//バレットの発射
	if (whetherDown())return;//ダウン時：発射不可
	if ((input->getMouseLButton() || input->getController()[type]->isButton(BUTTON_BULLET))
		&& intervalBullet == 0)
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
//【カメラの操作/更新】
//===================================================================================================================================
void Player::updateMemoryItem(float frameTime)
{
	//1Pのメモリーパイルのセット
	if (onGround && 
		memoryPile[elementMemoryPile].ready() &&
		(input->getMouseRButtonTrigger() || input->getController()[type]->wasButton(virtualControllerNS::L1)))
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
	}

	//敵のメモリーパイルの切断メッセージ
	if ((input->getController()[type]->wasButton(virtualControllerNS::A) || (GetAsyncKeyState(VK_RSHIFT) & 0x8000))
			&& state == GROUND) 
	{disconnectOpponentMemoryLine = true;}
	else
	{ disconnectOpponentMemoryLine = false;}

	//メモリーパイルの更新
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}
	
	//メモリーラインの更新
	memoryLine.update(device, frameTime);
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
	if (onShockWave)return;
	shockWave = new ShockWave();
	shockWave->initialize(device, position, attractorRadius, *textureLoader->getTexture(textureLoaderNS::UV_GRID), *shaderLoader->getEffect(shaderNS::SHOCK_WAVE));
	// サウンドの再生
	sound->play(soundNS::TYPE::SE_SHOCK_WAVE, soundNS::METHOD::PLAY);
	onShockWave = true;
}

//===================================================================================================================================
//【衝撃波を削除】
//===================================================================================================================================
void Player::deleteShockWave()
{
	SAFE_DELETE(shockWave);
	onShockWave = false;
}

//===================================================================================================================================
//【衝撃波を発動】
//===================================================================================================================================
void Player::updateShockWave(float frameTime)
{
	if (!onShockWave)return;
	if (!shockWave->whetherActive())
	{
		deleteShockWave();
		return;
	}
	shockWave->update(frameTime);
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
void Player::recoveryHp(int value) { hp = min(hp + value, maxHp); }
void Player::lostSp(int value) { sp = max(sp - value, 0); }
void Player::recoverySp(int value) { sp = min(sp + value, maxSp); }
void Player::setCollidedMemoryLine(bool frag) { collidedOpponentMemoryLine = frag; }

//===================================================================================================================================
//【getter】
//===================================================================================================================================
int Player::getHp() { return hp; }
int Player::getMaxHp() { return maxHp; }
int Player::getSp() { return sp; }
int Player::getMaxSp() { return maxSp; }
int Player::getState() { return state; }
int Player::getWage() { return wage; }
bool Player::whetherDown() { return downTimer > 0; }
bool Player::whetherDeath() {return hp <= 0;}
bool Player::whetherInvincible() {return invincibleTimer > 0;}
bool Player::whetherSky() { return skyTimer > 0; }
bool Player::whetherFall() { return fallTimer > 0; }
bool Player::whetherGenerationRecursion() { return onRecursion; }
bool Player::messageDisconnectOpponentMemoryLine() { return disconnectOpponentMemoryLine; }
Recursion* Player::getRecursion() { return recursion; }
MemoryLine*  Player::getMemoryLine() { return &memoryLine; }