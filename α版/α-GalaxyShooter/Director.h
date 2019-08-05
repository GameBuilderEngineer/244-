//===================================================================================================================================
//�yDirector.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/04
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
//#include <thread>

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
	HINSTANCE instance;						//
	Window* window;							//�E�B���h�E�N���X�E�n���h��
#ifdef _DEBUG
	DebugWindow* debugWindow0;				//�f�o�b�O�E�B���h�E�N���X
	DebugWindow* debugWindow1;				//�f�o�b�O�E�B���h�E�N���X
	//std::thread* thread_a;
#endif // _DEBUG
	HWND wnd;								//�E�B���h�E�n���h��
	Direct3D9* d3d;							//DirectX9�N���X�E�f�o�C�X
	Input* input;							//Input�N���X
	Camera* camera;							//�J�����N���X
	Sound* sound;
	AbstractScene* scene;					//���ۃV�[���N���X
	TextureLoader* textureLoader;			//�e�N�X�`���Ǎ��N���X
	StaticMeshLoader* staticMeshLoader;		//�X�^�e�B�b�N���b�V���Ǎ��N���X
	ShaderLoader* shaderLoader;				//�V�F�[�_�[�Ǎ��N���X
	TextManager* textManager;				//�e�L�X�g�f�[�^�Ǎ��N���X
	GameMaster* gameMaster;					//�Q�[���^�c�N���X
	std::string* currentSceneName;			//���݂̃V�[���̖��O
	int fpsMode;							//�t���[�����[�g��ԕϐ�
	LARGE_INTEGER timeStart;				// �p�t�H�[�}���X�J�E���^�[�̊J�n�l
	LARGE_INTEGER timeEnd;					// �p�t�H�[�}���X�J�E���^�[�̏I���l
	LARGE_INTEGER timerFreq;				// �p�t�H�[�}���X�J�E���^�[�̎��g��
	float frameTime;						//�t���[������
	bool hiddenCursor;						//�J�[�\����\���t���O
	bool lockCursor;						//�J�[�\���ʒu�Œ�t���O

											//Method
	Director();
	~Director();
	HRESULT initialize();					//������
	void run(HINSTANCE);					//�G���g���|�C���g�ɂ�����Ăяo���֐�
	void mainLoop();						//���b�Z�[�W���[�v�����[�v�����֐�
	void update();							//�X�V
	void render();							//�`��
	void setFrameTime();					//frameTime�̐ݒ�
	void displayFPS();						//FPS�\��
	void fixFPS60();						//FPS60�␳
	void changeNextScene();					//�V�[���̐؂�ւ�
};
//void setInstance(HINSTANCE* hinstance);
//void threadA();