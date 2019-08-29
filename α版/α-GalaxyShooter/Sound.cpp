//============================================================================================================================================
// Document
//============================================================================================================================================
// Sound.cpp
// HAL���� GP-12A-332 09 �T���v��
// 2019/07/19
//============================================================================================================================================
#include "Base.h"
#include "Sound.h"
//============================================================================================================================================
// Using Declaration
// using�錾
//============================================================================================================================================
using namespace soundNS;
//============================================================================================================================================
// Constructor
// �R���X�g���N�^
//============================================================================================================================================
Sound::Sound(void)
{
	directSound = NULL;
	settingVolume.max = DSBVOLUME_MAX;
	settingVolume.min = DSBVOLUME_MIN;

	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		volume[i] = DSBVOLUME_MAX;
		flag.play[i] = NULL;
		ZeroMemory(&soundBuffer[i], sizeof(LPDIRECTSOUNDBUFFER8));
	}

	return;
}
//============================================================================================================================================
// Destructor
// �f�X�g���N�^
//============================================================================================================================================
Sound::~Sound(void)
{
	//SAFE_DELETE(directSound);

	return;
}
//============================================================================================================================================
// initialize
// ������
//============================================================================================================================================
HRESULT Sound::initialize(HWND _windowHandle)
{
	// IDirectSound8�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectSoundCreate8	//	DirectSoundCreate8�֐��F"IDirectSound8"�C���^�[�t�F�C�X���T�|�[�g����I�u�W�F�N�g���쐬���A����������
	(
		NULL,						//	�T�E���h�f�o�C�X������GUID�̃A�h���X�FNULL = �V�X�e���S�̂̊���̃I�[�f�B�I�Đ��f�o�C�X���w��
		&directSound,				//	"IDirectSound8"�C���^�[�t�F�C�X�|�C���^���󂯎��ϐ��̃A�h���X
		NULL						//	�R���|�[�l���g�I�u�W�F�N�g���f��( COM )�W���ɑ΂��鐧��I�u�W�F�N�g��IUnknown�C���^�[�t�F�C�X�̃A�h���X�ւ̃|�C���^�F�C���^�[�t�F�C�X���W������Ă��Ȃ��ꍇ�ɂ�"NULL"( �ʏ�A�Ăяo������"NULL"��n�� )
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		MSG("�T�E���h�̍쐬�Ɏ��s���܂���");
	}

	// �������[�h��ݒ�( �t�H�A�O���E���h&��r�����[�h )
	if (FAILED(directSound->SetCooperativeLevel	//	SetCooperativeLevel�֐��F�A�v���P�[�V�����̍ŏ�ʓ�������肷��
	(
		_windowHandle,	//	�E�B���h�E�n���h��
		(DSSCL_EXCLUSIVE | DSSCL_PRIORITY)	//	������w��( DSSCL_PRIORITY�F�D�惌�x���ɐݒ肷�� )
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		MSG("�������[�h�̐ݒ�Ɏ��s���܂���");
	}

	// �T�E���h�̓ǂݍ���
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		soundBuffer[i] = load(i);
	}

	// ����I��
	return S_OK;
}
//============================================================================================================================================
// update
// �X�V
//============================================================================================================================================
void Sound::update(void)
{
	// �t�F�[�h����
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		if ((fadeType[i] != FADE::NONE) && (fadeType[i] == FADE::FADE_IN))
		{
			// �t�F�[�h�C��
			updateFadeIn(i);
		}
		else if ((fadeType[i] != FADE::NONE) && (fadeType[i] == FADE::FADE_OUT))
		{
			// �t�F�[�h�A�E�g
			updateFadeOut(i);
		}
	}

	return;
}
//============================================================================================================================================
// updateFadeIn
// �t�F�[�h�C���X�V
//============================================================================================================================================
void Sound::updateFadeIn(int _soundIndex)
{
	// �������^�[��
	if (!flag.fade[_soundIndex])
	{
		return;
	}

	if (settingVolume.max <= volume[_soundIndex])
	{
		// ���ʂ̐ݒ�
		soundBuffer[_soundIndex]->SetVolume(volume[_soundIndex]);
		return;
	}

	volume[_soundIndex] += CONST_FADE_VALUE;

	if (settingVolume.max > volume[_soundIndex])
	{
		// ���ʂ̐ݒ�
		soundBuffer[_soundIndex]->SetVolume(volume[_soundIndex]);
		return;
	}

	flag.fade[_soundIndex] = false;
	fadeType[_soundIndex] = FADE::NONE;
	volume[_soundIndex] = settingVolume.max;

	//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);

	// ���ʂ̐ݒ�
	soundBuffer[_soundIndex]->SetVolume(volume[_soundIndex]);

	return;
}
//============================================================================================================================================
// updateFadeOut
// �t�F�[�h�A�E�g�X�V
//============================================================================================================================================
void Sound::updateFadeOut(int _soundIndex)
{
	// �������^�[��
	if (!flag.fade[_soundIndex])
	{
		return;
	}

	if (settingVolume.min >= volume[_soundIndex])
	{
		// ���ʂ̐ݒ�
		soundBuffer[_soundIndex]->SetVolume(volume[_soundIndex]);
		return;
	}

	volume[_soundIndex] -= CONST_FADE_VALUE;

	if (settingVolume.min < volume[_soundIndex])
	{
		// ���ʂ̐ݒ�
		soundBuffer[_soundIndex]->SetVolume(volume[_soundIndex]);
		return;
	}

	//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);
	flag.fade[_soundIndex] = false;
	fadeType[_soundIndex] = FADE::NONE;
	volume[_soundIndex] = settingVolume.min;
	stop(_soundIndex);

	// ���ʂ̐ݒ�
	soundBuffer[_soundIndex]->SetVolume(volume[_soundIndex]);

	return;
}
//============================================================================================================================================
// load
// �T�E���h�̓ǂݍ���
//============================================================================================================================================
LPDIRECTSOUNDBUFFER8 Sound::load(int _soundIndex)
{
	// �ϐ��錾�F������ / �T�E���h�ǂݍ���
	const char *Sound_File[] =	//	�T�E���h�t�@�C��
	{
		"Aging.wav",
		"BGM_Character_Select.wav",
		"BGM_Credit.wav",
		"BGM_Game.wav",
		"BGM_Operation.wav",
		"BGM_Result.wav",
		"BGM_Splash.wav",
		"BGM_Title.wav",
		"BGM_Tutorial.wav",
		"SE_Attack.wav",
		"SE_Cancel.wav",
		"SE_Chingin.wav",
		"SE_Count.wav",
		"SE_Cut_Memory_Line.wav",
		"SE_Decision.wav",
		"SE_Destruction_Wasuremono.wav",
		"SE_Down.wav",
		"SE_Game_Start.wav",
		"SE_Game_Time_Up.wav",
		"SE_Hit.wav",
		"SE_Installation_Memory_Pile.wav",
		"SE_Jump.wav",
		"SE_Landing.wav",
		"SE_Paper.wav",
		"SE_Pause.wav",
		"SE_Ready.wav",
		"SE_Recursion.wav",
		"SE_Revival.wav",
		"SE_Revival_Point.wav",
		"SE_Select.wav",
		"SE_Shock_Wave.wav",
	};

	// �ϐ��錾�F������
	// MMIO�F�}���`���f�B�A�C���v�b�g/�A�E�g�v�b�g( �}���`���f�B�AI/O( ���o�� ) )�̗���
	// .wav�t�@�C���́A���t( RIFF )�Ƃ����t�H�[�}�b�g�`���ɏ]���Ă���( RIFF�FResource InterChange File Format )
	// ����̓`�����N( Chunk�F�� )�ƌĂ΂��f�[�^�̈�܂Ƃ܂����ׂĉ��̏��𐮗����Ă���
	LPDIRECTSOUNDBUFFER Sound_Base_Buffer = NULL;	//	�����f�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 Sound_Buffer = NULL;		//	�����f�[�^�̃o�b�t�@
	DSBUFFERDESC Sound_Buffer_Config;				//	�o�b�t�@�̐ݒ�\����
	HMMIO MultiMedia_Input_Output_Handle = NULL;	//	�}���`���f�B�AI/O�n���h��
	MMIOINFO MultiMedia_Input_Output_Data;			//	�}���`���f�B�AI/O�̃f�[�^�\����
	MMRESULT MultiMedia_Input_Output_Result = NULL;	//	�}���`���f�B�A�������ʂ��i�[����ϐ�
	MMCKINFO Riff_Chunk;							//	�`�����N�f�[�^�̍\����
	MMCKINFO Format_Chunk;							//	�`�����N�f�[�^�̍\����
	MMCKINFO Data_Chunk;							//	�`�����N�f�[�^�̍\����
	DWORD Data_Size = NULL;							//	�f�[�^�̃T�C�Y���i�[����ϐ�
	WAVEFORMATEX Pulse_Code_Modulation;				//	�����f�[�^�̃t�H�[�}�b�g�\����
	LPVOID Secondary_Buffer = NULL;					//	�Z�J���_���o�b�t�@�̃f�[�^�̏������ݐ�A�h���X
	DWORD Secondary_Buffer_Size = NULL;				//	�Z�J���_���o�b�t�@�̃T�C�Y

	// �P�D�}���`���f�B�AI/O�n���h�������ɉ����t�@�C�����J��
	memset	//	memset�֐��F�w�肳�ꂽ�|�C���^���w���I�u�W�F�N�g�̐擪����A�w�肳�ꂽ�o�C�g�����ɁA�w�肵�������f�[�^���������ނ͂��炫������( �|�C���^���w���Ă��郁��������e"1"�o�C�g���Ƃɕ������Z�b�g���� )
	(
		&MultiMedia_Input_Output_Data,	//	�Z�b�g��̃������u���b�N�A�h���X ( �Z�b�g����̈�( �|�C���^ / ������ )
		0,								//	�Z�b�g���̃������u���b�N�A�h���X ( �Z�b�g����l )
		sizeof(MMIOINFO)				//	�Z�b�g������A�Z�b�g��ɃZ�b�g���郁�����̃u���b�N�T�C�Y���w��	( �Z�b�g����T�C�Y )
	);
	MultiMedia_Input_Output_Handle = mmioOpen	//	mmioOpen�֐��F���o�͂̃o�b�t�@�����O���������邩�A���o�͂��o�b�t�@�����O���ăt�@�C�����J���B�J�����Ƃ��ł���t�@�C���́A�W���t�@�C���E�������t�@�C���E�܂��̓J�X�^���̊i�[�V�X�e��
	(
		(LPSTR)Sound_File[_soundIndex],	//	�J���t�@�C���̃t�@�C������������������̃A�h���X���w��
		&MultiMedia_Input_Output_Data,	//	mmioOpen�֐��Ŏg����ǉ��̃p�����[�^���������AMMIOINFO�\���̂̃A�h���X���w��
		MMIO_READ						//	�I�[�v������̂��߂̃t���O���w��( MMIO_READ�F�t�@�C����ǂݎ���p�Ƃ��ĊJ�� )
	);
	if (!MultiMedia_Input_Output_Handle)
	{
		// �G���[���b�Z�[�W�̏o��
		MSG("�T�E���h�t�@�C���̃C���v�b�g�Ɏ��s���܂���");
	}

	// �Q�D�t�@�C���̉��( 1 ) RIFF�`�����N�̌���
	// �������[�h���w��
	Riff_Chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');	//	mmioFOURCC�֐��F�S�̕������S�����̃R�[�h�ɕϊ����܂�( .wav�t�@�C����"FOURCC"�Ƃ����S�����̕�����Ń`�����N�̎�ނ���ʂ��Ă��� )
															//	mmioDescend�֐��͊�{�I�ɂ��̕�������Q�Ƃ��āA��������`�����N�𔻒f���邽�߁A�����ݒ肵�Ă����K�v������
	// �L�[���[�h��ΏۂɌ���
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend�֐��FmmioOpen�֐��ŊJ����RIFF�t�@�C���̃`�����N�ɐi������B�܂��A�w�肳�ꂽ�`�����N���������邱�Ƃ��ł���
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���RIFF�t�@�C���̃t�@�C���n���h�����w��
		&Riff_Chunk,					//	�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��
		NULL,							//	��������`�����N�̐e�����ʂ���F�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��B�e�`�����N���w�肳��Ă��Ȃ��ꍇ�A���̃p�����[�^��"NULL"�ɐݒ肷��
		MMIO_FINDRIFF					//	�����t���O���w��( MMIO_FINDRIFF�F�`�����N���ʎq��"RIFF"�ŁA�w�肳�ꂽ�t�H�[���^�C�v�̃`�����N���������� )
	);
	// �����Ɏ��s������ُ�I��
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		MSG("�`�����N�̌����Ɏ��s���܂���");
	}

	// �R�D�t�@�C���̉��( 2 ) �t�H�[�}�b�g�`�����N�̌���
	// �������[�h���w��
	Format_Chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');	//	mmioFOURCC�֐��F�S�̕������S�����̃R�[�h�ɕϊ����܂�( .wav�t�@�C����"FOURCC"�Ƃ����S�����̕�����Ń`�����N�̎�ނ���ʂ��Ă��� )
														//	mmioDescend�֐��͊�{�I�ɂ��̕�������Q�Ƃ��āA��������`�����N�𔻒f���邽�߁A�����ݒ肵�Ă����K�v������
	// �L�[���[�h��ΏۂɌ���
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend�֐��FmmioOpen�֐��ŊJ�����t�H�[�}�b�g�t�@�C���̃`�����N�ɐi������B�܂��A�w�肳�ꂽ�`�����N���������邱�Ƃ��ł���
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���t�H�[�}�b�g�t�@�C���̃t�@�C���n���h�����w��
		&Format_Chunk,					//	�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��
		&Riff_Chunk,					//	��������`�����N�̐e�����ʂ���F�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��B�e�`�����N���w�肳��Ă��Ȃ��ꍇ�A���̃p�����[�^��"NULL"�ɐݒ肷��
		MMIO_FINDCHUNK					//	�����t���O���w��( MMIO_FINDCHUNK�F�w�肳�ꂽ�`�����N���ʎq�̃`�����N���������܂� )
	);
	// �����Ɏ��s������ُ�I��
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		MSG("�`�����N�̌����Ɏ��s���܂���");
	}

	// �����������ɓǂݍ��ݏ���
	Data_Size = mmioRead	//	mmioRead�֐��FmmioOpen�֐��ŊJ�����t�@�C������A�w�肳�ꂽ�o�C�g����ǂݎ��
	(
		MultiMedia_Input_Output_Handle,	//	�ǂݎ��t�@�C���̃t�@�C���n���h�����w��
		(HPSTR)&Pulse_Code_Modulation,	//	�t�@�C������ǂݎ��ꂽ�f�[�^������o�b�t�@�̃A�h���X���w��
		Format_Chunk.cksize				//	�t�@�C������ǂݎ��o�C�g�����w��
	);
	// �ǂݍ��݂Ɏ��s������ُ�I��
	if (Data_Size != Format_Chunk.cksize)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		MSG("�T�E���h�t�@�C���n���h���̃��[�h�Ɏ��s���܂���");
	}

	mmioAscend	//	mmioAscend�֐��FmmioDescend�֐��Ői�������A�܂���mmioCreateChunk�֐��ō쐬����RIFF�t�@�C���̃`�����N����ޏo����
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���RIFF�t�@�C���̃t�@�C���n���h�����w��
		&Format_Chunk,					//	mmioDescend�֐��܂��́AmmioCreateChunk�֐��Œl���������܂�Ă���A�v���P�[�V������`��MMCKINFO�\���̂̃A�h���X���w��
		0								//	�\�񂳂�Ă���̂ŁA"0"���w��
	);

	// �S�D�t�@�C���̉��( 3 ) �f�[�^�`�����N�̌���
	// �������[�h���w��
	Data_Chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');	//	mmioFOURCC�֐��F�S�̕������S�����̃R�[�h�ɕϊ����܂�( .wav�t�@�C����"FOURCC"�Ƃ����S�����̕�����Ń`�����N�̎�ނ���ʂ��Ă��� )
														//	mmioDescend�֐��͊�{�I�ɂ��̕�������Q�Ƃ��āA��������`�����N�𔻒f���邽�߁A�����ݒ肵�Ă����K�v������
	MultiMedia_Input_Output_Result = mmioDescend		//	mmioDescend�֐��FmmioOpen�֐��ŊJ�����t�H�[�}�b�g�t�@�C���̃`�����N�ɐi������B�܂��A�w�肳�ꂽ�`�����N���������邱�Ƃ��ł���
	(
		MultiMedia_Input_Output_Handle,	//	�J���Ă���t�H�[�}�b�g�t�@�C���̃t�@�C���n���h�����w��
		&Data_Chunk,					//	�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��
		&Riff_Chunk,					//	��������`�����N�̐e�����ʂ���F�A�v���P�[�V������`��"MMCKINFO"�\���̂̃A�h���X���w��B�e�`�����N���w�肳��Ă��Ȃ��ꍇ�A���̃p�����[�^��"NULL"�ɐݒ肷��
		MMIO_FINDCHUNK					//	�����t���O���w��( MMIO_FINDCHUNK�F�w�肳�ꂽ�`�����N���ʎq�̃`�����N���������܂� )
	);
	// �����Ɏ��s������ُ�I��
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose�֐��FmmioOpen�֐��ŊJ�����t�@�C�������
		(
			MultiMedia_Input_Output_Handle,	//	����t�@�C���̃t�@�C���n���h�����w��
			0								//	�N���[�Y����̂��߂̃t���O���w��
		);
		// �G���[���b�Z�[�W�̏o��
		MSG("�`�����N�̌����Ɏ��s���܂���");
	}

	// �T�D�f�[�^�̓ǂݍ���
	// �|�C���^�ϐ��錾�F������
	char *Data = new char[Data_Chunk.cksize];	//	�K�v�ȑ傫���̗̈���m�ۂ���

	Data_Size = mmioRead	//	mmioRead�֐��FmmioOpen�֐��ŊJ�����t�@�C������A�w�肳�ꂽ�o�C�g����ǂݎ��
	(
		MultiMedia_Input_Output_Handle,	//	�ǂݎ��t�@�C���̃t�@�C���n���h�����w��
		(HPSTR)Data,					//	�t�@�C������ǂݎ��ꂽ�f�[�^������o�b�t�@�̃A�h���X���w��
		Data_Chunk.cksize				//	�t�@�C������ǂݎ��o�C�g�����w��
	);
	// �f�[�^�̓ǂݍ��݂Ɏ��s������ُ�I��
	if (Data_Size != Data_Chunk.cksize)
	{
		// �폜
		delete[] Data;

		// �G���[���b�Z�[�W�̏o��
		MSG("�T�E���h�t�@�C���n���h���̃��[�h�Ɏ��s���܂���");
	}

	// �U�D�����f�[�^��ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&Sound_Buffer_Config, sizeof(DSBUFFERDESC));	//	ZeroMemory�}�N���F�w�肵���ϐ��̒��g��"0"�N���A����}�N��

	// �e��ݒ�
	// DSBUFFERDESC�F�V�����o�b�t�@�I�u�W�F�N�g�̓������L�q����
	Sound_Buffer_Config.dwSize = sizeof(DSBUFFERDESC);	//	�\���̂̃T�C�Y( �P�ʁFbyte )���w��F�\���̂��g���O�ɁA���̃����o�����������Ȃ���΂Ȃ�Ȃ�
	Sound_Buffer_Config.dwFlags = (						//	�o�b�t�@�̔\�͂������t���O
		DSBCAPS_GETCURRENTPOSITION2 |
		DSBCAPS_GLOBALFOCUS |
		DSBCAPS_LOCDEFER |
		DSBCAPS_CTRLFX |
		DSBCAPS_CTRLVOLUME);
	Sound_Buffer_Config.dwBufferBytes = Data_Size;				//	�V�����o�b�t�@�̃T�C�Y( �P�ʁFbyte )���w��
	Sound_Buffer_Config.lpwfxFormat = &Pulse_Code_Modulation;	//	�o�b�t�@�̃E�F�[�u�t�H�[���t�H�[�}�b�g���w��

	// �����o�b�t�@���쐬
	if (FAILED(directSound->CreateSoundBuffer	//	CreateSoundBuffer�֐��F�T���v�����O�I�[�f�B�I���Ǘ����邽�߂ɁA�T�E���h�o�b�t�@�I�u�W�F�N�g���쐬����
	(
		&Sound_Buffer_Config,	//	�쐬����T�E���h�o�b�t�@���L�q����Ă���"DSBUFFERDESC"�\���̂̃A�h���X
		&Sound_Base_Buffer,		//	�V�����o�b�t�@�I�u�W�F�N�g��"IDirectSoundBuffer"�C���^�[�t�F�C�X���󂯎��ϐ��̃A�h���X
		NULL					//	�R���|�[�l���g�I�u�W�F�N�g���f��( COM )�W���ɑ΂��鐧��I�u�W�F�N�g��IUnknown�C���^�[�t�F�C�X�̃A�h���X�ւ̃|�C���^�B�C���^�[�t�F�C�X���W������Ă��Ȃ��ꍇ�ɂ�"NULL" // �ʏ�A�Ăяo������"NULL"��n��
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		MSG("�T�E���h�o�b�t�@�̍쐬�Ɏ��s���܂���");
	}

	// �T�E���h�o�b�t�@�̎��o��
	if (FAILED(Sound_Base_Buffer->QueryInterface	//	QueryInterface�֐��F�I�u�W�F�N�g������̃R���|�[�l���g�I�u�W�F�N�g���f��( COM )�C���^�[�t�F�C�X���T�|�[�g���Ă��邩�ǂ����𔻕ʂ���c�C���^�[�t�F�C�X���T�|�[�g����Ă���ꍇ�A�V�X�e���̓I�u�W�F�N�g�̎Q�ƃJ�E���g�𑝂₵�A�A�v���P�[�V�����͂��̃C���^�[�t�F�C�X�������Ɏg����
	(
		IID_IDirectSoundBuffer8,	//	�v������C���^�[�t�F�C�X�̎Q�Ǝ��ʎq
		(LPVOID*)&Sound_Buffer		//	�ړI�̃C���^�[�t�F�C�X���T�|�[�g����Ă���ꍇ�ɁA�C���^�[�t�F�C�X�ւ̃|�C���^���i�[�����|�C���^�ϐ��̃A�h���X
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		MSG("�T�E���h�C���^�[�t�F�C�X�̎擾�Ɏ��s���܂���");
	}

	// �T�E���h�o�b�t�@���o����A�����o�b�t�@���폜
	SAFE_RELEASE(Sound_Base_Buffer);

	// �V�D�p�ӂ����Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �������݉\�ɂ��邽�߁A�o�b�t�@�����b�N
	if (FAILED(Sound_Buffer->Lock	//	Lock�֐��F�f�b�h���b�N�Ȃ��ł��ׂĂ̈��������b�N����
	(
		0,
		0,
		&Secondary_Buffer,
		&Secondary_Buffer_Size,
		NULL,
		NULL,
		DSBLOCK_ENTIREBUFFER
	)))
	{
		// �G���[���b�Z�[�W�̏o��
		MSG("�T�E���h�o�b�t�@�̃��b�N�Ɏ��s���܂���");
	}

	// �f�[�^�̓]��
	memcpy	//	memcpy�֐��F��2����( �R�s�[�� )����A��3����( �w��T�C�Y )���A��1����( �R�s�[�� )�փ��������R�s�[����
	(
		Secondary_Buffer,		//	�R�s�[��̃������u���b�N�A�h���X
		Data,					//	�R�s�[���̃������u���b�N�A�h���X
		Secondary_Buffer_Size	//	�R�s�[������A�R�s�[��ɃR�s�[���郁�����̃u���b�N�T�C�Y���w��
	);

	// ���̓ǂݍ��ݗ̈���폜
	delete[] Data;

	// �o�b�t�@�̃��b�N������
	Sound_Buffer->Unlock	//	Unlock�֐��F���R�[�h�̃��b�N����������
	(
		Secondary_Buffer,
		Secondary_Buffer_Size,
		0,
		0
	);

	// �Z�J���_���o�b�t�@��߂�l�Ƃ��ĕԂ�
	return Sound_Buffer;
}
//============================================================================================================================================
// play
// �T�E���h�̍Đ�
//============================================================================================================================================
void Sound::play(int _soundIndex, int _playMethod)
{
	// Sound_Flag�F"1" = ( E_DS8_FLAG_LOOP )�Ȃ烋�[�v�Đ�
	if (!flag.pause[_soundIndex])
	{
		soundBuffer[_soundIndex]->SetCurrentPosition(0);
		soundBuffer[_soundIndex]->Play(0, 0, _playMethod);
	}
	else
	{
		soundBuffer[_soundIndex]->SetCurrentPosition(playPosition[_soundIndex]);
		soundBuffer[_soundIndex]->Play(0, 0, _playMethod);
	}

	playMethod[_soundIndex] = _playMethod;
	flag.play[_soundIndex] = true;
	flag.pause[_soundIndex] = false;

	return;
}
//============================================================================================================================================
// pause
// �T�E���h�̈ꎞ��~
//============================================================================================================================================
void Sound::pause(int _soundIndex)
{
	if (flag.play[_soundIndex])
	{
		flag.pause[_soundIndex] = true;
		getPlayPosition(_soundIndex);
	}
	else
	{
		flag.pause[_soundIndex] = false;
	}

	return;
}
//============================================================================================================================================
// stop
// �T�E���h�̒�~
//============================================================================================================================================
void Sound::stop(int _soundIndex)
{
	// �ϐ��錾�F������
	DWORD Status = NULL;	//	�X�e�[�^�X

	soundBuffer[_soundIndex]->GetStatus(&Status);	//	GetStatus�֐��F�w�肳�ꂽCFile�I�u�W�F�N�g�C���X�^���X�A�܂��͎w�肳�ꂽ�t�@�C���p�X�Ɋ֘A�����X�e�[�^�X�����擾���܂�

	// �T�E���h�Đ���
	if (Status & DSBSTATUS_PLAYING)
	{
		soundBuffer[_soundIndex]->Stop();	//	Stop�֐��F���݂̕\�����̎��s�𒆒f����( ���e�Ƃ��ẮA"Pause"�̂悤�Ȃ��� )
	}

	return;
}
//============================================================================================================================================
// checkPlayFlag
// �T�E���h�̍Đ���Ԃ𒲍�
//============================================================================================================================================
bool Sound::checkPlayFlag(int _soundIndex)
{
	// �ϐ��錾�F������
	DWORD Status = NULL;	//	�X�e�[�^�X

	soundBuffer[_soundIndex]->GetStatus(&Status);	//	GetStatus�֐��F�w�肳�ꂽCFile�I�u�W�F�N�g�C���X�^���X�A�܂��͎w�肳�ꂽ�t�@�C���p�X�Ɋ֘A�����X�e�[�^�X�����擾���܂�

	// �T�E���h�Đ���
	if (Status & DSBSTATUS_PLAYING)
	{
		return true;
	}

	return false;
}
//============================================================================================================================================
// checkPlayFlagAll
// �S�ẴT�E���h�̍Đ���Ԃ𒲍�
//============================================================================================================================================
void Sound::checkPlayFlagAll(void)
{
	// �ϐ��錾�F������
	DWORD Status = NULL;	//	�X�e�[�^�X

	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		soundBuffer[i]->GetStatus(&Status);	//	GetStatus�֐��F�w�肳�ꂽCFile�I�u�W�F�N�g�C���X�^���X�A�܂��͎w�肳�ꂽ�t�@�C���p�X�Ɋ֘A�����X�e�[�^�X�����擾���܂�

		if (Status & DSBSTATUS_PLAYING)
		{
			flag.play[i] = true;
		}
		else
		{
			flag.play[i] = false;
		}

		Status = NULL;
	}

	return;
}
//============================================================================================================================================
// setPause
// �T�E���h�̈ꎞ��~�ݒ�
//============================================================================================================================================
void Sound::setPause(void)
{
	//for (int i = 0; i < SOUND_MAX; i++)
	//{
	//	switch (i)
	//	{
	//	case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
	//		pauseSound(i);
	//		stopSound(i);
	//		continue;
	//		break;
	//	default:
	//		continue;
	//		break;
	//	}
	//}

	return;
}
//============================================================================================================================================
// setRePlay
// �T�E���h�̃��v���C�ݒ�
//============================================================================================================================================
void Sound::setRePlay(void)
{
	//for (int i = 0; i < SOUND_MAX; i++)
	//{
	//	// �����R���e�B�j���[
	//	if (!pauseFlag[i])
	//	{
	//		continue;
	//	}

	//	switch (i)
	//	{
	//	case SOUND_TYPE_BACKGROUND_MUSIC_002_GAME_PARTICLE:
	//		playSound(i, playMethod[i]);
	//		continue;
	//		break;
	//	default:
	//		continue;
	//		break;
	//	}
	//}

	return;
}
//============================================================================================================================================
// setFade
// �T�E���h�̃t�F�[�h�ݒ�
//============================================================================================================================================
void Sound::setFade(int _soundIndex, int _soundFadeType)
{
	if (_soundFadeType == FADE::NONE)
	{
		//Set_Switch(SWITCH_TYPE_SOUND_FADE, false);
	}
	else
	{
		//Set_Switch(SWITCH_TYPE_SOUND_FADE, true);
	}

	fadeType[_soundIndex] = _soundFadeType;
	flag.fade[_soundIndex] = true;

	return;
}
//============================================================================================================================================
// setVolume
// �T�E���h�̉��ʐݒ�
//============================================================================================================================================
void Sound::setVolume(int _soundIndex, int _soundVolumeType)
{
	setFade(_soundIndex, FADE::NONE);

	switch (_soundVolumeType)
	{
	case VOLUME::LOWEST:
		volume[_soundIndex] = settingVolume.min;
		break;
	case VOLUME::HIGHEST:
		volume[_soundIndex] = settingVolume.max;
		break;
	default:
		break;
	}

	// ���ʂ̐ݒ�
	soundBuffer[_soundIndex]->SetVolume(volume[_soundIndex]);

	return;
}
//============================================================================================================================================
// getPlayPosition
// �T�E���h�̍Đ��ʒu���擾
//============================================================================================================================================
void Sound::getPlayPosition(int _soundIndex)
{
	soundBuffer[_soundIndex]->GetCurrentPosition(&playPosition[_soundIndex], NULL);

	return;
}