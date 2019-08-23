//============================================================================================================================================
// Document
//============================================================================================================================================
// UIChingin.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/01
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace uiChinginNS
{
	const int WIDTH = (360);																		//	��
	const int HEIGHT = (75);																		//	����
	const float POSITION_X_PLAYER_1 = (uiChinginNS::WIDTH / 2);										//	���W x ( Player1 )
	const float POSITION_X_PLAYER_2 = (uiChinginNS::POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2.0f));	//	���W x ( Player2 )
	const float POSITION_Y = (140.0f);																//	���W y
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class UIChingin
{
private:
	static int instanceIndex;			//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture;	//	�e�N�X�`��
	Sprite sprite;						//	�X�v���C�g
	TextManager* textManager;			//	�e�L�X�g�}�l�[�W��
public:
	UIChingin(void);
	~UIChingin(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, TextManager* _textManager);
	void release(void);
	void render(LPDIRECT3DDEVICE9 _device, float _time, int _chingin);
};