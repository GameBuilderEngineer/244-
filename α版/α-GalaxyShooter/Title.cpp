#include "Title.h"
using namespace titleNS;

static int titletransition = 0;	//選択位置記憶変数

Title::Title()
{
	sceneName = "Scene -Title-";
}

Title::~Title()
{

}

void Title::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader,
	TextManager* _textManager) {
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

	titleTrans.initialize(direct3D9->device, 0, _textureLoader);
	titleTransPos.initialize(direct3D9->device, 0, _textureLoader);


	titlePlayer[0].initialize(playerNS::TITLE_PLAYER,direct3D9->device,staticMeshLoader,textureLoader,shaderLoader);
	titlePlayer[0].setPosition(D3DXVECTOR3(-20, 100, 25));


}

void Title::update(float frameTime) {

	// キーを押したら選択UI移動
	if (input->wasKeyPressed(VK_DOWN)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::DOWN) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::DOWN)
		)
	{
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
		titletransition++;
	}
	else if (input->wasKeyPressed(VK_UP)||
		input->getController()[PLAYER1]->wasButton(virtualControllerNS::UP) ||
		input->getController()[PLAYER2]->wasButton(virtualControllerNS::UP)
		)
	{
		sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
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
	titleTrans.cntTitle = titletransition;
	titleTransPos.cntTitle = titletransition;

	// 選択UI遷移処理
	titleTransition();

	titleTrans.update();
	titleTransPos.update();


	// カメラアップデート
	camera[0].setUpVector(titlePlayer[0].getAxisY()->direction);
	camera[0].update();

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

	titlePlayer[0].toonRender(direct3D9->device, currentCamera.view, currentCamera.projection, currentCamera.position,
		*shaderLoader->getEffect(shaderNS::TOON),
		*textureLoader->getTexture(textureLoaderNS::TOON_SHADE),
		*textureLoader->getTexture(textureLoaderNS::TOON_OUT_LINE));
}

void Title::renderUI(LPDIRECT3DDEVICE9 device) {

	titleTransPos.render(device);
	titleTrans.render(device);
}

void Title::collisions() {

}

void Title::AI(){

}

void Title::uninitialize() {

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
	switch (titletransition)
	{
		// セレクト
	case 0:

		nextScene = SceneList::SELECT;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)changeScene(nextScene);
		break;

		// チュートリアル
	case 1:

		nextScene = SceneList::TUTORIAL;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// 操作方法
	case 2:

		nextScene = SceneList::OPERATION;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// クレジット
	case 3:

		nextScene = SceneList::CREDIT;
		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			) 
		{
			sound->play(soundNS::TYPE::SE_DECISION, soundNS::METHOD::PLAY);
			changeScene(nextScene);
		}
		break;

		// ゲーム終了
	case 4:

		if (input->wasKeyPressed(VK_RETURN)||
			input->getController()[PLAYER1]->wasButton(virtualControllerNS::A) ||
			input->getController()[PLAYER2]->wasButton(virtualControllerNS::A)
			)PostQuitMessage(0);
		break;
	}
}
