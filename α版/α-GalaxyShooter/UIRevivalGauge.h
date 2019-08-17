//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRevivalGauge.h
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/07
//======================================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//======================================================================================================================================================
// NameSpace
// 名前空間
//======================================================================================================================================================
namespace uiRevivalGaugeNS
{
	const int WIDTH = (960);																//	幅
	const int HEIGHT = (50);																//	高さ
	const int MAX_REVIVAL_POINT = (1000);													//	復活連打ポイントの最大値
	const float POSITION_X_PLAYER_1 = ((WINDOW_WIDTH / 2) - (uiRevivalGaugeNS::WIDTH / 2));	//	座標 x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2.0f));		//	座標 x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);											//	座標 y
}
//======================================================================================================================================================
// Class
// クラス
//======================================================================================================================================================
class UIRevivalGauge
{
private:
	static int instanceIndex;			//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture;	//	テクスチャ
	Sprite sprite;						//	スプライト
public:
	UIRevivalGauge(void);
	~UIRevivalGauge(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void release(void);
	void update(int _revivalPoint);
	void render(LPDIRECT3DDEVICE9 _device);
};