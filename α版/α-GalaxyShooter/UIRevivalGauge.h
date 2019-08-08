//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIRevivalGauge.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/07
//======================================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//======================================================================================================================================================
// NameSpace
// ���O���
//======================================================================================================================================================
namespace uiRevivalGaugeNS
{
	const int WIDTH = (960);																//	��
	const int HEIGHT = (50);																//	����
	const int MAX_REVIVAL_POINT = (1000);													//	�����A�Ń|�C���g�̍ő�l
	const float POSITION_X_PLAYER_1 = ((WINDOW_WIDTH / 2) - (uiRevivalGaugeNS::WIDTH / 2));	//	���W x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2.0f));		//	���W x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);											//	���W y
}
//======================================================================================================================================================
// Class
// �N���X
//======================================================================================================================================================
class UIRevivalGauge
{
private:
	static int instanceIndex;			//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture;	//	�e�N�X�`��
	Sprite sprite;						//	�X�v���C�g
public:
	UIRevivalGauge(void);
	~UIRevivalGauge(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void release(void);
	void update(int _revivalPoint);
	void render(LPDIRECT3DDEVICE9 _device);
};