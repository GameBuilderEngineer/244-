#include "Director.h"
#include "Splash.h"
#include "Title.h"
#include "SelectCharacter.h"
#include "Game.h"
#include "Result.h"

Director::Director(){
	ZeroMemory(this, sizeof(Director));
	hiddenCursor = true;
	lockCursor = true;
	scene = new Title();
	fpsMode = FIXED_FPS;
	ShowCursor(FALSE);
}

Director::~Director(){
	SAFE_DELETE(window);
	SAFE_DELETE(camera);
	SAFE_DELETE(d3d);
	SAFE_DELETE(input);
	SAFE_DELETE(audio);
	SAFE_DELETE(sound);
	SAFE_DELETE(scene);
	SAFE_DELETE(textureLoader);
	SAFE_DELETE(staticMeshLoader);
	ShowCursor(TRUE);
}

HRESULT Director::initialize(){
	//window
	window = new Window;
	if (!window)
		return E_FAIL;
	MFAIL(window->initialize(instance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME), "ウィンドウ作成失敗");
	wnd = window->wnd;

#ifdef _DEBUG
	//debugWindow
	debugWindow0 = new DebugWindow;
	if (!debugWindow0)
		return E_FAIL;
	MFAIL(debugWindow0->initialize(instance, window->getRect().left, window->getRect().bottom, WINDOW_WIDTH, WINDOW_HEIGHT/2, DEBUG_NAME), "デバッグウィンドウ0作成失敗");
	debugWindow1 = new DebugWindow;
	if (!debugWindow1)
		return E_FAIL;
	MFAIL(debugWindow1->initialize(instance, window->getRect().right, window->getRect().top, WINDOW_WIDTH/2, WINDOW_HEIGHT, DEBUG_NAME), "デバッグウィンドウ1作成失敗");
	SetForegroundWindow(wnd);
#endif // _DEBUG


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
	input->initialize(instance,window->wnd,true);
	window->setInput(input);

	//textureLoader
	textureLoader = new TextureLoader;
	textureLoader->load(d3d->device);

	//メッシュ読み込み
	// Xファイルからメッシュをロードする	
	//StaticMesh
	staticMeshLoader = new StaticMeshLoader;
	staticMeshLoader->load(d3d->device);

	//HierarchyMesh
	//setVisualDirectory();
	//SKINMESH
	//setVisualDirectory();

	//Audio(XACTエンジン)
	setSoundDirectory();
	audio = new Audio;
	audio->initialize();

	//scene
	scene->initialize(d3d,input,textureLoader,staticMeshLoader);

	// 高分解能タイマーの準備を試みる
	if (QueryPerformanceFrequency(&timerFreq) == false)
	{
		MSG("高分解能タイマーの取得失敗しました。");
	}
	// 開始時間を取得
	QueryPerformanceCounter(&timeStart); 

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
}

void Director::mainLoop(){
	if (scene->checkChangeOrder())// シーン切替フラグの確認
		changeNextScene();

	if (input->wasKeyPressed(VK_OEM_3))
	{
		if (fpsMode != FIXED_FPS)
			fpsMode = FIXED_FPS;
		else
			fpsMode = VARIABLE_FPS;
	}

	setFrameTime();
	update();
	render();
	fixFPS60();
	displayFPS();

	input->clear(inputNS::MOUSE | inputNS::KEYS_PRESSED);// 入力をクリア	// すべてのキーチェックが行われた後これを呼び出す
}

void Director::update(){
	input->update(window->windowActivate);
	if (input->wasKeyPressed(VK_F1))
	{
		hiddenCursor = !hiddenCursor;
		if (hiddenCursor) {
			ShowCursor(FALSE);
		}
		else {
			ShowCursor(TRUE);
		}
	}
	if (input->wasKeyPressed(VK_F2))
		lockCursor = !lockCursor;
	audio->run();
	scene->update(frameTime);
	scene->collisions();
	if(lockCursor)SetCursorPos((int)window->getCenter().x, (int)window->getCenter().y);
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

void Director::setFrameTime()
{
	// 最後のフレームからの経過時間を計算、frameTimeに保存
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;

	timeStart = timeEnd;
}

void Director::fixFPS60() {
	if (fpsMode != FIXED_FPS)return;
	static INT Frames = 0, FPS = 0;
	static LARGE_INTEGER Frq = { 0 }, PreviousTime = { 0 }, CurrentTime = { 0 };
	DOUBLE Time = 0;
	char sz[11] = { 0 };

	while (Time < 16.6666)//1100ms / 60frame=16.6666 
	{
		QueryPerformanceFrequency(&Frq);

		QueryPerformanceCounter(&CurrentTime);
		Time = (DOUBLE)(CurrentTime.QuadPart - PreviousTime.QuadPart);

		Time *= (DOUBLE)1100.0 / (DOUBLE)Frq.QuadPart;

		//ここに次フレームまでの待機中にさせたい処理を記述
		if(lockCursor)SetCursorPos((int)window->getCenter().x, (int)window->getCenter().y);
	}
	PreviousTime = CurrentTime;
}

void Director::displayFPS() {
	//FPS計算表示
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
		char name[200] = { 0 };
		GetClassNameA(wnd, name, sizeof(name));
		sprintf(str, "fps=%d", frame);
		strcat(name, str);
		SetWindowTextA(wnd, name);
		frame = 0;
	}
}

void Director::variableFPS(){
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
	scene->initialize(d3d,input, textureLoader, staticMeshLoader);
	currentSceneName = scene->getSceneName();
}