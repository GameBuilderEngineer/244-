#include "Player.h"
using namespace playerNS;


//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Player::Player()
{
	hp = 100;
	maxHp = 100;
	sp = 100;
	maxSp = 100;
	onGravity = true;
	radius = 5.0f;
	activation();

	state = DEFAULT;

	recoveryTimer = 0.0f;		//自動回復時間
	invincibleTimer = 0.0f;		//無敵時間
	skyTimer = 0.0f;			//無敵時間
	downTimer = 0.0f;			//ダウンタイマー[体力が切れるorメモリーラインを切断される]
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
void Player::initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position)
{
	Object::initialize(device, _staticMesh, _position);
	bodyCollide.initialize(device, &position, _staticMesh->mesh);
	radius = bodyCollide.getRadius();
}
void Player::initialize(int playerType, LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh) {
	type = playerType;
	Object::initialize(device, _staticMesh, &(D3DXVECTOR3)START_POSITION[type]);
	bodyCollide.initialize(device, &position, _staticMesh->mesh);
	radius = bodyCollide.getRadius();
}



//===================================================================================================================================
//【更新】
//===================================================================================================================================
void Player::update(float frameTime)
{

	recoveryTimer += frameTime;
	if (recoveryTimer > RECOVERY_TIME)
	{
		recoveryHp(1);//自動HP回復
		//recoverySp(1);//自動SP回復
		recoveryTimer = 0.0f;
	}

	D3DXVECTOR3 moveDirection;

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//加速度が小さい場合、加算しない
		speed += acceleration;
	}

	//位置更新
	position += speed*frameTime;

	//加速度減衰
	acceleration *= 0.9f;
	
	//姿勢制御
	postureControl(axisY.direction, reverseAxisY.normal,3.0f * frameTime);


	Object::update();
}

//===================================================================================================================================
//【描画】
//===================================================================================================================================
//【トゥーンレンダー】
void Player::toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon,
	LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine)
{
	Object::toonRender(device,view,projection,cameraPositon,effect,textureShade,textureLine);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}
//【通常描画】
void Player::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device,view,projection,cameraPositon);
#ifdef _DEBUG

	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//【ジャンプ】
//【処理内容】加速度へ加算処理を行う
//===================================================================================================================================
void Player::jump()
{
	acceleration += axisY.direction*JUMP_FORCE;
}

//===================================================================================================================================
//【移動】
//【処理内容】入力された２次元ベクトルに応じてカメラ情報に基づき、速度へ加算処理を行う。
//          合わせて
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
//リセット
//===================================================================================================================================
void Player::reset()
{
	position = D3DXVECTOR3(0, 10, 0);
	quaternion = D3DXQUATERNION(0, 0, 0, 1);
	axisX.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 0, 0));
	axisY.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0));
	axisZ.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 1));
	reverseAxisX.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(-1, 0, 0));
	reverseAxisY.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, -1, 0));
	reverseAxisZ.initialize(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, -1));
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
	case DEFAULT:
		break;
	case DOWN:
		down();
		break;
	case SKY:
		break;
	default:
		break;
	}
}

//===================================================================================================================================
//【ダウン時 切替処理】
//===================================================================================================================================
void Player::down()
{
	downTimer = DOWN;
}

//===================================================================================================================================
//【上空モード 切替処理】
//===================================================================================================================================
void Player::sky()
{
	skyTimer = DOWN;
}



//===================================================================================================================================
//【setter】
//===================================================================================================================================
void Player::damgae(int value) { hp = max(hp - value, 0); }
void Player::recoveryHp(int value) { hp = min(hp + value, maxHp); }
void Player::lostSp(int value) { sp = max(sp - value, 0); }
void Player::recoverySp(int value) { sp = min(sp + value, maxSp); }

//===================================================================================================================================
//【getter】
//===================================================================================================================================
int Player::getHp() { return hp; }
int Player::getMaxHp() { return maxHp; }
int Player::getSp() { return sp; }
int Player::getMaxSp() { return maxSp; }
int Player::getState() { return state; }
int Player::getWage() { return wage; }
