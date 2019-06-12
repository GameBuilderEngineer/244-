#pragma once
#include "Base.h"
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <dxerr.h>
#pragma comment( lib, "dxerr.lib" )
#pragma comment(lib,"dinput8.lib")

#define DIDEVICE_BUFFERSIZE 100;		// デバイスに設定するバッファ・サイズ

class DirectInputController:public Base
{
public:
	LPDIRECTINPUTDEVICE8 device;	// DirectInputデバイス
	DIDEVCAPS deviceCaps;			// ジョイスティックの能力
	DIJOYSTATE2 joyState;			// 状態保存変数
	DIDEVICEOBJECTDATA objectData;	// POV保存変数(十字キー)
	TCHAR name[MAX_PATH + 1];		// コントローラの名前
	bool connected;					// 接続状態

	HRESULT initialize(HWND wnd);
	void update(bool windowActivate);
	DirectInputController() {
		device = NULL;
	}

	static BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);

};