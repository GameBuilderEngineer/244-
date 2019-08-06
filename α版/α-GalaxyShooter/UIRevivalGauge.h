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
	const float WIDTH = (960.0f);															//	��
	const float HEIGHT = (50.0f);															//	����
	const float POSITION_X_PLAYER_1 = ((WINDOW_WIDTH / 2) - (uiRevivalGaugeNS::WIDTH / 2));	//	���W x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2.0f));		//	���W x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);											//	Y���W

	enum TYPE
	{
		FOUNDATION,	//	�y��
		CURRENT,	//	����
		TYPE_MAX	//	�ő�l
	};
}
//======================================================================================================================================================
// Class
// �N���X
//======================================================================================================================================================
class UIRevivalGauge
{
private:
	static int instanceIndex;												//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture[uiRevivalGaugeNS::TYPE::TYPE_MAX];	//	�e�N�X�`��
	Sprite sprite[uiRevivalGaugeNS::TYPE::TYPE_MAX];						//	�X�v���C�g
	int playerIndex;														//	�v���C���[�C���f�b�N�X
public:
	UIRevivalGauge(void);
	~UIRevivalGauge(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _index);
	void release(void);
	void update(int _revivalPoint);
	void render(LPDIRECT3DDEVICE9 _device);
};