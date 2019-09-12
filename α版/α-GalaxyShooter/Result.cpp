//============================================================================================================================================
// Document
//============================================================================================================================================
// Result.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/28
//============================================================================================================================================
#include "Result.h"
//============================================================================================================================================
// Using Declaration
// using宣言
//============================================================================================================================================
using namespace resultNS;
//============================================================================================================================================
// Constructor
// コンストラクタ
//============================================================================================================================================
Result::Result(void)
{
	// 今のシーン( リザルト )
	sceneName = ("Scene -Result-");

	// 次のシーン( タイトル )
	nextScene = SceneList::TITLE;

	return;
}
//============================================================================================================================================
// Destructor
// デストラクタ
//============================================================================================================================================
Result::~Result(void)
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_RESULT);

	return;
}
//============================================================================================================================================
// initialize
// 初期化
//============================================================================================================================================
void Result::initialize(Direct3D9* _direct3D9, Input* _input, Sound* _sound, TextureLoader* _textureLoader, StaticMeshLoader* _staticMeshLoader, ShaderLoader* _shaderLoader, TextManager* _textManager)
{
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
	// テキストマネージャ
	textManager = _textManager;

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_RESULT, soundNS::METHOD::LOOP);

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

	// リザルトUIの初期化
	uiResult.initialize(_direct3D9->device, _textureLoader, _textManager, gameMaster);

	// シーンエフェクト初期化
	sceneEffect.initialize(_direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

	return;
}
//============================================================================================================================================
// uninitialize
// 解放
//============================================================================================================================================
void Result::uninitialize(void)
{
	uiResult.release();

	// カメラ
	SAFE_DELETE_ARRAY(camera);

	// ライト
	SAFE_DELETE(light);

	return;
}
//============================================================================================================================================
// update
// 更新
//============================================================================================================================================
void Result::update(float _frameTime)
{
	// カメラ更新
	camera->update();

	// Enterまたは〇ボタンでタイトルへ
	if (input->wasKeyPressed(VK_RETURN) ||
		input->getController()[inputNS::DINPUT_1P]->wasButton(virtualControllerNS::A) ||
		input->getController()[inputNS::DINPUT_2P]->wasButton(virtualControllerNS::A))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
		// 遷移
		changeScene(nextScene);
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
// render
// 描画
//============================================================================================================================================
void Result::render(Direct3D9* _direct3D9)
{
	//1Pカメラ・ウィンドウ
	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_1].view);
	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_1].projection);
	_direct3D9->changeViewportFullWindow();

	render3D(_direct3D9, camera[PLAYER_TYPE::PLAYER_1]);

	// αブレンドをつかう
	_direct3D9->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// αソースカラーの指定
	_direct3D9->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	_direct3D9->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//UI
	renderUI(_direct3D9->device);

	return;
}
//=============================================================================
// 3D描画処理
//=============================================================================
void Result::render3D(Direct3D9* direct3D9, Camera _currentCamera)
{
	// シーンエフェクトの描画
	sceneEffect.render(direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

}
//=============================================================================
// 2D描画処理
//=============================================================================
void Result::renderUI(LPDIRECT3DDEVICE9 device)
{
	// リザルトUI
	uiResult.render(device);
}

//============================================================================================================================================
// None
//============================================================================================================================================
void Result::collisions(void)
{
	// None
	return;
}
void Result::AI(void)
{
	// None
	return;
}