//======================================================================================================================================================
// Document
//======================================================================================================================================================
// Sound.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/07/19
//======================================================================================================================================================
#pragma once
#include <dsound.h>
#pragma comment(lib,"dsound.lib")
//======================================================================================================================================================
// Macro
// マクロ
//======================================================================================================================================================
#define SOUND_FILE_BGM_GAME ("BGM_Test_Ver_Game.wav")					//	サウンドファイル
#define SOUND_FILE_BGM_SPLASH_TITLE ("BGM_Test_Ver_Splash_Title.wav")	//	サウンドファイル
#define SOUND_FILE_SE_SELECT ("SE_Test_Ver_Select.wav")					//	サウンドファイル
#define SOUND_FILE_SE_DECISION ("SE_Test_Ver_Decision.wav")				//	サウンドファイル
#define SOUND_FILE_SE_CANCEL ("SE_Test_Ver_Cancel.wav")					//	サウンドファイル
#define SOUND_FILE_SE_DAMAGE_GIVE ("SE_Test_Ver_Damage_Give.wav")		//	サウンドファイル
#define SOUND_FILE_SE_DAMAGE_COVERED ("SE_Test_Ver_Damage_Covered.wav")	//	サウンドファイル
//======================================================================================================================================================
// NameSpace
// 名前空間
//======================================================================================================================================================
namespace soundNS
{
	const int CONST_FADE_VALUE = (25);				//	フェード値
	const int CONST_VOLUME_MIN = (DSBVOLUME_MIN);	//	音量最小値
	const int CONST_VOLUME_MAX = (DSBVOLUME_MAX);	//	音量最大値

	enum TYPE
	{
		BGM_GAME,			//	BGM：ゲーム
		BGM_SPLASH_TITLE,	//	BGM：スプラッシュ - タイトル
		SE_SELECT,			//	SE：セレクト
		SE_DECISION,		//	SE：決定
		SE_CANCEL,			//	SE：キャンセル
		SE_DAMAGE_GIVE,		//	SE：与ダメ
		SE_DAMAGE_COVERED,	//	SE：被ダメ
		TYPE_MAX			//	最大値
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
//======================================================================================================================================================
// Structure
// 構造体
//======================================================================================================================================================
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
//======================================================================================================================================================
// Class
// クラス
//======================================================================================================================================================
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