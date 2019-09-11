//============================================================================================================================================
// Document
//============================================================================================================================================
// UICountDown.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/09/10
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace uiCountDownNS
{
	const int WIDTH_COUNT_DOWN = (260);												//	��
	const int HEIGHT_COUNT_DOWN = (260);											//	����
	const float POSITION_X_PLAYER_1 = (WINDOW_WIDTH / 4);							//	���W x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));	//	���W x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);									//	���W y

	enum TYPE
	{
		GO,
		ONE,
		TWO,
		THREE,
		TYPE_MAX
	};
	enum PLAYER_TYPE
	{
		PLAYER_1,
		PLAYER_2,
		PLAYER_TYPE_MAX,
	};
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class UICountDown
{
private:
	static int instanceIndex;											//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture[uiCountDownNS::TYPE::TYPE_MAX];	//	�e�N�X�`��
	Sprite sprite[uiCountDownNS::TYPE::TYPE_MAX];						//	�X�v���C�g
	int alpha;															//	�A���t�@�l
public:
	UICountDown(void);
	~UICountDown(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index);
	void release(void);
	void update(bool _startFlag);
	void updateFadeOut(void);
	void render(LPDIRECT3DDEVICE9 _device, int _renderIndex);
};