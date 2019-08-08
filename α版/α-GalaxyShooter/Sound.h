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
// NameSpace
// ���O���
//======================================================================================================================================================
namespace soundNS
{
	const int CONST_FADE_VALUE = (25);											//	�t�F�[�h�l
	const int CONST_VOLUME_MIN = (DSBVOLUME_MIN);								//	���ʍŏ��l
	const int CONST_VOLUME_MAX = (DSBVOLUME_MAX);								//	���ʍő�l

	enum TYPE
	{
		AGING,					//	�G�C�W���O
		BGM_CHARACTER_SELECT,	//	BGM�F�L�����N�^�[�Z���N�g
		BGM_CREDIT,				//	BGM�F�N���W�b�g
		BGM_GAME,				//	BGM�F�Q�[��
		BGM_RESULT,				//	BGM�F���U���g
		BGM_SPLASH,				//	BGM�F�X�v���b�V��
		BGM_TITLE,				//	BGM�F�^�C�g��
		BGM_TUTORIAL,			//	BGM�F�`���[�g���A��
		SE_ATTACK,				//	SE�F�U��
		SE_CANCEL,				//	SE�F�L�����Z��
		SE_DAMAGE_COVERED,		//	SE�F��_��
		SE_DECISION,			//	SE�F����
		SE_PAPER,				//	SE�F�y�[�p�[
		SE_SELECT,				//	SE�F�Z���N�g
		SE_SWITCH,				//	SE�F�X�C�b�`
		TYPE_MAX				//	�ő�l
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