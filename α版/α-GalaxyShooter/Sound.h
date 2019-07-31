//======================================================================================================================================================
// Document
//======================================================================================================================================================
// Sound.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/07/19
//======================================================================================================================================================
#pragma once
#include <dsound.h>
#pragma comment(lib,"dsound.lib")
//======================================================================================================================================================
// Macro
// �}�N��
//======================================================================================================================================================
#define SOUND_FILE_BGM_GAME ("BGM_Test_Ver_Game.wav")					//	�T�E���h�t�@�C��
#define SOUND_FILE_BGM_SPLASH_TITLE ("BGM_Test_Ver_Splash_Title.wav")	//	�T�E���h�t�@�C��
#define SOUND_FILE_SE_SELECT ("SE_Test_Ver_Select.wav")					//	�T�E���h�t�@�C��
#define SOUND_FILE_SE_DECISION ("SE_Test_Ver_Decision.wav")				//	�T�E���h�t�@�C��
#define SOUND_FILE_SE_CANCEL ("SE_Test_Ver_Cancel.wav")					//	�T�E���h�t�@�C��
#define SOUND_FILE_SE_DAMAGE_GIVE ("SE_Test_Ver_Damage_Give.wav")		//	�T�E���h�t�@�C��
#define SOUND_FILE_SE_DAMAGE_COVERED ("SE_Test_Ver_Damage_Covered.wav")	//	�T�E���h�t�@�C��
//======================================================================================================================================================
// NameSpace
// ���O���
//======================================================================================================================================================
namespace soundNS
{
	const int CONST_FADE_VALUE = (25);				//	�t�F�[�h�l
	const int CONST_VOLUME_MIN = (DSBVOLUME_MIN);	//	���ʍŏ��l
	const int CONST_VOLUME_MAX = (DSBVOLUME_MAX);	//	���ʍő�l

	enum TYPE
	{
		BGM_GAME,			//	BGM�F�Q�[��
		BGM_SPLASH_TITLE,	//	BGM�F�X�v���b�V�� - �^�C�g��
		SE_SELECT,			//	SE�F�Z���N�g
		SE_DECISION,		//	SE�F����
		SE_CANCEL,			//	SE�F�L�����Z��
		SE_DAMAGE_GIVE,		//	SE�F�^�_��
		SE_DAMAGE_COVERED,	//	SE�F��_��
		TYPE_MAX			//	�ő�l
	};
	enum METHOD
	{
		PLAY,		//	�Đ�
		LOOP,		//	���[�v�Đ�
		METHOD_MAX	//	�ő�l
	};
	enum FADE
	{
		NONE = (-1),	//	�t�F�[�h����
		FADE_IN,		//	�t�F�[�h�C��
		FADE_OUT,		//	�t�F�[�h�A�E�g
		FADE_MAX		//	�ő�l
	};
	enum VOLUME
	{
		LOWEST,		//	�ŏ�
		HIGHEST,	//	�ő�
		VOLUME_MAX	//	�ő�l
	};
}
//======================================================================================================================================================
// Structure
// �\����
//======================================================================================================================================================
struct SettingVolume
{
	int max = DSBVOLUME_MAX;	//	�ő剹��
	int min = DSBVOLUME_MIN;	//	�ŏ�����
};
struct SoundFlag
{
	bool fade[soundNS::TYPE::TYPE_MAX];		//	�t�F�[�h�t���O
	bool play[soundNS::TYPE::TYPE_MAX];		//	�Đ��t���O
	bool pause[soundNS::TYPE::TYPE_MAX];	//	�ꎞ��~�t���O
};
//======================================================================================================================================================
// Class
// �N���X
//======================================================================================================================================================
class Sound
{
private:
	IDirectSound8 *directSound;									//	�T�E���h�̃I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER8 soundBuffer[soundNS::TYPE::TYPE_MAX];	//	�T�E���h
	DWORD playPosition[soundNS::TYPE::TYPE_MAX];				//	�Đ��ʒu
	DWORD playMethod[soundNS::TYPE::TYPE_MAX];					//	�Đ����@
	SettingVolume settingVolume;								//	�ݒ艹��
	SoundFlag flag;												//	�t���O
	int fadeType[soundNS::TYPE::TYPE_MAX];						//	�t�F�[�h�^�C�v
	int volume[soundNS::TYPE::TYPE_MAX];						//	����
public:
	Sound(void);
	~Sound(void);
	HRESULT initialize(HWND _windowHandle);
	void update(void);
	void updateFadeIn(int _soundIndex);
	void updateFadeOut(int _soundIndex);
	LPDIRECTSOUNDBUFFER8 load(int _soundIndex);
	void play(int _soundIndex, int _playMethod);
	void pause(int _soundIndex);
	void stop(int _soundIndex);
	bool checkPlayFlag(int _soundIndex);
	void checkPlayFlagAll(void);
	void setPause(void);
	void setRePlay(void);
	void setFade(int _soundIndex, int _soundFadeType);
	void setVolume(int _soundIndex, int _soundVolumeType);
	void getPlayPosition(int _soundIndex);
};