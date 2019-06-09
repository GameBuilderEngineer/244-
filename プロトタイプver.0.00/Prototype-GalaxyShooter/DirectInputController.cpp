#include "DirectInputController.h"


HRESULT DirectInputController::initialize(HWND wnd)
{
	connected = false;

	if (device == NULL)return E_FAIL;

	// �f�o�C�X���W���C�X�e�B�b�N�ɐݒ�
	MFAIL(device->SetDataFormat(&c_dfDIJoystick2), "�W���C�X�e�B�b�N�̐ݒ�Ɏ��s���܂����B");

	// �������x���̐ݒ�
	MFAIL(device->SetCooperativeLevel(wnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND),"�������x���̐ݒ�Ɏ��s���܂����B");

	//�A�v���P�[�V�����Ŏg�p����R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��
	MFAIL(device->EnumObjects(EnumObjectsCallback, this, DIDFT_ALL),"�R���g���[���v���p�e�B�̗񋓂Ɛݒ�Ɏ��s���܂����B");

	// �����[�h��ݒ�i��Βl���[�h�ɐݒ�B�f�t�H���g�Ȃ̂ŕK�������ݒ�͕K�v�Ȃ��j
	DIPROPDWORD propWord;
	propWord.diph.dwSize = sizeof(propWord);
	propWord.diph.dwHeaderSize = sizeof(propWord.diph);
	propWord.diph.dwObj = 0;
	propWord.diph.dwHow = DIPH_DEVICE;
	propWord.dwData = DIPROPAXISMODE_ABS;
	//diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�̏ꍇ
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &propWord.diph)))
	{
		MSG("�����[�h�̐ݒ�Ɏ��s");
		return E_FAIL;
	}

	// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
	propWord.dwData = DIDEVICE_BUFFERSIZE;
	if (FAILED(device->SetProperty(DIPROP_BUFFERSIZE, &propWord.diph)))
	{
		MSG("�o�b�t�@�E�T�C�Y�̐ݒ�Ɏ��s");
		return E_FAIL;
	}

	// ���͐���J�n
	connected = true;
	device->Acquire();
	return S_OK;
}

//�A�v���P�[�V�����Ŏg�p����R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��
BOOL CALLBACK DirectInputController::EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* objectInstance, VOID* context)
{
	DirectInputController* obj = (DirectInputController*)context;

	if (objectInstance->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE propRange;//���͈�
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