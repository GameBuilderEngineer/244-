//===================================================================================================================================
//【Director.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/04
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "Window.h"
#include "DebugWindow.h"
#include "Direct3D9.h"
#include "Input.h"
#include "Camera.h"
#include "Sound.h"
#include "AbstractScene.h"
#include "VirtualController.h"
#include "TextureLoader.h"
#include "StaticMeshLoader.h"
#include "ShaderLoader.h"
#include "TextManager.h"
#include "GameMaster.h"
#include "AnimationLoader.h"
//#include <thread>

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
	HINSTANCE instance;						//
	Window* window;							//ウィンドウクラス・ハンドル
#ifdef _DEBUG
	DebugWindow* debugWindow0;				//デバッグウィンドウクラス
	DebugWindow* debugWindow1;				//デバッグウィンドウクラス
	//std::thread* thread_a;
#endif // _DEBUG
	HWND wnd;								//ウィンドウハンドル
	Direct3D9* d3d;							//DirectX9クラス・デバイス
	Input* input;							//Inputクラス
	Camera* camera;							//カメラクラス
	Sound* sound;
	AbstractScene* scene;					//抽象シーンクラス
	TextureLoader* textureLoader;			//テクスチャ読込クラス
	StaticMeshLoader* staticMeshLoader;		//スタティックメッシュ読込クラス
	ShaderLoader* shaderLoader;				//シェーダー読込クラス
	TextManager* textManager;				//テキストデータ読込クラス
	GameMaster* gameMaster;					//ゲーム運営クラス
	AnimationLoader* animationLoader;		//アニメーション読込クラス
	std::string* currentSceneName;			//現在のシーンの名前
	int fpsMode;							//フレームレート状態変数
	LARGE_INTEGER timeStart;				// パフォーマンスカウンターの開始値
	LARGE_INTEGER timeEnd;					// パフォーマンスカウンターの終了値
	LARGE_INTEGER timerFreq;				// パフォーマンスカウンターの周波数
	float frameTime;						//フレーム時間
	bool hiddenCursor;						//カーソル非表示フラグ
	bool lockCursor;						//カーソル位置固定フラグ

											//Method
	Director();
	~Director();
	HRESULT initialize();					//初期化
	void run(HINSTANCE);					//エントリポイントにおける呼び出し関数
	void mainLoop();						//メッセージループ内ループ処理関数
	void update();							//更新
	void render();							//描画
	void setFrameTime();					//frameTimeの設定
	void displayFPS();						//FPS表示
	void fixFPS60();						//FPS60補正
	void changeNextScene();					//シーンの切り替え
};
//void setInstance(HINSTANCE* hinstance);
//void threadA();