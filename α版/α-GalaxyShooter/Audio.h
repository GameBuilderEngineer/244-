#pragma once
#define WIN32_LEAN_AND_MEAN

#include "Base.h"
#include <xact3.h>

// audio.cppに必要なオーディオファイル
// WAVE_BANKは.xwbファイルの場所でなければなりません。
const char WAVE_BANK[] = "Win\\WavesBank.xwb";
// SOUND_BANKは.xsbファイルの場所でなければなりません。
const char SOUND_BANK[] = "Win\\SoundsBank.xsb";

// aiueo

// オーディオキュー
namespace audioCue {
	const char SPLASH_BGM[]						= "splashBGM";						//スプラッシュシーン：BGM
	const char TITLE_BGM[]						= "titleBGM";						//タイトルシーン：BGM
	const char TITLE_SELECT_SE[]				= "titleSelectSE";					//タイトルシーン：選択音
	const char TITLE_DECISION_SE[]				= "titleDecisionSE";				//タイトルシーン：決定音
	const char TITLE_CANCEL_SE[]				= "titleCancelSE";					//タイトルシーン：キャンセル音
	const char GAME_START_COUNTDOWN_SE[]		= "gameStartCountDownSE";			//ゲームシーン：ゲーム開始カウントダウン効果音
	const char GAME_START_SE[]					= "gameStartSE";					//ゲームシーン：ゲーム開始効果音
	const char GAME_END_COUNTDOWN_SE[]			= "gameEndCountDownSE";				//ゲームシーン：ゲーム終了カウントダウン効果音
	const char GAME_END_SE[]					= "gameEndSE";						//ゲームシーン：ゲーム終了効果音
	const char GAME_BGM_001[]					= "gameBGM001";						//ゲームシーン：BGM001
	const char GAME_BGM_002[]					= "gameBGM002";						//ゲームシーン：BGM002
	const char GAME_BGM_003[]					= "gameBGM003";						//ゲームシーン：BGM003
	const char GAME_PAUSE_SE[]					= "gamePauseSE";					//ゲームシーン：ポーズ効果音
	const char SELECT_CHARACTER_BGM[]			= "selectCharacterBGM";				//キャラクター選択シーン：BGM
	const char SELECT_CHARACTER_SELECT_SE[]		= "selectCharacterSelectSE";		//キャラクター選択シーン：選択効果音
	const char SELECT_CHARACTER_DECISION_SE[]	= "selectCharacterDecisionSE";		//キャラクター選択シーン：決定効果音
	const char SELECT_CHARACTER_CANCEL_SE[]		= "selectCharacterCancelSE";		//キャラクター選択シーン：キャンセル効果音
	const char TUTORIAL_BGM[]					= "tutorialBGM";					//チュートリアルシーン：BGM
	const char OPERATION_SELECT_SE[]			= "operationSelectSE";				//操作方法説明シーン：切替効果音
	const char RESULT_BGM[]						= "resultBGM";						//リザルトシーン：BGM
	const char WALK_SE[]						= "walkSE";							//歩き効果音
	const char DASH_SE[]						= "dashSE";							//ダッシュ効果音
	const char JUMP_SE[]						= "jumpSE";							//ジャンプ効果音
	const char BULLET_FIRE_SE[]					= "bulletFireSE";					//弾発射効果音
	const char BULLET_HIT_SE[]					= "bulletHitSE";					//弾ヒット効果音
	const char WAGE_GENERATE_SE[]				= "wageGenerateSE";					//賃金発生効果音
	const char WAGE_GET_SE[]					= "wageGetSE";						//賃金取得効果音
	const char SHOCK_WAVE_GENERATE_SE[]			= "shockWaveGenerateSE";			//衝撃波発生効果音
	const char SHOCK_WAVE_HIT_SE[]				= "shockWaveHitSE";					//衝撃波ヒット効果音
	const char MEMORY_PILE_INSTALLATION_SE[]	= "memoryPileInstallationSE";		//メモリーパイル設置効果音
	const char MEMORY_LINE_CUTTING_SE[]			= "memoryLineCuttingSE";			//メモリーライン切断効果音
	const char RECURSION_GENERATE_SE[]			= "recursionGenerateSE";			//リカージョン発生効果音
	const char DOWN_REVIVAL_QTE_SE[]			= "downRevivalQuickTimeEventSE";	//ダウン復活QuickTimeEvent効果音
	const char DOWN_REVIVAL_SE[]				= "downRevivalSE";					//ダウン復活効果音
}

class Audio
{
//プロパティ
private:
	IXACT3Engine * xactEngine;		// XACTエンジンへのポインタ
	IXACT3WaveBank* waveBank;		// XACTウェイブバンクへのポインタ
	IXACT3SoundBank* soundBank;		// XACTサウンドバンクへのポインタ
	XACTINDEX cueI;					// XACTサウンドインデックス
	void* mapWaveBank;				// UnmapViewOfFile()を呼び出してファイルを解放
	void* soundBankData;
	bool coInitialized;				// CoInitializeExが成功した場合、trueを設定

public:
	// コンストラクタ
	Audio();
	// デストラクタ
	virtual ~Audio();

	// メンバ関数
	// オーディオの初期化
	HRESULT initialize();

	// サウンドエンジン周期的なタスクを実行
	void run();

	// キューで指定されたサウンドをサウンドバンクから再生
	// キューが存在しない場合は、エサウンドが再生されないだけで、エラーは発生しない
	void playCue(const char cue[]);

	// キューで指定されたサウンドをサウンドバンクで停止
	// キューが存在しない場合、エラーは発生しない
	void stopCue(const char cue[]);

};