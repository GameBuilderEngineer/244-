#pragma once
#define _WIN32_DCOM
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <xaudio2.h>
#include "Base.h"
#include "Window.h"

#pragma comment(lib,"winmm.lib")

#define MAX_WAV 110 //WAVサウンド最大数

class Sound : public Base
{
public:
	HWND wnd;
	IXAudio2* xAudio2;
	IXAudio2MasteringVoice* masteringVoice;
	IXAudio2SourceVoice* sourceVoice[MAX_WAV];
	BYTE* wavBuffer[MAX_WAV];//波形データ（フォーマット等を含まない、純粋に波形データのみ）
	DWORD wavSize[MAX_WAV];//波形データのサイズ
	int soundIndex[11];//今回読み込む音の番号
	int soundCurrentIndex;//音の現在の再生番号

	Sound();
	~Sound();
	HRESULT initialize();
	int load(char* fileName);
	void PlaySound(int soundIndex, bool onLoop);
	void StopSound(int soundIndex);

};

