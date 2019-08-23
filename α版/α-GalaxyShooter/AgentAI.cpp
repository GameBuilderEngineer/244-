//-----------------------------------------------------------------------------
// �G�[�W�F���gAI���� [AgentAI.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "AgentAI.h"
using namespace playerNS;

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int AgentAI::numAgent = 0;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
AgentAI::AgentAI(Player* opponentPlayer, Camera* camera, std::vector<Wasuremono*>* wasuremono)
{
	aiID = numAgent++;

	// �A�[�r�^�[
	arbiter = new Arbiter;

	// ���W���[��
	sensor = new Sensor(&camera->position, &camera->gazePosition, &camera->fieldOfView);
	environmentAnalysis = new EnvironmentAnalysis(wasuremono);
	pathPlanning = new PathPlanning;
	decisionMaking = new DecisionMaking;
	motionGeneration = new MotionGeneration;

	// �u���b�N�{�[�h
	recognitionBB = new RecognitionBB(opponentPlayer);
	bodyBB = new BodyBB;
	memoryBB = new MemoryBB;

	// �A�[�r�^�[�Ƀ��W���[����ڑ�
	arbiter->setModule(Module::SENSOR, sensor);
	arbiter->setModule(Module::ENVIRONMENT_ANSLYSIS, environmentAnalysis);
	arbiter->setModule(Module::PATH_PLANNING, pathPlanning);
	arbiter->setModule(Module::DECISION_MAKING, decisionMaking);
	arbiter->setModule(Module::MOTION_GENERATION, motionGeneration);

	// ���W���[���Ƀu���b�N�{�[�h��ڑ�
	sensor->setBlackBoard(recognitionBB);
	environmentAnalysis->setBlackBoard(recognitionBB);
	pathPlanning->setBlackBoard(recognitionBB, memoryBB);
	decisionMaking->setBlackBoard(recognitionBB, memoryBB, bodyBB);
	motionGeneration->setBlackBoard(memoryBB, bodyBB);
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
AgentAI::~AgentAI(void)
{
	// ���W���[���ƃu���b�N�{�[�h�j��
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
// ����������
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

	// �A�[�r�^�[������
	arbiter->initialize();

	// ���W���[��������
	KnowledgeSourceBase::setDevice(device);
	sensor->initialize();
	environmentAnalysis->initialize();
	decisionMaking->initialize();
	pathPlanning->initialize();
	motionGeneration->initialize();

	// �u���b�N�{�[�h������
	recognitionBB->initialize();
	memoryBB->initialize();
	bodyBB->initialize();

	// �����ݒ荀�ڂ𖄂߂�
	recognitionBB->setMemoryBB(memoryBB);
	recognitionBB->setMyPosition(&position);
	bodyBB->configMovingDestination(opponent->getPosition());
}


//=============================================================================
// �I������
//=============================================================================
void AgentAI::uninitialize(void)
{
	// ���W���[���I��
	sensor->uninitialize();
	environmentAnalysis->uninitialize();
	decisionMaking->uninitialize();
	pathPlanning->uninitialize();
	motionGeneration->uninitialize();
}


//=============================================================================
// �X�V����
//=============================================================================
void AgentAI::update(float frameTime)
{
	// �v���C���[�����̎��O�X�V
	updatePlayerBefore(frameTime);

	// AI�̍X�V
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

	// �v���C���[�����̎���X�V
	updatePlayerAfter(frameTime);

	// �v���C���[���ȏ��AI�ɑ��M 
	updateAgentSelfData();
}


//=============================================================================
// �v���C���[�����̎��O�X�V
//=============================================================================
void AgentAI::updatePlayerBefore(float frameTime)
{
	setSpeed(D3DXVECTOR3(0, 0, 0));	// ���x�i�ړ��ʁj�̏�����
	this->frameTime = frameTime;	// frameTime�L�^
}


//=============================================================================
// �v���C���[�����̎���X�V
//=============================================================================
void AgentAI::updatePlayerAfter(float frameTime)
{
#ifdef _DEBUG
	// �����p
	if (input->getController()[type]->wasButton(virtualControllerNS::UP))
		difference += 0.01f;
	if (input->getController()[type]->wasButton(virtualControllerNS::DOWN))
		difference -= 0.01f;
#endif

	//===========
	//�y�񕜁z
	//===========
	recorvery(frameTime);

//#ifdef _DEBUG��
// �f�o�b�O���[�h�̂Ƃ��̓R���g���[���̓��͂��ꕔ�󂯕t����
// ���i���R�͂Ȃ��@��������������

	//===========
	//�y�ړ������z
	//===========
	moveOperation();

	//===========
	//�y�W�����v�z
	//===========
	bool onJump = false;
	if (input->wasKeyPressed(keyTable.jump) ||
		input->getController()[type]->wasButton(playerNS::BUTTON_JUMP))
	{
		onJump = true;
	}
//#endif

	//===========
	//�y�ڒn�����z
	//===========
	//�d�͐����쐬
	D3DXVECTOR3 gravityDirection;
	between2VectorDirection(&gravityDirection, position, *attractorPosition);
	gravityRay.initialize(position, gravityDirection);//�d�̓��C�̏�����
	if (radius + attractorRadius >= (between2VectorLength(position, *attractorPosition) - difference))
	{
		onGround = true;
		//�߂荞�ݕ␳
		//���݈ʒu+ ��������*(�߂荞�݋���)
		setPosition(position + axisY.direction * (radius + attractorRadius - between2VectorLength(position, *attractorPosition)));
		//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
		setSpeed(reverseAxisY.slip(speed, axisY.direction));
#ifdef _DEBUG
		if (onJump)jump();//�W�����v
#endif
	}
	else {
		onGround = false;
		setGravity(gravityDirection, playerNS::GRAVITY_FORCE);//�d�͏���
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
	position += speed * frameTime;

	//===========
	//�y�p������z
	//===========
	postureControl(axisY.direction, -gravityRay.direction, 3.0f * frameTime);

	//===========
	//�y�I�u�W�F�N�g�F�X�V�z
	//===========
	Object::update();

	//===========
	//�y�e�̍X�V�z
	//===========
	//�C���^�[�o���̍X�V
	intervalBullet = max(intervalBullet - frameTime, 0);
	//�o���b�g�̍X�V
	for (int i = 0; i < NUM_BULLET; i++)
	{
		bullet[i].update(frameTime);
	}

	//===========
	//�y�J�����̑���z
	//===========
	controlCamera(frameTime);

	//==========================
	//�y�������[�A�C�e���̍X�V�z
	//==========================
	// �������[�p�C���̍X�V3
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}

	// �������[���C���̍X�V
	memoryLine.update(device, frameTime);
}


//=============================================================================
// �v���C���[���ȏ��AI�ɑ��M 
//=============================================================================
void AgentAI::updateAgentSelfData(void)
{
	recognitionBB->setWhetherInAir(!onGround);							// �󒆂ɂ��邩
	recognitionBB->setIsDown(whetherDown());							// �_�E������
	bodyBB->setShootingInterval(intervalBullet);						// �o���b�g���˃C���^�[�o��
	bodyBB->setIsReadyForPile(memoryPile[elementMemoryPile].ready());	// �p�C���ݒu�\��
}


//=============================================================================
// �o���b�g�̔���
//=============================================================================
void AgentAI::shootBullet(D3DXVECTOR3 targetDirection)
{
	// ���̏�������̓r�w�C�r�A�c���[�ł��s���Ă���
	// if (whetherDown())return;//�_�E�����F���˕s��
	// if (intervalBullet == 0)


	//�o���b�g�̔���
	if (whetherDown())return;//�_�E�����F���˕s��
	if (intervalBullet == 0)
	{
		bullet[elementBullet].setPosition(position);
		//Y�������ւ̐������폜����
		D3DXVECTOR3 front = slip(camera->getDirectionZ(), axisY.direction);
		D3DXVec3Normalize(&front, &front);//���K��
		bullet[elementBullet].addSpeed(front*0.2);//���x�����Z
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
// �������[�p�C���̐ݒu
//=============================================================================
void AgentAI::locateMemoryPile(void)
{
	// ���̕ӂ̏�������̓r�w�C�r�A�c���[�ōs���Ă���
	// onGround &&
	// memoryPile[elementMemoryPile].ready()

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

	//�������[�p�C���̐ؒf����
	//if (input->getController()[type]->wasButton(virtualControllerNS::A)
	//	|| (GetAsyncKeyState(VK_RSHIFT) & 0x8000))
	//{
	//	if (collitionMemoryLine && !onRecursion1P)
	//	{//[��������]1P�̃������[���C����2P���Փ�
	//		for (int i = 0; i < NUM_1P_MEMORY_PILE; i++)
	//		{//�������[�p�C���ƃ������[���C���̏���
	//			memoryPile[i].switchLost();//����
	//			memoryLine.disconnect();//�ؒf
	//		}
	//		player[PLAYER2].changeState(playerNS::DOWN);
	//	}
	//}
}
