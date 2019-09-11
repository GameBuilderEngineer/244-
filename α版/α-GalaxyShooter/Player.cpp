//===================================================================================================================================
//�yPlayer.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/09/03
//===================================================================================================================================
#include "Player.h"
#include "UIRevival.h"

using namespace playerNS;

// ��
static float time = 0.0f;

//===================================================================================================================================
//�y�R���X�g���N�^�z
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

	recoveryTimer = 0.0f;					//�����񕜎���
	invincibleTimer = 0.0f;					//���G����
	fallTimer = 0.0f;						//��������
	skyTimer = 0.0f;						//��󃂁[�h����
	decreaseRevivalTimer = 0.0f;			//�_�E���^�C�}�[[�̗͂��؂��or�������[���C����ؒf�����]

	onGround = false;						//�ڒn����

	skyHeight = 0.0f;
	modelType = gameMasterNS::ADAM;
	reverseValueXAxis = CAMERA_SPEED;		//����w��
	reverseValueYAxis = CAMERA_SPEED;		//����x��
	onJump = false;							//�W�����v�t���O
	onRecursion = false;					//���J�[�W���������t���O
	for (int i = 0; i < NUM_SHOCK_WAVE; i++)
	{
		onShockWave[i] = false;
	}//�Ռ��g�����t���O
	canShockWave = false;
	collidedOpponentMemoryLine = false;		//����̃������[���C���Ƃ̏Փ˃t���O
	disconnectOpponentMemoryLine = false;	//�G�������[���C���ؒf���b�Z�[�W�t���O
	elementBullet = 0;						//�e�A�N�Z�X�v�f��
	elementMemoryPile = 0;					//�������[�p�C���v�f��
	intervalBullet = 0;						//���e�Ԋu
	difference = DIFFERENCE_FIELD;			//�t�B�[���h�␳����
	recursion = NULL;						//���J�[�W����NULL
	recursionTimer = 0.0f;					//���J�[�W�����̐�������
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
void Player::initialize(int playerType, int modelType, LPDIRECT3DDEVICE9 _device, StaticMeshLoader* staticMeshLoader, TextureLoader* textureLoader, ShaderLoader* shaderLoader) {
	device = _device;
	type = playerType;
	this->modelType = modelType;
	this->textureLoader = textureLoader;
	this->shaderLoader = shaderLoader;
	this->sound = NULL;
	this->staticMeshLoader = staticMeshLoader;

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
		*shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::LIGHT_001));
	//�X�^�[���C���̏�����
	starLine.initialize(device, memoryPile, NUM_MEMORY_PILE, this,
		*shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::LIGHT_001));

	// �e�G�t�F�N�g������
	bulletEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// �_�E���G�t�F�N�g������
	downEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// �A�b�v�G�t�F�N�g������
	upEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// ���C���G�t�F�N�g������
	lineEffect.initialize(device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// �A�j���[�V����
	animationPlayer.initialize(_device, playerType, modelType);

	return;
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
	onJump = false;					//�W�����v�t���O

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
	if (animationPlayer.getFlagMoveBan() == false &&
		input->wasKeyPressed(keyTable.jump) ||
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


	switch (state)
	{
	case FALL:		updateFall(frameTime);			break;
	case SKY:		updateSky(frameTime);			break;
	case GROUND:	updateGround(frameTime,onJump);	break;
	case DOWN:		updateDown(frameTime);			break;
	case REVIVAL:	updateRevival(frameTime);		break;
	}

	//===========
	//�y�����x�����z
	//===========
	if (D3DXVec3Length(&acceleration) > 0.05f)
	{//�����x���������ꍇ�A���Z���Ȃ�
		speed += acceleration;
	}
	//acceleration *= 0.9f;//�����x����

	
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

	animationPlayer.update(input, state);

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
	for (int i = 0; i < NUM_SHOCK_WAVE; i++)
	{
		updateShockWave(frameTime,i);
	}

	//===========
	//�y�A�b�v�G�t�F�N�g�̍X�V�z
	//===========
	updateUpEffect(frameTime);
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
	//Object::toonRender(device,view,projection, cameraPosition,effect,textureShade,textureLine);
	animationPlayer.render(device, matrixWorld, staticMeshLoader);
	// ���̃I�u�W�F�N�g�̕`��
	otherRender(device,view,projection,cameraPosition);
}
//======================
//�y�ʏ�`��z
//======================
void Player::render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	//Object::render(device,view,projection, cameraPosition);
	animationPlayer.render(device, matrixWorld, staticMeshLoader);
	//���̃I�u�W�F�N�g�̕`��
	otherRender(device,view,projection,cameraPosition);
}
//======================
//�y�{�̈ȊO�̑��̃I�u�W�F�N�g�`��z
//======================
void Player::otherRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	// �e�G�t�F�N�g�̕`��
	bulletEffect.render(device, view, projection, cameraPosition);

	// �_�E���G�t�F�N�g�̕`��
	downEffect.render(device, view, projection, cameraPosition);

	// �A�b�v�G�t�F�N�g�̕`��
	upEffect.render(device, view, projection, cameraPosition);

	// ���C���G�t�F�N�g�̕`��
	lineEffect.render(device, view, projection, cameraPosition);

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
	//���J�[�W�����̕`��
	if (onRecursion) recursion->render(device, view, projection, cameraPosition);
	//�������[���C���̕`��
	memoryLine.render(device, view, projection, cameraPosition);
	//�X�^�[���C���̕`��
	starLine.render(device, view, projection, cameraPosition);
	//�Ռ��g�̕`��
	for(int i = 0;i<NUM_SHOCK_WAVE;i++)
		if (onShockWave[i])
			shockWave[i]->render(device, view, projection, cameraPosition);
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
	if (whetherDown())return; 

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
	if (whetherDown() || animationPlayer.getFlagMoveBan()) return;
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
	if (onGround) {
		addSpeed(moveDirection*SPEED);
	}
	else {
		addSpeed(moveDirection*SPEED/10);
	}
	postureControl(getAxisZ()->direction, moveDirection, 0.1f);
}

//===================================================================================================================================
//�y�W�����v�z
// [�������e]�����x�։��Z�������s��
//===================================================================================================================================
void Player::jump()
{
	if (whetherDown())return;
	acceleration += axisY.direction * JUMP_FORCE+speed/0.9f;
	onGround = false;
	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::SE_JUMP, soundNS::METHOD::PLAY);
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
	case GROUND:	changeGround();		break;
	case FALL:		changeFall();		break;
	case DOWN:		changeDown();		break;
	case SKY:		changeSky();		break;
	case REVIVAL:	changeRevival();	break;
	default:							break;
	}
}

//===================================================================================================================================
//�y�n�ヂ�[�h �ؑ֏����z
//===================================================================================================================================
void Player::changeGround()
{
	onGround = true;
	triggerShockWave();//�Ռ��g�𔭐�������
}
//===================================================================================================================================
//�y�n�ヂ�[�h �X�V�����z
//===================================================================================================================================
void Player::updateGround(float frameTime, bool _onJump)
{
	//===========
	//�y�ڒn�����z
	//===========
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//�d�͕������Z�o
	gravityRay.initialize(position, gravityDirection);								//�d�̓��C�̏�����
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//�d�͔������Ƃ̋���
	if (radius + attractorRadius >= distanceToAttractor - difference)
	{
		//���ݔ��a���v�l�����͔������Ƃ̋������Z���Ɛڒn
		onGround = true;
		onGravity = false;
		//�߂荞�ݕ␳
		//���݈ʒu+ ��������*(�߂荞�݋���)
		setPosition(position + axisY.direction * (radius + attractorRadius - distanceToAttractor));
		//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
		setSpeed(reverseAxisY.slip(speed, axisY.direction));
		acceleration *= 0;
		if (_onJump)jump();//�W�����v
	}
	else {
		//��
		onGround = false;
		onGravity = true;
	}
	setGravity(gravityDirection, GRAVITY_FORCE*frameTime);//�d�͏���

}

//===================================================================================================================================
//�y�������[�h �ؑ֏����z
//===================================================================================================================================
void Player::changeFall()
{
	fallTimer = FALL_TIME;//�������Ԃ̃Z�b�g
	onGround = false;
}
//===================================================================================================================================
//�y�������[�h �X�V�����z
//===================================================================================================================================
void Player::updateFall(float frameTime)
{
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
	fallTimer -= frameTime;
	rate = fallTimer / FALL_TIME;
	groundPosition = axisY.direction * (radius + attractorRadius);
	skyPosition = axisY.direction * (radius + attractorRadius + skyHeight);
	D3DXVec3Lerp(&fallPosition, &groundPosition, &skyPosition, rate);
	setPosition(fallPosition);
	//�y�n��z���[�h�֐ؑ�
	if (!whetherFall())
	{
		changeState(REVIVAL);
		animationPlayer.setFlagLanding(true);
	}
}

//===================================================================================================================================
//�y�_�E���� �ؑ֏����z
//===================================================================================================================================
void Player::changeDown()
{
	revivalPoint = 0;
	decreaseRevivalTimer = DECREASE_REVIVAL_TIME;//�����|�C���g�������Ԃ̃Z�b�g

	// �_�E���G�t�F�N�g����
	downEffect.generateDownEffect(200, position, downVec());

}
//===================================================================================================================================
//�y�_�E���� �X�V�����z
//===================================================================================================================================
void Player::updateDown(float frameTime)
{
	// �_�E���G�t�F�N�g�̍X�V
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
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_REVIVAL_POINT, soundNS::METHOD::PLAY);
		revivalPoint += INCREASE_REVIVAL_POINT;
		// �A�b�v�G�t�F�N�g����
		upEffect.generateUpEffect(200, position, upVec());
		if (whetherRevival())changeState(REVIVAL);
	}

	updateGround(frameTime, false);
}
//===================================================================================================================================
//�y�_�E���� �X�V�����z
//===================================================================================================================================
void Player::updateUpEffect(float frameTime)
{
	// �A�b�v�G�t�F�N�g�̍X�V
	upEffect.update(frameTime);
}
//===================================================================================================================================
//�y��󃂁[�h �ؑ֏����z
//===================================================================================================================================
void Player::changeSky()
{
	skyTimer = SKY_TIME;//��󃂁[�h���Ԃ̃Z�b�g
	skyHeight = 0.0f;
	hp = MAX_HP;
	onGround = true;
	canShockWave = true;
	time = 0;
	animationPlayer.setFlagRecursion(true);
	deleteMemoryItem();
}

//===================================================================================================================================
//�y��󃂁[�h �X�V�����z
//===================================================================================================================================
void Player::updateSky(float frameTime)
{
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);		//�d�͕������Z�o
	gravityRay.initialize(position, gravityDirection);								//�d�̓��C�̏�����
	float distanceToAttractor = between2VectorLength(position, *attractorPosition);	//�d�͔������Ƃ̋���
	skyTimer -= frameTime;
	skyHeight = min(skyHeight + 80.0f * frameTime, SKY_HEIGHT);
	if (radius + attractorRadius + skyHeight >= distanceToAttractor - difference)
	{
		//�߂荞�ݕ␳
		//���݈ʒu+ ��������*(�߂荞�݋���)
		setPosition(position + axisY.direction * (radius + attractorRadius + skyHeight - distanceToAttractor));
		//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
		setSpeed(reverseAxisY.slip(speed, axisY.direction));

	}
	else {
		//��
		//onGround = false;
		setGravity(gravityDirection, GRAVITY_FORCE);//�d�͏���
	}

	// ��
	time += 1.0f;
	if (time > 90.0f)
	{
		animationPlayer.setFlagRecursion(false);
	}

	//�y�����z���[�h�֐ؑ�
	if (!whetherSky())
	{
		changeState(FALL);
		animationPlayer.setFlagRecursion(false);
		animationPlayer.setFlagFalling(true);
	}
}

//===================================================================================================================================
//�y������ �ؑ֏����z
//===================================================================================================================================
void Player::changeRevival()
{
	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::SE_REVIVAL, soundNS::METHOD::PLAY);
	animationPlayer.setFlagRevival(true);
	animationPlayer.setFlagMoveBan(true);
	invincibleTimer = INVINCIBLE_TIME;//���G���Ԃ̃Z�b�g
	changeState(GROUND);
	triggerShockWave();//�Ռ��g�𔭐�������
}
//===================================================================================================================================
//�y������ �X�V�����z
//===================================================================================================================================
void Player::updateRevival(float frameTime)
{
	updateGround(frameTime,false);
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

	// �e�G�t�F�N�g�̍X�V
	bulletEffect.update(frameTime);

	//�o���b�g�̔���
	if (whetherDown() || animationPlayer.getFlagMoveBan() == true || animationPlayer.getFlagJump() == true) return;//�_�E�����F���˕s��
	if ((input->getMouseLButton() || input->getController()[type]->isButton(BUTTON_BULLET))
		&& intervalBullet == 0)
	{
		// �o���b�g�G�t�F�N�g
		bulletEffect.generateBulletEffect(20, position, bulletVec());

		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_ATTACK, soundNS::METHOD::PLAY);

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
//�y�������[�A�C�e���̑���/�X�V�z
//===================================================================================================================================
void Player::updateMemoryItem(float frameTime)
{
	//�_�E����ԂȂ�ΑS�Ẵ������A�C�e�����폜
	if (whetherDown())
	{
		deleteMemoryItem();
	}

	if (onRecursion)recursionTimer -= frameTime;

	//���J�[�W�������Ԃ��Ȃ��Ȃ����ꍇ���J�[�W�������폜����
	if (recursionTimer < 0)
	{
		if(onRecursion)SAFE_DELETE(recursion);
		onRecursion = false;
	}

	//�ڒn�L���������ǂ���
	bool whetherInstallationEffectiveDistance = false;
	int k = UtilityFunction::wrap(elementMemoryPile - 1, 0, NUM_MEMORY_PILE);
	if(k == 0)
	{
		whetherInstallationEffectiveDistance = true;
	}
	else if(D3DXVec3Length(&(position-*memoryPile[k].getPosition()))
		<= memoryLineNS::MAXIMUM_DISTANCE)//�ő勗���ȉ�
	{
		whetherInstallationEffectiveDistance = true;
	}
	else if (D3DXVec3Length(&(position - *memoryPile[k].getPosition())) 
		>= memoryLineNS::MINIMUM_DISTANCE)//�ŏ������ȏ�
	{
		whetherInstallationEffectiveDistance = true;
	}

	if ( k != 0 &&//�Q�{�ڈȍ~�̐ݒu���s�����
		D3DXVec3Length(&(position - *memoryPile[k].getPosition())) 
		> memoryLineNS::MAXIMUM_DISTANCE//�ő勗���ȉ�
		)
	{
		//�������[�p�C���E�������[���C�����������A�v���C���[�̓_�E����ԂɂȂ�B
	}

	//1P�̃������[�p�C���̃Z�b�g
	if (animationPlayer.getFlagSlash() == false &&
		animationPlayer.getFlagInstallation() == false &&
		whetherInstallationEffectiveDistance &&
		onGround &&
		memoryPile[elementMemoryPile].ready() &&
		(input->getMouseRButtonTrigger() || input->getController()[type]->wasButton(virtualControllerNS::L1)))
	{
		// �T�E���h�̍Đ�
		sound->play(soundNS::TYPE::SE_INSTALLATION_MEMORY_PILE, soundNS::METHOD::PLAY);
		animationPlayer.setFlagInstallation(true);

		memoryPile[elementMemoryPile].setPosition(position);
		memoryPile[elementMemoryPile].setQuaternion(quaternion);
		memoryPile[elementMemoryPile].activation();
		memoryPile[elementMemoryPile].Object::update();

		elementMemoryPile++;
		//�������[�p�C����S�Đݒu���邱�Ƃɐ���
		if (elementMemoryPile >= NUM_MEMORY_PILE)
		{
			memoryLine.update(device, frameTime,memoryLineNS::PENTAGON);//�������[���C���̍X�V
			elementMemoryPile = 0;//�Z�b�g����Ώۂ�0�Ԃ̃������p�C���ɐؑ�
			//���J�[�W�����ɂ�郏�X�����m��������ւ̕ϊ����I���܂ł́A�������[�p�C�����Z�b�g�ł��Ȃ���Ԃɂ���
			onRecursion = true;
			recursionTimer = RECURSION_TIME;
			//�ݒu���ꂽ�������[�p�C��5�_��p���ă��J�[�W�����p�̃|���S���𐶐�����B
			D3DXVECTOR3 vertex[NUM_MEMORY_PILE];
			for (int i = 0; i < NUM_MEMORY_PILE; i++)
			{
				vertex[i] = *memoryPile[i].getPosition();
			}
			//���J�[�W�����̐���
			recursion = new Recursion;
			recursion->initialize(device, vertex, *textureLoader->getTexture(textureLoaderNS::RECURSION), *shaderLoader->getEffect(shaderNS::RECURSION));
			//�X�^�[���C���̃��Z�b�g
			starLine.resetCurrentRenderNum();
			//�������[�p�C���ƃ������[���C���̏���
			for (int i = 0; i < NUM_MEMORY_PILE; i++)
			{
				memoryPile[i].switchLost();//����
				memoryLine.disconnect();//�ؒf
			}
		}
	}

	//[���b�Z�[�W]�G�̃������[�p�C����ؒf����
	if ((input->getController()[type]->wasButton(BUTTON_CUT) || //�R���g���[������
		 (input->getMouseWheelState()==inputNS::DOWN)||			//�}�E�X�z�C�[������
		 (GetAsyncKeyState(VK_RSHIFT) & 0x8000))				//�L�[�{�[�h����i���j
			&& state == GROUND) 								//�n�ヂ�[�h��
	{
		disconnectOpponentMemoryLine = true;
		// ���C���G�t�F�N�g����
		lineEffect.generateLineEffect(200, collideMemoryLinePosition, upVec());
	}
	else
	{ disconnectOpponentMemoryLine = false;}

	//�������[�p�C���̍X�V
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}
	
	//�������[���C���̍X�V
	memoryLine.update(device, frameTime,memoryLineNS::PENTAGON);

	// ���C���G�t�F�N�g�̍X�V
	lineEffect.update(frameTime);

	//�X�^�[���C���̍X�V
	starLine.update(device, frameTime,memoryLineNS::STAR);//�X�^�[���C���̍X�V
	
	//���J�[�W�����̍X�V
	if (onRecursion)
	{
		recursion->update(frameTime);
	}
}
//===================================================================================================================================
//�y�������[�A�C�e���̍폜�����z
//===================================================================================================================================
void Player::deleteMemoryItem()
{
	//�X�^�[���C���̃��Z�b�g
	starLine.resetCurrentRenderNum();
	//�������[�p�C���ƃ������[���C���̏���
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].switchLost();//����
		memoryLine.disconnect();//�ؒf
	}
	//���J�[�W�����̍폜
	if (onRecursion)SAFE_DELETE(recursion);
	onRecursion = false;
	recursionTimer = 0;
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
//�y�_�E���x�N�g���擾�z
//===================================================================================================================================
D3DXVECTOR3 Player::downVec()
{
	D3DXVECTOR3 downVec = reverseAxisY.direction;
	D3DXVec3Normalize(&downVec, &downVec);//���K��

	return downVec;
}
//===================================================================================================================================
//�y�A�b�v�x�N�g���擾�z
//===================================================================================================================================
D3DXVECTOR3 Player::upVec()
{
	D3DXVECTOR3 upVec = axisY.direction;
	D3DXVec3Normalize(&upVec, &upVec);//���K��

	return upVec;
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
	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::SE_CUT_MEMORY_LINE, soundNS::METHOD::PLAY);
	changeState(playerNS::DOWN);
}

//===================================================================================================================================
//�y�Ռ��g�𔭓��z
//===================================================================================================================================
void Player::triggerShockWave()
{
	if (!canShockWave)return;	//�g�p�\��
	for (int i = 0;i < NUM_SHOCK_WAVE; i++)
	{
		if(onShockWave[i])continue;		//��������Ă��邩
		shockWave[i] = new ShockWave();
		shockWave[i]->initialize(device, position, attractorRadius, *textureLoader->getTexture(textureLoaderNS::SHOCKWAVE), *shaderLoader->getEffect(shaderNS::SHOCK_WAVE));
		shockWave[i]->update(0.05*(float)i);
		onShockWave[i] = true;		//�������ɂ���
	}
	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::SE_SHOCK_WAVE, soundNS::METHOD::PLAY);
	canShockWave = false;	//�g�p�s�\�ɂ���
}

//===================================================================================================================================
//�y�Ռ��g���폜�z
//===================================================================================================================================
void Player::deleteShockWave(int n)
{
	delete shockWave[n];
	onShockWave[n] = false;
}

//===================================================================================================================================
//�y�Ռ��g�̍X�V�����z
//===================================================================================================================================
void Player::updateShockWave(float frameTime,int n)
{
	if (!onShockWave[n])return;//��������Ă��Ȃ���΍X�V���Ȃ�
	if (!shockWave[n]->whetherActive())//�Ռ��g�̓A�N�e�B�u�łȂ�
	{
		deleteShockWave(n);//�폜
		return;
	}
	shockWave[n]->update(frameTime);//�X�V
}

//===================================================================================================================================
//�y�Ռ��g�̍X�V�����z
//===================================================================================================================================
bool Player::collideShockWave(D3DXVECTOR3 point,float radius)
{
	if (!onShockWave[1])return false;
	if(shockWave[1]->collision(point,radius))return false;
	return true;
}

//===================================================================================================================================
//�ysetter�z
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
//�ygetter�z
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
MemoryLine*  Player::getMemoryLine() { return &memoryLine; }
MemoryPile* Player::getMemoryPile() { return memoryPile; }