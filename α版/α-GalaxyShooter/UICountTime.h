////======================================================================================================================================================
//// Document
////======================================================================================================================================================
//// UICountTime.h
//// HAL東京 GP-12A-332 09 亀岡竣介
//// 2019/08/07
////======================================================================================================================================================
//#pragma once
//#include "Sprite.h"
//#include "AbstractScene.h"
////======================================================================================================================================================
//// NameSpace
//// 名前空間
////======================================================================================================================================================
//namespace uiCountTimeNS
//{
//	const int WIDTH = (360);														//	幅
//	const int HEIGHT = (75);														//	高さ
//	const float POSITION_X_PLAYER_1 = ((WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 4));	//	座標 x ( Player1 )
//	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));	//	座標 x ( Player2 )
//	const float POSITION_Y = (WINDOW_HEIGHT / 2);									//	座標 y
//
//	enum START_COUNT_TYPE
//	{
//		THREE,
//		TWO,
//		ONE,
//		TYPE_MAX
//	};
//}
////======================================================================================================================================================
//// Class
//// クラス
////======================================================================================================================================================
//class UICountTime
//{
//private:
//	static int instanceIndex;			//	インスタンスインデックス
//	//static LPDIRECT3DTEXTURE9 texture;	//	テクスチャ
//	//Sprite sprite;						//	スプライト
//	TextManager* textManager;			//	テキストマネージャ
//	bool startCountSoundFlag[uiCountTimeNS::START_COUNT_TYPE::TYPE_MAX];	//	ゲーム開始カウントのサウンドフラグ
//public:
//	UICountTime(void);
//	~UICountTime(void);
//	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, TextManager* _textManager);
//	void release(void);
//	void update(Sound* _sound, float _time, bool* _startCountFlag);
//	void updateStartCount(Sound* _sound, float _time, bool* _startCountFlag);
//	void render(LPDIRECT3DDEVICE9 _device, float _time);
//};