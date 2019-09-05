////============================================================================================================================================
//// Document
////============================================================================================================================================
//// PlayerAnimation.h
//// HAL���� GP-12A-332 09 �T���v��
//// 2019/09/04
////============================================================================================================================================
//#pragma once
//#include "Input.h"
//#include "Player.h"
//#include "Animation.h"
////============================================================================================================================================
//// NameSpace
//// ���O���
////============================================================================================================================================
//namespace playerAnimationNS
//{
//	const float TIME_PER_FRAME = (0.0167f);
//}
////============================================================================================================================================
//// Class
//// �N���X
////============================================================================================================================================
//// PlayerAnimation
//class PlayerAnimation
//{
//private:
//	Animation* animation;		//	�A�j���[�V����
//	AnimationID animationID;	//	�A�j���[�V����ID
//public:
//	PlayerAnimation(void);
//	~PlayerAnimation(void);
//	HRESULT initialize(LPDIRECT3DDEVICE9 _device);
//	void release(void);
//	void update(void);
//	void updateAnimation(void);
//	void updateAnimationCurrent(void);
//	void updateAnimationCurrentIdle(void);
//	void updateAnimationCurrentFastRun(void);
//	void updateAnimationNext(void);
//	void updateAnimationNextIdle(void);
//	void updateAnimationNextFastRun(void);
//	void render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX* _matrixWorld);
//	void installation(void);
//};