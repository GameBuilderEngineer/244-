//===================================================================================================================================
//�yEntry.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/07
//===================================================================================================================================
#include <windows.h>
#include "Director.h"

INT WINAPI WinMain(HINSTANCE instance,HINSTANCE,LPSTR,INT)
{
	//setInstance(&instance);

	Director* director = new Director;
	if (director == NULL)
	{
		MSG("�N���X�������s�@�A�v�����I�����܂�");
		return 0;
	}
	//�i�s�̓f�B���N�^�[�ɔC����
	director->run(instance);

	//�A�v���I��
	delete director;

	return 0;
}

