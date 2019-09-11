//============================================================================================================================================
// Document
//============================================================================================================================================
// UICutMemoryLine.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/07
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace uiCutMemoryLineNS
{
	const int WIDTH = (653);														//	��
	const int HEIGHT = (160);														//	����
	const float POSITION_X_PLAYER_1 = (WINDOW_WIDTH / 4);							//	���W x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));	//	���W x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 4);									//	���W y
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class UICutMemoryLine
{
private:
	static int instanceIndex;			//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture;	//	�e�N�X�`��
	Sprite sprite;						//	�X�v���C�g
	bool renderFlag;					//	�`��t���O
public:
	UICutMemoryLine(void);
	~UICutMemoryLine(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void release(void);
	void update(D3DXVECTOR3 _playerPosition1, D3DXVECTOR3 _playerPosition2);
	void updateRenderFlag(D3DXVECTOR3 _playerPosition1, D3DXVECTOR3 _playerPosition2);
	void render(LPDIRECT3DDEVICE9 _device);
};