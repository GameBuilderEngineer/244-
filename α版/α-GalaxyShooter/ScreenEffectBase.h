//=============================================================================
// �G�t�F�N�g���� [ScreenEffectBase.h]
//
//=============================================================================

#pragma once
#include "Base.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ScreenEffectBase
{
protected:
	int					settingFrame;					// �G�t�F�N�g��������
	int					cntFrame;						// �G�t�F�N�g�������ԉ��Z

public:
	ScreenEffectBase();
	~ScreenEffectBase();

	virtual void initialize(void);
	virtual void uninitialize(void) = 0;// �������z�֐��@�p�����Ă̂ݎg���֐��̂��ߎ����s�v
	virtual void update(void) = 0;
	virtual void render(void);
	virtual void activate(int second);
	virtual void inactivate(void);
	bool isActive;

};
