//===================================================================================================================================
//�yDirectInputController.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/08/07
// [�X�V��]2019/08/07
//===================================================================================================================================
#pragma once
#include "Base.h"
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <dxerr.h>
#pragma comment( lib, "dxerr.lib" )
#pragma comment(lib,"dinput8.lib")
#pragma comment( lib, "dxguid.lib" )


#define DIDEVICE_BUFFERSIZE 100;		// �f�o�C�X�ɐݒ肷��o�b�t�@�E�T�C�Y

class DirectInputController:public Base
{
public:
	LPDIRECTINPUTDEVICE8 device;	// DirectInput�f�o�C�X
	DIDEVCAPS deviceCaps;			// �W���C�X�e�B�b�N�̔\��
	DIJOYSTATE2 joyState;			// ��ԕۑ��ϐ�
	DIDEVICEOBJECTDATA objectData;	// POV�ۑ��ϐ�(�\���L�[)
	TCHAR name[MAX_PATH + 1];		// �R���g���[���̖��O
	bool connected;					// �ڑ����

	HRESULT initialize(HWND wnd);
	void update(bool windowActivate);
	DirectInputController() {
		device = NULL;
	}

	static BOOL CALLBACK EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE, VOID* pContext);

};