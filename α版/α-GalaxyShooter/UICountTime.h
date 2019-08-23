////============================================================================================================================================
//// Document
////============================================================================================================================================
//// UICountTime.h
//// HAL���� GP-12A-332 09 �T���v��
//// 2019/08/07
////============================================================================================================================================
//#pragma once
//#include "Sprite.h"
//#include "AbstractScene.h"
////============================================================================================================================================
//// NameSpace
//// ���O���
////============================================================================================================================================
//namespace uiCountTimeNS
//{
//	const int WIDTH = (360);														//	��
//	const int HEIGHT = (75);														//	����
//	const float POSITION_X_PLAYER_1 = ((WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 4));	//	���W x ( Player1 )
//	const float POSITION_X_PLAYER_2 = (POSITION_X_PLAYER_1 + (WINDOW_WIDTH / 2));	//	���W x ( Player2 )
//	const float POSITION_Y = (WINDOW_HEIGHT / 2);									//	���W y
//
//	enum START_COUNT_TYPE
//	{
//		THREE,
//		TWO,
//		ONE,
//		TYPE_MAX
//	};
//}
////============================================================================================================================================
//// Class
//// �N���X
////============================================================================================================================================
//class UICountTime
//{
//private:
//	static int instanceIndex;			//	�C���X�^���X�C���f�b�N�X
//	//static LPDIRECT3DTEXTURE9 texture;	//	�e�N�X�`��
//	//Sprite sprite;						//	�X�v���C�g
//	TextManager* textManager;			//	�e�L�X�g�}�l�[�W��
//	bool startCountSoundFlag[uiCountTimeNS::START_COUNT_TYPE::TYPE_MAX];	//	�Q�[���J�n�J�E���g�̃T�E���h�t���O
//public:
//	UICountTime(void);
//	~UICountTime(void);
//	HRESULT initialize(LPDIRECT3DDEVICE9 _device, int _playerIndex, TextureLoader* _textureLoader, TextManager* _textManager);
//	void release(void);
//	void update(Sound* _sound, float _time, bool* _startCountFlag);
//	void updateStartCount(Sound* _sound, float _time, bool* _startCountFlag);
//	void render(LPDIRECT3DDEVICE9 _device, float _time);
//};