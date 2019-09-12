//=============================================================================
// オペレーション処理 [Operation.cpp]
// 制作者 飯塚春輝
////===========================================================================
#include "Operation.h"
// オペレーション名前空間有効
using namespace operationNS;
//=============================================================================
// コンストラクタ
//=============================================================================
Operation::Operation()
{
	// 現在のシーン(オペレーション)
	sceneName = "Scene -Operation-";
	// 次のシーン(タイトル)
	nextScene = SceneList::TITLE;
}
//=============================================================================
// デストラクタ
//=============================================================================
Operation::~Operation()
{
	// サウンドの停止
	sound->stop(soundNS::TYPE::BGM_OPERATION);
}
//=============================================================================
// 初期化処理
//=============================================================================
void Operation::initialize(
	Direct3D9* direct3D9,
	Input* _input,
	Sound* _sound,
	TextureLoader* _textureLoader,
	StaticMeshLoader* _staticMeshLoader,
	ShaderLoader* _shaderLoader, 
	TextManager* _textManager)
{
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

	// サウンドの再生
	sound->play(soundNS::TYPE::BGM_OPERATION, soundNS::METHOD::PLAY);

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
	light->initialize(direct3D9);

	// キーボード説明初期化
	keyOpe.initialize(direct3D9->device, 0, _textureLoader);

	// パッド説明初期化
	padOpe.initialize(direct3D9->device, 0, _textureLoader);

	opeTransition = NULL; // オペレーション画像入れ替え

	// シーンエフェクト初期化
	sceneEffect.initialize(direct3D9->device, textureLoader, *shaderLoader->getEffect(shaderNS::INSTANCE_BILLBOARD));

}

void Operation::update(float frameTime)
{
	// カメラ更新
	camera->update();

	// 前の遷移へ戻る
	if (input->wasKeyPressed(VK_BACK) ||
		input->getController()[PLAYER_TYPE::PLAYER_1]->wasButton(virtualControllerNS::B) ||
		input->getController()[PLAYER_TYPE::PLAYER_2]->wasButton(virtualControllerNS::B))
	{
		// サウンドの再生
		sound->play(soundNS::TYPE::SE_CANCEL, soundNS::METHOD::PLAY);
		nextScene = SceneList::TITLE;
		changeScene(nextScene);
		return;
	}

	// キーを押したら選択UI移動
	if (input->wasKeyPressed(VK_RIGHT) ||
		input->getController()[PLAYER_TYPE::PLAYER_1]->wasButton(virtualControllerNS::RIGHT) ||
		input->getController()[PLAYER_TYPE::PLAYER_2]->wasButton(virtualControllerNS::RIGHT))
	{
		if (opeTransition < 1)
		{
			// サウンドの再生
			sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
			opeTransition++;
		}
	}
	else if (input->wasKeyPressed(VK_LEFT) ||
		input->getController()[PLAYER_TYPE::PLAYER_1]->wasButton(virtualControllerNS::LEFT) ||
		input->getController()[PLAYER_TYPE::PLAYER_2]->wasButton(virtualControllerNS::LEFT))
	{
		if (opeTransition > 0)
		{
			// サウンドの再生
			sound->play(soundNS::TYPE::SE_SELECT, soundNS::METHOD::PLAY);
			opeTransition--;
		}
	}

	// 選択UI下限
	if (opeTransition > OPE_MAX)
	{
		opeTransition = 0;
	}
	// 選択UI上限
	else if (opeTransition < 0)
	{
		opeTransition = OPE_MAX;
	}

	// シーンエフェクトの更新
	sceneEffect.update(frameTime);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		// シーンエフェクト発生
		sceneEffect.generateSceneEffect(1, D3DXVECTOR3((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50)));
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void Operation::render(Direct3D9* direct3D9)
{
	//1Pカメラ・ウィンドウ
	direct3D9->device->SetTransform(D3DTS_VIEW, &camera[PLAYER_TYPE::PLAYER_1].view);
	direct3D9->device->SetTransform(D3DTS_PROJECTION, &camera[PLAYER_TYPE::PLAYER_1].projection);
	direct3D9->changeViewportFullWindow();
	render3D(direct3D9 , camera[PLAYER_TYPE::PLAYER_1]);

	// αブレンドをつかう
	direct3D9->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// αソースカラーの指定
	direct3D9->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// αデスティネーションカラーの指定
	direct3D9->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//UI
	renderUI(direct3D9->device);
}
//=============================================================================
// 3D描画処理
//=============================================================================
void Operation::render3D(Direct3D9* direct3D9, Camera _currentCamera)
{
	// シーンエフェクトの描画
	sceneEffect.render(direct3D9->device, _currentCamera.view, _currentCamera.projection, _currentCamera.position);

}
//=============================================================================
// 2D描画処理
//=============================================================================
void Operation::renderUI(LPDIRECT3DDEVICE9 device)
{
	switch (opeTransition)
	{
		// パッド説明
	case 0:

		padOpe.render(device);
		keyOpe.render(device);

		break;
		// キーボード説明
	case 1:

		keyOpe.render(device);
		padOpe.render(device);

		break;
	}
}
//=============================================================================
// コリジョン処理
//=============================================================================
void Operation::collisions()
{
}
//=============================================================================
// AI処理
//=============================================================================
void Operation::AI()
{
}
//=============================================================================
// 終了処理
//=============================================================================
void Operation::uninitialize()
{
	// カメラ
	SAFE_DELETE_ARRAY(camera);

	// ライト
	SAFE_DELETE(light);

}
