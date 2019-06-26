#pragma once
#include "Base.h"
#include "Window.h"
#include "Direct3D9.h"
#include "Input.h"
#include "Text.h"
#include "TextureLoader.h"
#include <thread>
#include <mutex>


enum
{
	VARIABLE_FPS,	//可変フレームレート
	FIXED_FPS,		//固定フレームレート
};


//管理クラス
class Director : public Base
{
public:
	//Data
	HINSTANCE instance;				//
	Window* window;					//ウィンドウクラス・ハンドル
	HWND wnd;						//ウィンドウハンドル
	Direct3D9* d3d;					//DirectX9クラス・デバイス
	Input* input;					//Inputクラス
	//Camera* camera;					//カメラクラス
	//Audio* audio;					//オーディオクラス
	//Sound* sound;					//サウンドクラス
	//AbstractScene* scene;			//抽象シーンクラス
	//std::string* currentSceneName;	//現在のシーンの名前
	Text text;



	int fpsMode;					//フレームレート状態変数
	LARGE_INTEGER timeStart;		// パフォーマンスカウンターの開始値
	LARGE_INTEGER timeEnd;			// パフォーマンスカウンターの終了値
	LARGE_INTEGER timerFreq;		// パフォーマンスカウンターの周波数
	float frameTime;				//フレーム時間
	bool hiddenCursor;				//カーソル非表示フラグ
	bool lockCursor;				//カーソル位置固定フラグ
	//Method
	Director();
	~Director();

	void SetLockFlag(bool _);
	bool GetLockFlag();
	
	HRESULT initialize();			//初期化
	void run(HINSTANCE);			//エントリポイントにおける呼び出し関数
	void mainLoop();				//メッセージループ内ループ処理関数
	void update();					//更新
	void render();					//描画
	void setFrameTime();			//frameTimeの設定
	void displayFPS();				//FPS表示
	void variableFPS();				//可変FPS(最大FPS)
	void fixFPS60();				//FPS60補正
	void changeNextScene();			//シーンの切り替え
};