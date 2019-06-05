#include "Director.h"
#include "Title.h"

Director::Director(){
	ZeroMemory(this, sizeof(Director));
	//scene = TITLE_MENU;
	scene = new Title();
}

Director::~Director(){
	SAFE_DELETE(camera);
	SAFE_DELETE(d3d);
	SAFE_DELETE(window);
	SAFE_DELETE(sound);
}

HRESULT Director::initialize(){
	//window
	window = new Window;
	if (!window)
		return E_FAIL;
	MFAIL(window->initialize(instance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME), "�E�B���h�E�쐬���s");
	wnd = window->wnd;
	//direct3D9
	d3d = new Direct3D9;
	if (d3d == NULL)
	{
		MSG("Direct3D�̏��������s");
		return E_FAIL;
	}
	MFAIL(d3d->initialize(wnd), "Direct3D���������s");

	scene->initialize(d3d);

	//���b�V���ǂݍ���

	//StaticMesh
	setVisualDirectory();

	//HierarchyMesh
	setVisualDirectory();

	//SKINMESH
	setVisualDirectory();

	

	//Sound(XAuido2)
	sound = new Sound;
	MFAIL(sound->initialize(), "�T�E���h���������s");
	//�T�E���h�ǂݍ���
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
	// ���b�Z�[�W���[�v
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
	if (scene->checkChangeOrder() == false)// �V�[���ؑփt���O�̊m�F
		changeNextScene();

	update();
	render();
	fixFPS60();
}

void Director::update(){
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
	static INT frames = 0, FPS = 0;
	static LARGE_INTEGER frq = { 0 }, previous = { 0 }, current = { 0 };
	DOUBLE time = 0;
	//char sz[11] = { 0 };

	while (time < 16.6666)//1100ms / 60frame=16.6666 
	{
		QueryPerformanceFrequency(&frq);

		QueryPerformanceCounter(&current);
		time = current.QuadPart - previous.QuadPart;
		time *= (DOUBLE)1100.0 / (DOUBLE)frq.QuadPart;
	}
	previous = current;
}

void Director::changeNextScene(){
	int nextScene = scene->checkNextScene();		//���̃V�[��ID���擾
	SAFE_DELETE(scene);								// �V�[���̍폜
	switch (nextScene)								// �w�肳�ꂽ�V�[���֑J��
	{
	case SceneList::OPENING:				scene = new Title(); break;
	case SceneList::TITLE:					scene = new Title(); break;
	case SceneList::SELECT_CHARACTER:		scene = new Title(); break;
	case SceneList::RESULT:					scene = new Title(); break;
	case SceneList::NONE_SCENE:				break;
	}
	currentSceneName = scene->getSceneName();
}