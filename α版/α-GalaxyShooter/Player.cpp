#include "Player.h"
using namespace playerNS;


//===================================================================================================================================
//ÅyÉRÉìÉXÉgÉâÉNÉ^Åz
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

	recoveryTimer = 0.0f;		//é©ìÆâÒïúéûä‘
	invincibleTimer = 0.0f;		//ñ≥ìGéûä‘
	skyTimer = 0.0f;			//ñ≥ìGéûä‘
	downTimer = 0.0f;			//É_ÉEÉìÉ^ÉCÉ}Å[[ëÃóÕÇ™êÿÇÍÇÈorÉÅÉÇÉäÅ[ÉâÉCÉìÇêÿífÇ≥ÇÍÇÈ]
}

//===================================================================================================================================
//ÅyÉfÉXÉgÉâÉNÉ^Åz
//===================================================================================================================================
Player::~Player()
{
}

//===================================================================================================================================
//Åyèâä˙âªÅz
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
//ÅyçXêVÅz
//===================================================================================================================================
void Player::update(float frameTime)
{

	recoveryTimer += frameTime;
	if (recoveryTimer > RECOVERY_TIME)
	{
		recoveryHp(1);//é©ìÆHPâÒïú
		//recoverySp(1);//é©ìÆSPâÒïú
		recoveryTimer = 0.0f;
	}

	D3DXVECTOR3 moveDirection;

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//â¡ë¨ìxÇ™è¨Ç≥Ç¢èÍçáÅAâ¡éZÇµÇ»Ç¢
		speed += acceleration;
	}

	//à íuçXêV
	position += speed*frameTime;

	//â¡ë¨ìxå∏êä
	acceleration *= 0.9f;
	
	//épê®êßå‰
	postureControl(axisY.direction, reverseAxisY.normal,3.0f * frameTime);


	Object::update();
}

//===================================================================================================================================
//Åyï`âÊÅz
//===================================================================================================================================
//ÅyÉgÉDÅ[ÉìÉåÉìÉ_Å[Åz
void Player::toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon,
	LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine)
{
	Object::toonRender(device,view,projection,cameraPositon,effect,textureShade,textureLine);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}
//Åyí èÌï`âÊÅz
void Player::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device,view,projection,cameraPositon);
#ifdef _DEBUG

	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//ÅyÉWÉÉÉìÉvÅz
//Åyèàóùì‡óeÅzâ¡ë¨ìxÇ÷â¡éZèàóùÇçsÇ§
//===================================================================================================================================
void Player::jump()
{
	acceleration += axisY.direction*JUMP_FORCE;
}

//===================================================================================================================================
//Åyà⁄ìÆÅz
//Åyèàóùì‡óeÅzì¸óÕÇ≥ÇÍÇΩÇQéüå≥ÉxÉNÉgÉãÇ…âûÇ∂ÇƒÉJÉÅÉâèÓïÒÇ…äÓÇ√Ç´ÅAë¨ìxÇ÷â¡éZèàóùÇçsÇ§ÅB
//          çáÇÌÇπÇƒ
//===================================================================================================================================
void Player::move(D3DXVECTOR2 operationDirection,D3DXVECTOR3 cameraAxisX,D3DXVECTOR3 cameraAxisZ)
{
	if (operationDirection.x == 0 && operationDirection.y == 0)return;//ì¸óÕílÇ™0à»â∫Ç»ÇÁÇŒà⁄ìÆÇµÇ»Ç¢
	//Yé≤ï˚å¸Ç÷ÇÃê¨ï™ÇçÌèúÇ∑ÇÈ
	D3DXVECTOR3 front = slip(cameraAxisZ, axisY.direction);
	D3DXVECTOR3 right = slip(cameraAxisX, axisY.direction);
	D3DXVec3Normalize(&front, &front);//ê≥ãKâª
	D3DXVec3Normalize(&right, &right);//ê≥ãKâª

	//ëÄçÏï˚å¸ÇÉJÉÅÉâÇÃXZï˚å¸Ç…èÄãíÇµÇΩà⁄ìÆÉxÉNÉgÉãÇ÷ïœä∑Ç∑ÇÈ
	D3DXVECTOR3 moveDirection = operationDirection.x*right + -operationDirection.y*front;
	addSpeed(moveDirection*SPEED);
	postureControl(getAxisZ()->direction, moveDirection, 0.1f);
}

//===================================================================================================================================
//ÉäÉZÉbÉg
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
//ÅyèÛë‘êÿë÷Åz
//===================================================================================================================================
void Player::changeState(int _state)
{
	if (state == _state)return;//ìØÇ∂èÛë‘Ç»ÇÁèàóùÇµÇ»Ç¢
	state = _state;
	//Åyêÿë÷éûèâä˙âªèàóùÅz
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
//ÅyÉ_ÉEÉìéû êÿë÷èàóùÅz
//===================================================================================================================================
void Player::down()
{
	downTimer = DOWN;
}

//===================================================================================================================================
//Åyè„ãÛÉÇÅ[Éh êÿë÷èàóùÅz
//===================================================================================================================================
void Player::sky()
{
	skyTimer = DOWN;
}



//===================================================================================================================================
//ÅysetterÅz
//===================================================================================================================================
void Player::damgae(int value) { hp = max(hp - value, 0); }
void Player::recoveryHp(int value) { hp = min(hp + value, maxHp); }
void Player::lostSp(int value) { sp = max(sp - value, 0); }
void Player::recoverySp(int value) { sp = min(sp + value, maxSp); }

//===================================================================================================================================
//ÅygetterÅz
//===================================================================================================================================
int Player::getHp() { return hp; }
int Player::getMaxHp() { return maxHp; }
int Player::getSp() { return sp; }
int Player::getMaxSp() { return maxSp; }
int Player::getState() { return state; }
int Player::getWage() { return wage; }
