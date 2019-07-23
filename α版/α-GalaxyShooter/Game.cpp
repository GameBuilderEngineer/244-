#include "Game.h"
#include "Direct3D9.h"
using namespace gameNS;

Game::Game()
{
	sceneName = "Scene -Game-";
	currentMemoryPile1 = 0;
	currentMemoryPile2 = 0;
	intervalBullet1 = 0;
	intervalBullet2 = 0;
	currentBullet1 = 0;
	currentBullet2 = 0;

	reverseValue1PXAxis = 1;
	reverseValue1PYAxis = 1;
	reverseValue2PXAxis = 1;
	reverseValue2PYAxis = 1;

	nextScene = SceneList::RESULT;
}

Game::~Game()
{

}

void Game::initialize(Direct3D9* direct3D9,Input* _input, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader) {
	//Input
	input = _input;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;

	//camera
	camera = new Camera[NUM_PLAYER];
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		camera[i].setTarget(player[i].getPosition());
		camera[i].setTargetX(&player[i].getAxisX()->direction);
		camera[i].setTargetY(&player[i].getAxisY()->direction);
		camera[i].setTargetZ(&player[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[i]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 10, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
	}

	//light
	light = new Light;
	light->initialize(direct3D9);

	//�R���j�[
	colony[0].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON_X100], &D3DXVECTOR3(150, 0, 300));
	colony[1].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::PLANET], &D3DXVECTOR3(-150, 0, 300));
	//�t�B�[���h
	field.initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::PLANET], &(D3DXVECTOR3)PLANET_POSITION);

	for (int i = 0; i < NUM_PLAYER; i++)
	{//�v���C���[�̏�����
		player[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::SAMPLE_TOON_MESH], &(D3DXVECTOR3)gameNS::PLAYER_POSITION[i]);
		hp[i].initialize(direct3D9->device, i, _textureLoader);
		sp[i].initialize(direct3D9->device, i, _textureLoader);
		colonyHp[i].initialize(direct3D9->device, i, _textureLoader);
		missileInfomation[i].initialize(direct3D9->device, i, _textureLoader);
		weaponInfomation[i].initialize(direct3D9->device, i, _textureLoader);
		timerUI[i].initialize(direct3D9->device, i, _textureLoader);
		chingin[i].initialize(direct3D9->device, i, _textureLoader);
		hpEffect[i].initialize(direct3D9->device, i, _textureLoader);
		target.initialize(direct3D9->device, i, _textureLoader, _staticMeshLoader);

		//�d�͐����쐬
		D3DXVECTOR3 gravityDirection;
		between2VectorDirection(&gravityDirection, *player[i].getPosition(), *field.getPosition());
		player[i].getGravityRay()->initialize(*player[i].getPosition(), gravityDirection);
		if (player[i].getGravityRay()->rayIntersect(*field.getMesh(), field.getMatrixWorld()))
		{//�d�͐���Ƀ|���S�����Փ˂��Ă����ꍇ�A�|���S���@�����d�͕����Ƃ��A�p����@���ƈ�v������B
			player[i].postureControl(player[i].getAxisY()->direction, player[i].getGravityRay()->normal, 1.0f);
			player[i].setGravity(-player[i].getGravityRay()->normal, playerNS::GRAVITY_FORCE);
		}
		else 
		{//�Փ˃|���S�������݂��Ȃ��ꍇ�́A�d�͐������̂܂܏d�͕����Ƃ��A�p�����d�͐��ƈ�v������B
			player[i].postureControl(player[i].getAxisY()->direction, gravityDirection, 1.0f);
			player[i].setGravity(gravityDirection, playerNS::GRAVITY_FORCE);
		}
	}

	for (int i = 0; i < NUM_MAGNET; i++)
	{//����
		if (NUM_MAGNET / 2 > i) {
			magnet[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::MAGNET_N],2.0f);
		}
		else {
			magnet[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::MAGNET_S] ,-2.0f);
		}
	}

	for (int i = 0; i < NUM_BULLET; i++)
	{//�o���b�g�̏�����
		bullet1[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::BULLET], &D3DXVECTOR3(0,0,0));
		bullet2[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::BULLET], &D3DXVECTOR3(0,0,0));
		//bullet[i].anyAxisRotation(D3DXVECTOR3(0, 1, 0), (float)(rand() % 360));
	}

	text.initialize(direct3D9->device,10,10, 0xff00ff00);
	text2.initialize(direct3D9->device,11,11, 0xff0000ff);

	//�K���N�^
	for (int i = 0; i < JUNK_MAX; i++)
	{
		D3DXVECTOR3 position((float)(rand()%100-50), (float)(rand()%100-50), (float)(rand()%100-50));
		D3DXVec3Normalize(&position, &position);
		position *= 100;
		junk[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON], &position);
	}

	//�|�C���g�X�v���C�g
	pointSprite.initilaize(direct3D9->device);

	//�C���X�^���X�v���[��
	plane.createPositionSpherical(1000, 300.0f);
	plane.initialize(direct3D9->device);

	//�������[�p�C���̏�����
	for (int i = 0; i < NUM_1P_MEMORY_PILE; i++)
	{
		memoryPile1P[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::MEMORY_PILE], &D3DXVECTOR3(0, 0, 0));
	}
	for (int i = 0; i < NUM_2P_MEMORY_PILE; i++)
	{
		memoryPile2P[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::MEMORY_PILE], &D3DXVECTOR3(0, 0, 0));
	}

	pose.initialize(direct3D9->device, 0, _textureLoader);

}

float difference = 1.0f;

void Game::update(float frameTime) {
	
	sceneTimer += frameTime;
	FrameTime = frameTime;
	if (frameTime > 0.03)return;//�t���[�����Ԃ���30FPS���̎��̎��Ԃ�蒷���ꍇ�́A���������i�X�V���Ȃ��j��������Ԃ���

	if (input->wasKeyPressed(VK_RETURN))// �|�[�Y����
	{
		pose.poseon = false;
	}

	if (pose.poseon)return;// �|�[�Y���Ă���X�V���Ȃ�

	for (int i = 0; i < NUM_PLAYER; i++)
	{//�v���C���[�̍X�V
		player[i].setSpeed(D3DXVECTOR3(0, 0, 0));
		if (input->getController()[PLAYER1]->wasButton(virtualControllerNS::UP))
			difference += 0.01f;
		if(input->getController()[PLAYER1]->wasButton(virtualControllerNS::DOWN))
			difference -= 0.01f;

		bool onJump = false;
		switch (i)
		{
		case PLAYER1:
			if (input->isKeyDown('W')) {
				player[i].move(D3DXVECTOR2(0,-1), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->isKeyDown('S')) {
				player[i].move(D3DXVECTOR2(0,1), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->isKeyDown('A')) {
				player[i].move(D3DXVECTOR2(-1,0), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->isKeyDown('D'))
			{
				player[i].move(D3DXVECTOR2(1,0), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->wasKeyPressed(VK_SPACE)||input->getController()[i]->wasButton(virtualControllerNS::B))
			{
				onJump = true;
			}
			if (input->wasKeyPressed('R'))
			{
				player[i].reset();
			}
			break;
		case PLAYER2:
			if (input->isKeyDown(VK_UP)) {
				player[i].move(D3DXVECTOR2(0,-1), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->isKeyDown(VK_DOWN)) {
				player[i].move(D3DXVECTOR2(0,1), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->isKeyDown(VK_LEFT)) {
				player[i].move(D3DXVECTOR2(-1,0), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->isKeyDown(VK_RIGHT))
			{
				player[i].move(D3DXVECTOR2(1,0), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			if (input->wasKeyPressed(VK_RETURN)|| input->getController()[i]->wasButton(virtualControllerNS::B))
			{
				onJump = true;
			}
			break;
		}

		//�R���g���[���X�e�B�b�N�ɂ��ړ�
		if (input->getController()[i]->checkConnect()) {
			player[i].move(input->getController()[i]->getLeftStick()*0.001f, camera[i].getDirectionX(), camera[i].getDirectionZ());
		}

		//�t�B�[���h�␳
		if (player[i].getReverseAxisY()->rayIntersect(*field.getMesh(), field.getMatrixWorld()) &&
			player[i].getRadius() >= (player[i].getReverseAxisY()->distance -difference))
		{
			//�߂荞�ݕ␳
			//���݈ʒu+ ��������*(�߂荞�݋���)
			player[i].setPosition(*player[i].getPosition() + player[i].getAxisY()->direction*(player[i].getRadius() - player[i].getReverseAxisY()->distance));

			//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
			player[i].setSpeed(player[i].getReverseAxisY()->slip(player[i].getSpeed(), player[i].getReverseAxisY()->normal));
			//Ray moveRay;//�ړ��x�N�g�����g���ă��C���쐬
			//moveRay.initialize(*player[i].getPosition(), player[i].getSpeed());
			//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && player[i].getRadius() > moveRay.distance)
			//{//��d�`�F�b�N
			//	player[i].setSpeed(moveRay.slip(player[i].getSpeed(),moveRay.normal));
			//}
			if(onJump)player[i].jump();
		}
		else {
			player[i].setGravity(-player[i].getAxisY()->direction, playerNS::GRAVITY_FORCE);
		}

		player[i].update(frameTime);
	}

	//�o���b�g�̔���
	//���I�����ɂ�����
	if (intervalBullet1 > 0)
		intervalBullet1 -= frameTime;
	else 
		intervalBullet1 = 0;
	if (intervalBullet2 > 0)intervalBullet2 -= frameTime;
	else intervalBullet2 = 0;
	if ((input->getMouseLButton() || input->getController()[PLAYER1]->wasButton(virtualControllerNS::R1))
		&& intervalBullet1 == 0)
	{
		bullet1[currentBullet1].setPosition(*player[PLAYER1].getPosition());
		//Y�������ւ̐������폜����
		D3DXVECTOR3 front = slip(camera[PLAYER1].getDirectionZ(), player[PLAYER1].getAxisY()->direction);
		D3DXVec3Normalize(&front, &front);//���K��
		bullet1[currentBullet1].addSpeed(front*0.2);//���x�����Z
		bullet1[currentBullet1].setQuaternion(player[PLAYER1].getQuaternion());
		bullet1[currentBullet1].postureControl(player[PLAYER1].getAxisZ()->direction, front,1.0f);
		bullet1[currentBullet1].activation();
		bullet1[currentBullet1].Object::update();
		currentBullet1++;
		if (currentBullet1 >= NUM_BULLET)currentBullet1 = 0;
		intervalBullet1 = INTERVAL_TIME_BULLET1;
	}
	if ((input->getMouseRButton() || input->getController()[PLAYER2]->wasButton(virtualControllerNS::R1))
		&& intervalBullet2 == 0)
	{
		bullet2[currentBullet2].setPosition(*player[PLAYER2].getPosition());
		//Y�������ւ̐������폜����
		D3DXVECTOR3 front = slip(camera[PLAYER2].getDirectionZ(), player[PLAYER2].getAxisY()->direction);
		D3DXVec3Normalize(&front, &front);//���K��
		bullet2[currentBullet2].addSpeed(front*0.2);//���x�����Z
		bullet2[currentBullet2].setQuaternion(player[PLAYER2].getQuaternion());
		bullet2[currentBullet2].postureControl(player[PLAYER2].getAxisZ()->direction, front,1.0f);
		bullet2[currentBullet2].activation();
		bullet2[currentBullet2].Object::update();
		currentBullet2++;
		if (currentBullet2 >= NUM_BULLET)currentBullet2 = 0;
		intervalBullet2 = INTERVAL_TIME_BULLET2;
	}

	for (int i = 0; i < NUM_BULLET; i++)
	{//�o���b�g�̍X�V
		bullet1[i].update(frameTime,*field.getMesh(),field.getMatrixWorld());
		bullet2[i].update(frameTime,*field.getMesh(),field.getMatrixWorld());
	}

	//�J�����̉�]
	{
		if (input->wasKeyPressed(VK_F3))reverseValue1PXAxis*=-1;
		if (input->wasKeyPressed(VK_F4))reverseValue1PYAxis*=-1;
		//1P�J��������
		camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), (float)(input->getMouseRawX() * reverseValue1PXAxis));
		camera[PLAYER1].rotation(camera[PLAYER1].getHorizontalAxis(), (float)(input->getMouseRawY() * reverseValue1PYAxis));

		if (input->isKeyDown('G')) {
			//camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), -1.0f);
		};
		if (input->isKeyDown('J')) {
			//camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), 1.0f);
		};

		if (input->getController()[PLAYER1]->checkConnect()) {
			camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), input->getController()[PLAYER1]->getRightStick().x*0.001f*reverseValue1PXAxis);
			camera[PLAYER1].rotation(camera->getHorizontalAxis(), input->getController()[PLAYER1]->getRightStick().y*0.001f*reverseValue1PYAxis);
		}
		//2P�����b�N�I��(����)
		if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
			camera[PLAYER1].lockOn(*player[PLAYER2].getPosition(),frameTime);
		}

		if (input->wasKeyPressed(VK_F5))reverseValue2PXAxis*=-1;
		if (input->wasKeyPressed(VK_F6))reverseValue2PYAxis*=-1;
		//2P�J��������
		if (input->getMouseLButton()) {
			camera[PLAYER2].rotation(D3DXVECTOR3(0, 1, 0), (float)(input->getMouseRawX() * reverseValue2PXAxis));
			camera[PLAYER2].rotation(camera[PLAYER2].getHorizontalAxis(), (float)(input->getMouseRawY() * reverseValue2PYAxis));
		};

		if (input->getController()[PLAYER2]->checkConnect()) {
			camera[PLAYER2].rotation(D3DXVECTOR3(0, 1, 0), input->getController()[PLAYER2]->getRightStick().x * 0.001f * reverseValue2PXAxis);
			camera[PLAYER2].rotation(D3DXVECTOR3(0, 0, 1), input->getController()[PLAYER2]->getRightStick().y * 0.001f * reverseValue2PYAxis);
		}

		for (int i = 0; i < NUM_PLAYER; i++)
		{//�J�����̍X�V
			camera[i].setUpVector(player[i].getAxisY()->direction);
			camera[i].update();
		}
	}

	//�v���C���[�̍X�V
	{
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			hp[i].update(player[i].getHp(), player[i].getMaxHp());
			sp[i].update(player[i].getSp(), player[i].getMaxSp());
			colonyHp[i].update();
			missileInfomation[i].update();
			weaponInfomation[i].update();
			timerUI[i].update();
			chingin[i].update();
			hpEffect[i].update();
			target.update();
		}
	}

	// �R���j�[�A�b�v�f�[�g
	{
		colony[0].update();

		for (int i = 0; i < JUNK_MAX; i++)
		{
			// �K���N�^�A�b�v�f�[�g
			junk[i].update(frameTime, *field.getMesh(), field.getMatrixWorld(), *field.getPosition());
		}
	}

	//���΂̍X�V
	{
		if (input->getController()[PLAYER1]->wasButton(virtualControllerNS::A))
		{
			magnet[NUM_MAGNET - 1].reverseAmount();
		}
		magnet[NUM_MAGNET - 1].setPosition(*player[PLAYER1].getPosition());
		magnet[1].setPosition(*player[PLAYER2].getPosition());
		for (int i = 0; i < NUM_MAGNET; i++)
		{
			for (int j = 0; j < NUM_MAGNET; j++)
			{
				if (j != i)
					magnet[i].calculationMagneticeForce(magnet[j]);
			}
		}
		for (int i = 0; i < NUM_MAGNET; i++)
		{
			magnet[i].update();
		}
	}

	//�������[�p�C���̍X�V
	{
		//1P�̃������[�p�C���̃Z�b�g
		if ( input->getMouseRButtonTrigger() || input->getController()[PLAYER1]->wasButton(virtualControllerNS::L1))
		{
			memoryPile1P[currentMemoryPile1].setPosition(*player[PLAYER1].getPosition());
			memoryPile1P[currentMemoryPile1].setQuaternion(player[PLAYER1].getQuaternion());
			memoryPile1P[currentMemoryPile1].activation();
			memoryPile1P[currentMemoryPile1].Object::update();
			currentMemoryPile1++;
			if (currentMemoryPile1 >= NUM_1P_MEMORY_PILE)currentMemoryPile1 = 0;
		}

		//2P�̃������[�p�C���̃Z�b�g
		if (input->getController()[PLAYER2]->wasButton(virtualControllerNS::L1))
		{
			memoryPile2P[currentMemoryPile2].setPosition(*player[PLAYER2].getPosition());
			memoryPile2P[currentMemoryPile2].setQuaternion(player[PLAYER2].getQuaternion());
			memoryPile2P[currentMemoryPile2].activation();
			memoryPile2P[currentMemoryPile2].Object::update();
			currentMemoryPile2++;
			if (currentMemoryPile2 >= NUM_2P_MEMORY_PILE)currentMemoryPile2 = 0;
		}


		//1P�̃������[�p�C���̍X�V
		for (int i = 0; i < NUM_1P_MEMORY_PILE; i++)
		{
			memoryPile1P[i].update(frameTime);
		}
		//2P�̃������[�p�C���̍X�V
		for (int i = 0; i < NUM_2P_MEMORY_PILE; i++)
		{
			memoryPile2P[i].update(frameTime);
		}
	}

	if (input->wasKeyPressed('P'))// �|�[�Y�J�n
	{
		pose.poseon = true;
	}

}

void Game::render(Direct3D9* direct3D9) {

	//1P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewport1PWindow();
	render3D(direct3D9,camera[0]);

	//2P�J�����E�E�B���h�E
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[1].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[1].projection);
	direct3D9->changeViewport2PWindow();
	render3D(direct3D9,camera[1]);
	//UI
	//direct3D9->device->SetTransform(D3DTS_VIEW, &camera[2].view);
	//direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[2].projection);
	direct3D9->changeViewportFullWindow();
	renderUI(direct3D9->device);
}

void Game::render3D(Direct3D9* direct3D9, Camera currentCamera) {

	target.renderStencilMask(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	for (int i = 0; i < NUM_PLAYER; i++)
	{//�v���C���[�̕`��
		player[i].toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	target.renderEffectImage(direct3D9->device);

	target.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);


	for (int i = 0; i < NUM_BULLET; i++)
	{//�o���b�g�̕`��
		bullet1[i].render(direct3D9->device,currentCamera.view,currentCamera.projection,currentCamera.position);
		bullet2[i].render(direct3D9->device,currentCamera.view,currentCamera.projection,currentCamera.position);
	}

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, false);

	for (int i = 0; i < NUM_COLONY; i++)
	{// �R���j�[�̕`��
		colony[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, true);

	for (int i = 0; i < JUNK_MAX; i++)
	{// �K���N�^�̕`��
		junk[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	//�t�B�[���h�̕`��
	field.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	//(��)//�}�O�l�b�g�̕`��
	for (int i = 0; i < NUM_MAGNET; i++)
	{
		magnet[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	//(��)//�|�C���g�X�v���C�g�̕`��
	pointSprite.render(direct3D9->device,currentCamera.position);

	//(��)//�v���[���̕`��(�C���X�^���V���O)
	plane.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	//�������[�p�C���̕`��
	{
		for (int i = 0; i < NUM_1P_MEMORY_PILE; i++)
		{
			memoryPile1P[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
		}
		for (int i = 0; i < NUM_2P_MEMORY_PILE; i++)
		{
			memoryPile2P[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
		}
	}

#ifdef _DEBUG
	Ray debugRay;
	//�@��
	debugRay.color = D3DXCOLOR(128, 0, 128, 255);
	debugRay.update(*player[PLAYER1].getPosition(), player[PLAYER1].getReverseAxisY()->normal);
	debugRay.render(direct3D9->device, 100.0f);
#endif
}



void Game::renderUI(LPDIRECT3DDEVICE9 device) {
#ifdef _DEBUG
	text.print(50, 200,
		"difference:%.3f\n",difference);
	text.print(10, 150,
		"\
		sceneTime:%.2f\n\
		frameTime:%.2f\n\
		",
		sceneTimer, FrameTime);
	text.print(10, 10, "acceleration(\t%.2f,\t%.2f,\t%.2f)",
		player[PLAYER1].getAcceleration().x,
		player[PLAYER1].getAcceleration().y,
		player[PLAYER1].getAcceleration().z);
	text.print(10, 30, "gravity(\t%.2f,\t%.2f,\t%.2f)", 
		player[PLAYER1].getGravity().x,
		player[PLAYER1].getGravity().y,
		player[PLAYER1].getGravity().z);
	text.print(10, 50, "quaternion(\t%.2f,\t%.2f,\t%.2f,\t%.2f)", 
		player[PLAYER1].getQuaternion().x,
		player[PLAYER1].getQuaternion().y,
		player[PLAYER1].getQuaternion().z,
		player[PLAYER1].getQuaternion().w);
	text.print(10, 70, "normal(\t%.2f,\t%.2f,\t%.2f)", 
		player[PLAYER1].getReverseAxisY()->normal.x,
		player[PLAYER1].getReverseAxisY()->normal.y,
		player[PLAYER1].getReverseAxisY()->normal.z);
	text.print(10, 90, "cameraRelative(\t%.2f,\t%.2f,\t%.2f,\t%.2f)", 
		camera[PLAYER1].relativeQuaternion.x,
		camera[PLAYER1].relativeQuaternion.y,
		camera[PLAYER1].relativeQuaternion.z,
		camera[PLAYER1].relativeQuaternion.w);
	text.print(10, 110, "input(x:%d,y:%d,rowX%d,rowY%d)", 
		input->getMouseX(),
		input->getMouseY(),
		input->getMouseRawX(),
		input->getMouseRawY());

	text.print(WINDOW_WIDTH / 2, 10, 
		"magnetPosition(%.02f,%.02f,%.02f)\n\
		 magnetSpeed(%.02f,%.02f,%.02f)\n\
		",
		magnet[0].getPosition()->x,magnet[0].getPosition()->y,magnet[0].getPosition()->z,
		magnet[0].getSpeed().x,magnet[0].getSpeed().y,magnet[0].getSpeed().z
	);

	text2.print(10, 450,
		"1P:Controller\n\
		isA:%d wasA:%d\n\
		isB:%d wasB:%d\n\
		isX:%d wasX:%d\n\
		isY:%d wasY:%d\n\
		isUP:%d wasUP:%d\n\
		isRIGHT:%d wasRIGHT:%d\n\
		isDOWN:%d wasDOWN:%d\n\
		isLEFT:%d wasLEFT:%d\n\
		isR1:%d wasR1:%d\n\
		isR2:%d wasR2:%d\n\
		isR3:%d wasR3:%d\n\
		isL1:%d wasL1:%d\n\
		isL2:%d wasL2:%d\n\
		isL3:%d wasL3:%d\n\
		isHOME:%d wasHOME:%d\n\
		isCAPTURE:%d wasCAPTURE:%d\n\
		isSPECIAL_MAIN:%d wasSPECIAL_MAIN:%d\n\
		isSPECIAL_SUB:%d wasSPECIAL_SUB:%d\n\
		LeftStick:(%.2f,%.2f)\n\
		RightStick:(%.2f,%.2f)\n\
		",
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::A),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::B),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::B),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::X),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::X),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::Y),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::Y),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::UP),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::UP),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::RIGHT),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::RIGHT),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::DOWN),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::DOWN),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::LEFT),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::LEFT),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::R1),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::R1),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::R2),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::R2),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::R3),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::R3),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::L1),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::L1),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::L2),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::L2),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::L3),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::L3),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::HOME),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::HOME),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::CAPTURE),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::CAPTURE),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::SPECIAL_MAIN),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::SPECIAL_MAIN),
		input->getController()[inputNS::DINPUT_1P]->isButton(virtualControllerNS::SPECIAL_SUB),input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::SPECIAL_SUB),
		input->getController()[inputNS::DINPUT_1P]->getLeftStick().x,input->getController()[inputNS::DINPUT_1P]->getLeftStick().y,
		input->getController()[inputNS::DINPUT_1P]->getRightStick().x,input->getController()[inputNS::DINPUT_1P]->getRightStick().y
	);
	text2.print(WINDOW_WIDTH/2.0f, 450,
		"2P:Controller\n\
		isA:%d wasA:%d\n\
		isB:%d wasB:%d\n\
		isX:%d wasX:%d\n\
		isY:%d wasY:%d\n\
		isUP:%d wasUP:%d\n\
		isRIGHT:%d wasRIGHT:%d\n\
		isDOWN:%d wasDOWN:%d\n\
		isLEFT:%d wasLEFT:%d\n\
		isR1:%d wasR1:%d\n\
		isR2:%d wasR2:%d\n\
		isR3:%d wasR3:%d\n\
		isL1:%d wasL1:%d\n\
		isL2:%d wasL2:%d\n\
		isL3:%d wasL3:%d\n\
		isHOME:%d wasHOME:%d\n\
		isCAPTURE:%d wasCAPTURE:%d\n\
		isSPECIAL_MAIN:%d wasSPECIAL_MAIN:%d\n\
		isSPECIAL_SUB:%d wasSPECIAL_SUB:%d\n\
		LeftStick:(%.2f,%.2f)\n\
		RightStick:(%.2f,%.2f)\n\
		",
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::A),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::B),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::B),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::X),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::X),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::Y),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::Y),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::UP),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::UP),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::RIGHT),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::RIGHT),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::DOWN),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::DOWN),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::LEFT),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::LEFT),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::R1),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::R1),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::R2),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::R2),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::R3),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::R3),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::L1),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::L1),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::L2),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::L2),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::L3),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::L3),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::HOME),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::HOME),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::CAPTURE),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::CAPTURE),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::SPECIAL_MAIN),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::SPECIAL_MAIN),
		input->getController()[inputNS::DINPUT_2P]->isButton(virtualControllerNS::SPECIAL_SUB),input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::SPECIAL_SUB),
		input->getController()[inputNS::DINPUT_2P]->getLeftStick().x,input->getController()[inputNS::DINPUT_2P]->getLeftStick().y,
		input->getController()[inputNS::DINPUT_2P]->getRightStick().x,input->getController()[inputNS::DINPUT_2P]->getRightStick().y
	);
#endif
	// ���̂ւ�͑S�̂�initialize�̂ق���������������Ȃ����Ȃ�����
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��

	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	if (input->wasKeyPressed('U'))onUI = !onUI;

	if (onUI) {
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			hp[i].render(device);
			sp[i].render(device);
			colonyHp[i].render(device);
			missileInfomation[i].render(device);
			weaponInfomation[i].render(device);
			timerUI[i].render(device);
			chingin[i].render(device);
			hpEffect[i].render(device);
		}
	}

	if (pose.poseon )
	{
		pose.render(device);
	}

	// ���e�X�g�𖳌���
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

void Game::collisions() {
	for (int i = 0; i < NUM_BULLET; i++)
	{	//�o���b�g1<->�v���C���[2
		if (!bullet1[i].getActive())continue;
		if (player[PLAYER2].bodyCollide.collide(
			bullet1[i].bodyCollide.getCenter(), bullet1[i].bodyCollide.getRadius(),
			player[PLAYER2].getMatrixWorld(), bullet1[i].getMatrixWorld()))
		{
			player[PLAYER2].damgae(5);
			bullet1[i].inActivation();
		}
	}
		
	for (int i = 0; i < NUM_BULLET; i++)
	{
		//�o���b�g2<->�v���C���[1
		if (!bullet2[i].getActive())continue;
		if (player[PLAYER1].bodyCollide.collide(
			bullet2[i].bodyCollide.getCenter(), bullet2[i].bodyCollide.getRadius(),
			player[PLAYER1].getMatrixWorld(), bullet2[i].getMatrixWorld()))
		{
			player[PLAYER1].damgae(5);
			bullet2[i].inActivation();
			
		}
	}

	//�l�X�g���[���I�I
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		for (int k = 0; k < JUNK_MAX; k++)
		{
			if (between2VectorLength(*player[i].getPosition(), *junk[k].getPosition()) <= junkNS::HEAD_DISTANCE)
			{
				if (player[i].bodyCollide.collide(junk[k].bodyCollide.getCenter(),junk[k].getRadius(),
					player[i].getMatrixWorld(),junk[k].getMatrixWorld()))
				{//�v���C���[�ƃK���N�^���Փ˂�����
					junk[k].inActivation();
					hpEffect[i].activate(10);
				}
				junk[k].headPosition(*player[i].getPosition());
			}
		}
	}

}

void Game::AI() {

}

void Game::uninitialize() {
	SAFE_DELETE(light);
	SAFE_DELETE_ARRAY(camera);
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hp[i].uninitialize();
		sp[i].uninitialize();
		colonyHp[i].uninitialize();
		missileInfomation[i].uninitialize();
		weaponInfomation[i].uninitialize();
		timerUI[i].uninitialize();
		chingin[i].uninitialize();
		hpEffect[i].uninitialize();
		target.uninitialize();
		pose.uninitialize();

	}
}