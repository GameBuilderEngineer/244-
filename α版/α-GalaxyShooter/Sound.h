//============================================================================================================================================
// Document
//============================================================================================================================================
// Sound.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/07/19
//============================================================================================================================================
#pragma once
#include <dsound.h>
#pragma comment(lib,"dsound.lib")
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace soundNS
{
	const int CONST_FADE_VALUE = (25);				//	フェード値
	const int CONST_VOLUME_MIN = (DSBVOLUME_MIN);	//	音量最小値
	const int CONST_VOLUME_MAX = (DSBVOLUME_MAX);	//	音量最大値

	enum TYPE
	{
		AGING,							//	エイジング
		BGM_CHARACTER_SELECT,			//	BGM：キャラクターセレクト
		BGM_CREDIT,						//	BGM：クレジット
		BGM_GAME,						//	BGM：ゲーム
		BGM_OPERATION,					//	BGM：操作方法
		BGM_RESULT,						//	BGM：リザルト
		BGM_SPLASH,						//	BGM：スプラッシュ
		BGM_TITLE,						//	BGM：タイトル
		BGM_TUTORIAL,					//	BGM：チュートリアル
		SE_ATTACK,						//	SE：攻撃
		SE_CANCEL,						//	SE：キャンセル
		SE_CHINGIN,						//	SE：チンギン
		SE_COUNT,						//	SE：カウント
		SE_CUT_MEMORY_LINE,				//	SE：メモリー・ライン切断
		SE_DECISION,					//	SE：決定
		SE_DESTRUCTION_WASUREMONO,		//	SE：ワスレモノ破壊
		SE_DOWN,						//	SE：ダウン
		SE_GAME_START,					//	SE：ゲーム - スタート
		SE_GAME_TIME_UP,				//	SE：ゲーム - タイムアップ
		SE_HIT,							//	SE：ヒット
		SE_INSTALLATION_MEMORY_PILE,	//	SE：メモリー・パイル設置
		SE_JUMP,						//	SE：ジャンプ
		SE_LANDING,						//	SE：着地
		SE_PAPER,						//	SE：ペーパー
		SE_PAUSE,						//	SE：ポーズ
		SE_READY,						//	SE：準備完了
		SE_RECURSION,					//	SE：再帰回収
		SE_REVIVAL,						//	SE：復活
		SE_REVIVAL_POINT,				//	SE：復活ポイント
		SE_SELECT,						//	SE：セレクト
		SE_SHOCK_WAVE,					//	SE：衝撃波
		TYPE_MAX						//	最大値
	};
	enum METHOD
	{
		PLAY,		//	再生
		LOOP,		//	ループ再生
		METHOD_MAX	//	最大値
	};
	enum FADE
	{
		NONE = (-1),	//	フェード無効
		FADE_IN,		//	フェードイン
		FADE_OUT,		//	フェードアウト
		FADE_MAX		//	最大値
	};
	enum VOLUME
	{
		LOWEST,		//	最小
		HIGHEST,	//	最大
		VOLUME_MAX	//	最大値
	};
}
//============================================================================================================================================
// Structure
// 構造体
//============================================================================================================================================
struct SettingVolume
{
	int max = DSBVOLUME_MAX;	//	最大音量
	int min = DSBVOLUME_MIN;	//	最小音量
};
struct SoundFlag
{
	bool fade[soundNS::TYPE::TYPE_MAX];		//	フェードフラグ
	bool play[soundNS::TYPE::TYPE_MAX];		//	再生フラグ
	bool pause[soundNS::TYPE::TYPE_MAX];	//	一時停止フラグ
};
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class Sound
{
private:
	IDirectSound8 *directSound;									//	サウンドのオブジェクト
	LPDIRECTSOUNDBUFFER8 soundBuffer[soundNS::TYPE::TYPE_MAX];	//	サウンド
	DWORD playPosition[soundNS::TYPE::TYPE_MAX];				//	再生位置
	DWORD playMethod[soundNS::TYPE::TYPE_MAX];					//	再生方法
	SettingVolume settingVolume;								//	設定音量
	SoundFlag flag;												//	フラグ
	int fadeType[soundNS::TYPE::TYPE_MAX];						//	フェードタイプ
	int volume[soundNS::TYPE::TYPE_MAX];						//	音量
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