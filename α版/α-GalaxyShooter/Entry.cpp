//===================================================================================================================================
//【Entry.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/07
//===================================================================================================================================
#include <windows.h>
#include "Director.h"

INT WINAPI WinMain(HINSTANCE instance,HINSTANCE,LPSTR,INT)
{
	//setInstance(&instance);

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

