//============================================================================================================================================
// Document
//============================================================================================================================================
// Title.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/29
//============================================================================================================================================
#include "Title.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace titleNS;
//============================================================================================================================================
// Global Variable
// グローバル変数
//============================================================================================================================================
int selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_START;	//	タイトルメニュー選択状態記憶
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
Title::Title(void)
{
	// 今のシーン( タイトル )
	sceneName = ("Scene -Title-");
	
	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
Title::~Title(void)
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_TITLE);

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
void Title::initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager)
{
	// Direct3D9
	direct3D9 = _direct3D9;
	// Input
	input = _input;
	// Sound
	sound = _sound;
	// TextureLoader
	textureLoader = _textureLoader;
	// StaticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	// ShaderLoader
	shaderLoader = _shaderLoader;

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_TITLE, soundNS::METHOD::LOOP);

	//// Player
	//player[PLAYER_TYPE::PLAYER_1] = new Player;
	//player[PLAYER_TYPE::PLAYER_2] = new Player;

	// Camera
	camera = new Camera[PLAYER_TYPE::PLAYER_TYPE_MAX];

	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		//camera[i].setTarget(player[i].getPosition());
		//camera[i].setTargetX(&player[i].getAxisX()->direction);
		//camera[i].setTargetY(&player[i].getAxisY()->direction);
		//camera[i].setTargetZ(&player[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
		camera[i].setFieldOfView(D3DX_PI / 2.5);
	}

	// Light
	light = new Light;
	light->initialize(_direct3D9);

	// プレイヤーの初期化
	//player[PLAYER_TYPE::PLAYER_1].initialize(playerNS::PLAYER_TYPE::PLAYER1, gameMaster->getPlayerInfomation()[PLAYER_TYPE::PLAYER_1].modelType, _direct3D9->device, staticMeshLoader, textureLoader, shaderLoader);
	//player[PLAYER_TYPE::PLAYER_1].setPosition(PLAYER_POSITION[playerNS::PLAYER_TYPE::PLAYER1]);
	//player[PLAYER_TYPE::PLAYER_1].animationPlayer.setAnimationConfiguration(animationPlayerNS::SCENE_TYPE::TITLE);

	// タイトルUIの初期化
	uiTitle.initialize(_direct3D9->device, _textureLoader, selectStateMemory);

	// インスタンスプレーンの初期化
	plane.createPositionSpherical(_direct3D9->device, 3000, 250.0f);
	plane.initialize(_direct3D9->device, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::BACKGROUND_DUST));

	// シーンエフェクト初期化
	sceneEffect.initialize(_direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	return;
}
//============================================================================================================================================
// uninitialize
// 解放
//============================================================================================================================================
void Title::uninitialize(void)
{
	// プレイヤー
	//player[PLAYER_TYPE::PLAYER_1].animationPlayer.release();

	// ライト
	SAFE_DELETE(light);

	// カメラ
	SAFE_DELETE_ARRAY(camera);

	// タイトルUI
	uiTitle.release();

	return;
}
//============================================================================================================================================
// update
// 更新
//============================================================================================================================================
void Title::update(float _frameTime)
{
	// カメラ
	//camera[0].setUpVector(player[PLAYER_TYPE::PLAYER_1].getAxisY()->direction);
	camera[0].update();

	//player[PLAYER_TYPE::PLAYER_1].animationPlayer.updateTitle();

	// タイトルUI
	uiTitle.update(input, sound);

	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
		updateInput();
	}

	// シーンエフェクトの更新
	sceneEffect.update(_frameTime);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		// シーンエフェクト発生
		sceneEffect.generateSceneEffect(1, D3DXVECTOR3((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50)));
	}
	return;
}
//============================================================================================================================================
// updateInput
// 更新 - 入力
//============================================================================================================================================
void Title::updateInput(void)
{
	switch (uiTitle.getSelectState())
	{
	case uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_START:
		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_START;
		nextScene = (SceneList::SELECT);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_TUTORIAL:
		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_TUTORIAL;
		nextScene = (SceneList::TUTORIAL);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_OPERATION:
		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_OPERATION;
		nextScene = (SceneList::OPERATION);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_CREDIT:
		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_CREDIT;
		nextScene = (SceneList::CREDIT);
		changeScene(nextScene);
		break;
	case uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_EXIT:
		PostQuitMessage(NULL);
		break;
	default:
		break;
	}

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void Title::render(Direct3D9* _direct3D9)
{
	// カメラ・ウィンドウ
	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_1].view);
	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_1].projection);
	_direct3D9->changeViewportFullWindow();

	// 3D
	render3D(_direct3D9, camera[PLAYER_TYPE::PLAYER_1]);

	// αブレンドをつかう
	_direct3D9->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// αソースカラーの指定
	_direct3D9->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	_direct3D9->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 2D
	render2D(_direct3D9->device);

	return;
}
//============================================================================================================================================
// render3D
// 描画 - 3D
//============================================================================================================================================
void Title::render3D(Direct3D9* _direct3D9, Camera _currentCamera)
{
	// シーンエフェクトの描画
	sceneEffect.render(_direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

	//// プレーン( インスタンシング )
	//plane.render(_direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

	// タイトルプレイヤー描画
	//player[0].toonRender
	//(
	//	_direct3D9->device,
	//	_currentCamera.view,
	//	_currentCamera.projection,
	//	_currentCamera.position,
	//	*shaderLoader->getEffect(shaderNS::TOON),
	//	*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
	//	*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
}

	return;
}
//============================================================================================================================================
// render2D
// 描画 - 2D
//============================================================================================================================================
void Title::render2D(LPDIRECT3DDEVICE9 _device)
{
	// タイトルUI
	uiTitle.render(_device);

	return;
}
//============================================================================================================================================
// None
//============================================================================================================================================
void Title::collisions(void)
{
	// None
}
void Title::AI(void)
{
	// None
}

////============================================================================================================================================
//// Document
////============================================================================================================================================
//// Title.cpp
//// HAL東京 GP-12A-332 09 亀岡竣介
//// 2019/08/29
////============================================================================================================================================
//#include "Title.h"
////============================================================================================================================================
//// Using Declaration
//// using宣言
////============================================================================================================================================
//using namespace titleNS;
////============================================================================================================================================
//// Global Variable
//// グローバル変数
////============================================================================================================================================
//int selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_START;	//	タイトルメニュー選択状態記憶
////============================================================================================================================================
//// Constructor
//// コンストラクタ
////============================================================================================================================================
//Title::Title(void)
//{
//	// 今のシーン( タイトル )
//	sceneName = ("Scene -Title-");
//
//	return;
//}
////============================================================================================================================================
//// Destructor
//// デストラクタ
////============================================================================================================================================
//Title::~Title(void)
//{
//	// サウンドの停止
//	sound->stop(soundNS::TYPE::BGM_TITLE);
//
//	uninitialize();
//
//	return;
//}
////============================================================================================================================================
//// initialize
//// 初期化
////============================================================================================================================================
//void Title::initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager)
//{
//	// Direct3D9
//	direct3D9 = _direct3D9;
//	// Input
//	input = _input;
//	// Sound
//	sound = _sound;
//	// TextureLoader
//	textureLoader = _textureLoader;
//	// StaticMeshLoader
//	staticMeshLoader = _staticMeshLoader;
//	// ShaderLoader
//	shaderLoader = _shaderLoader;
//
//	// サウンドの再生
//	sound->play(soundNS::TYPE::BGM_TITLE, soundNS::METHOD::LOOP);
//
//	// プレイヤー
//	player[PLAYER_TYPE::PLAYER_1] = new Player;
//	player[PLAYER_TYPE::PLAYER_2] = new Player;
//
//	// Camera
//	camera = new Camera[PLAYER_TYPE::PLAYER_TYPE_MAX];
//
//	//for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
//	//{
//	//	camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
//	//	camera[i].setTarget(player[i]->getPosition());
//	//	camera[i].setTargetX(&player[i]->getAxisX()->direction);
//	//	camera[i].setTargetY(&player[i]->getAxisY()->direction);
//	//	camera[i].setTargetZ(&player[i]->getAxisZ()->direction);
//	//	camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
//	//	camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
//	//	camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
//	//	camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
//	//	camera[i].setFieldOfView(D3DX_PI / 2.5);
//	//}
//	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
//	{
//		camera[i].initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
//		camera[i].setTarget(player[i]->getPosition());
//		camera[i].setTargetX(&player[i]->getAxisX()->direction);
//		camera[i].setTargetY(&player[i]->getAxisY()->direction);
//		camera[i].setTargetZ(&player[i]->getAxisZ()->direction);
//		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[i]);
//		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
//		camera[i].setRelativeGaze(D3DXVECTOR3(0, 10, 0));
//		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
//		camera[i].setFieldOfView(D3DX_PI / 2.5);
//	}
//
//	// Light
//	light = new Light;
//	light->initialize(_direct3D9);
//
//	// プレイヤー
//	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
//	{
//		if (i == 0)
//		{
//			player[i]->initialize(i, gameMasterNS::MODEL_TYPE::EVE, direct3D9->device, staticMeshLoader, textureLoader, shaderLoader);
//		}
//		else
//		{
//			player[i]->initialize(i, gameMasterNS::MODEL_TYPE::ADAM, direct3D9->device, staticMeshLoader, textureLoader, shaderLoader);
//		}
//		player[i]->setInput(input);
//		player[i]->setCamera(&camera[i]);
//		player[i]->setSound(sound);
//		player[i]->setPosition(PLAYER_POSITION[i]);
//		player[i]->animationPlayer.setAnimationConfiguration(animationPlayerNS::SCENE_TYPE::TITLE);
//	}
//
//	// タイトルUIの初期化
//	uiTitle.initialize(_direct3D9->device, _textureLoader, selectStateMemory);
//
//	// インスタンスプレーンの初期化
//	plane.createPositionSpherical(_direct3D9->device, 3000, 250.0f);
//	plane.initialize(_direct3D9->device, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD), *textureLoader->getTexture(textureLoaderNS::BACKGROUND_DUST));
//
//	return;
//}
////============================================================================================================================================
//// uninitialize
//// 解放
////============================================================================================================================================
//void Title::uninitialize(void)
//{
//	// ライト
//	SAFE_DELETE(light);
//
//	// カメラ
//	SAFE_DELETE_ARRAY(camera);
//
//	// プレイヤー
//	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
//	{
//		player[i]->animationPlayer.release();
//		SAFE_DELETE(player[i]);
//	}
//
//	// タイトルUI
//	uiTitle.release();
//
//	return;
//}
////============================================================================================================================================
//// update
//// 更新
////============================================================================================================================================
//void Title::update(float _frameTime)
//{
//	// カメラ
//	camera[0].setUpVector(player[PLAYER_TYPE::PLAYER_1]->getAxisY()->direction);
//	camera[0].update();
//
//	// プレイヤー
//	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
//	{
//		player[i]->animationPlayer.updateTitle();
//	}
//
//	// タイトルUI
//	uiTitle.update(input, sound);
//
//	if (input->wasKeyPressed(VK_RETURN) ||
//		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
//		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
//	{
//		// サウンドの再生
//		sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
//		updateInput();
//	}
//
//	return;
//}
////============================================================================================================================================
//// updateInput
//// 更新 - 入力
////============================================================================================================================================
//void Title::updateInput(void)
//{
//	switch (uiTitle.getSelectState())
//	{
//	case uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_START:
//		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_START;
//		nextScene = (SceneList::SELECT);
//		changeScene(nextScene);
//		break;
//	case uiTitleNS::TITLE_MENU_TYPE::MENU_TUTORIAL:
//		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_TUTORIAL;
//		nextScene = (SceneList::TUTORIAL);
//		changeScene(nextScene);
//		break;
//	case uiTitleNS::TITLE_MENU_TYPE::MENU_OPERATION:
//		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_OPERATION;
//		nextScene = (SceneList::OPERATION);
//		changeScene(nextScene);
//		break;
//	case uiTitleNS::TITLE_MENU_TYPE::MENU_CREDIT:
//		selectStateMemory = uiTitleNS::TITLE_MENU_TYPE::MENU_CREDIT;
//		nextScene = (SceneList::CREDIT);
//		changeScene(nextScene);
//		break;
//	case uiTitleNS::TITLE_MENU_TYPE::MENU_GAME_EXIT:
//		PostQuitMessage(NULL);
//		break;
//	default:
//		break;
//	}
//
//	return;
//}
////============================================================================================================================================
//// render
//// 描画
////============================================================================================================================================
//void Title::render(Direct3D9* _direct3D9)
//{
//	// 1Pカメラ・ウィンドウ
//	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_1].view);
//	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_1].projection);
//	_direct3D9->changeViewportFullWindow();
//	render3D(_direct3D9, camera[PLAYER_TYPE::PLAYER_1]);
//
//	// 2Pカメラ・ウィンドウ
//	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_2].view);
//	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_2].projection);
//	_direct3D9->changeViewportFullWindow();
//	render3D(_direct3D9, camera[PLAYER_TYPE::PLAYER_2]);
//
//
//
//	//// カメラ・ウィンドウ
//	//_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
//	//_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
//	//_direct3D9->changeViewportFullWindow();
//
//	//// 3D
//	//render3D(_direct3D9, camera[0]);
//
//	// 2D
//	render2D(_direct3D9->device);
//
//	return;
//}
////============================================================================================================================================
//// render3D
//// 描画 - 3D
////============================================================================================================================================
//void Title::render3D(Direct3D9* _direct3D9, Camera _currentCamera)
//{
//	// プレーン( インスタンシング )
//	plane.render(_direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);
//
//	// タイトルプレイヤー描画
//	for (int i = 0; i < PLAYER_TYPE::PLAYER_TYPE_MAX; i++)
//	{
//		player[i]->toonRender
//		(
//			_direct3D9->device,
//			_currentCamera.view,
//			_currentCamera.projection,
//			_currentCamera.position,
//			*shaderLoader->getEffect(shaderNS::TOON),
//			*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
//			*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE)
//		);
//	}
//
//	return;
//}
////============================================================================================================================================
//// render2D
//// 描画 - 2D
////============================================================================================================================================
//void Title::render2D(LPDIRECT3DDEVICE9 _device)
//{
//	// タイトルUI
//	uiTitle.render(_device);
//
//	return;
//}
////============================================================================================================================================
//// None
////============================================================================================================================================
//void Title::collisions(void)
//{
//	// None
//}
//void Title::AI(void)
//{
//	// None
//}