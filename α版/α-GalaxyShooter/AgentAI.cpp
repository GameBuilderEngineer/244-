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
	virticalTime = 0.0f;
	horizontalTime = 0.0f;

	// �A�[�r�^�[
	arbiter = new Arbiter;

	// ���W���[��
	sensor = new Sensor(camera);
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
	recognitionBB->setFrameTimePointer(&frameTime);
	bodyBB->configMovingDestination(opponent->getPosition()); // ��
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

	// AI�p�I�[�g�J��������
	autoCamera();

	// �v���C���[�����̎���X�V
	updatePlayerAfter(frameTime);

	// �v���C���[���ȏ��AI�ɑ��M 
	updateAgentSelfData();

	//��
	if (input->isKeyDown('Q'))
	{
		recognitionBB->flag = true;
	}
}


//=============================================================================
// �v���C���[�����̎��O�X�V
//=============================================================================
void AgentAI::updatePlayerBefore(float frameTime)
{
	setSpeed(D3DXVECTOR3(0, 0, 0));	// ���x�i�ړ��ʁj�̏�����
	onJump = false;
	disconnectOpponentMemoryLine = false;
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

#ifdef _DEBUG
	// �f�o�b�O���[�h�̂Ƃ��̓R���g���[���̓��͂��ꕔ�󂯕t����
	// ���i���R�͂Ȃ��@��������������

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
#endif

	switch (state)
	{
	case FALL:		updateFall(frameTime);			break;
	case SKY:		updateSky(frameTime);			break;
	case GROUND:	updateGround(frameTime, onJump); break;
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
	camera->setUpVector(axisY.direction);
	camera->update();

	//==========================
	//�y�������[�A�C�e���̍X�V�z
	//==========================
	if (whetherDown())
	{
		deleteMemoryItem();//�_�E����ԂȂ�ΑS�Ẵ������A�C�e�����폜
	}
	if (onRecursion)recursionTimer -= frameTime;
	if (recursionTimer < 0)
	{
		if (onRecursion)SAFE_DELETE(recursion);
		onRecursion = false;
	}

	// �������[�p�C���̃Z�b�g�̓r�w�C�r�A�c���[����

	// �������[���C���̐ؒf���r�w�C�r�A�c���[����

	// �������[�p�C���̍X�V
	for (int i = 0; i < NUM_MEMORY_PILE; i++)
	{
		memoryPile[i].update(frameTime);
	}

	// �������[���C���̍X�V
	memoryLine.update(device, frameTime, memoryLineNS::PENTAGON);

	//�X�^�[���C���̍X�V
	starLine.update(device, frameTime, memoryLineNS::STAR);//�X�^�[���C���̍X�V

	//���J�[�W�����̍X�V
	if (onRecursion)
	{
		recursion->update(frameTime);
	}

	//===========
	//�y�Ռ��g�̍X�V�z
	//===========
	for (int i = 0; i < NUM_SHOCK_WAVE; i++)
	{
		updateShockWave(frameTime, i);
	}
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

	// �T�E���h�̍Đ�
	sound->play(soundNS::TYPE::SE_INSTALLATION_MEMORY_PILE, soundNS::METHOD::PLAY);

	memoryPile[elementMemoryPile].setPosition(position);
	memoryPile[elementMemoryPile].setQuaternion(quaternion);
	memoryPile[elementMemoryPile].activation();
	memoryPile[elementMemoryPile].Object::update();
	elementMemoryPile++;

	//�������[�p�C����S�Đݒu���邱�Ƃɐ���
	if (elementMemoryPile >= NUM_MEMORY_PILE)
	{
		memoryLine.update(device, frameTime, memoryLineNS::PENTAGON);//�������[���C���̍X�V
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


//=============================================================================
// �������[���C���ؒf
//=============================================================================
void AgentAI::cutMemoryLine(void)
{
	disconnectOpponentMemoryLine = true;
}


//=============================================================================
// �����|�C���g����
//=============================================================================
void AgentAI::increaseRevivalPoint(void)
{
	revivalPoint += INCREASE_REVIVAL_POINT;
}

//=============================================================================
// �I�[�g�J��������
//=============================================================================
void AgentAI::autoCamera(void)
{

	if (D3DXVec3Length(&(*opponent->getPosition() - position)) < 90.0f/*����Ȃ��񂩁H*/)
	{// ����ɋ߂���΃��b�N�I��
		lockOnHorizontally(*opponent->getPosition(), frameTime);
	}
	else
	{// ����ȊO�͎�U��

		// ����������]
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

		// ����������]
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
// �������b�N�I��
//=============================================================================
void AgentAI::lockOnHorizontally(D3DXVECTOR3 lockOnTarget, float frameTime)
{
	float radian;						// ��]�p�x
	D3DXVECTOR3 axis(0, 1, 0);			// ��]��
	D3DXVECTOR3 lockOnTargetDirection;	// �^�[�Q�b�g�����x�N�g��

	// �v���C���[���^�[�Q�b�g�̃x�N�g���ɂ���
	between2VectorDirection(&lockOnTargetDirection, *camera->target, lockOnTarget);

	// �J�����ʒu�ƒ����_���܂ޕ��ʂ̍��E�ǂ���Ƀ^�[�Q�b�g�����邩
	// ���ʂ̕������Ƀ^�[�Q�b�g�̍��W�������Ē��ׂ�
	bool isRight = false;
	D3DXVECTOR3 planeN = camera->getDirectionX();
	float d = -(planeN.x * camera->position.x + planeN.y * camera->position.y + planeN.z * camera->position.z);
	if (planeN.x * lockOnTarget.x + planeN.y * lockOnTarget.y + planeN.z * lockOnTarget.z + d > 0)
	{
		isRight = true;
	}

	// �J�����̒��������x�N�g���ƃ^�[�Q�b�g�����x�N�g�����J������XZ���ʂƕ��s�ɂȂ�悤�X���b�v
	lockOnTargetDirection = slip(lockOnTargetDirection, camera->getDirectionY());
	D3DXVec3Normalize(&lockOnTargetDirection, &lockOnTargetDirection);
	D3DXVECTOR3 front = slip(camera->getDirectionZ(), camera->getDirectionY());
	D3DXVec3Normalize(&front, &front);

	// ��]������
	if (formedRadianAngle(&radian, front, lockOnTargetDirection))
	{
		if (isRight)
		{// ��]�������̂܂�
		}
		else//(isLeft)
		{// ��]�����ς���
			radian = -radian;
		}
		camera->rotation(axis, D3DXToDegree(radian * frameTime));
	}
}


//=============================================================================
// 3�������b�N�I���i�����j
//=============================================================================
// �^�[�Q�b�g�Ƃ̈ʒu�֌W�ɂ���āi�����炭�j�^�[�Q�b�g�����̋t�����������悤��]
// �����낵�łȂ����グ������ɂȂ��Ă��܂�
// �悭�킩���I
void AgentAI::lockOn3D(D3DXVECTOR3 lockOnTarget, float frameTime)
{
	float radian;						// ��]�p�x
	D3DXVECTOR3 axis;					// ��]��
	D3DXVECTOR3 lockOnTargetDirection;	// �^�[�Q�b�g�����x�N�g��

	// �O�ς���]����
	D3DXVec3Cross(&axis, &camera->getDirectionZ(), &(lockOnTarget - camera->position));

	// �v���C���[���^�[�Q�b�g�̃x�N�g���ɂ���
	between2VectorDirection(&lockOnTargetDirection, *camera->target, lockOnTarget);

	// �J��������]������
	D3DXVECTOR3 front = camera->getDirectionZ();
	if (formedRadianAngle(&radian, front, lockOnTargetDirection))
	{
		camera->rotation(axis, D3DXToDegree(radian* frameTime));
	}

	//// �t�B�[���h�̉��ɃJ���������荞�񂾂�
	//if (D3DXVec3Dot(&camera->getDirectionZ(), &getReverseAxisY()->direction) < 0)
	//{
	//	isOpponentLockOn = false;
	//}
}


//=============================================================================
// �f�o�b�O�`��
//=============================================================================
void AgentAI::debugRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition)
{
	environmentAnalysis->debugRender(this);	// �f�o�b�O�`�悪�L���ɂȂ��Ă���Ή��z���J�[�W������`��
}
