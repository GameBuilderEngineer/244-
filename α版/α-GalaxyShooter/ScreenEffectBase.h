//=============================================================================
// エフェクト基本処理 [ScreenEffectBase.h]
// 制作者 飯塚春輝
//=============================================================================
#pragma once
#include "Base.h"
#include "Camera.h"
//*****************************************************************************
// クラス定義
//*****************************************************************************
class ScreenEffectBase
{
protected:
	int	settingFrame;					// エフェクト生存時間
	int	cntFrame;						// エフェクト生存時間加算
	Camera *camera;
	D3DXVECTOR3 position;				//位置

public:
	ScreenEffectBase();
	~ScreenEffectBase();

	virtual void initialize(void);
	virtual void uninitialize(void) = 0;// 純粋仮想関数　継承してのみ使う関数のため実装不要
	virtual void update(void) = 0;
	virtual void render(void);
	virtual void activate(int second);
	virtual void inactivate(void);
	bool isActive;
	void setCamera(Camera* _camera) { camera = _camera; }
};
