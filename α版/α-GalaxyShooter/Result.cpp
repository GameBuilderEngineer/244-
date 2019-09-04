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
	// 今のシーン( キャラクターセレクト )
	sceneName = ("Scene -Result-");

	// 次のシーン( ゲーム )
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
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	// リザルトUIの初期化
	uiResult.initialize(_direct3D9->device, _textureLoader, _textManager, gameMaster);

	return;
}
//============================================================================================================================================
// uninitialize
// 解放
//============================================================================================================================================
void Result::uninitialize(void)
{
	uiResult.release();

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

	return;
}
//============================================================================================================================================
// render
// 描画
//============================================================================================================================================
void Result::render(Direct3D9* _direct3D9)
{
	// カメラ・ウィンドウ
	_direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	_direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	_direct3D9->changeViewportFullWindow();

	// リザルトUI
	uiResult.render(_direct3D9->device);

	return;
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