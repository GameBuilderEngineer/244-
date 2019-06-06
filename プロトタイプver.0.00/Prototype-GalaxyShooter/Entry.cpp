#include <windows.h>
#include "Director.h"

INT WINAPI WinMain(HINSTANCE instance,HINSTANCE,LPSTR,INT)
{
	Director* director = new Director;
	if (director == NULL)
	{
		MSG("クラス生成失敗　アプリを終了します");
		return 0;
	}
	//進行はディレクターに任せる
	director->run(instance);

	//アプリ終了
	delete director;

	return 0;
}

