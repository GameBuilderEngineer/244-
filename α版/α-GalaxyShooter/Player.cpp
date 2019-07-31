#include "Player.h"
using namespace playerNS;


//===================================================================================================================================
//�y�R���X�g���N�^�z
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

	recoveryTimer = 0.0f;		//�����񕜎���
	invincibleTimer = 0.0f;		//���G����
	skyTimer = 0.0f;			//���G����
	downTimer = 0.0f;			//�_�E���^�C�}�[[�̗͂��؂��or�������[���C����ؒf�����]
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
Player::~Player()
{
}

//===================================================================================================================================
//�y�������z
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
//�y�X�V�z
//===================================================================================================================================
void Player::update(float frameTime)
{

	recoveryTimer += frameTime;
	if (recoveryTimer > RECOVERY_TIME)
	{
		recoveryHp(1);//����HP��
		//recoverySp(1);//����SP��
		recoveryTimer = 0.0f;
	}

	D3DXVECTOR3 moveDirection;

	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}

	//�ʒu�X�V
	position += speed*frameTime;

	//�����x����
	acceleration *= 0.9f;
	
	//�p������
	postureControl(axisY.direction, reverseAxisY.normal,3.0f * frameTime);


	Object::update();
}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
//�y�g�D�[�������_�[�z
void Player::toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon,
	LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine)
{
	Object::toonRender(device,view,projection,cameraPositon,effect,textureShade,textureLine);
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}
//�y�ʏ�`��z
void Player::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon)
{
	Object::render(device,view,projection,cameraPositon);
#ifdef _DEBUG

	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//�y�W�����v�z
//�y�������e�z�����x�։��Z�������s��
//===================================================================================================================================
void Player::jump()
{
	acceleration += axisY.direction*JUMP_FORCE;
}

//===================================================================================================================================
//�y�ړ��z
//�y�������e�z���͂��ꂽ�Q�����x�N�g���ɉ����ăJ�������Ɋ�Â��A���x�։��Z�������s���B
//          ���킹��
//===================================================================================================================================
void Player::move(D3DXVECTOR2 operationDirection,D3DXVECTOR3 cameraAxisX,D3DXVECTOR3 cameraAxisZ)
{
	if (operationDirection.x == 0 && operationDirection.y == 0)return;//���͒l��0�ȉ��Ȃ�Έړ����Ȃ�
	//Y�������ւ̐������폜����
	D3DXVECTOR3 front = slip(cameraAxisZ, axisY.direction);
	D3DXVECTOR3 right = slip(cameraAxisX, axisY.direction);
	D3DXVec3Normalize(&front, &front);//���K��
	D3DXVec3Normalize(&right, &right);//���K��

	//����������J������XZ�����ɏ��������ړ��x�N�g���֕ϊ�����
	D3DXVECTOR3 moveDirection = operationDirection.x*right + -operationDirection.y*front;
	addSpeed(moveDirection*SPEED);
	postureControl(getAxisZ()->direction, moveDirection, 0.1f);
}

//===================================================================================================================================
//���Z�b�g
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
//�y��Ԑؑցz
//===================================================================================================================================
void Player::changeState(int _state)
{
	if (state == _state)return;//������ԂȂ珈�����Ȃ�
	state = _state;
	//�y�ؑ֎������������z
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
//�y�_�E���� �ؑ֏����z
//===================================================================================================================================
void Player::down()
{
	downTimer = DOWN;
}

//===================================================================================================================================
//�y��󃂁[�h �ؑ֏����z
//===================================================================================================================================
void Player::sky()
{
	skyTimer = DOWN;
}



//===================================================================================================================================
//�ysetter�z
//===================================================================================================================================
void Player::damgae(int value) { hp = max(hp - value, 0); }
void Player::recoveryHp(int value) { hp = min(hp + value, maxHp); }
void Player::lostSp(int value) { sp = max(sp - value, 0); }
void Player::recoverySp(int value) { sp = min(sp + value, maxSp); }

//===================================================================================================================================
//�ygetter�z
//===================================================================================================================================
int Player::getHp() { return hp; }
int Player::getMaxHp() { return maxHp; }
int Player::getSp() { return sp; }
int Player::getMaxSp() { return maxSp; }
int Player::getState() { return state; }
int Player::getWage() { return wage; }
