#include "Input.h"
using namespace inputNS;

Input::Input()
{
	// キーが押されている状態を示す配列をクリア
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		keysDown[i] = false;
	}
	// キーが押されたことを示す配列をクリア
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		keysPressed[i] = false;
	}
	newLine = true;			// 新しい行を開始
	textIn = "";			// textInをクリア
	charIn = 0;				// charInをクリア

	// マウスデータ
	mouseX = 0;				// 画面X
	mouseY = 0;				// 画面Y
	mouseRawX = 0;			// 高精細X
	mouseRawY = 0;			// 高精細Y
	mouseLButton = false;	// 左マウスボタンが押されている場合にtrue
	mouseMButton = false;	// 中央マウスボタンが押されている場合にtrue
	mouseRButton = false;	// 右マウスボタンが押されている場合にtrue
	mouseX1Button = false;	// X1マウスボタンが押されている場合にtrue
	mouseX2Button = false;	// X2マウスボタンが押されている場合にtrue
}

Input::~Input()
{
	if (mouseCaptured)
	{
		ReleaseCapture(); // マウスを解放
	}
}

HRESULT Input::initialize(HINSTANCE instance,HWND _wnd,bool capture)
{
	wnd = _wnd;
	//------------------------------------------------
	// 高精細マウスを登録
	mouseCaptured = capture;
	if (mouseCaptured)
	{
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = wnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
	}
	//------------------------------------------------

	//------------------------------------------------
	// 「DirectInput」オブジェクトの作成
	MFAIL(DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dinput, NULL),
		"DirectInputオブジェクトの作成に失敗しました。");

	enumDInputNum = 0;
	//利用可能なゲームコントローラーの列挙関数を実行
	MFAIL(dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumJoysticksCallback, this, DIEDFL_ATTACHEDONLY),
		"利用可能なゲームコントローラーの列挙に失敗しました。");
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		dInputController[i].initialize(_wnd);
		
		if (strcmp(dInputController[i].name, "Controller (Xbox One For Windows)") == 0)
			virtualController[i] = new D_XBOX_ONE_ELITE(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Pro Controller") == 0)
			virtualController[i] = new Nintendo_Switch_Pro_Contoroller(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Wireless Controller") == 0)
			virtualController[i] = new DualShock4(i, &dInputController[i]);
		else
			virtualController[i] = new EMPTY_CONTROLLER();
	}
	//------------------------------------------------

	return S_OK;
}
HRESULT Input::resetController()
{
	//for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	//{//仮想コントローラの削除
	//	SAFE_DELETE(virtualController[i]);
	//}

	//再度初期化
	enumDInputNum = 0;
	//利用可能なゲームコントローラーの列挙関数を実行
	MFAIL(dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumJoysticksCallback, this, DIEDFL_ATTACHEDONLY),
		"利用可能なゲームコントローラーの列挙に失敗しました。");
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		dInputController[i].initialize(wnd);

		if (strcmp(dInputController[i].name, "Controller (Xbox One For Windows)") == 0)
			virtualController[i] = new D_XBOX_ONE_ELITE(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Pro Controller") == 0)
			virtualController[i] = new Nintendo_Switch_Pro_Contoroller(i, &dInputController[i]);
		else if (strcmp(dInputController[i].name, "Wireless Controller") == 0)
			virtualController[i] = new DualShock4(i, &dInputController[i]);
		else
			virtualController[i] = new EMPTY_CONTROLLER();
	}

}

//=============================================================================
// このキーについて、keysDown配列とkeysPressed配列にtrueを設定
// 実行前：wParamに、仮想キーコード(0～255)が格納されている
//=============================================================================
void Input::keyDown(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{// キーコードが、バッファ範囲内にあることを確認
		if (keysDown[wParam] == false)
		{
			keysPressed[wParam] = true;
		}
		// keysDown配列を更新
		keysDown[wParam] = true;
		// keysPressed配列を更新
	}
}

//=============================================================================
// このキーについて、keysDown配列にfalseを設定
// 実行前：wParamに、仮想キーコード(0～255)が格納されている
//=============================================================================
void Input::keyUp(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{// キーコードが、バッファ範囲内あることを確認
		// 状態テーブルを更新
		keysDown[wParam] = false;
	}
}

//=============================================================================
// 入力された文字をtextIn文字列に保存
// 実行前：wParamに、文字が格納されている
//=============================================================================
void Input::keyIn(WPARAM wParam)
{
	if (newLine)
	{// 新しい行の開始の場合
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')
	{// バックスペースキーの場合
		if (textIn.length() > 0)
		{// 文字が存在する場合
			// 最後に入力された文字を消去
			textIn.erase(textIn.size() - 1);
		}
	}
	else {
		textIn += wParam;	// 文字をtextInに追加
		charIn = wParam;	// 最後に入力された文字を保存
	}

	if ((char)wParam == '\r')
	{// リターンキーの場合
		newLine = true;		// 新しい行を開始
	}
}

//=============================================================================
// 指定された仮想キーが押されている場合はtrue、それ以外の場合はfalseを戻す
//=============================================================================
bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	
	return false;
}

//=============================================================================
// 直近のフレームにおいて、指定の仮想キーが押されたことがある場合、trueを戻します。
// キーの押し下げの状態は、各フレームの終了時に消去されます。
//=============================================================================
bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	return false;
}

//=============================================================================
// 直近のフレームにおいて、何らかのキーが押された場合、trueを戻します。
// キーの押し下げの状態は、各フレームの終了時に消去されます。
//=============================================================================
bool Input::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		if (keysPressed[i] == true)return true;
	}
	return false;
}

//=============================================================================
// 指定されたキーの押し下げをクリア
//=============================================================================
void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

//=============================================================================
// 指定の入力バッファをクリア
// whatの値についてはinput.hを参照
//=============================================================================
void Input::clear(UCHAR what)
{
	// キーが押されている状態かどうかをクリアする場合
	if (what & inputNS::KEYS_DOWN)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		{
			keysDown[i] = false;
		}
	}

	// キーが押されたかどうかをクリアする場合
	if (what & inputNS::KEYS_PRESSED)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		{
			keysPressed[i] = false;
		}
	}

	// マウスをクリアする場合
	if (what & inputNS::MOUSE)
	{
		mouseX = 0;
		mouseY = 0;
		mouseRawX = 0;
		mouseRawY = 0;
	}

	if (what & inputNS::TEXT_IN)
	{
		clearTextIn();
	}
}

//=============================================================================
// マウスの画面位置を読み取り、mouseXとmouseYに保存
//=============================================================================
void Input::mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

//=============================================================================
// マウスからのローデータを読み取り、mouseRawXとmouseRawYに保存
// このルーチンは、高精細マウスに対応しています。
//=============================================================================
void Input::mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}

//=============================================================================
//利用可能なジョイスティックを列挙するコールバック関数
//=============================================================================
BOOL CALLBACK Input::enumJoysticksCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
	Input* obj = (Input*)context;
	int num = obj->enumDInputNum;
	if (num > NUM_DINPUT_CONTROLLER)
	{
		obj->enumDInputNum = 0;
		return DIENUM_STOP;
	}
	//複数列挙される場合、ユーザーに選択・確認させる
	TCHAR confirm[MAX_PATH + 1];
	sprintf(confirm, "この物理デバイスでデバイスオブジェクトを作成しますか？\n%s\n%s",
		instance->tszProductName, instance->tszInstanceName);
	if (MessageBox(0, confirm, "確認", MB_YESNO) == IDNO)
	{
		return DIENUM_CONTINUE;
	}

	//製品名を登録
	sprintf(obj->dInputController[num].name, "%s", instance->tszProductName);

	// 「DirectInputデバイス」オブジェクトの作成
	if (FAILED(obj->dinput->CreateDevice(instance->guidInstance, &obj->dInputController[num].device, NULL)))
	{
		return DIENUM_CONTINUE;
	}

	// ジョイスティックの能力を調べる
	obj->dInputController[num].deviceCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(obj->dInputController[num].device->GetCapabilities(&obj->dInputController[num].deviceCaps)))
	{
		//ジョイスティックの能力の取得に失敗
		SAFE_RELEASE(obj->dInputController[num].device);
		return DIENUM_CONTINUE;//列挙を続ける
	}

	//1つのインターフェースの取得が成功したので、次の格納先へ移動
	obj->enumDInputNum++;

	//このデバイスを使う
#if 0
	//列挙を終了する場合
	return DIENUM_STOP;
#else
	//他のジョイスティックも探す（列挙する）場合
	return DIENUM_CONTINUE;
#endif
}

void Input::update(bool windowActivate)
{
	int connectNum = 0;
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		if (dInputController[i].connected == false)continue;
		dInputController[i].update(windowActivate);
		connectNum++;
	}
	for (int i = 0; i < connectNum; i++)
	{
			virtualController[i]->update();
	}

}

