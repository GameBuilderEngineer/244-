#pragma once
#include "Base.h"
#include "Window.h"
#include "Direct3D9.h"
#include "Input.h"
#include "Camera.h"
#include "Sound.h"
#include "AbstractScene.h"
#include "VirtualController.h"
#include "Audio.h"
//管理クラス
class Director : public Celement
{
public:
	//Data
	HINSTANCE instance;				//
	Window* window;					//ウィンドウクラス・ハンドル
	HWND wnd;						//ウィンドウハンドル
	Direct3D9* d3d;					//DirectX9クラス・デバイス
	Input* input;					//Inputクラス
	Camera* camera;					//カメラクラス
	Audio* audio;					//オーディオクラス
	Sound* sound;					//サウンドクラス
	AbstractScene* scene;			//抽象シーンクラス
	std::string* currentSceneName;	//現在のシーンの名前

	//Method
	Director();
	~Director();
	HRESULT initialize();			//初期化
	void run(HINSTANCE);			//エントリポイントにおける呼び出し関数
	void mainLoop();				//メッセージループ内ループ処理関数
	void update();					//更新
	void render();					//描画
	void fixFPS60();				//FPS60補正
	void changeNextScene();			//シーンの切り替え
};