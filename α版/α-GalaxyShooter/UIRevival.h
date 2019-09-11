//============================================================================================================================================
// Document
//============================================================================================================================================
// UIRevival.h
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
namespace uiRevivalNS
{
	const int MAX_REVIVAL_POINT = (1000);											//	�����A�Ń|�C���g�̍ő�l
	const int WIDTH_BAR = (960);												//	��
	const int HEIGHT_BAR = (160);												//	����
	const int WIDTH_GAUGE = (960);												//	��
	const int HEIGHT_GAUGE = (50);												//	����
	const int WIDTH_CONCENTRATION = (960);										//	��
	const int HEIGHT_CONCENTRATION = (1080);									//	����
	const int WIDTH_TONE = (960);												//	��
	const int HEIGHT_TONE = (1080);												//	����
	const float POSITION_X_PLAYER_1 = (WINDOW_WIDTH / 4);							//	���W x ( Player1 )
	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));	//	���W x ( Player2 )
	const float POSITION_Y = (WINDOW_HEIGHT / 2);									//	���W y
	const float POSITION_Y_BAR = (POSITION_Y + 115.0f);								//	���W y ( BAR )

	enum TYPE
	{
		BAR,			//	����
		GAUGE,			//	�Q�[�W
		CONCENTRATION,	//	�W����
		TONE,			//	�J���[�g�[��
		TYPE_MAX		//	�ő�l
	};
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class UIRevival
{
private:
	static int instanceIndex;										//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture[uiRevivalNS::TYPE::TYPE_MAX];	//	�e�N�X�`��
	Sprite sprite[uiRevivalNS::TYPE::TYPE_MAX];						//	�X�v���C�g
public:
	UIRevival(void);
	~UIRevival(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _playerIndex, int _index);
	void release(void);
	void update(int _revivalPoint);
	void render(LPDIRECT3DDEVICE9 _device);
};