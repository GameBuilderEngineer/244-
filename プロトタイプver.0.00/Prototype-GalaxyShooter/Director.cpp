#include "Director.h"
#include "Splash.h"
#include "Title.h"
#include "SelectCharacter.h"
#include "Game.h"
#include "Result.h"


Director::Director(){
	ZeroMemory(this, sizeof(Director));
	scene = new Title();
}

Director::~Director(){
	SAFE_DELETE(window);
	SAFE_DELETE(camera);
	SAFE_DELETE(d3d);
	SAFE_DELETE(input);
	SAFE_DELETE(audio);
	SAFE_DELETE(sound);
	SAFE_DELETE(scene);
}

HRESULT Director::initialize(){
	//window
	window = new Window;
	if (!window)
		return E_FAIL;
	MFAIL(window->initialize(instance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME), "ウィンドウ作成失敗");
	wnd = window->wnd;
	//direct3D9
	d3d = new Direct3D9;
	if (d3d == NULL)
	{
		MSG("Direct3Dの初期化失敗");
		return E_FAIL;
	}
	MFAIL(d3d->initialize(wnd), "Direct3D初期化失敗");

	//input
	input = new Input();
	input->initialize(window->wnd,true);
	window->setInput(input);

	scene->initialize(d3d,input);

	//メッシュ読み込み
	// Xファイルからメッシュをロードする	
	//StaticMesh
	setVisualDirectory();
	//HierarchyMesh
	setVisualDirectory();
	//SKINMESH
	setVisualDirectory();

	//Audio(XACTエンジン)
	setSoundDirectory();
	audio = new Audio;
	audio->initialize();
	//Sound(XAuido2)
	sound = new Sound;
	MFAIL(sound->initialize(), "サウンド初期化失敗");
	//サウンド読み込み
	setSoundDirectory();
	sound->load((char*)"Chorus.wav");

	return S_OK;

}

void Director::run(HINSTANCE _instance){
	char directory[512];
	GetCurrentDirectory(sizeof(directory), directory);
	initializeDirectory(directory);

	instance = _instance;
	if (FAILED(initialize()))
	{
		return;
	}
	ShowWindow(wnd, SW_SHOW);
	UpdateWindow(wnd);
	// メッセージループ
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	sound->PlaySound(0, true);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mainLoop();
		}
	}
	sound->StopSound(0);
}

void Director::mainLoop(){
	if (scene->checkChangeOrder())// シーン切替フラグの確認
		changeNextScene();

	update();
	render();
	fixFPS60();

	//input->clearAll();
	input->clear(inputNS::MOUSE | inputNS::KEYS_PRESSED);// 入力をクリア	// すべてのキーチェックが行われた後これを呼び出す
}

void Director::update(){
	input->update(window->windowActivate);
	audio->run();
	scene->update();
}

void Director::render(){

	d3d->clear();
	if (SUCCEEDED(d3d->beginScene()))
	{
		scene->render(d3d);
		d3d->endScene();
	}
	d3d->present();
}

void Director::fixFPS60(){
	static LARGE_INTEGER time;
	LARGE_INTEGER time2, frq;
	double elaptime = 0;
	static int frame = 0;
	QueryPerformanceFrequency(&frq);
	double microsec = 1000000 / (double)frq.QuadPart;

	frame++;

	QueryPerformanceCounter(&time2);
	elaptime = (time2.QuadPart - time.QuadPart)*microsec;
	if (elaptime > 1000000)
	{
		QueryPerformanceCounter(&time);

		char str[50];
		sprintf(str, "fps=%d", frame);
		SetWindowTextA(wnd, str);
		frame = 0;
	}
}

void Director::changeNextScene(){
	int nextScene = scene->checkNextScene();		//次のシーンIDを取得
	SAFE_DELETE(scene);								// シーンの削除
	switch (nextScene)								// 指定されたシーンへ遷移
	{
	case SceneList::SPLASH:					scene = new Splash(); break;
	case SceneList::TITLE:					scene = new Title(); break;
	case SceneList::SELECT_CHARACTER:		scene = new SelectCharacter(); break;
	case SceneList::GAME:					scene = new Game(); break;
	case SceneList::RESULT:					scene = new Result(); break;
	case SceneList::NONE_SCENE:				break;
	}
	scene->initialize(d3d,input);
	currentSceneName = scene->getSceneName();
}