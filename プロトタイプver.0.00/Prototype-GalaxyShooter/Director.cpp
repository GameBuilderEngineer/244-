#include "Director.h"
#include "Title.h"
#include "Game.h"

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

	//input
	input = new Input();
	input->initialize(window->wnd,true);
	window->setInput(input);

	scene->initialize(d3d,input);

	//���b�V���ǂݍ���
	// X�t�@�C�����烁�b�V�������[�h����	
	//StaticMesh
	setVisualDirectory();
	//HierarchyMesh
	setVisualDirectory();
	//SKINMESH
	setVisualDirectory();

	//Audio(XACT�G���W��)
	setSoundDirectory();
	audio = new Audio;
	audio->initialize();
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
	if (scene->checkChangeOrder())// �V�[���ؑփt���O�̊m�F
		changeNextScene();

	update();
	render();
	fixFPS60();

	//input->clearAll();
	input->clear(inputNS::MOUSE | inputNS::KEYS_PRESSED);// ���͂��N���A	// ���ׂẴL�[�`�F�b�N���s��ꂽ�ケ����Ăяo��
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
	int nextScene = scene->checkNextScene();		//���̃V�[��ID���擾
	SAFE_DELETE(scene);								// �V�[���̍폜
	switch (nextScene)								// �w�肳�ꂽ�V�[���֑J��
	{
	case SceneList::OPENING:				scene = new Title(); break;
	case SceneList::TITLE:					scene = new Title(); break;
	case SceneList::GAME:					scene = new Game(); break;
	case SceneList::SELECT_CHARACTER:		scene = new Title(); break;
	case SceneList::RESULT:					scene = new Title(); break;
	case SceneList::NONE_SCENE:				break;
	}
	scene->initialize(d3d,input);
	currentSceneName = scene->getSceneName();
}