#pragma once
#include <vector>
#include "AbstractScene.h"
#include "Object.h"
#include "Player.h"
#include "Text.h"
#include "Magnet.h"
#include "TimerUI.h"
#include "Colony.h"
#include "Junk.h"
#include "GameMaster.h"
#include "Bullet.h"
#include "Planet.h"
#include "PointSprite.h"
#include "InstancingBillboard.h"
#include "MemoryPile.h"
#include "MemoryLine.h"
#include "Recursion.h"
#include "Wasuremono.h"
#include "WasuremonoManager.h"
#include "HpEffect.h"
#include "TargetDisplayEffect.h"
#include "Pose.h"
#include "UIRecursion.h"
#include "UIPlayTime.h"
#include "UIChingin.h"

#define JUNK_MAX (100) //�K���N�^�̐�

namespace gameNS
{
	enum {
		PLAYER1,
		PLAYER2,
		NUM_PLAYER,
	};

	const int NUM_BULLET = 30;
	const int NUM_MAGNET = 30;
	const int NUM_CUBE = 1000;
	const D3DXVECTOR3 PLANET_POSITION(0.0f,0.0f,0.0f);

	const D3DXVECTOR3 PLAYER_POSITION[NUM_PLAYER] =
	{
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(0,-100,0)
	};
	const D3DXQUATERNION CAMERA_RELATIVE_QUATERNION[NUM_PLAYER] =
	{
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f),
#ifdef _DEBUG
		D3DXQUATERNION(0.0f,20.0f,-40,0.0f)
#else
		D3DXQUATERNION(0.0f,20.0f,-40.0f,0.0f)
#endif // _DEBUG
	};
	
	const D3DXVECTOR3 CAMERA_RELATIVE_GAZE = D3DXVECTOR3(0,10,0);
	
	enum {
		COLONY1,
		COLONY2,
		NUM_COLONY,
	};

	const int NUM_1P_MEMORY_PILE = 5;
	const int NUM_2P_MEMORY_PILE = 5;
	const float INTERVAL_TIME_BULLET1 = 0.2f;
	const float INTERVAL_TIME_BULLET2 = 0.2f;
}

class Game : public AbstractScene
{
private:	
	GameMaster gameMaster;
	
	Planet field;
	Magnet magnet[gameNS::NUM_MAGNET];
	Text text;
	Text text2;
	TimerUI timerUI[gameNS::NUM_PLAYER];



	UIRecursion uiRecursion[gameNS::NUM_PLAYER];
	UIPlayTime uiPlayTime[gameNS::NUM_PLAYER];
	UIChingin uiChingin[gameNS::NUM_PLAYER];

	Colony colony[gameNS::NUM_COLONY];
	Junk junk[JUNK_MAX];
	PointSprite pointSprite;
	InstancingBillboard plane;
	Object testObject;//��
	Object testCube;//��

	//�v���C���[
	Player player[gameNS::NUM_PLAYER];
	//�v���C���[�N���X�֓���
	Bullet bullet1[gameNS::NUM_BULLET];
	Bullet bullet2[gameNS::NUM_BULLET];
	MemoryPile memoryPile1P[gameNS::NUM_1P_MEMORY_PILE];
	MemoryPile memoryPile2P[gameNS::NUM_2P_MEMORY_PILE];
	MemoryLine memoryLine1P;
	MemoryLine memoryLine2P;
	Recursion* recursion1P;


	std::vector<Wasuremono*> wasuremono;
	WasuremonoManager wasuremonoManager;
	HpEffect hpEffect[gameNS::NUM_PLAYER];
	TargetDisplayEffect target;
	Pose pose;

	bool onUI = true;
	int currentBullet1;//���݂̒e�ԍ�[1P]
	int currentBullet2;//���݂̒e�ԍ�[2P]
	float intervalBullet1;
	float intervalBullet2;
	int currentMemoryPile1;//���݂̃������[�p�C���ԍ�[1P]
	int currentMemoryPile2;//���݂̃������[�p�C���ԍ�[1P]
	float frameTime = 0.0f;//�t���[���^�C���ۑ��ϐ�
	bool onRecursion1P;					//1P�̃��J�[�W�������������ꂽ���ǂ���
	bool recursion1PAnd2P;				//1P�̃��J�[�W������2P���Փ˂������ǂ���
	bool collitionMemoryLine1P;			//1P�̃������[���C����2P���Փ˂��Ă��邩�ǂ���

	int reverseValue1PXAxis;
	int reverseValue1PYAxis;
	int reverseValue2PXAxis;
	int reverseValue2PYAxis;

	float difference = 1.0f;

public:
	Game();
	~Game();
	virtual void initialize(
		Direct3D9* _direct3D9,
		Input* _input,
		Sound* _sound,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader,
		TextManager* _textManager) override;
	virtual void update(float frameTime) override;
	virtual void render(Direct3D9* direct3D9) override;
	virtual void collisions() override;
	virtual void AI() override;
	virtual void uninitialize() override;

	void render3D(Direct3D9* direct3D9, Camera currentCamera);
	void renderUI(LPDIRECT3DDEVICE9 device);
};