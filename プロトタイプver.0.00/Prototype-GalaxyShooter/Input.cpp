#include "Input.h"
using namespace inputNS;

Input::Input()
{
	// �L�[��������Ă����Ԃ������z����N���A
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		keysDown[i] = false;
	}
	// �L�[�������ꂽ���Ƃ������z����N���A
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		keysPressed[i] = false;
	}
	newLine = true;			// �V�����s���J�n
	textIn = "";			// textIn���N���A
	charIn = 0;				// charIn���N���A

	// �}�E�X�f�[�^
	mouseX = 0;				// ���X
	mouseY = 0;				// ���Y
	mouseRawX = 0;			// ������X
	mouseRawY = 0;			// ������Y
	mouseLButton = false;	// ���}�E�X�{�^����������Ă���ꍇ��true
	mouseMButton = false;	// �����}�E�X�{�^����������Ă���ꍇ��true
	mouseRButton = false;	// �E�}�E�X�{�^����������Ă���ꍇ��true
	mouseX1Button = false;	// X1�}�E�X�{�^����������Ă���ꍇ��true
	mouseX2Button = false;	// X2�}�E�X�{�^����������Ă���ꍇ��true
}

Input::~Input()
{
	if (mouseCaptured)
	{
		ReleaseCapture(); // �}�E�X�����
	}
}

HRESULT Input::initialize(HWND wnd,bool capture)
{
	//------------------------------------------------
	// �����׃}�E�X��o�^
	mouseCaptured = capture;
	if (mouseCaptured)
	{
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = wnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
		SetCapture(wnd);	// �}�E�X���L���v�`��
	}
	//------------------------------------------------

	//------------------------------------------------
	// �uDirectInput�v�I�u�W�F�N�g�̍쐬
	MFAIL(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dinput, NULL),
		"DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B");

	enumDInputNum = 0;
	//���p�\�ȃQ�[���R���g���[���[�̗񋓊֐������s
	MFAIL(dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumJoysticksCallback, this, DIEDFL_ATTACHEDONLY),
		"���p�\�ȃQ�[���R���g���[���[�̗񋓂Ɏ��s���܂����B");
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		dInputController[i].initialize(wnd);
		if(strcmp(dInputController[i].name,"Controller (Xbox One For Windows)"))
			virtualController[i] = new D_XBOX_ONE_ELITE(i, &dInputController[i]);
		if(strcmp(dInputController[i].name,"Wireless Controller"))
			virtualController[i] = new DualShock4(i, &dInputController[i]);
		if(strcmp(dInputController[i].name,"Pro Controller"))
			virtualController[i] = new Nintendo_Switch_Pro_Contoroller(i, &dInputController[i]);
	}
	//------------------------------------------------

	return S_OK;
}
//=============================================================================
// ���̃L�[�ɂ��āAkeysDown�z���keysPressed�z���true��ݒ�
// ���s�O�FwParam�ɁA���z�L�[�R�[�h(0�`255)���i�[����Ă���
//=============================================================================
void Input::keyDown(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{// �L�[�R�[�h���A�o�b�t�@�͈͓��ɂ��邱�Ƃ��m�F
		// keysDown�z����X�V
		keysDown[wParam] = true;
		// keysPressed�z����X�V
		keysPressed[wParam] = true;
	}
}

//=============================================================================
// ���̃L�[�ɂ��āAkeysDown�z���false��ݒ�
// ���s�O�FwParam�ɁA���z�L�[�R�[�h(0�`255)���i�[����Ă���
//=============================================================================
void Input::keyUp(WPARAM wParam)
{
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{// �L�[�R�[�h���A�o�b�t�@�͈͓����邱�Ƃ��m�F
		// ��ԃe�[�u�����X�V
		keysDown[wParam] = false;
	}
}

//=============================================================================
// ���͂��ꂽ������textIn������ɕۑ�
// ���s�O�FwParam�ɁA�������i�[����Ă���
//=============================================================================
void Input::keyIn(WPARAM wParam)
{
	if (newLine)
	{// �V�����s�̊J�n�̏ꍇ
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')
	{// �o�b�N�X�y�[�X�L�[�̏ꍇ
		if (textIn.length() > 0)
		{// ���������݂���ꍇ
			// �Ō�ɓ��͂��ꂽ����������
			textIn.erase(textIn.size() - 1);
		}
	}
	else {
		textIn += wParam;	// ������textIn�ɒǉ�
		charIn = wParam;	// �Ō�ɓ��͂��ꂽ������ۑ�
	}

	if ((char)wParam == '\r')
	{// ���^�[���L�[�̏ꍇ
		newLine = true;		// �V�����s���J�n
	}
}

//=============================================================================
// �w�肳�ꂽ���z�L�[��������Ă���ꍇ��true�A����ȊO�̏ꍇ��false��߂�
//=============================================================================
bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	
	return false;
}

//=============================================================================
// ���߂̃t���[���ɂ����āA�w��̉��z�L�[�������ꂽ���Ƃ�����ꍇ�Atrue��߂��܂��B
// �L�[�̉��������̏�Ԃ́A�e�t���[���̏I�����ɏ�������܂��B
//=============================================================================
bool Input::wasKeyPressed(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysPressed[vkey];

	return false;
}

//=============================================================================
// ���߂̃t���[���ɂ����āA���炩�̃L�[�������ꂽ�ꍇ�Atrue��߂��܂��B
// �L�[�̉��������̏�Ԃ́A�e�t���[���̏I�����ɏ�������܂��B
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
// �w�肳�ꂽ�L�[�̉����������N���A
//=============================================================================
void Input::clearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

//=============================================================================
// �w��̓��̓o�b�t�@���N���A
// what�̒l�ɂ��Ă�input.h���Q��
//=============================================================================
void Input::clear(UCHAR what)
{
	// �L�[��������Ă����Ԃ��ǂ������N���A����ꍇ
	if (what & inputNS::KEYS_DOWN)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		{
			keysDown[i] = false;
		}
	}

	// �L�[�������ꂽ���ǂ������N���A����ꍇ
	if (what & inputNS::KEYS_PRESSED)
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
		{
			keysPressed[i] = false;
		}
	}

	// �}�E�X���N���A����ꍇ
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
// �}�E�X�̉�ʈʒu��ǂݎ��AmouseX��mouseY�ɕۑ�
//=============================================================================
void Input::mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

//=============================================================================
// �}�E�X����̃��[�f�[�^��ǂݎ��AmouseRawX��mouseRawY�ɕۑ�
// ���̃��[�`���́A�����׃}�E�X�ɑΉ����Ă��܂��B
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
//���p�\�ȃW���C�X�e�B�b�N��񋓂���R�[���o�b�N�֐�
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
	//�����񋓂����ꍇ�A���[�U�[�ɑI���E�m�F������
	TCHAR confirm[MAX_PATH + 1];
	sprintf(confirm, "���̕����f�o�C�X�Ńf�o�C�X�I�u�W�F�N�g���쐬���܂����H\n%s\n%s",
		instance->tszProductName, instance->tszInstanceName);
	if (MessageBox(0, confirm, "�m�F", MB_YESNO) == IDNO)
	{
		return DIENUM_CONTINUE;
	}

	//���i����o�^
	sprintf(obj->dInputController[num].name, "%s", instance->tszProductName);

	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	if (FAILED(obj->dinput->CreateDevice(instance->guidInstance, &obj->dInputController[num].device, NULL)))
	{
		return DIENUM_CONTINUE;
	}

	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	obj->dInputController[num].deviceCaps.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(obj->dInputController[num].device->GetCapabilities(&obj->dInputController[num].deviceCaps)))
	{
		//�W���C�X�e�B�b�N�̔\�͂̎擾�Ɏ��s
		SAFE_RELEASE(obj->dInputController[num].device);
		return DIENUM_CONTINUE;//�񋓂𑱂���
	}

	//1�̃C���^�[�t�F�[�X�̎擾�����������̂ŁA���̊i�[��ֈړ�
	obj->enumDInputNum++;

	//���̃f�o�C�X���g��
#if 0
	//�񋓂��I������ꍇ
	return DIENUM_STOP;
#else
	//���̃W���C�X�e�B�b�N���T���i�񋓂���j�ꍇ
	return DIENUM_CONTINUE;
#endif
}

void Input::update(bool windowActivate)
{
	for (int i = 0; i < NUM_DINPUT_CONTROLLER; i++)
	{
		dInputController[i].update(windowActivate);
	}
}

void DirectInputController::update(bool windowActivate)
{
	if (device == NULL)	return;

	HRESULT hr;
	// �f�o�C�X�̒��ڃf�[�^���擾����
	hr = device->Poll();
	if (FAILED(hr))
	{
		hr = device->Acquire();
		while (windowActivate && hr == DIERR_INPUTLOST)
		{
			hr = device->Acquire();
		}
	}

	// �R���g���[���[�̏�Ԃ��擾����
	hr = device->GetDeviceState(sizeof(DIJOYSTATE2), &joyState);
	if (FAILED(hr))
	{
		if (windowActivate && hr == DIERR_INPUTLOST)
		{
			device->Acquire();
		}
	}

	// �o�b�t�@�����O�f�[�^���擾����
	while (windowActivate)
	{
		DWORD items = 1;
		hr = device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &objectData, &items, 0);
		if (hr == DIERR_INPUTLOST)
		{
			device->Acquire();
		}
		else if (FAILED(hr) || items == 0)
		{
			break;// �f�[�^���ǂ߂Ȃ����A���݂��Ȃ�
		}
	}
}