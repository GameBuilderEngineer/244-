#include "Title.h"
using namespace titleNS;

static int titletransition = 0;	//選択位置記憶変数

Title::Title()
{
	sceneName = "Scene -Title-";
}

Title::~Title()
{
	//BGMの停止
	audio->stopCue(audioCue::TITLE_BGM);
}

void Title::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Audio* _audio,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader) {
	//Input
	input = _input;
	//audio
	audio = _audio;
	//textureLoader
	textureLoader = _textureLoader;
	//staticMeshLoader
	staticMeshLoader = _staticMeshLoader;
	//shaderLoader
	shaderLoader = _shaderLoader;
	//camera
	camera = new Camera[NUM_PLAYER];
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		camera[i].initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
		camera[i].setTarget(titlePlayer[i].getPosition());
		camera[i].setTargetX(&titlePlayer[i].getAxisX()->direction);
		camera[i].setTargetY(&titlePlayer[i].getAxisY()->direction);
		camera[i].setTargetZ(&titlePlayer[i].getAxisZ()->direction);
		camera[i].setRelative(CAMERA_RELATIVE_QUATERNION[0]);
		camera[i].setGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setRelativeGaze(D3DXVECTOR3(0, 0, 0));
		camera[i].setUpVector(D3DXVECTOR3(0, 1, 0));
	}

	//light
	light = new Light;
	light->initialize(direct3D9);

	backGround.initialize(
		direct3D9->device, 
		*textureLoader->getTexture(textureLoaderNS::WHITE_TEXTURE),
		spriteNS::TOP_LEFT,								// 原点
		WINDOW_WIDTH,											// 横幅
		WINDOW_HEIGHT,											// 高さ
		D3DXVECTOR3(0, 0, 0),		// 座標
		D3DXVECTOR3(0, 0, 0),					// 回転
		TITLE_TRANSPOS_COLOR							// 色
	);
	titleTrans.initialize(direct3D9->device, 0, _textureLoader);
	titleTransPos.initialize(direct3D9->device, 0, _textureLoader);

	//BGMの再生
	audio->playCue(audioCue::TITLE_BGM);

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		titlePlayer[i].initialize(direct3D9->device, &staticMeshLoader->staticMesh[staticMeshNS::SAMPLE_TOON_MESH], &(D3DXVECTOR3)titleNS::PLAYER_POSITION[i]);
		titlePlayer[i].setPosition(D3DXVECTOR3(-15, 100, 15));
	}
}

void Title::update(float frameTime) {

	// キーを押したら選択UI移動
	if (input->wasKeyPressed(VK_DOWN))
	{
		titletransition++;
	}
	else if (input->wasKeyPressed(VK_UP))
	{
		titletransition--;
	}

	// 選択UI限界
	if (titletransition > CNT_TITLE_MAX)
	{
		titletransition = 0;
	}
	// 選択UI上限
	else if (titletransition < 0)
	{
		titletransition = CNT_TITLE_MAX;
	}

	// 位置記憶
	titleTransPos.cntTitle = titletransition;

	// 選択UI遷移処理
	titleTransition();

	titleTrans.update();
	titleTransPos.update();


	for (int i = 0; i < NUM_PLAYER; i++)
	{
		// カメラアップデート
		camera[i].setUpVector(titlePlayer[i].getAxisY()->direction);
		camera[i].update();
	}

}

void Title::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[0].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[0].projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9, camera[0]);
	//UI
	renderUI(direct3D9->device);
}

void Title::render3D(Direct3D9* direct3D9, Camera currentCamera) {
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		titlePlayer[i].toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
			*shaderLoader->getEffect(shaderNS::TOON),
			*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
			*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
	}
}

void Title::renderUI(LPDIRECT3DDEVICE9 device) {

	backGround.render(device);
	titleTransPos.render(device);
	titleTrans.render(device);
}

void Title::collisions() {

}

void Title::AI(){

}

void Title::uninitialize() {
	backGround.uninitialize();

	SAFE_DELETE(light);
	SAFE_DELETE_ARRAY(camera);

	titleTrans.uninitialize();
	titleTransPos.uninitialize();
}

//=============================================================================
// 選択UI遷移処理
//=============================================================================
void Title::titleTransition(void)
{
	switch (titleTransPos.cntTitle)
	{
		// セレクト
	case 0:

		nextScene = SceneList::SELECT;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// チュートリアル
	case 1:

		nextScene = SceneList::TUTORIAL;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// 操作方法
	case 2:

		nextScene = SceneList::OPERATION;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// クレジット
	case 3:

		nextScene = SceneList::CREDIT;
		if (input->wasKeyPressed(VK_RETURN))changeScene(nextScene);
		break;

		// ゲーム終了
	case 4:

		if (input->wasKeyPressed(VK_RETURN))PostQuitMessage(0);
		break;
	}
}
