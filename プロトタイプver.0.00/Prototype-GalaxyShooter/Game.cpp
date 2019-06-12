#include "Game.h"
#include "Direct3D9.h"
using namespace gameNS;

int currentBullet;//仮

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

	//プレイヤー
	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの初期化
		player[i].initialize(direct3D9->device, (LPSTR)"Toon_6Color.x", &(D3DXVECTOR3)gameNS::PLAYER_POSITION[i]);
	}

	//磁石
	magnet.initialize(direct3D9->device);

	for (int i = 0; i < NUM_BULLET; i++)
	{//バレットの初期化
		bullet[i].initialize(direct3D9->device, (LPSTR)"bullet.x", &D3DXVECTOR3(0,0,0));
		bullet[i].anyAxisRotation(D3DXVECTOR3(0, 1, 0), rand() % 360);
		
		hp[i].initialize(direct3D9->device, i);
		sp[i].initialize(direct3D9->device, i);
		colonyHp[i].initialize(direct3D9->device, i);
		missileInfomation[i].initialize(direct3D9->device, i);
		weaponInfomation[i].initialize(direct3D9->device, i);
	}

	//フィールド
	field.initialize(direct3D9->device, (LPSTR)"planet.x", &D3DXVECTOR3(0, -100, 0));



	//仮置き
	// ライトをあてる 白色で光沢反射ありに設定
	D3DXVECTOR3 vDirection(1, 1, 1);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vDirection);
	light.Range = 200.0f;
	direct3D9->device->SetLight(0, &light);

	text.initialize(direct3D9->device,0,10, 0xff00ff00);
	text2.initialize(direct3D9->device,7,7, 0xff0000ff);
	
}

void Game::update() {
	
	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの更新
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
			break;
		}
		//フィールド補正
		if (player[i].getReverseAxisY()->rayIntersect(*field.getMesh(), field.getMatrixWorld()) &&
			player[i].getRadius() >= (player[i].getReverseAxisY()->distance -0.01f))
		{
			//めり込み補正
			player[i].setPosition(*player[i].getPosition() + player[i].getAxisY()->direction*(player[i].getRadius() - player[i].getReverseAxisY()->distance));
			//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
			player[i].setSpeed(player[i].getReverseAxisY()->slip(player[i].getSpeed(), player[i].getReverseAxisY()->normal));
			//Ray moveRay;//移動ベクトルを使ってレイを作成
			//moveRay.initialize(*player[i].getPosition(), player[i].getSpeed());
			//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && player[i].getRadius() > moveRay.distance)
			//{//二重チェック
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
	{//バレットの更新
		
		bullet[i].setSpeed(D3DXVECTOR3(0, 0, 0));
		bullet[i].setGravity(*field.getPosition(), 0.4f);
		bullet[i].addSpeed(bullet[i].getAxisZ()->direction*0.2*(i+1));//自動移動
		
		bullet[i].anyAxisRotation(bullet[i].getAxisY()->direction, (rand() % 10) -5);
		//フィールド補正
		if (bullet[i].getReverseAxisY()->rayIntersect(*field.getMesh(), field.getMatrixWorld()) &&
			bullet[i].getRadius() >= (bullet[i].getReverseAxisY()->distance -0.01f))
		{
			//めり込み補正
			bullet[i].setPosition(*bullet[i].getPosition() + bullet[i].getAxisY()->direction*(bullet[i].getRadius() - bullet[i].getReverseAxisY()->distance));
			//移動ベクトルのスリップ（面方向へのベクトル成分の削除）
			bullet[i].setSpeed(bullet[i].getReverseAxisY()->slip(bullet[i].getSpeed(), bullet[i].getReverseAxisY()->normal));
			//Ray moveRay;//移動ベクトルを使ってレイを作成
			//moveRay.initialize(*bullet[i].getPosition(), bullet[i].getSpeed());
			//if(moveRay.rayIntersect(*field.getMesh(),field.getMatrixWorld()) && bullet[i].getRadius() > moveRay.distance)
			//{//二重チェック
			//	bullet[i].setSpeed(moveRay.slip(bullet[i].getSpeed(),moveRay.normal));
			//}
		}

		bullet[i].update();
	}

	//カメラの回転
	if (input->isKeyDown('G')) {
		camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), -1.0f);
	};
	if (input->isKeyDown('J')) {
		camera[PLAYER1].rotation(D3DXVECTOR3(0, 1, 0), 1.0f);
	};



	if (input->getMouseLButton()) {
		camera[PLAYER2].rotation(D3DXVECTOR3(0, 1, 0), input->getMouseRawX());
	};
	if (input->getMouseRButton()) {
		camera[PLAYER2].rotation(D3DXVECTOR3(0, 1, 0), -1.0f);
	};
	
	for (int i = 0; i < NUM_PLAYER; i++)
	{//カメラの更新
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
}

void Game::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewport1PWindow();
	render3D(direct3D9,camera[0]);

	//2Pカメラ・ウィンドウ
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
	{//プレイヤーの描画
		player[i].toonRender(direct3D9->device,currentCamera.view,currentCamera.projection,currentCamera.position);
	}
	for (int i = 0; i < NUM_BULLET; i++)
	{//バレットの描画
		bullet[i].render(direct3D9->device,currentCamera.view,currentCamera.projection,currentCamera.position);
	}
	//フィールドの描画
	field.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	magnet.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
#ifdef _DEBUG
	Ray debugRay;
	//法線
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
	text2.print(800, 10,
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

	// このへんは全体のinitializeのほうがいいかもしれない＠なかごみ
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
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
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hp[i].uninitialize();
		sp[i].uninitialize();
		colonyHp[i].uninitialize();
		missileInfomation[i].uninitialize();
		weaponInfomation[i].uninitialize();
	}
}