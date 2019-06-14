#include "Game.h"
#include "Direct3D9.h"
using namespace gameNS;

int currentBullet;//��

Game::Game()
{
	sceneName = "Scene -Game-";
	nextScene = SceneList::NONE_SCENE;
	currentBullet = 0;
}

Game::~Game()
{

}

void Game::initialize(Direct3D9* direct3D9,Input* _input) {
	//Input
	input = _input;
	//camera
	camera = new Camera[NUM_PLAYER];
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
		camera[i].setTarget(player[i].getPosition());
		camera[i].setTargetX(&player[i].getAxisX()->direction);
		camera[i].setTargetY(&player[i].getAxisY()->direction);
		camera[i].setTargetZ(&player[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[i]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
	}

	//light
	light = new Light;
	light->initialize(direct3D9);

	colony[0].initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(150, 0, 300));
	colony[1].initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(-150, 0, 300));

	for (int i = 0; i < NUM_PLAYER; i++)
	{//�v���C���[�̏�����
		player[i].initialize(direct3D9->device, (LPSTR)"Toon_6Color.x", &(D3DXVECTOR3)gameNS::PLAYER_POSITION[i]);
		hp[i].initialize(direct3D9->device, i);
		sp[i].initialize(direct3D9->device, i);
		colonyHp[i].initialize(direct3D9->device, i);
		missileInfomation[i].initialize(direct3D9->device, i);
		weaponInfomation[i].initialize(direct3D9->device, i);
	}
	for (int i = 0; i < NUM_MAGNET; i++)
	{//����
		if (NUM_MAGNET / 2 > i) {
			magnet[i].initialize(direct3D9->device,2.0f);
		}
		else {
			magnet[i].initialize(direct3D9->device,-2.0f);
		}
	}

	for (int i = 0; i < NUM_BULLET; i++)
	{//�o���b�g�̏�����
		bullet[i].initialize(direct3D9->device, (LPSTR)"bullet.x", &D3DXVECTOR3(0,0,0));
		bullet[i].anyAxisRotation(D3DXVECTOR3(0, 1, 0), (float)(rand() % 360));
		
	}

	//�t�B�[���h
	field.initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(0, -100, 0));

	text.initialize(direct3D9->device,10,10, 0xff00ff00);
	text2.initialize(direct3D9->device,11,11, 0xff0000ff);
	for (int i = 0; i < JUNK_MAX; i++)
	{
		junk[i].initialize(direct3D9->device, (LPSTR)"RobotB.x", &D3DXVECTOR3((float)(5 + i), 3, 3));
	}
}

void Game::update() {
	
	for (int i = 0; i < NUM_PLAYER; i++)
	{//�v���C���[�̍X�V
		player[i].setSpeed(D3DXVECTOR3(0, 0, 0));
		player[i].setGravity(*field.getPosition(), 0.1f);
		
		D3DXVECTOR3 moveDirection;
		switch (i)
		{
		case PLAYER1:
			if (input->isKeyDown('W')) {
				D3DXVec3Normalize(&moveDirection, &slip(camera[i].getDirectionZ(), player[i].getAxisY()->direction));
				player[i].addSpeed(moveDirection*0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, moveDirection, 0.1f);
			}
			if (input->isKeyDown('S')) {
				D3DXVec3Normalize(&moveDirection, &slip(camera[i].getDirectionZ(), player[i].getAxisY()->direction));
				player[i].addSpeed(moveDirection*-0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, -moveDirection, 0.1f);
			}
			if (input->isKeyDown('A')) {
				moveDirection = camera[i].getDirectionX();
				player[i].addSpeed(moveDirection*-0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, -moveDirection, 0.1f);
			}
			if (input->isKeyDown('D'))
			{
				moveDirection = camera[i].getDirectionX();
				player[i].addSpeed(moveDirection*0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, moveDirection, 0.1f);
			}
			if (input->wasKeyPressed(VK_SPACE))
			{
				player[i].jump();
			}
			if (input->getController()[PLAYER1]->checkConnect()) {
				player[i].move(input->getController()[PLAYER1]->getLeftStick(), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			break;

		case PLAYER2:
			if (input->isKeyDown(VK_UP)) {
				D3DXVec3Normalize(&moveDirection, &slip(camera[i].getDirectionZ(), player[i].getAxisY()->direction));
				player[i].addSpeed(moveDirection*0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, moveDirection, 0.1f);
			}
			if (input->isKeyDown(VK_DOWN)) {
				D3DXVec3Normalize(&moveDirection, &slip(camera[i].getDirectionZ(), player[i].getAxisY()->direction));
				player[i].addSpeed(moveDirection*-0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, -moveDirection, 0.1f);
			}
			if (input->isKeyDown(VK_LEFT)) {
				moveDirection = camera[i].getDirectionX();
				player[i].addSpeed(moveDirection*-0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, -moveDirection, 0.1f);
			}
			if (input->isKeyDown(VK_RIGHT))
			{
				moveDirection = camera[i].getDirectionX();
				player[i].addSpeed(moveDirection*0.1);
				player[i].postureControl(player[i].getAxisZ()->direction, moveDirection, 0.1f);
			}
			if (input->wasKeyPressed(VK_RETURN))
			{
				player[i].jump();
			}
			if (input->getController()[PLAYER2]->checkConnect()) {
				player[i].move(input->getController()[PLAYER2]->getLeftStick(), camera[i].getDirectionX(), camera[i].getDirectionZ());
			}
			break;
		}
		//�t�B�[���h�␳
		if (player[i].getReverseAxisY()->rayIntersect(*field.getMesh(), field.getMatrixWorld()) &&
			player[i].getRadius() >= (player[i].getReverseAxisY()->distance -0.01f))
		{
			//�߂荞�ݕ␳
			player[i].setPosition(*player[i].getPosition() + player[i].getAxisY()->direction*(player[i].getRadius() - player[i].getReverseAxisY()->distance));
			//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
			player[i].setSpeed(player[i].getReverseAxisY()->slip(player[i].getSpeed(), player[i].getReverseAxisY()->normal));
			//Ray moveRay;//�ړ��x�N�g�����g���ă��C���쐬
			//moveRay.initialize(*player[i].getPosition(), player[i].getSpeed());
			//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && player[i].getRadius() > moveRay.distance)
			//{//��d�`�F�b�N
			//	player[i].setSpeed(moveRay.slip(player[i].getSpeed(),moveRay.normal));
			//}
		}

		player[i].update();
	}

	if (input->wasKeyPressed('Z'))
	{
		bullet[currentBullet].setPosition(*player[PLAYER1].getPosition());
		bullet[currentBullet].addSpeed(player[PLAYER1].getAxisZ()->direction*0.2);
		bullet[currentBullet].postureControl(bullet[currentBullet].getAxisZ()->direction, player[PLAYER1].getAxisZ()->direction, 1.0f);
		currentBullet++;
		if (currentBullet >= NUM_BULLET)currentBullet = 0;
	}

	for (int i = 0; i < NUM_BULLET; i++)
	{//�o���b�g�̍X�V
		
		bullet[i].setSpeed(D3DXVECTOR3(0, 0, 0));
		bullet[i].setGravity(*field.getPosition(), 0.4f);
		bullet[i].addSpeed(bullet[i].getAxisZ()->direction*0.2*(i+1));//�����ړ�
		
		bullet[i].anyAxisRotation(bullet[i].getAxisY()->direction, (rand() % 10) -5);
		//�t�B�[���h�␳
		if (bullet[i].getReverseAxisY()->rayIntersect(*field.getMesh(), field.getMatrixWorld()) &&
			bullet[i].getRadius() >= (bullet[i].getReverseAxisY()->distance -0.01f))
		{
			//�߂荞�ݕ␳
			bullet[i].setPosition(*bullet[i].getPosition() + bullet[i].getAxisY()->direction*(bullet[i].getRadius() - bullet[i].getReverseAxisY()->distance));
			//�ړ��x�N�g���̃X���b�v�i�ʕ����ւ̃x�N�g�������̍폜�j
			bullet[i].setSpeed(bullet[i].getReverseAxisY()->slip(bullet[i].getSpeed(), bullet[i].getReverseAxisY()->normal));
			//Ray moveRay;//�ړ��x�N�g�����g���ă��C���쐬
			//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
			//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
			//{//��d�`�F�b�N
			//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
			//}
		}

		bullet[i].update();
	}

	//�J�����̉�]
	if (input->isKeyDown('G')) {
		camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), -1.0f);
	};
	if (input->isKeyDown('J')) {
		camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), 1.0f);
	};

	if (input->getController()[PLAYER1]->checkConnect()) {
		camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), input->getController()[PLAYER1]->getRightStick().x*0.001f);
		camera[PLAYER1].rotation(camera->getHorizontalAxis(), input->getController()[PLAYER1]->getRightStick().y*0.001f);
	}

	if (input->getMouseLButton()) {
		camera[PLAYER2].rotation(D3DXVECTOR3(0, 1, 0), input->getMouseRawX());
	};
	if (input->getMouseRButton()) {
		camera[PLAYER2].rotation(D3DXVECTOR3(0, 1, 0), -1.0f);
	};

	if (input->getController()[PLAYER2]->checkConnect()) {
		camera[PLAYER2].rotation(D3DXVECTOR3(0, 1, 0), input->getController()[PLAYER2]->getRightStick().x*0.001f);
		camera[PLAYER2].rotation(D3DXVECTOR3(0, 0, 1), input->getController()[PLAYER2]->getRightStick().y*0.001f);
	}

	for (int i = 0; i < NUM_PLAYER; i++)
	{//�J�����̍X�V
		camera[i].setUpVector(player[i].getAxisY()->direction);
		camera[i].update();
	}

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hp[i].update();
		sp[i].update();
		colonyHp[i].update();
		missileInfomation[i].update();
		weaponInfomation[i].update();
	}
	// �R���j�[�A�b�v�f�[�g
	colony[0].update();

	for (int i = 0; i < JUNK_MAX; i++)
	{
		// �K���N�^�A�b�v�f�[�g
		junk[i].update();
	}

	if (input->getController()[PLAYER1]->wasButton(virtualControllerNS::A))
	{
		magnet[NUM_MAGNET - 1].reverseAmount();
	}

	magnet[NUM_MAGNET-1].setPosition(*player[PLAYER1].getPosition());
	magnet[1].setPosition(*player[PLAYER2].getPosition());

	//���΂̍X�V
	for (int i = 0; i < NUM_MAGNET; i++)
	{
		for (int j = 0; j < NUM_MAGNET; j++)
		{
			if(j != i)
				magnet[i].calculationMagneticeForce(magnet[j]);
		}
	}
	for (int i = 0; i < NUM_MAGNET; i++)
	{
		magnet[i].update();
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

void Game::render3D(Direct3D9* direct3D9,Camera currentCamera) {
	for (int i = 0; i < NUM_PLAYER; i++)
	{//�v���C���[�̕`��
		player[i].toonRender(direct3D9->device,currentCamera.view,currentCamera.projection,currentCamera.position);
	}
	for (int i = 0; i < NUM_BULLET; i++)
	{//�o���b�g�̕`��
		bullet[i].render(direct3D9->device,currentCamera.view,currentCamera.projection,currentCamera.position);
	}

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, false);

	for (int i = 0; i < NUM_COLONY; i++)
	{
		colony[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, true);

	for (int i = 0; i < JUNK_MAX; i++)
	{
		junk[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	//�t�B�[���h�̕`��
	field.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	for (int i = 0; i < NUM_MAGNET; i++)
	{//
		magnet[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
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
	// ���u�����h���s��
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���\�[�X�J���[�̎w��
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ���f�X�e�B�l�[�V�����J���[�̎w��
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hp[i].render(device);
		sp[i].render(device);
		colonyHp[i].render(device);
		missileInfomation[i].render(device);
		weaponInfomation[i].render(device);
	}
}

void Game::collisions() {

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
	}
}