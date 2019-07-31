//#pragma once
//#define WIN32_LEAN_AND_MEAN
//
//#include "Base.h"
//#include <xact3.h>
//
//// audio.cpp�ɕK�v�ȃI�[�f�B�I�t�@�C��
//// WAVE_BANK��.xwb�t�@�C���̏ꏊ�łȂ���΂Ȃ�܂���B
//const char WAVE_BANK[] = "Win\\WavesBank.xwb";
//// SOUND_BANK��.xsb�t�@�C���̏ꏊ�łȂ���΂Ȃ�܂���B
//const char SOUND_BANK[] = "Win\\SoundsBank.xsb";
//
//// aiueo
//
//// �I�[�f�B�I�L���[
//namespace audioCue {
//	const char SPLASH_BGM[]						= "splashBGM";						//�X�v���b�V���V�[���FBGM
//	const char TITLE_BGM[]						= "titleBGM";						//�^�C�g���V�[���FBGM
//	const char TITLE_SELECT_SE[]				= "titleSelectSE";					//�^�C�g���V�[���F�I����
//	const char TITLE_DECISION_SE[]				= "titleDecisionSE";				//�^�C�g���V�[���F���艹
//	const char TITLE_CANCEL_SE[]				= "titleCancelSE";					//�^�C�g���V�[���F�L�����Z����
//	const char GAME_START_COUNTDOWN_SE[]		= "gameStartCountDownSE";			//�Q�[���V�[���F�Q�[���J�n�J�E���g�_�E�����ʉ�
//	const char GAME_START_SE[]					= "gameStartSE";					//�Q�[���V�[���F�Q�[���J�n���ʉ�
//	const char GAME_END_COUNTDOWN_SE[]			= "gameEndCountDownSE";				//�Q�[���V�[���F�Q�[���I���J�E���g�_�E�����ʉ�
//	const char GAME_END_SE[]					= "gameEndSE";						//�Q�[���V�[���F�Q�[���I�����ʉ�
//	const char GAME_BGM_001[]					= "gameBGM001";						//�Q�[���V�[���FBGM001
//	const char GAME_BGM_002[]					= "gameBGM002";						//�Q�[���V�[���FBGM002
//	const char GAME_BGM_003[]					= "gameBGM003";						//�Q�[���V�[���FBGM003
//	const char GAME_PAUSE_SE[]					= "gamePauseSE";					//�Q�[���V�[���F�|�[�Y���ʉ�
//	const char SELECT_CHARACTER_BGM[]			= "selectCharacterBGM";				//�L�����N�^�[�I���V�[���FBGM
//	const char SELECT_CHARACTER_SELECT_SE[]		= "selectCharacterSelectSE";		//�L�����N�^�[�I���V�[���F�I�����ʉ�
//	const char SELECT_CHARACTER_DECISION_SE[]	= "selectCharacterDecisionSE";		//�L�����N�^�[�I���V�[���F������ʉ�
//	const char SELECT_CHARACTER_CANCEL_SE[]		= "selectCharacterCancelSE";		//�L�����N�^�[�I���V�[���F�L�����Z�����ʉ�
//	const char TUTORIAL_BGM[]					= "tutorialBGM";					//�`���[�g���A���V�[���FBGM
//	const char OPERATION_SELECT_SE[]			= "operationSelectSE";				//������@�����V�[���F�ؑ֌��ʉ�
//	const char RESULT_BGM[]						= "resultBGM";						//���U���g�V�[���FBGM
//	const char WALK_SE[]						= "walkSE";							//�������ʉ�
//	const char DASH_SE[]						= "dashSE";							//�_�b�V�����ʉ�
//	const char JUMP_SE[]						= "jumpSE";							//�W�����v���ʉ�
//	const char BULLET_FIRE_SE[]					= "bulletFireSE";					//�e���ˌ��ʉ�
//	const char BULLET_HIT_SE[]					= "bulletHitSE";					//�e�q�b�g���ʉ�
//	const char WAGE_GENERATE_SE[]				= "wageGenerateSE";					//�����������ʉ�
//	const char WAGE_GET_SE[]					= "wageGetSE";						//�����擾���ʉ�
//	const char SHOCK_WAVE_GENERATE_SE[]			= "shockWaveGenerateSE";			//�Ռ��g�������ʉ�
//	const char SHOCK_WAVE_HIT_SE[]				= "shockWaveHitSE";					//�Ռ��g�q�b�g���ʉ�
//	const char MEMORY_PILE_INSTALLATION_SE[]	= "memoryPileInstallationSE";		//�������[�p�C���ݒu���ʉ�
//	const char MEMORY_LINE_CUTTING_SE[]			= "memoryLineCuttingSE";			//�������[���C���ؒf���ʉ�
//	const char RECURSION_GENERATE_SE[]			= "recursionGenerateSE";			//���J�[�W�����������ʉ�
//	const char DOWN_REVIVAL_QTE_SE[]			= "downRevivalQuickTimeEventSE";	//�_�E������QuickTimeEvent���ʉ�
//	const char DOWN_REVIVAL_SE[]				= "downRevivalSE";					//�_�E���������ʉ�
//}
//
//class Audio
//{
////�v���p�e�B
//private:
//	IXACT3Engine * xactEngine;		// XACT�G���W���ւ̃|�C���^
//	IXACT3WaveBank* waveBank;		// XACT�E�F�C�u�o���N�ւ̃|�C���^
//	IXACT3SoundBank* soundBank;		// XACT�T�E���h�o���N�ւ̃|�C���^
//	XACTINDEX cueI;					// XACT�T�E���h�C���f�b�N�X
//	void* mapWaveBank;				// UnmapViewOfFile()���Ăяo���ăt�@�C�������
//	void* soundBankData;
//	bool coInitialized;				// CoInitializeEx�����������ꍇ�Atrue��ݒ�
//
//public:
//	// �R���X�g���N�^
//	Audio();
//	// �f�X�g���N�^
//	virtual ~Audio();
//
//	// �����o�֐�
//	// �I�[�f�B�I�̏�����
//	HRESULT initialize();
//
//	// �T�E���h�G���W�������I�ȃ^�X�N�����s
//	void run();
//
//	// �L���[�Ŏw�肳�ꂽ�T�E���h���T�E���h�o���N����Đ�
//	// �L���[�����݂��Ȃ��ꍇ�́A�G�T�E���h���Đ�����Ȃ������ŁA�G���[�͔������Ȃ�
//	void playCue(const char cue[]);
//
//	// �L���[�Ŏw�肳�ꂽ�T�E���h���T�E���h�o���N�Œ�~
//	// �L���[�����݂��Ȃ��ꍇ�A�G���[�͔������Ȃ�
//	void stopCue(const char cue[]);
//
//};