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

void Title::initialize(Direct3D9* direct3D9,Input* _input) {
	//Input
	input = _input;
	//camera
	camera = new Camera;
	camera->initialize(WINDOW_WIDTH/2, WINDOW_HEIGHT);
	camera->setGaze(D3DXVECTOR3(0, 0, 0));
	camera->setPosition(D3DXVECTOR3(0, 0, -1));
	camera->setUpVector(D3DXVECTOR3(0, 1, 0));

	titleTrans.initialize(direct3D9->device, 0);
	titleTransPos.initialize(direct3D9->device, 0);
}

void Title::update() {

	camera->update();

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
}

void Title::render(Direct3D9* direct3D9) {
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera->view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera->projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9);
	//UI
	renderUI(direct3D9->device);
}

void Title::render3D(Direct3D9* direct3D9) {

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
		// ゲーム開始
	case 0:

		nextScene = SceneList::SELECT_CHARACTER;
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