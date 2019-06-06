#pragma once
#define WIN32_LEAN_AND_MEAN

#include "Base.h"
#include <xact3.h>

// audio.cpp�ɕK�v�ȃI�[�f�B�I�t�@�C��
// WAVE_BANK��.xwb�t�@�C���̏ꏊ�łȂ���΂Ȃ�܂���B
const char WAVE_BANK[] = "Win\\WavesBank.xwb";
// SOUND_BANK��.xsb�t�@�C���̏ꏊ�łȂ���΂Ȃ�܂���B
const char SOUND_BANK[] = "Win\\SoundsBank.xsb";

// �I�[�f�B�I�L���[
//const char ENGINE1[] = "engine1";
//const char BEEP1[] = "beep1";
//const char BEEP2[] = "beep2";
//const char BEEP3[] = "beep3";
//const char BEEP4[] = "beep4";
//const char HIT[] = "hit";
//const char CHEER[] = "cheer";
//const char COLLIDE[] = "collide";
//const char EXPLODE[] = "explode";
//const char ENGINE2[] = "engine2";
//const char TORPEDO_CRASH[] = "torpedoCrash";
//const char TORPEDO_FIRE[] = "torpedoFire";
//const char TORPEDO_HIT[] = "torpedoHit";
class Audio
{
//�v���p�e�B
private:
	IXACT3Engine * xactEngine;		// XACT�G���W���ւ̃|�C���^
	IXACT3WaveBank* waveBank;		// XACT�E�F�C�u�o���N�ւ̃|�C���^
	IXACT3SoundBank* soundBank;		// XACT�T�E���h�o���N�ւ̃|�C���^
	XACTINDEX cueI;					// XACT�T�E���h�C���f�b�N�X
	void* mapWaveBank;				// UnmapViewOfFile()���Ăяo���ăt�@�C�������
	void* soundBankData;
	bool coInitialized;				// CoInitializeEx�����������ꍇ�Atrue��ݒ�

public:
	// �R���X�g���N�^
	Audio();
	// �f�X�g���N�^
	virtual ~Audio();

	// �����o�֐�
	// �I�[�f�B�I�̏�����
	HRESULT initialize();

	// �T�E���h�G���W�������I�ȃ^�X�N�����s
	void run();

	// �L���[�Ŏw�肳�ꂽ�T�E���h���T�E���h�o���N����Đ�
	// �L���[�����݂��Ȃ��ꍇ�́A�G�T�E���h���Đ�����Ȃ������ŁA�G���[�͔������Ȃ�
	void playCue(const char cue[]);

	// �L���[�Ŏw�肳�ꂽ�T�E���h���T�E���h�o���N�Œ�~
	// �L���[�����݂��Ȃ��ꍇ�A�G���[�͔������Ȃ�
	void stopCue(const char cue[]);

};