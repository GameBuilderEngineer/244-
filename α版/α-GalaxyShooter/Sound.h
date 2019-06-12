#pragma once
#define _WIN32_DCOM
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <xaudio2.h>
#include "Base.h"
#include "Window.h"

#pragma comment(lib,"winmm.lib")

#define MAX_WAV 110 //WAV�T�E���h�ő吔

class Sound : public Base
{
public:
	HWND wnd;
	IXAudio2* xAudio2;
	IXAudio2MasteringVoice* masteringVoice;
	IXAudio2SourceVoice* sourceVoice[MAX_WAV];
	BYTE* wavBuffer[MAX_WAV];//�g�`�f�[�^�i�t�H�[�}�b�g�����܂܂Ȃ��A�����ɔg�`�f�[�^�̂݁j
	DWORD wavSize[MAX_WAV];//�g�`�f�[�^�̃T�C�Y
	int soundIndex[11];//����ǂݍ��މ��̔ԍ�
	int soundCurrentIndex;//���̌��݂̍Đ��ԍ�

	Sound();
	~Sound();
	HRESULT initialize();
	int load(char* fileName);
	void PlaySound(int soundIndex, bool onLoop);
	void StopSound(int soundIndex);

};

