#include <Windows.h>
#include "Direct3D9.h"
#include "Window.h"
#include "Director.h"
std::thread th(AsyncLoad);
bool isLoaded = false;
std::mutex isLoadedMutex;
void AsyncLoad();
TextureLoader textureLoader;

void SetLockFlag(bool _)
{
	std::lock_guard <std::mutex> lock(isLoadedMutex);
	isLoaded = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex> lock(isLoadedMutex);
	return isLoaded;
}
Director* director = NULL;

INT WINAPI WinMain(HINSTANCE instance,HINSTANCE,LPSTR,INT)
{
	Director* director;
	if (director == NULL)
	{
		MSG("�N���X�������s�@�A�v�����I�����܂�");
		return 0;
	}
	//�i�s�̓f�B���N�^�[�ɔC����
	director->run(instance);
	//�A�v���I��
	delete director;
	director->d3d->device

	return 0;
}

void AsyncLoad()
{
	//�_�~�[��10�b�҂�
	//auto sleepTime = std::chrono::seconds(10);
	//std::this_thread::sleep_for(sleepTime);
	textureLoader.load(d3d->device);

	SetLockFlag(true);
}