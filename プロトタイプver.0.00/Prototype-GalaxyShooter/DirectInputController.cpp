#include "DirectInputController.h"


HRESULT DirectInputController::initialize(HWND wnd)
{
	connected = false;

	if (device == NULL)return E_FAIL;

	// デバイスをジョイスティックに設定
	MFAIL(device->SetDataFormat(&c_dfDIJoystick2), "ジョイスティックの設定に失敗しました。");

	// 協調レベルの設定
	MFAIL(device->SetCooperativeLevel(wnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND),"協調レベルの設定に失敗しました。");

	//アプリケーションで使用するコントローラーのプロパティを列挙して設定する
	MFAIL(device->EnumObjects(EnumObjectsCallback, this, DIDFT_ALL),"コントローラプロパティの列挙と設定に失敗しました。");

	// 軸モードを設定（絶対値モードに設定。デフォルトなので必ずしも設定は必要ない）
	DIPROPDWORD propWord;
	propWord.diph.dwSize = sizeof(propWord);
	propWord.diph.dwHeaderSize = sizeof(propWord.diph);
	propWord.diph.dwObj = 0;
	propWord.diph.dwHow = DIPH_DEVICE;
	propWord.dwData = DIPROPAXISMODE_ABS;
	//diprop.dwData = DIPROPAXISMODE_REL; // 相対値モードの場合
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &propWord.diph)))
	{
		MSG("軸モードの設定に失敗");
		return E_FAIL;
	}

	// バッファリング・データを取得するため、バッファ・サイズを設定
	propWord.dwData = DIDEVICE_BUFFERSIZE;
	if (FAILED(device->SetProperty(DIPROP_BUFFERSIZE, &propWord.diph)))
	{
		MSG("バッファ・サイズの設定に失敗");
		return E_FAIL;
	}

	// 入力制御開始
	connected = true;
	device->Acquire();
	return S_OK;
}

//アプリケーションで使用するコントローラーのプロパティを列挙して設定する
BOOL CALLBACK DirectInputController::EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* objectInstance, VOID* context)
{
	DirectInputController* obj = (DirectInputController*)context;

	if (objectInstance->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE propRange;//軸範囲
		propRange.diph.dwSize = sizeof(DIPROPRANGE);
		propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		propRange.diph.dwHow = DIPH_BYID;
		propRange.diph.dwObj = objectInstance->dwType;
		propRange.lMin = -1000;
		propRange.lMax = +1000;

		if (FAILED(obj->device->SetProperty(DIPROP_RANGE, &propRange.diph)))
		{
			return DIENUM_STOP;
		}
	}
	return DIENUM_CONTINUE;
}