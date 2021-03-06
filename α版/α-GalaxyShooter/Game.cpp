//===================================================================================================================================
//【Game.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/09/12
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
	startCountFlag = true;
	endCountFlag = false;

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
	sound->stop(soundNS::TYPE::BGM_TITLE);
	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_GAME, soundNS::METHOD::LOOP);

	//camera
	camera = new Camera[NUM_PLAYER];

//--------------------------------------------------------------------
// キャラクターセレクトから連携されるまではここでplayer<-->AI切り替え
//--------------------------------------------------------------------
// 今はカメラの情報を貰っていろいろ試したいのでこんな位置になっている
//#if 1
//#define USING_AI
//#else
//#endif
	if (input->getController()[1]->getControllerID() == virtualControllerNS::EMPTY)
	{
		player[0] = new Player;
		player[1] = new AgentAI(player[0], &camera[1], &wasuremono);
	}
	else {
		player[0] = new Player;
		player[1] = new Player;
	}

	//camera
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH/2, WINDOW_HEIGHT);
		camera[i].setTarget(player[i]->getPosition());
		camera[i].setTargetX(&player[i]->getAxisX()->direction);
		camera[i].setTargetY(&player[i]->getAxisY()->direction);
		camera[i].setTargetZ(&player[i]->getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[i]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 10, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
		camera[i].setFieldOfView(D3DX_PI / 2.5);
	}

	//light
	light = new Light;
	light->initialize(direct3D9);

	//コロニー
	for (int i = 0; i < NUM_COLONY; i++)
	{
		colony[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::PLANET], &(D3DXVECTOR3)COLONY_POSITION[i]);
	}

	for (int i = 0; i < NUM_STAR_X10; i++)
	{
		star10[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON_X10], &(D3DXVECTOR3)STAR_X10_POSITION[i]);
	}
	for (int i = 0; i < NUM_STAR_X100; i++)
	{
		star100[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON_X100], &(D3DXVECTOR3)STAR_X100_POSITION[i]);
	}
	//フィールド
	field.Planet::initilaize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::PLANET], &(D3DXVECTOR3)PLANET_POSITION);

	// 画面分割線の初期化
	uiScreenSplitLine.initialize(direct3D9->device, textureLoader);

	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの初期化
		//player[i]->initialize(i, gameMaster->getPlayerInfomation()[i].modelType, direct3D9->device, staticMeshLoader, textureLoader, shaderLoader);
		player[i]->setInput(input);			//入力クラスのセット
		player[i]->setAnimationModel(animationLoader->getAnimationModel(i, gameMaster->getPlayerInfomation()[i].modelType));
		// テスト中
		if (i == 0)
		{
			player[i]->initialize(i, gameMasterNS::MODEL_TYPE::EVE, direct3D9->device, staticMeshLoader, textureLoader, shaderLoader);
		}
		else if (i == 1)
		{
			player[i]->initialize(i, gameMasterNS::MODEL_TYPE::ADAM, direct3D9->device, staticMeshLoader, textureLoader, shaderLoader);
		}
		player[i]->setCamera(&camera[i]);	//カメラのセット
		player[i]->setSound(sound);			//サウンドのセット
		player[i]->configurationGravity(field.getPosition(),field.getRadius());	//重力を作成
		player[i]->animationPlayer->setAnimationConfiguration(animationPlayerNS::SCENE_TYPE::GAME);
		player[i]->animationPlayer->resetAnimation();

		hpEffect[i].initialize(direct3D9->device, i, _textureLoader);
		target.initialize(direct3D9->device, i, _textureLoader, _staticMeshLoader);
		uiPlayTime[i].initialize(direct3D9->device, i, _textureLoader, _textManager);
		uiChingin[i].initialize(direct3D9->device, i, _textureLoader, _textManager);
		uiCutMemoryLine[i].initialize(direct3D9->device, i, _textureLoader);
		uiRevival[i].initialize(direct3D9->device, i, _textureLoader);
		uiCountDown[i].initialize(direct3D9->device, i, _textureLoader);
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
	plane.createPositionSpherical(direct3D9->device, 3000, 250.0f);
	plane.initialize(direct3D9->device, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::BACKGROUND_DUST));

	// シーンエフェクト初期化
	sceneEffect.initialize(direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));
	sceneEffect.setOnGameScene(true);
	//ポーズの初期化
	uiPause.initialize(direct3D9->device, _textureLoader);

	// マップ初期化
	map.initialize(direct3D9->device, &field);

	// ワスレモノの初期化
	wasuremonoManager.initialize(direct3D9->device, &wasuremono, staticMeshLoader, &field);

	// チンギン初期化
	chinginManager.initialize(direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// ラインエフェクト初期化
	lineEffect.initialize(direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	// マップ初期化
	map.initialize(direct3D9->device, &field);

	//xFile読込meshのインスタンシング描画のテスト
	//D3DXVECTOR3 positionList[] =
	//{
	//	D3DXVECTOR3(100,50,50),
	//	D3DXVECTOR3(-100,-100,-50),
	//	D3DXVECTOR3(100,-50,10),
	//	D3DXVECTOR3(100,50,10),
	//	D3DXVECTOR3(100,0,100),
	//	D3DXVECTOR3(0,100,0),
	//	D3DXVECTOR3(-100,100,100),
	//	D3DXVECTOR3(-100,-100,100),
	//	D3DXVECTOR3(-100,100,0),
	//	D3DXVECTOR3(-100,100,-100),
	//	D3DXVECTOR3(100,50,50),
	//	D3DXVECTOR3(-100,-100,-50),
	//	D3DXVECTOR3(100,-50,10),
	//	D3DXVECTOR3(100,50,10),
	//	D3DXVECTOR3(100,0,100),
	//	D3DXVECTOR3(0,100,0),
	//	D3DXVECTOR3(-100,100,100),
	//	D3DXVECTOR3(-100,-100,100),
	//	D3DXVECTOR3(-100,100,0),
	//	D3DXVECTOR3(-100,100,-100),
	//};
	//testObject.initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON_X10], &D3DXVECTOR3(0, 0, 0));
	//testObject.setNumOfRender(direct3D9->device, 20, positionList);
	//testObject.activation();

	//D3DXVECTOR3 cubeList[NUM_CUBE];
	//for (int i = 0; i < NUM_CUBE; i++)
	//{
	//	cubeList[i] = D3DXVECTOR3((float)(rand() % 1000 - 500), (float)(rand() % 1000 - 500), (float)(rand() % 1000 - 500));
	//}
	//testCube.initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::CUBE], &D3DXVECTOR3(0, 0, 0));
	//testCube.setNumOfRender(direct3D9->device, NUM_CUBE, cubeList);
	//testCube.activation();

	//ゲームマスター
	gameMaster->gameStart();//ゲーム開始時処理
#ifdef _DEBUG
	//極座標動作テスト用
	polarTest.initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::STAR_REGULAR_POLYHEDRON], &D3DXVECTOR3(0, 0, 0));
	polarTest.setPosition(*player[PLAYER1]->getPosition());
	polarTest.activation();

	polarPosition.radius = 0.0f;
	polarPosition.phi = 0.0f;
	polarPosition.theta = 0.0f;

	transPosition = D3DXVECTOR3(0, 0, 0);

#endif // _DEBUG


	//lambert = new Lambert(direct3D9->device);
	//lambert->load(*shaderLoader->getEffect(shaderNS::LAMBERT));
}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void Game::update(float _frameTime) {

	sceneTimer += _frameTime;
	frameTime = _frameTime;

	//ゲームが開始した場合ポーズが有効
	if (gameMaster->whetherAlreadyStart())
	{
		if (uiPause.getRenderFlag())
		{
			if (input->wasKeyPressed('P') ||
				input->getController()[PLAYER1]->wasButton(virtualControllerNS::SPECIAL_MAIN) ||
				input->getController()[PLAYER2]->wasButton(virtualControllerNS::SPECIAL_MAIN)
				)// ポーズ解除
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_PAUSE, soundNS::METHOD::PLAY);
				uiPause.setRenderFlag(false);
			}
		}
		else if (!uiPause.getRenderFlag())
		{
			if (input->wasKeyPressed('P') ||
				input->getController()[PLAYER1]->wasButton(virtualControllerNS::SPECIAL_MAIN) ||
				input->getController()[PLAYER2]->wasButton(virtualControllerNS::SPECIAL_MAIN)
				)// ポーズ解除
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_PAUSE, soundNS::METHOD::PLAY);
				uiPause.setRenderFlag(true);
			}
		}
		if (uiPause.getRenderFlag())return;// ポーズしてたら更新しない
	}

	//【処理落ち】
	//フレーム時間が約10FPS時の時の時間より長い場合は、処理落ち（更新しない）
	//※フレーム時間に準拠している処理が正常に機能しないため
	if (frameTime > 0.10)return;

	//【ゲームマスターの更新】
	gameMaster->update(frameTime);
	//ゲームオーバー時処理
	if (gameMaster->whetherGameOver())
	{//シーン切替
		for (int i = 0; i < playerNS::NUM_PLAYER; i++)
		{
			gameMaster->setWage(i, player[i]->getWage());
		}
		changeScene(SceneList::RESULT);
	}

	//【プレイヤーの更新】
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		player[i]->update(frameTime);
	}

	//【プレイヤーUIの更新】
	{
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			hpEffect[i].update();
			target.update();
			uiCutMemoryLine[i].update(*player[0]->getPosition(), *player[1]->getPosition());
			uiRevival[i].update(player[i]->getRevivalPoint());
		}
	}

	// コロニーアップデート
	for (int i = 0; i < NUM_COLONY; i++)
	{
		colony[i].update();
	}

	for (int i = 0; i < NUM_STAR_X10; i++)
	{
		star10[i].update();
	}
	for (int i = 0; i < NUM_STAR_X100; i++)
	{
		star100[i].update();
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
		magnet[NUM_MAGNET - 1].setPosition(*player[PLAYER1]->getPosition());
		magnet[1].setPosition(*player[PLAYER2]->getPosition());
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

	// ワスレモノの更新１（リスポーン処理）
	wasuremonoManager.update(frameTime);

	// ワスレモノの更新２
	for (int i = 0; i < wasuremono.size(); i++)
	{
		wasuremono[i]->update(frameTime, *field.getMesh(), *field.getMatrixWorld(), *field.getPosition());
	}

	// チンギンの更新
	chinginManager.update(sound, frameTime);
	D3DXVECTOR3 chinginTestPos = D3DXVECTOR3(200.0f, 200.0f, 200.0f);


	// ラインエフェクトの更新
	lineEffect.update(frameTime);

	//シーンエフェクトの更新
	sceneEffect.update(frameTime);


	// マップの更新
	map.update(frameTime, wasuremono);

	D3DXCOLOR* colorList = new D3DXCOLOR[3000];
	float sinValue = (sinf(gameMaster->getGameTime() * 4)+1.0f)/2.0f;
	float cosValue = cosf(gameMaster->getGameTime() * 4);
	for (int i = 0; i < 3000; i++)
	{
		colorList[i] = D3DXCOLOR(sinValue,sinValue,sinValue,sinValue);
	}
	plane.setColorBuffer(direct3D9->device, 3000, colorList);
	SAFE_DELETE_ARRAY(colorList);


#ifdef _DEBUG
	//極座標動作テスト用

	if (input->isKeyDown('F'))polarPosition.radius += 0.03f;
	if (input->isKeyDown('G'))polarPosition.theta += 0.03f;
	if (input->isKeyDown('H'))polarPosition.phi += 0.03f;

	if (input->isKeyDown('C'))polarPosition.radius -= 0.03f;
	if (input->isKeyDown('V'))polarPosition.theta -= 0.03f;
	if (input->isKeyDown('B'))polarPosition.phi -= 0.03f;

	transPosition = UtilityFunction::fromTransformationPolar3D(polarPosition.radius, polarPosition.theta, polarPosition.phi);

	polarTest.setPosition(*player[PLAYER1]->getPosition()+transPosition);

	polarTest.update();
#endif // _DEBUG
}

//===================================================================================================================================
//【描画】
//===================================================================================================================================
void Game::render(Direct3D9* direct3D9) {

	LPDIRECT3DSURFACE9 oldSurface = NULL;
	direct3D9->device->GetRenderTarget(0, &oldSurface);
	direct3D9->device->SetRenderTarget(0, colorSurface);
	direct3D9->device->SetRenderTarget(1, zMapSurface);


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

	 //フィールドの描画
	field.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);


	for (int i = 0; i < NUM_COLONY; i++)
	{// コロニーの描画
		colony[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}
	for (int i = 0; i < NUM_STAR_X10; i++)
	{
		star10[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}
	for (int i = 0; i < NUM_STAR_X100; i++)
	{
		star100[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}


	////(仮)ガラクタの描画
	//for (int i = 0; i < JUNK_MAX; i++)
	//{
	//	junk[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	//}


	////(仮)マグネットの描画
	//for (int i = 0; i < NUM_MAGNET; i++)
	//{
	//	magnet[i].render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	//}

	//(仮)//ポイントスプライトの描画
	pointSprite.render(direct3D9->device, currentCamera.position);

	// シーンエフェクトの描画
	sceneEffect.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	//(仮)//プレーンの描画(インスタンシング)
	plane.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	//xFileStaticMeshテスト描画
	//testObject.multipleRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
	//	*shaderLoader->getEffect(shaderNS::INSTANCE_STATIC_MESH));
	//testCube.multipleRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
	//	*shaderLoader->getEffect(shaderNS::INSTANCE_STATIC_MESH));

	// ワスレモノの描画
#if 1
	for (int i = 0; i < wasuremono.size(); i++)
	{
		wasuremono[i]->render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}
#else
	wasuremonoManager.instancingRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
		*shaderLoader->getEffect(shaderNS::INSTANCE_STATIC_MESH));	// インスタンシング描画をやろうしたが上手くいっていない
#endif
	// チンギンの描画
	chinginManager.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	// マップノードの描画
	map.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	
	// ラインエフェクトの描画
	lineEffect.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);


	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// プレイヤーの描画
		player[i]->toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position, *shaderLoader->getEffect(shaderNS::TOON), *textureLoader->getTexture(textureLoaderNS::TOON_SHADE), *textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
		// プレイヤーの他のオブジェクトの描画
		player[i]->otherRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
	}



#ifdef _DEBUG
	//極座標動作テスト用
	polarTest.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
#endif // _DEBUG

#ifdef _DEBUG
	Ray debugRay;
	//法線
	debugRay.color = D3DXCOLOR(128, 0, 128, 255);
	debugRay.update(*player[PLAYER1]->getPosition(), player[PLAYER1]->getReverseAxisY()->normal);
	debugRay.render(direct3D9->device, 100.0f);

#ifdef USING_AI
	AgentAI* agentAI = (AgentAI*)player[1];
	agentAI->debugRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);
#endif// USING_AI

#endif


	//ステンシル準備
	target.renderSetUp(direct3D9->device);

	// 一般ステンシル
	target.renderGeneral(direct3D9->device, 2, D3DCMPFUNC::D3DCMP_ALWAYS);

	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの描画
		player[i]->toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
			*shaderLoader->getEffect(shaderNS::TOON),
			*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
			*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
	}

	// 一般ステンシル
	target.renderGeneral(direct3D9->device, 2, D3DCMPFUNC::D3DCMP_EQUAL);

	// フィールドの描画
	field.render(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position);

	//ステンシルマスク
	target.renderStencilMask(direct3D9->device, 2, D3DCMPFUNC::D3DCMP_ALWAYS);

	for (int i = 0; i < NUM_PLAYER; i++)
	{//プレイヤーの描画
		player[i]->toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
			*shaderLoader->getEffect(shaderNS::TOON),
			*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
			*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
	}

	// ステンシル画像
	target.renderEffectImage(direct3D9->device, 2, D3DCMPFUNC::D3DCMP_EQUAL);

	target.render(direct3D9->device);

	// ステンシル終了
	target.renderStencilEnd(direct3D9->device);

}

//===================================================================================================================================
//【UI/2D描画】
//===================================================================================================================================
void Game::renderUI(LPDIRECT3DDEVICE9 device) {
#ifdef _DEBUG
	text.print(10, 150,
		"\
		sceneTime:%.2f\n\
		frameTime:%.2f\n\
		",
		sceneTimer, frameTime);
	text.print(10, 10, "acceleration(\t%.2f,\t%.2f,\t%.2f)",
		player[PLAYER1]->getAcceleration().x,
		player[PLAYER1]->getAcceleration().y,
		player[PLAYER1]->getAcceleration().z);
	text.print(10, 30, "gravity(\t%.2f,\t%.2f,\t%.2f)", 
		player[PLAYER1]->getGravity().x,
		player[PLAYER1]->getGravity().y,
		player[PLAYER1]->getGravity().z);
	text.print(10, 50, "quaternion(\t%.2f,\t%.2f,\t%.2f,\t%.2f)", 
		player[PLAYER1]->getQuaternion().x,
		player[PLAYER1]->getQuaternion().y,
		player[PLAYER1]->getQuaternion().z,
		player[PLAYER1]->getQuaternion().w);
	text.print(10, 70, "normal(\t%.2f,\t%.2f,\t%.2f)", 
		player[PLAYER1]->getReverseAxisY()->normal.x,
		player[PLAYER1]->getReverseAxisY()->normal.y,
		player[PLAYER1]->getReverseAxisY()->normal.z);
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
	text.print(10, 120, "position(%02.2f,%02.2f,%02.2f)", 
		player[PLAYER1]->getPosition()->x,
		player[PLAYER1]->getPosition()->y,
		player[PLAYER1]->getPosition()->z);

	text.print(WINDOW_WIDTH / 2, 10, 
		"magnetPosition(%.02f,%.02f,%.02f)\n\
		 magnetSpeed(%.02f,%.02f,%.02f)\n\
		",
		magnet[0].getPosition()->x,magnet[0].getPosition()->y,magnet[0].getPosition()->z,
		magnet[0].getSpeed().x,magnet[0].getSpeed().y,magnet[0].getSpeed().z
	);

	switch (input->getMouseWheelState())
	{
	case inputNS::MOUSE_WHEEL_STATE::NONE:	text.print(WINDOW_WIDTH / 2, 40, "mouseWheel:NONE");	break;
	case inputNS::MOUSE_WHEEL_STATE::UP:	text.print(WINDOW_WIDTH / 2, 40, "mouseWheel:UP");		break;
	case inputNS::MOUSE_WHEEL_STATE::DOWN:	text.print(WINDOW_WIDTH / 2, 40, "mouseWheel:DOWN");	break;
	}

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

	// ユーザインタフェース
		// 優先度：低
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			hpEffect[i].render(device);

			if (player[i]->whetherCollidedOpponentMemoryLine())
			{
				uiCutMemoryLine[i].render(device);
			}

			if (player[i]->getState() == playerNS::STATE::DOWN)
			{
				uiRevival[i].render(device);
			}
		}

		// 優先度：高
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			uiPlayTime[i].render(device, gameMaster->getGameTime());
			uiChingin[i].render(device, gameMaster->getGameTime(), player[i]->getWage(),i);
		}

	// 画面分割線
	uiScreenSplitLine.render(device);

	if (uiPause.getRenderFlag())
	{
		uiPause.render(device);
	}

#ifdef _DEBUG
	//極座標動作テスト用
	text.print(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 30, "polarPosition調整(radius:C[-]F[+],theta:V[-]G[+],phi:B[-]H[+])");
	text.print(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2+60, "polarPosition(radius:%02.2f,theta:%02.2f,phi:%02.2f)",
		polarPosition.radius,	polarPosition.theta,	polarPosition.phi);
	text.print(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2+90, "transPosition(x:%02.2f,y:%02.2f,z:%02.2f)",
		transPosition.x,transPosition.y,transPosition.z);
#endif // _DEBUG

	if (!gameMaster->whetherAlreadyStart())
	{
		//カウントダウン３…２…１…
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			uiCountDown[i].render(device, gameMaster->getCount());
		}
		if (gameMaster->getCountFlag())
		{
			// サウンドの再生
			sound->play(soundNS::TYPE::SE_COUNT, soundNS::METHOD::PLAY);
		}
	}
	else {
		//スタート
		if (gameMaster->displayStart())
		{
			for (int i = 0; i < NUM_PLAYER; i++)
			{
				uiCountDown[i].render(device, uiCountDownNS::TYPE::GO);
			}
			if (gameMaster->getStartFinishFlag())
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_GAME_START, soundNS::METHOD::PLAY);
				gameMaster->setStartFinishFlag(false);
			}
		}
	}

	if(gameMaster->whetherCountFinish()&&gameMaster->getCount()>0)
	{
		//カウントダウン３…２…１…
		for (int i = 0; i < NUM_PLAYER; i++)
		{
			uiCountDown[i].render(device, gameMaster->getCount());
		}
		if (gameMaster->getCountFlag())
		{
			// サウンドの再生
			sound->play(soundNS::TYPE::SE_COUNT, soundNS::METHOD::PLAY);
		}
	}
	if (gameMaster->whetherAlreadyFinish())
	{
		//フィニッシュ
		if (gameMaster->displayFinish())
		{
			for (int i = 0; i < NUM_PLAYER; i++)
			{
				uiCountDown[i].render(device, uiCountDownNS::TYPE::FINISH);
			}
			if (gameMaster->getStartFinishFlag())
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_GAME_TIME_UP, soundNS::METHOD::PLAY);
				gameMaster->setStartFinishFlag(false);
			}
		}
	}

	// αテストを無効に
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//===================================================================================================================================
//【衝突判定処理】
//===================================================================================================================================
void Game::collisions() {
	//1Pバレット<->プレイヤー2
	if (player[PLAYER2]->getState() == playerNS::STATE::GROUND)
	{
		for (int i = 0; i < playerNS::NUM_BULLET; i++)
		{
			if (!player[PLAYER1]->bullet[i].getActive())continue;
			if (player[PLAYER2]->bodyCollide.collide(
				player[PLAYER1]->bullet[i].bodyCollide.getCenter(),
				player[PLAYER1]->bullet[i].bodyCollide.getRadius(),
				*player[PLAYER2]->getMatrixWorld(),
				*player[PLAYER1]->bullet[i].getMatrixWorld()))
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_HIT, soundNS::METHOD::PLAY);
				player[PLAYER2]->damgae(12);
				hpEffect[PLAYER2].activate(20);
				player[PLAYER1]->bullet[i].inActivation();
			}
		}
	}

	//2Pバレット<->プレイヤー1
	if (player[PLAYER1]->getState() == playerNS::STATE::GROUND)
	{
		for (int i = 0; i < playerNS::NUM_BULLET; i++)
		{
			if (!player[PLAYER2]->bullet[i].getActive())continue;
			if (player[PLAYER1]->bodyCollide.collide(
				player[PLAYER2]->bullet[i].bodyCollide.getCenter(),
				player[PLAYER2]->bullet[i].bodyCollide.getRadius(),
				*player[PLAYER1]->getMatrixWorld(),
				*player[PLAYER2]->bullet[i].getMatrixWorld()))
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_HIT, soundNS::METHOD::PLAY);
				player[PLAYER1]->damgae(12);
				hpEffect[PLAYER1].activate(20);
				player[PLAYER2]->bullet[i].inActivation();

			}
		}
	}

	// 1P衝撃波<->プレイヤー2
	if (player[PLAYER2]->getState() == playerNS::STATE::GROUND)
	{
		if (player[PLAYER1]->collideShockWave(*player[PLAYER2]->getPosition(), player[PLAYER2]->getRadius()))
		{
			player[PLAYER2]->changeState(playerNS::STATE::DOWN);
		}
	}

	// 2P衝撃波<->プレイヤー1
	if (player[PLAYER1]->getState() == playerNS::STATE::GROUND)
	{
		if (player[PLAYER2]->collideShockWave(
			*player[PLAYER1]->getPosition(), player[PLAYER1]->getRadius()))
		{
			player[PLAYER1]->changeState(playerNS::STATE::DOWN);
		}
	}

	// リカージョン1<->ワスレモノ
	if (player[PLAYER1]->whetherGenerationRecursion()) {
		for (int i = 0; i < wasuremono.size(); i++)
		{
			if (!wasuremono[i]->getActive())	continue;
			if (player[PLAYER1]->getRecursion()->collide(
				*wasuremono[i]->getPosition(),
				wasuremono[i]->bodyCollide.getCenter(),
				wasuremono[i]->bodyCollide.getRadius(),
				*wasuremono[i]->getMatrixWorld()))
			{
				chinginManager.generateChingin(1, *wasuremono[i]->getPosition(), player[PLAYER1]);
				wasuremono[i]->startUpRecursion(player[PLAYER1]->getRecursion()->getWeightCenter(),*field.getPosition());
				//wasuremono[i]->inActivation();
			}
		}
	}
	// リカージョン2<->ワスレモノ
	if (player[PLAYER2]->whetherGenerationRecursion()) {
		for (int i = 0; i < wasuremono.size(); i++) 
		{
			if (!wasuremono[i]->getActive())	continue;
			if (player[PLAYER2]->getRecursion()->collide(
				*wasuremono[i]->getPosition(),
				wasuremono[i]->bodyCollide.getCenter(),
				wasuremono[i]->bodyCollide.getRadius(),
				*wasuremono[i]->getMatrixWorld()))
			{
				chinginManager.generateChingin(1, *wasuremono[i]->getPosition(), player[PLAYER2]);
				wasuremono[i]->startUpRecursion(player[PLAYER2]->getRecursion()->getWeightCenter(), *field.getPosition());
				//wasuremono[i]->inActivation();
			}
		}
	}


	for (int i = 0; i < wasuremono.size(); i++)
	{
		if (!wasuremono[i]->getActive())	continue;
		for (int j = 0; j < NUM_BULLET; j++)
		{
			// ワスレモノ<->バレット1
			if (wasuremono[i]->bodyCollide.collide(
				player[PLAYER1]->bullet[j].bodyCollide.getCenter(), player[PLAYER1]->bullet[j].bodyCollide.getRadius(),
				*wasuremono[i]->getMatrixWorld(), *player[PLAYER1]->bullet[j].getMatrixWorld()))
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_DESTRUCTION_WASUREMONO, soundNS::METHOD::PLAY);

				wasuremono[i]->inActivation();
				player[PLAYER1]->bullet[j].inActivation();
			}

			// ワスレモノ<->バレット2
			if (wasuremono[i]->bodyCollide.collide(
				player[PLAYER2]->bullet[j].bodyCollide.getCenter(), player[PLAYER2]->bullet[j].bodyCollide.getRadius(),
				*wasuremono[i]->getMatrixWorld(), *player[PLAYER2]->bullet[j].getMatrixWorld()))
			{
				// サウンドの再生
				sound->play(soundNS::TYPE::SE_DESTRUCTION_WASUREMONO, soundNS::METHOD::PLAY);
				wasuremono[i]->inActivation();
				player[PLAYER2]->bullet[j].inActivation();
			}
		}
	}



	//ガラクタとプレイヤー
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		for (int k = 0; k < JUNK_MAX; k++)
		{
			if (between2VectorLength(*player[i]->getPosition(), *junk[k].getPosition()) <= junkNS::HEAD_DISTANCE)
			{
				if (player[i]->bodyCollide.collide(junk[k].bodyCollide.getCenter(),junk[k].getRadius(),
					*player[i]->getMatrixWorld(),*junk[k].getMatrixWorld()))
				{//プレイヤーとガラクタが衝突したら
					junk[k].inActivation();
				}
				junk[k].headPosition(*player[i]->getPosition());
			}
		}
	}


	//1Pのメモリーライン<->2Pプレイヤーの衝突検知
	if (player[PLAYER1]->getMemoryLine()->collision(*player[PLAYER2]->getPosition(), player[PLAYER2]->bodyCollide.getRadius()))
	{
		player[PLAYER2]->setCollidedMemoryLine(true);
		//衝突位置を2Pに保存（エフェクト用）
		player[PLAYER2]->setCollideMemoryLinePosition(player[PLAYER1]->getMemoryLine()->calculationNearPoint(*player[PLAYER2]->getPosition()));
		if (player[PLAYER2]->messageDisconnectOpponentMemoryLine())
		{
			// ラインエフェクト発生
			lineEffect.generateLineEffect(200, player[PLAYER2]->collideMemoryLinePosition, player[PLAYER2]->upVec());

			//1Pのメモリーラインの切断処理
			player[PLAYER1]->disconnectMemoryLine();

		}
	}else{
		player[PLAYER2]->setCollidedMemoryLine(false);
	}
	//2Pのメモリーライン<->1Pプレイヤーの衝突検知
	if (player[PLAYER2]->getMemoryLine()->collision(*player[PLAYER1]->getPosition(), player[PLAYER1]->bodyCollide.getRadius()))
	{
		player[PLAYER1]->setCollidedMemoryLine(true);
		//衝突位置を1Pに保存（エフェクト用）
		player[PLAYER1]->setCollideMemoryLinePosition(
			player[PLAYER2]->getMemoryLine()->calculationNearPoint(*player[PLAYER1]->getPosition()));
		if (player[PLAYER1]->messageDisconnectOpponentMemoryLine())
		{
			// ラインエフェクト発生
			lineEffect.generateLineEffect(200, player[PLAYER1]->collideMemoryLinePosition, player[PLAYER1]->upVec());

			//2Pのメモリーラインの切断処理
			player[PLAYER2]->disconnectMemoryLine();
		}
	}else{
		player[PLAYER1]->setCollidedMemoryLine(false);
	}

	//1Pのリカージョン<->2Pプレイヤーの衝突検知
	if (player[PLAYER1]->whetherGenerationRecursion())
	{
		if(player[PLAYER1]->getRecursion()->collide(
				*player[PLAYER2]->getPosition(),
				player[PLAYER2]->bodyCollide.getCenter(),
				player[PLAYER2]->bodyCollide.getRadius(),
				*player[PLAYER2]->getMatrixWorld()))
		{
			player[PLAYER2]->changeState(playerNS::SKY);
		}
	}
	//2Pのリカージョン<->1Pプレイヤーの衝突検知
	if (player[PLAYER2]->whetherGenerationRecursion())
	{
		if(player[PLAYER2]->getRecursion()->collide(
				*player[PLAYER1]->getPosition(),
				player[PLAYER1]->bodyCollide.getCenter(),
				player[PLAYER1]->bodyCollide.getRadius(),
				*player[PLAYER1]->getMatrixWorld()))
		{
			player[PLAYER1]->changeState(playerNS::SKY);
		}
	}
}

//===================================================================================================================================
//【AI処理】
//===================================================================================================================================
void Game::AI() {
#ifdef USING_AI

#endif// USING_AI
}

//===================================================================================================================================
//【終了処理】
//===================================================================================================================================
void Game::uninitialize() {
	SAFE_DELETE(light);
	SAFE_DELETE_ARRAY(camera);
	//SAFE_DELETE(lambert);
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		hpEffect[i].uninitialize();
		target.uninitialize();
		uiPause.release();
		uiPlayTime[i].release();
		uiChingin[i].release();
		uiCutMemoryLine[i].release();
		uiRevival[i].release();
		//player[i]->animationPlayer.release();
	}
	uiScreenSplitLine.release();
	wasuremonoManager.uninitialize();
	map.uninitialize();
	SAFE_DELETE(player[0])
	SAFE_DELETE(player[1])
	chinginManager.uninitialize();
}