//=============================================================================
// �������\���w�b�_�[ [ChinginCnt.h]
// ����� �ђˏt�P
//=============================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ChinginCnt :public Sprite
{
private:
	// Data
	int playerNumber;								// �v���C���[�ԍ�
	TextManager* textManager;						//	�e�L�X�g�}�l�[�W��
public:
	// Method
	ChinginCnt(void);
	~ChinginCnt(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 device, int _playerNumber, TextureLoader*textureLoader, TextManager* _textManager);
	void uninitialize(void);
	void update(void);
	void render(LPDIRECT3DDEVICE9 device, float _chinginCnt, float _chinginCnt2);
};

