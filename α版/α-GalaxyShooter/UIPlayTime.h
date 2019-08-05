//======================================================================================================================================================
// Document
//======================================================================================================================================================
// UIPlayTime.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/01
//======================================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//======================================================================================================================================================
// NameSpace
// ���O���
//======================================================================================================================================================
namespace uiPlayTimeNS
{
	const int WIDTH = (360);															//	��
	const int HEIGHT = (75);															//	����
	const float POSITION_X_PLAYER_1 = (WIDTH / 2);										//	X���W
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2.0f));	//	X���W
	const float POSITION_Y = (50.0f);													//	Y���W
}
//======================================================================================================================================================
// Class
// �N���X
//======================================================================================================================================================
class UIPlayTime
{
private:
	static int instanceIndex;			//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture;	//	�e�N�X�`��
	Sprite sprite;						//	�X�v���C�g
	TextManager* textManager;			//	�e�L�X�g�}�l�[�W��
	int playerIndex;					//	�v���C���[�C���f�b�N�X
public:
	UIPlayTime(void);
	~UIPlayTime(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, TextManager* _textManager);
	void release(void);
	void render(LPDIRECT3DDEVICE9 _device, float _sceneTimer);
};