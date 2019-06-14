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
enum
{
	VARIABLE_FPS,	//�σt���[�����[�g
	FIXED_FPS,		//�Œ�t���[�����[�g
};

//�Ǘ��N���X
class Director : public Base
{
public:
	//Data
	HINSTANCE instance;				//
	Window* window;					//�E�B���h�E�N���X�E�n���h��
	HWND wnd;						//�E�B���h�E�n���h��
	Direct3D9* d3d;					//DirectX9�N���X�E�f�o�C�X
	Input* input;					//Input�N���X
	Camera* camera;					//�J�����N���X
	Audio* audio;					//�I�[�f�B�I�N���X
	Sound* sound;					//�T�E���h�N���X
	AbstractScene* scene;			//���ۃV�[���N���X
	std::string* currentSceneName;	//���݂̃V�[���̖��O
	int fpsMode;					//�t���[�����[�g��ԕϐ�

	//Method
	Director();
	~Director();
	HRESULT initialize();			//������
	void run(HINSTANCE);			//�G���g���|�C���g�ɂ�����Ăяo���֐�
	void mainLoop();				//���b�Z�[�W���[�v�����[�v�����֐�
	void update();					//�X�V
	void render();					//�`��
	void displayFPS();				//FPS�\��
	void variableFPS();				//��FPS(�ő�FPS)
	void fixFPS60();				//FPS60�␳
	void changeNextScene();			//�V�[���̐؂�ւ�
};