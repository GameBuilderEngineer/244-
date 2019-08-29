//============================================================================================================================================
// Document
//============================================================================================================================================
// UITitle.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/29
//============================================================================================================================================
#pragma once
#include "Sprite.h"
#include "AbstractScene.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace uiTitleNS
{
	const int WIDTH_TITLE_LOGO = (1920 / 2);					//	��
	const int HEIGHT_TITLE_LOGO = (250 / 2);					//	����
	const int WIDTH_TITLE_BAR = (1200 / 2);						//	��
	const int HEIGHT_TITLE_BAR = (150 / 2);						//	����
	const int WIDTH_GAME_START = (1200 / 2);					//	��
	const int HEIGHT_GAME_START = (150 / 2);					//	����
	const int WIDTH_TUTORIAL = (1200 / 2);						//	��
	const int HEIGHT_TUTORIAL = (150 / 2);						//	����
	const int WIDTH_OPERATION = (1200 / 2);						//	��
	const int HEIGHT_OPERATION = (150 / 2);						//	����
	const int WIDTH_CREDIT = (1200 / 2);						//	��
	const int HEIGHT_CREDIT = (150 / 2);						//	����
	const int WIDTH_GAME_EXIT = (1200 / 2);						//	��
	const int HEIGHT_GAME_EXIT = (150 / 2);						//	����
	const float POSITION_TITLE_LOGO_X = (WINDOW_WIDTH / 3.5f);	//	���W x
	const float POSITION_TITLE_LOGO_Y = (WINDOW_HEIGHT / 4);	//	���W y
	const float POSITION_TITLE_BAR_X = (WIDTH_TITLE_BAR / 2);	//	���W x
	const float POSITION_TITLE_BAR_Y = (475.0f);				//	���W y
	const float POSITION_GAME_START_X = (WIDTH_TITLE_BAR / 2);	//	���W x
	const float POSITION_GAME_START_Y = (475.0f);				//	���W y
	const float POSITION_TUTORIAL_X = (WIDTH_TITLE_BAR / 2);	//	���W x
	const float POSITION_TUTORIAL_Y = (575.0f);					//	���W y
	const float POSITION_OPERATION_X = (WIDTH_TITLE_BAR / 2);	//	���W x
	const float POSITION_OPERATION_Y = (675.0f);				//	���W y
	const float POSITION_CREDIT_X = (WIDTH_TITLE_BAR / 2);		//	���W x
	const float POSITION_CREDIT_Y = (775.0f);					//	���W y
	const float POSITION_GAME_EXIT_X = (WIDTH_TITLE_BAR / 2);	//	���W x
	const float POSITION_GAME_EXIT_Y = (875.0f);				//	���W y

	enum TYPE
	{
		TITLE_LOGO,
		TITLE_BAR,
		GAME_START,
		GAME_START_SELECT,
		TUTORIAL,
		TUTORIAL_SELECT,
		OPERATION,
		OPERATION_SELECT,
		CREDIT,
		CREDIT_SELECT,
		GAME_EXIT,
		GAME_EXIT_SELECT,
		TYPE_MAX
	};

	enum TITLE_MENU_TYPE
	{
		MENU_GAME_START,
		MENU_TUTORIAL,
		MENU_OPERATION,
		MENU_CREDIT,
		MENU_GAME_EXIT,
		TITLE_MENU_TYPE_MAX
	};
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class UITitle
{
private:
	static int instanceIndex;										//	�C���X�^���X�C���f�b�N�X
	static LPDIRECT3DTEXTURE9 texture[uiTitleNS::TYPE::TYPE_MAX];	//	�e�N�X�`��
	Sprite sprite[uiTitleNS::TYPE::TYPE_MAX];						//	�X�v���C�g
	int selectState;												//	�I�����
public:
	UITitle(void);
	~UITitle(void);
	HRESULT initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader);
	void initializeSprite(LPDIRECT3DDEVICE9 _device, int _index);
	void release(void);
	void update(Input* _input, Sound* _sound);
	void updateBar(void);
	void render(LPDIRECT3DDEVICE9 _device);
	int getSelectState(void) { return selectState; }
};