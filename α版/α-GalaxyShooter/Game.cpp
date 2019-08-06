//===================================================================================================================================
//【Game.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/04
//===================================================================================================================================
#include "Game.h"
#include "Direct3D9.h"
using namespace gameNS;
//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
Game::Game()
{
	sceneName = "Scene -Game-";
	currentMemoryPile1 = 0;
	currentMemoryPile2 = 0;
	intervalBullet1 = 0;
	intervalBullet2 = 0;
	currentBullet1 = 0;
	currentBullet2 = 0;
	onRecursion1P = false;
	recursion1PAnd2P = false;

	reverseValue1PXAxis = 2;
	reverseValue1PYAxis = 2;
	reverseValue2PXAxis = 2;
	reverseValue2PYAxis = 2;

	nextScene = SceneList::RESULT;
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
Game::~Game()
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_GAME);
}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
void Game::initialize(
	Direct3D9* _direct3D9,
	Input* _input,
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader,
	TextManager* _textManager) {
	//direct3D9
	direct3D9 = _direct3D9;
	//Input
	input = _input;
	//sound
	sound = _sound;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	//shaderLoader
	shaderLoader = _shaderLoader;
	//textManager
	textManager = _textManager;

	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_SPLASH_TITLE);
	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_GAME, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera[NUM_PLAYER];
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH/2, WINDOW_HEIGHT);
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

	//コロニー
	colony[0].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON_X100], &D3DXVECTOR3(150, 0, 300));
	colony[1].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::PLANET], &D3DXVECTOR3(-150, 0, 300));
	//フィールド
	field.Planet::initilaize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::PLANET], &(D3DXVECTOR3)PLANET_POSITION);

	// 画面分割線の初期化
	uiScreenSplitLine.initialize(direct3D9->device, textureLoader);

	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの初期化
		player[i].initialize(i, direct3D9->device, staticMeshLoader,textureLoader,shaderLoader);
		player[i].setInput(input);			//入力クラスのセット
		player[i].setCamera(&camera[i]);	//カメラのセット
		player[i].configurationGravity(field.getPosition(),field.getRadius());	//重力を作成

		hpEffect[i].initialize(direct3D9->device, i, _textureLoader);
		target.initialize(direct3D9->device, i, _textureLoader, _staticMeshLoader);
		uiRecursion[i].initialize(direct3D9->device, i, _textureLoader, _input);
		uiPlayTime[i].initialize(direct3D9->device, i, _textureLoader, _textManager);
		uiChingin[i].initialize(direct3D9->device, i, _textureLoader, _textManager);
		uiRevivalGauge[i].initialize(direct3D9->device, i, _textureLoader);
	}

	//磁石の初期化
	for (int i = 0; i < NUM_MAGNET; i++)
	{
		if (NUM_MAGNET / 2 > i) {
			magnet[i].initialize(direct3D9->device, staticMeshLoader,2.0f);
		}
		else {
			magnet[i].initialize(direct3D9->device, staticMeshLoader ,-2.0f);
		}
	}

	//テキストの初期化
	text.initialize(direct3D9->device,10,10, 0xff00ff00);
	text2.initialize(direct3D9->device,11,11, 0xff0000ff);

	//ガラクタ
	for (int i = 0; i < JUNK_MAX; i++)
	{
		D3DXVECTOR3 position((float)(rand()%100-50), (float)(rand()%100-50), (float)(rand()%100-50));
		D3DXVec3Normalize(&position, &position);
		position *= 100;
		junk[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON], &position);
	}

	//ポイントスプライト
	pointSprite.initilaize(direct3D9->device);

	//インスタンスプレーン
	plane.createPositionSpherical(direct3D9->device,3000, 250.0f);
	plane.initialize(direct3D9->device,*shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD),*textureLoader->getTexture(textureLoaderNS::RING));

	//ポーズの初期化
	pose.initialize(direct3D9->device, 0, _textureLoader);


	// ワスレモノの初期化
	wasuremonoManager.initialize(direct3D9->device, &wasuremono, staticMeshLoader, &field);
	// チンギン初期化
	chinginManager.initialize(direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));
	// マップ初期化
	map.initialize(direct3D9->device, &field);
	//xFile読込meshのインスタンシング描画のテスト
	D3DXVECTOR3 positionList[] =
	{
		D3DXVECTOR3(100,50,50),
		D3DXVECTOR3(-100,-100,-50),
		D3DXVECTOR3(100,-50,10),
		D3DXVECTOR3(100,50,10),
		D3DXVECTOR3(100,0,100),
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(-100,100,100),
		D3DXVECTOR3(-100,-100,100),
		D3DXVECTOR3(-100,100,0),
		D3DXVECTOR3(-100,100,-100),
	};
	testObject.initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON_X10], &D3DXVECTOR3(0, 0, 0));
	testObject.setNumOfRender(direct3D9->device, 10, positionList);
	testObject.activation();

	D3DXVECTOR3 cubeList[NUM_CUBE];
	for (int i = 0; i < NUM_CUBE; i++)
	{
		cubeList[i] = D3DXVECTOR3((float)(rand() % 1000 - 500), (float)(rand() % 1000 - 500), (float)(rand() % 1000 - 500));
	}
	testCube.initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::CUBE], &D3DXVECTOR3(0, 0, 0));
	testCube.setNumOfRender(direct3D9->device, NUM_CUBE, cubeList);
	testCube.activation();

	//ゲームマスター
	gameMaster->resetGameTime();//ゲーム時間のリセット
}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void Game::update(float _frameTime) {

	sceneTimer += _frameTime;
	frameTime = _frameTime;
	if (pose.poseon)
	{
		if (input->wasKeyPressed('P') ||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::SPECIAL_MAIN) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::SPECIAL_MAIN)
			)// ポーズ解除
		{
			pose.poseon = false;

		}
	}
	else if (!pose.poseon)
	{
		if (input->wasKeyPressed('P') ||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::SPECIAL_MAIN) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::SPECIAL_MAIN)
			)// ポーズ解除
		{
			pose.poseon = true;

		}
	}

	if (pose.poseon)return;// ポーズしてたら更新しない

	//【処理落ち】
	//フレーム時間が約10FPS時の時の時間より長い場合は、処理落ち（更新しない）
	//※フレーム時間に準拠している処理が正常に機能しないため
	if (frameTime > 0.10)return;

	//【ゲームマスターの更新】
	gameMaster->update(frameTime);
	if (gameMaster->whetherGameOver())
	{//シーン切替
		changeScene(SceneList::RESULT);
	}

	//【プレイヤーの更新】
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		player[i].update(frameTime);
	}

	//プレイヤーの更新
	{
		// 連打復活が完成するまでの仮
		static int revivalPoint = 0;
		if (revivalPoint < 50000) { revivalPoint++; }

		for (int i = 0; i < NUM_PLAYER; i++)
		{
			hpEffect[i].update();
			target.update();

			uiRecursion[i].update();
			uiRevivalGauge[i].update(revivalPoint);
		}
	}

	// コロニーアップデート
	{
		colony[0].update();

	}

	// ガラクタアップデート
	for (int i = 0; i < JUNK_MAX; i++)
	{
		junk[i].update(frameTime, field.getSphereMesh(), *field.getMatrixWorld(), *field.getPosition());
	}

	//磁石の更新
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


	// ワスレモノの更新
	wasuremonoManager.update(frameTime);
	for (int i = 0; i < wasuremono.size(); i++)
	{
		wasuremono[i]->update(frameTime, *field.getMesh(), *field.getMatrixWorld(), *field.getPosition());
	}

	// チンギンの更新
	chinginManager.update(frameTime, &player[1]);
	D3DXVECTOR3 unko = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	if (input->isKeyDown('M')) {
		chinginManager.generateChingin(10, unko);
	};
}

//===================================================================================================================================
//【描画】
//===================================================================================================================================
void Game::render(Direct3D9* direct3D9) {


	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER1].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER1].projection);
	direct3D9->changeViewport1PWindow();
	render3D(direct3D9,camera[PLAYER1]);

	//2Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER2].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER2].projection);
	direct3D9->changeViewport2PWindow();
	render3D(direct3D9,camera[PLAYER2]);
	//UI
	//direct3D9->device->SetTransform(D3DTS_VIEW, &camera[2].view);
	//direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[2].projection);
	direct3D9->changeViewportFullWindow();
	renderUI(direct3D9->device);
}

//===================================================================================================================================
//【3D描画】
//===================================================================================================================================
void Game::render3D(Direct3D9* direct3D9, Camera currentCamera) {

	//ステンシルマスク
	target.renderStencilMask(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの描画
		player[i].toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
			*shaderLoader->getEffect(shaderNS::TOON),
			*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
			*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
	}

	target.renderEffectImage(direct3D9->device);

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, false);

	for (int i = 0; i < NUM_COLONY; i++)
	{// コロニーの描画
		colony[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	direct3D9->device->SetRenderState(D3DRS_LIGHTING, true);

	//(仮)ガラクタの描画
	for (int i = 0; i < JUNK_MAX; i++)
	{
		junk[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	// フィールドの描画
	field.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	//(仮)マグネットの描画
	for (int i = 0; i < NUM_MAGNET; i++)
	{
		magnet[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	//(仮)//ポイントスプライトの描画
	pointSprite.render(direct3D9->device, currentCamera.position);

	//(仮)//プレーンの描画(インスタンシング)
	plane.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);


	//メモリーラインの切断ガイドの表示
	if (collitionMemoryLine1P)
	{

	}

	//xFileStaticMeshテスト描画
	testObject.multipleRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
		*shaderLoader->getEffect(shaderNS::INSTANCE_STATIC_MESH));
	testCube.multipleRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
		*shaderLoader->getEffect(shaderNS::INSTANCE_STATIC_MESH));
	// ワスレモノの描画
	for(int i = 0; i < wasuremono.size(); i++)
	{
		wasuremono[i]->render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}

	// チンギンの描画
	chinginManager.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	map.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

#ifdef _DEBUG
	Ray debugRay;
	//法線
	debugRay.color = D3DXCOLOR(128, 0, 128, 255);
	debugRay.update(*player[PLAYER1].getPosition(), player[PLAYER1].getReverseAxisY()->normal);
	debugRay.render(direct3D9->device, 100.0f);
#endif

}

//===================================================================================================================================
//【UI/2D描画】
//===================================================================================================================================
void Game::renderUI(LPDIRECT3DDEVICE9 device) {
#ifdef _DEBUG
	text.print(50, 200,
		"difference:%.3f\n",difference);
	text.print(10, 150,
		"\
		sceneTime:%.2f\n\
		frameTime:%.2f\n\
		",
		sceneTimer, frameTime);
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

	text.print(WINDOW_WIDTH / 2, 170, 
		"collisionMemoryLine(%d)\n",
		collitionMemoryLine1P
	);
	text.print(WINDOW_WIDTH / 2, 200,
		"collisionMemoryLine(%.02f)\n",
		memoryLine1P.calculationDistance(*player[PLAYER2].getPosition())
	);
	text.print(WINDOW_WIDTH / 2, 230,
		"recrusion1PAnd2P(%d)\n",
		recursion1PAnd2P
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
	// このへんは全体のinitializeのほうがいいかもしれない＠なかごみ
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定

	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	if (input->wasKeyPressed('U'))onUI = !onUI;

	if (onUI) {

		// チンギン完成までの仮
		static int chingin = 0;
		if (chingin < 99999) { chingin++; }

		for (int i = 0; i < NUM_PLAYER; i++)
		{
			//hpEffect[i].render(device);
			uiRecursion[i].render(device);
			uiPlayTime[i].render(device, gameMaster->getGameTime());
			uiChingin[i].render(device, gameMaster->getGameTime(), chingin);
			uiRevivalGauge[i].render(device);
		}
	}

	// 画面分割線
	uiScreenSplitLine.render(device);

	if (pose.poseon)
	{
		pose.render(device);
	}

	// αテストを無効に
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//===================================================================================================================================
//【衝突判定処理】
//===================================================================================================================================
void Game::collisions() {
	//1Pバレット<->プレイヤー2
	for (int i = 0; i < playerNS::NUM_BULLET; i++)
	{
		if (!player[PLAYER1].bullet[i].getActive())continue;
		if (player[PLAYER2].bodyCollide.collide(
			player[PLAYER1].bullet[i].bodyCollide.getCenter(), 
			player[PLAYER1].bullet[i].bodyCollide.getRadius(),
			*player[PLAYER2].getMatrixWorld(), 
			*player[PLAYER1].bullet[i].getMatrixWorld()))
		{
			sound->play(soundNS::TYPE::SE_DAMAGE_COVERED, soundNS::METHOD::PLAY);
			player[PLAYER2].damgae(5);
			player[PLAYER1].bullet[i].inActivation();
		}
	}

	//2Pバレット<->プレイヤー1
	for (int i = 0; i < playerNS::NUM_BULLET; i++)
	{
		if (!player[PLAYER2].bullet[i].getActive())continue;
		if (player[PLAYER1].bodyCollide.collide(
			player[PLAYER2].bullet[i].bodyCollide.getCenter(), 
			player[PLAYER2].bullet[i].bodyCollide.getRadius(),
			*player[PLAYER1].getMatrixWorld(), 
			*player[PLAYER2].bullet[i].getMatrixWorld()))
		{
			sound->play(soundNS::TYPE::SE_DAMAGE_COVERED, soundNS::METHOD::PLAY);
			player[PLAYER1].damgae(5);
			player[PLAYER2].bullet[i].inActivation();
			
		}
	}

	for (int i = 0; i < wasuremono.size(); i++)
	{
		if (!wasuremono[i]->getActive())	continue;
		for (int j = 0; j < NUM_BULLET; j++)
		{
			// ワスレモノ<->バレット1
			if (wasuremono[i]->bodyCollide.collide(
				player[PLAYER1].bullet[j].bodyCollide.getCenter(), player[PLAYER1].bullet[j].bodyCollide.getRadius(),
				*wasuremono[i]->getMatrixWorld(), *player[PLAYER1].bullet[j].getMatrixWorld()))
			{
				wasuremono[i]->inActivation();
				player[PLAYER1].bullet[j].inActivation();
			}

			// ワスレモノ<->バレット2
			if (wasuremono[i]->bodyCollide.collide(
				player[PLAYER2].bullet[j].bodyCollide.getCenter(), player[PLAYER2].bullet[j].bodyCollide.getRadius(),
				*wasuremono[i]->getMatrixWorld(), *player[PLAYER2].bullet[j].getMatrixWorld()))
			{
				wasuremono[i]->inActivation();
				player[PLAYER2].bullet[j].inActivation();
			}
		}
	}

	//ガラクタとプレイヤー
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		for (int k = 0; k < JUNK_MAX; k++)
		{
			if (between2VectorLength(*player[i].getPosition(), *junk[k].getPosition()) <= junkNS::HEAD_DISTANCE)
			{
				if (player[i].bodyCollide.collide(junk[k].bodyCollide.getCenter(),junk[k].getRadius(),
					*player[i].getMatrixWorld(),*junk[k].getMatrixWorld()))
				{//プレイヤーとガラクタが衝突したら
					junk[k].inActivation();
					hpEffect[i].activate(10);
				}
				junk[k].headPosition(*player[i].getPosition());
			}
		}
	}

	//1Pのメモリーライン<->2Pプレイヤーの衝突検知
	//if (memoryLine1P.collision(*player[PLAYER2].getPosition(),player[PLAYER2].bodyCollide.getRadius()))
	//	collitionMemoryLine1P = true;
	//else 
	//	collitionMemoryLine1P = false;

	//1Pのリカージョン<->2Pプレイヤーの衝突検知
	//if (onRecursion1P)
	//{
	//	recursion1PAnd2P = recursion1P->collide(
	//			*player[PLAYER2].getPosition(),
	//			player[PLAYER2].bodyCollide.getCenter(),
	//			player[PLAYER2].bodyCollide.getRadius(),
	//			*player[PLAYER2].getMatrixWorld());
	//	if (recursion1PAnd2P)
	//	{
	//		player[PLAYER2].changeState(playerNS::SKY);
	//	}
	//}
}
//===================================================================================================================================
//【AI処理】
//===================================================================================================================================
void Game::AI() {

}

//===================================================================================================================================
//【終了処理】
//===================================================================================================================================
void Game::uninitialize() {
	SAFE_DELETE(light);
	SAFE_DELETE_ARRAY(camera);
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hpEffect[i].uninitialize();
		target.uninitialize();
		pose.uninitialize();
		uiRecursion[i].release();
		uiPlayTime[i].release();
		uiChingin[i].release();
		uiRevivalGauge[i].release();
	}
	uiScreenSplitLine.release();
	wasuremonoManager.uninitialize();
	map.uninitialize();
}