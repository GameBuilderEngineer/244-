//=============================================================================
// 賃金数表示ヘッダー [ChinginCnt.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//*****************************************************************************
// クラス定義
//*****************************************************************************
class ChinginCnt :public Sprite
{
private:
	// Data
	int playerNumber;								// プレイヤー番号
	TextManager* textManager;						//	テキストマネージャ
public:
	// Method
	ChinginCnt(void);
	~ChinginCnt(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader, TextManager* _textManager);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, float _chinginCnt, float _chinginCnt2);
};

