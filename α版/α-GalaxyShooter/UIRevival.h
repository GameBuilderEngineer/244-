//============================================================================================================================================
// Document
//============================================================================================================================================
// UIRevival.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/07
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// 名前空間
//============================================================================================================================================
namespace uiRevivalNS
{
	const int MAX_REVIVAL_POINT = (1000);											//	復活連打ポイントの最大値
	const int WIDTH_BAR = (1920 / 2);												//	幅
	const int HEIGHT_BAR = (320 / 2);												//	高さ
	const int WIDTH_GAUGE = (1920 / 2);												//	幅
	const int HEIGHT_GAUGE = (100 / 2);												//	高さ
	const int WIDTH_CONCENTRATION = (1920 / 2);										//	幅
	const int HEIGHT_CONCENTRATION = (2160 / 2);									//	高さ
	const int WIDTH_TONE = (1920 / 2);												//	幅
	const int HEIGHT_TONE = (2160 / 2);												//	高さ
	const float POSITION_X_PLAYER_1 = (WINDOW_WIDTH / 4);							//	座標 x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));	//	座標 x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);									//	座標 y
	const float POSITION_Y_BAR = (POSITION_Y + 115.0f);								//	座標 y ( BAR )

	enum TYPE
	{
		BAR,			//	説明
		GAUGE,			//	ゲージ
		CONCENTRATION,	//	集中線
		TONE,			//	カラートーン
		TYPE_MAX		//	最大値
	};
}
//============================================================================================================================================
// Class
// クラス
//============================================================================================================================================
class UIRevival
{
private:
	static int instanceIndex;										//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture[uiRevivalNS::TYPE::TYPE_MAX];	//	テクスチャ
	Sprite sprite[uiRevivalNS::TYPE::TYPE_MAX];						//	スプライト
public:
	UIRevival(void);
	~UIRevival(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index);
	void release(void);
	void update(int _revivalPoint);
	void render(LPDIRECT3DDEVICE9 _device);
};