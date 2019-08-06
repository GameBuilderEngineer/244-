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
	const float WIDTH = (960.0f);															//	幅
	const float HEIGHT = (50.0f);															//	高さ
	const float POSITION_X_PLAYER_1 = ((WINDOW_WIDTH / 2) - (uiRevivalGaugeNS::WIDTH / 2));	//	座標 x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2.0f));		//	座標 x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);											//	Y座標

	enum TYPE
	{
		FOUNDATION,	//	土台
		CURRENT,	//	現在
		TYPE_MAX	//	最大値
	};
}
//======================================================================================================================================================
// Class
// クラス
//======================================================================================================================================================
class UIRevivalGauge
{
private:
	static int instanceIndex;												//	インスタンスインデックス
	static LPDIRECT3DTEXTURE9 texture[uiRevivalGaugeNS::TYPE::TYPE_MAX];	//	テクスチャ
	Sprite sprite[uiRevivalGaugeNS::TYPE::TYPE_MAX];						//	スプライト
	int playerIndex;														//	プレイヤーインデックス
public:
	UIRevivalGauge(void);
	~UIRevivalGauge(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _index);
	void release(void);
	void update(int _revivalPoint);
	void render(LPDIRECT3DDEVICE9 _device);
};