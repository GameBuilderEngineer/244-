//===================================================================================================================================
//�yPlayer.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/04
//===================================================================================================================================
#include "Player.h"
using namespace playerNS;

//===================================================================================================================================
//�y�R���X�g���N�^�z
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

	recoveryTimer = 0.0f;					//�����񕜎���
	invincibleTimer = 0.0f;					//���G����
	fallTimer = 0.0f;						//��������
	skyTimer = 0.0f;						//��󃂁[�h����
	downTimer = 0.0f;						//�_�E���^�C�}�[[�̗͂��؂��or�������[���C����ؒf�����]

	onGround = false;						//�ڒn����

	skyHeight = 0.0f;
	modelType = staticMeshNS::ADULT;
	reverseValueXAxis = CAMERA_SPEED;		//����w��
	reverseValueYAxis = CAMERA_SPEED;		//����x��
	onRecursion = false;					//���J�[�W���������t���O
	onShockWave = false;					//�Ռ��g�����t���O
	collidedOpponentMemoryLine = false;		//����̃������[���C���Ƃ̏Փ˃t���O
	disconnectOpponentMemoryLine = false;	//�G�������[���C���ؒf���b�Z�[�W�t���O
	elementBullet = 0;						//�e�A�N�Z�X�v�f��
	elementMemoryPile = 0;					//�������[�p�C���v�f��
	intervalBullet = 0;						//���e�Ԋu
	difference = DIFFERENCE_FIELD;			//�t�B�[���h�␳����
	recursion = NULL;						//���J�[�W����NULL
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
//�v���C���[�^�C�v���Ƃɏ��������e��ύX
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
	//Object::initialize(device, &staticMeshLoader->staticMesh[modelType], &(D3DXVECTOR3)START_POSITION[type]);
	bodyCollide.initialize(device, &position, staticMesh->mesh);
	radius = bodyCollide.getRadius();
	
	//�e�̏�����
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].initialize(device, &staticMeshLoader->staticMesh[staticMeshNS::BULLET], &D3DXVECTOR3(0, 0, 0));
	}
	//�������[�p�C���̏�����
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].initialize(device, &staticMeshLoader->staticMesh[staticMeshNS::MEMORY_PILE], &D3DXVECTOR3(0, 0, 0));
	}

	//�������[���C���̏�����
	memoryLine.initialize(device, memoryPile, NUM_MEMORY_PILE, this,
		*shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::LIGHT001));

}

//===================================================================================================================================
//�y�X�V�z
//[�������e1]�񕜏���
//[�������e2]�ړ�����
//[�������e3]�W�����v����
//[�������e4]�d�͏���
//[�������e5]�ڒn����
//[�������e6]�������[�p�C���E�������[���C���E���J�[�W�����̏���
//===================================================================================================================================
void Player::update(float frameTime)
{
#ifdef _DEBUG
	//�����p
	if (input->getController()[type]->wasButton(virtualControllerNS::UP))
		difference += 0.01f;
	if (input->getController()[type]->wasButton(virtualControllerNS::DOWN))
		difference -= 0.01f;
#endif // _DEBUG

	//�O����
	setSpeed(D3DXVECTOR3(0, 0, 0));	//���x�i�ړ��ʁj�̏�����
	bool onJump = false;			//�W�����v�t���O

	//===========
	//�y�񕜁z
	//===========
	recorvery(frameTime);

	//===========
	//�y�ړ������z
	//===========
	moveOperation();

	//===========
	//�y�W�����v�z
	//===========
	if (input->wasKeyPressed(keyTable.jump) ||
		input->getController()[type]->wasButton(BUTTON_JUMP))
	{
		onJump = true;
	}

	//��
	if (input->wasKeyPressed('H'))
	{
		changeState(SKY);
	}
	//��
	if (input->wasKeyPressed(keyTable.provisional))
	{
		triggerShockWave();
	}


	//===========
	//�y�ڒn�����z
	//===========
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//�d�͕������Z�o
	gravityRay.initialize(position, gravityDirection);								//�d�̓��C�̏�����
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//�d�͔������Ƃ̋���
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
			//���ݔ��a���v�l�����͔������Ƃ̋������Z���Ɛڒn
			//���ݔ��a���v�l�����͔������Ƃ̋������Z���Ɛڒn
			onGround = true;
			//�߂荞�ݕ␳
			//���݈ʒu+ ��������*(�߂荞�݋���)
			setPosition(position + axisY.direction * (radius + attractorRadius + skyHeight - distanceToAttractor));
			//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
			setSpeed(reverseAxisY.slip(speed, axisY.direction));
		}
		else {
			//��
			onGround = false;
			setGravity(gravityDirection, GRAVITY_FORCE);//�d�͏���
		}
		if (!whetherSky())changeState(FALL);
		break;
	case GROUND:
		if (radius + attractorRadius >= distanceToAttractor - difference)
		{
			//���ݔ��a���v�l�����͔������Ƃ̋������Z���Ɛڒn
			onGround = true;
			//�߂荞�ݕ␳
			//���݈ʒu+ ��������*(�߂荞�݋���)
			setPosition(position + axisY.direction * (radius + attractorRadius - distanceToAttractor));
			//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
			setSpeed(reverseAxisY.slip(speed, axisY.direction));
			if (onJump)jump();//�W�����v
		}
		else {
			//��
			onGround = false;
			setGravity(gravityDirection, GRAVITY_FORCE);//�d�͏���
		}
		break;
	}

	//===========
	//�y�����x�����z
	//===========
	if (D3DXVec3Length(&acceleration) > 0.01f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}
	acceleration *= 0.9f;//�����x����
	
	//===========
	//�y�ʒu�X�V�z
	//===========
	position += speed*frameTime;
	
	//===========
	//�y�p������z
	//===========
	postureControl(axisY.direction, -gravityRay.direction,3.0f * frameTime);
	
	//===========
	//�y�I�u�W�F�N�g�F�X�V�z
	//===========
	Object::update();

	//===========
	//�y�e�̍X�V�z
	//===========
	updateBullet(frameTime);

	//===========
	//�y�J�����̑���z
	//===========
	controlCamera(frameTime);

	//===========
	//�y�������[�p�C���E�������[���C���E���J�[�W�����̍X�V�z
	//===========
	updateMemoryItem(frameTime);

	//===========
	//�y�Ռ��g�̍X�V�z
	//===========
	updateShockWave(frameTime);
}

//===================================================================================================================================
//�y�`��z
//===================================================================================================================================
//======================
//�y�g�D�[�������_�[�z
//======================
void Player::toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition,
	LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine)
{
	Object::toonRender(device,view,projection, cameraPosition,effect,textureShade,textureLine);
	//���̃I�u�W�F�N�g�̕`��
	otherRender(device,view,projection,cameraPosition);
}
//======================
//�y�ʏ�`��z
//======================
void Player::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	Object::render(device,view,projection, cameraPosition);
	//���̃I�u�W�F�N�g�̕`��
	otherRender(device,view,projection,cameraPosition);
}
//======================
//�y�{�̈ȊO�̑��̃I�u�W�F�N�g�`��z
//======================
void Player::otherRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	//�o���b�g�̕`��
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].render(device, view, projection, cameraPosition);
	}
	//�������[�p�C���̕`��
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].render(device, view, projection, cameraPosition);
	}
	//�������[���C���̕`��
	memoryLine.render(device, view, projection, cameraPosition);
	//���J�[�W�����̕`��
	if (onRecursion) recursion->render(device, view, projection, cameraPosition);
	//�Ռ��g�̕`��
	if (onShockWave) shockWave->render(device, view, projection, cameraPosition);
	//�������[���C���̐ؒf�K�C�h�̕\��
	if (collidedOpponentMemoryLine)
	{

	}
	//�f�o�b�O���`��
#ifdef _DEBUG
	bodyCollide.render(device, matrixWorld);
#endif // _DEBUG
}

//===================================================================================================================================
//�y�񕜏����z
// [�������e]�����񕜂��s��
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
	recoveryHp(AMOUNT_RECOVERY);//����HP��
	recoveryTimer = 0.0f;
}

//===================================================================================================================================
//�y�ړ�����z
// [�������e1]���͂��ꂽ�Q�����x�N�g���ɉ����ăJ�������Ɋ�Â��A���x�։��Z�������s���B
//===================================================================================================================================
void Player::moveOperation()
{
	if (whetherDown())return;
	//�L�[�ɂ��ړ�
	//�O�֐i��
	if (input->isKeyDown(keyTable.front)) {
		move(D3DXVECTOR2(0, -1), camera->getDirectionX(), camera->getDirectionZ());
	}

	//���֐i��
	if (input->isKeyDown(keyTable.back)) {
		move(D3DXVECTOR2(0, 1), camera->getDirectionX(), camera->getDirectionZ());
	}
	//���֐i��
	if (input->isKeyDown(keyTable.left)) {
		move(D3DXVECTOR2(-1, 0), camera->getDirectionX(), camera->getDirectionZ());
	}
	//�E�֐i��
	if (input->isKeyDown(keyTable.right))
	{
		move(D3DXVECTOR2(1, 0), camera->getDirectionX(), camera->getDirectionZ());
	}
	//���Z�b�g
	if (input->wasKeyPressed(keyTable.reset))
	{
		reset();
	}
	//�R���g���[���X�e�B�b�N�ɂ��ړ�
	if (input->getController()[type]->checkConnect()) {
		move(input->getController()[type]->getLeftStick()*0.001f, camera->getDirectionX(), camera->getDirectionZ());
	}
}
//===================================================================================================================================
//�y�ړ��z
// [�������e1]���͂��ꂽ�Q�����x�N�g���ɉ����ăJ�������Ɋ�Â��A���x�։��Z�������s���B
// [�������e2]�ړ���̎p��������s���B
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
//�y�W�����v�z
// [�������e]�����x�։��Z�������s��
//===================================================================================================================================
void Player::jump()
{
	if (whetherDown())return;
	acceleration += axisY.direction*JUMP_FORCE;
}

//===================================================================================================================================
//�y���Z�b�g�z
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
//�y��Ԑؑցz
//===================================================================================================================================
void Player::changeState(int _state)
{
	if (state == _state)return;//������ԂȂ珈�����Ȃ�
	state = _state;
	//�y�ؑ֎������������z
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
//�y�n�ヂ�[�h �ؑ֏����z
//===================================================================================================================================
void Player::ground()
{
	triggerShockWave();//�Ռ��g�𔭐�������
}

//===================================================================================================================================
//�y�������[�h �ؑ֏����z
//===================================================================================================================================
void Player::fall()
{
	fallTimer = FALL_TIME;//�������Ԃ̃Z�b�g
}

//===================================================================================================================================
//�y�_�E���� �ؑ֏����z
//===================================================================================================================================
void Player::down()
{
	downTimer = DOWN_TIME;//�_�E�����Ԃ̃Z�b�g
}

//===================================================================================================================================
//�y��󃂁[�h �ؑ֏����z
//===================================================================================================================================
void Player::sky()
{
	skyTimer = SKY_TIME;//��󃂁[�h���Ԃ̃Z�b�g
	skyHeight = 0.0f;
}

//===================================================================================================================================
//�y������ �ؑ֏����z
//===================================================================================================================================
void Player::revival()
{
	invincibleTimer = INVINCIBLE_TIME;//���G���Ԃ̃Z�b�g
}

//===================================================================================================================================
//�y�d�͐ݒ�z
//[���e]�d�͌��̈ʒu���ŏd�͂�ݒ肷��
//[����]
//D3DXVECTOR3* attractorPosition�F���͔����n�_
//===================================================================================================================================
void Player::configurationGravity(D3DXVECTOR3* _attractorPosition,float _attractorRadius)
{
	//�d�͏������s�����߂ɕK�v�ȗv�f���Z�b�g
	attractorPosition = _attractorPosition;
	attractorRadius = _attractorRadius;
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//�d�̓��C�̏�����
	setGravity(gravityDirection, GRAVITY_FORCE);
	postureControl(axisY.direction, gravityDirection, 1.0f);
}

//===================================================================================================================================
//�y�d�͐ݒ�(���C)�z
//[���e]���C���g�p���ďd�͌��̃��b�V���̖@������肾���A���̖@�����d�͕����Ƃ���
//[����]
// D3DXVECTOR3* attractorPosition	�F���͔����n�_
// LPD3DXMESH _attractorMesh		�F�i���C�����p�j���͔������b�V��
// D3DXMATRIX _attractorMatrix		�F�i���C�����p�j���͔����s��
//[�ߒl]�Ȃ�
//===================================================================================================================================
void Player::configurationGravityWithRay(D3DXVECTOR3* attractorPosition, LPD3DXMESH _attractorMesh, D3DXMATRIX* _attractorMatrix)
{
	//���C������s�����߂ɕK�v�ȗv�f���Z�b�g
	attractorMesh =_attractorMesh;
	attractorMatrix = _attractorMatrix;

	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//�d�̓��C�̏�����
	
	//���C����
	if (gravityRay.rayIntersect(attractorMesh, *attractorMatrix))
	{//�d�͐���Ƀ|���S�����Փ˂��Ă����ꍇ�A�|���S���@�����d�͕����Ƃ��A�p����@���ƈ�v������B
		postureControl(axisY.direction, gravityRay.normal, 1.0f);
		setGravity(-gravityRay.normal, GRAVITY_FORCE);
	}
	else
	{//�Փ˃|���S�������݂��Ȃ��ꍇ�́A�d�͐������̂܂܏d�͕����Ƃ��A�p�����d�͐��ƈ�v������B
		postureControl(axisY.direction, gravityDirection, 1.0f);
		setGravity(gravityDirection, GRAVITY_FORCE);
	}
}

//===================================================================================================================================
//�y�e�̍X�V�z
//===================================================================================================================================
void Player::updateBullet(float frameTime)
{
	intervalBullet = max(intervalBullet - frameTime, 0);//�C���^�[�o���̍X�V
	//�o���b�g�̍X�V
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].update(frameTime);
	}

	//�o���b�g�̔���
	if (whetherDown())return;//�_�E�����F���˕s��
	if ((input->getMouseLButton() || input->getController()[type]->isButton(BUTTON_BULLET))
		&& intervalBullet == 0)
	{
		bullet[elementBullet].setPosition(position);
		//Y�������ւ̐������폜����
		D3DXVECTOR3 front = slip(camera->getDirectionZ(), axisY.direction);
		D3DXVec3Normalize(&front, &front);//���K��
		bullet[elementBullet].addSpeed(front*0.2);//���x�����Z
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
//�y�J�����̑���/�X�V�z
//===================================================================================================================================
void Player::controlCamera(float frameTime)
{
	//���쎲���]����
	if (input->wasKeyPressed(keyTable.cameraX))reverseValueXAxis *= -1;
	if (input->wasKeyPressed(keyTable.cameraY))reverseValueYAxis *= -1;
	//�}�E�X����
	camera->rotation(D3DXVECTOR3(0, 1, 0), (float)(input->getMouseRawX() * reverseValueXAxis));
	camera->rotation(camera->getHorizontalAxis(), (float)(input->getMouseRawY() * reverseValueYAxis));
	//�R���g���[������
	if (input->getController()[type]->checkConnect()) {
		camera->rotation(D3DXVECTOR3(0, 1, 0), input->getController()[type]->getRightStick().x*0.1f*frameTime*reverseValueXAxis);
		camera->rotation(camera->getHorizontalAxis(), input->getController()[type]->getRightStick().y*0.1f*frameTime*reverseValueYAxis);
	}

	//��������b�N�I��(����)
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
		//camera[PLAYER1].lockOn(*player[PLAYER2].getPosition(), frameTime);
	}

	camera->setUpVector(axisY.direction);
	camera->update();
}

//===================================================================================================================================
//�y�J�����̑���/�X�V�z
//===================================================================================================================================
void Player::updateMemoryItem(float frameTime)
{
	//1P�̃������[�p�C���̃Z�b�g
	if (onGround && 
		memoryPile[elementMemoryPile].ready() &&
		(input->getMouseRButtonTrigger() || input->getController()[type]->wasButton(virtualControllerNS::L1)))
	{
		memoryPile[elementMemoryPile].setPosition(position);
		memoryPile[elementMemoryPile].setQuaternion(quaternion);
		memoryPile[elementMemoryPile].activation();
		memoryPile[elementMemoryPile].Object::update();
		elementMemoryPile++;
		//�������[�p�C����S�Đݒu���邱�Ƃɐ���
		if (elementMemoryPile >= NUM_MEMORY_PILE)
		{
			elementMemoryPile = 0;//�Z�b�g����Ώۂ�0�Ԃ̃������p�C���ɐؑ�
			//���J�[�W�����ɂ�郏�X�����m��������ւ̕ϊ����I���܂ł́A�������[�p�C�����Z�b�g�ł��Ȃ���Ԃɂ���
			onRecursion = true;
			//�ݒu���ꂽ�������[�p�C��5�_��p���ă��J�[�W�����p�̃|���S���𐶐�����B
			D3DXVECTOR3 vertex[NUM_MEMORY_PILE];
			for (int i = 0; i < NUM_MEMORY_PILE; i++)
			{
				vertex[i] = *memoryPile[i].getPosition();
			}
			//���J�[�W�����̐���
			recursion = new Recursion;
			recursion->initialize(device, vertex, *textureLoader->getTexture(textureLoaderNS::RECURSION), *shaderLoader->getEffect(shaderNS::RECURSION));
			//�������[�p�C���ƃ������[���C���̏���
			for (int i = 0; i < NUM_MEMORY_PILE; i++)
			{
				memoryPile[i].switchLost();//����
				memoryLine.disconnect();//�ؒf
			}
		}
	}

	//�G�̃������[�p�C���̐ؒf���b�Z�[�W
	if ((input->getController()[type]->wasButton(virtualControllerNS::A) || (GetAsyncKeyState(VK_RSHIFT) & 0x8000))
			&& state == GROUND) 
	{disconnectOpponentMemoryLine = true;}
	else
	{ disconnectOpponentMemoryLine = false;}

	//�������[�p�C���̍X�V
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}
	
	//�������[���C���̍X�V
	memoryLine.update(device, frameTime);
}
//===================================================================================================================================
//�y�e�x�N�g���擾�z
//===================================================================================================================================
D3DXVECTOR3 Player::bulletVec()
{
	//Y�������ւ̐������폜����
	D3DXVECTOR3 front = slip(camera->getDirectionZ(), axisY.direction);
	D3DXVec3Normalize(&front, &front);//���K��

	return front;
}
//===================================================================================================================================
//�y�������[���C���̐ؒf�����z
// [�������e]�Ăяo�����Ƃ��̃v���C���[�̃������[���C�����ؒf����A�_�E����ԂɂȂ�B
//===================================================================================================================================
void Player::disconnectMemoryLine()
{
	if (onRecursion)return;
	//�������[�p�C���ƃ������[���C���̏���
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].switchLost();//����
		memoryLine.disconnect();//�ؒf
	}
	changeState(playerNS::DOWN);
}

//===================================================================================================================================
//�y�Ռ��g�𔭓��z
//===================================================================================================================================
void Player::triggerShockWave()
{
	if (onShockWave)return;
	shockWave = new ShockWave();
	shockWave->initialize(device, position, attractorRadius, *textureLoader->getTexture(textureLoaderNS::UV_GRID), *shaderLoader->getEffect(shaderNS::SHOCK_WAVE));
	onShockWave = true;
}

//===================================================================================================================================
//�y�Ռ��g���폜�z
//===================================================================================================================================
void Player::deleteShockWave()
{
	SAFE_DELETE(shockWave);
	onShockWave = false;
}

//===================================================================================================================================
//�y�Ռ��g�𔭓��z
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
//�ysetter�z
//===================================================================================================================================
void Player::setInput(Input* _input) { input = _input; }
void Player::setCamera(Camera* _camera) { camera = _camera; }
void Player::damgae(int value) { 
	hp = max(hp - value, 0);
	if (whetherDeath())changeState(DOWN);
}
void Player::recoveryHp(int value) { hp = min(hp + value, maxHp); }
void Player::lostSp(int value) { sp = max(sp - value, 0); }
void Player::recoverySp(int value) { sp = min(sp + value, maxSp); }
void Player::setCollidedMemoryLine(bool frag) { collidedOpponentMemoryLine = frag; }

//===================================================================================================================================
//�ygetter�z
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