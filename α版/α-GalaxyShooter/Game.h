//===================================================================================================================================
//�yGame.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/09/03
//===================================================================================================================================
#pragma once
#include <vector>
#include "AbstractScene.h"
#include "Object.h"
#include "Player.h"
#include "Text.h"
#include "Magnet.h"
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
#include "UIPause.h"
#include "UIRecursion.h"
#include "UIPlayTime.h"
#include "UIChingin.h"
#include "Map.h"
#include "AgentAI.h"
#include "ChinginManager.h"
#include "UIScreenSplitLine.h"
#include "UIRevival.h"
#include "UICutMemoryLine.h"
#include "LineEffect.h"
#include "EffectManager.h"
#include "Lambert.h"

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
	const int NUM_MEMORY_PILE = 5;

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
		const BYTE BUTTON_BULLET = virtualControllerNS::R1;
		const BYTE BUTTON_REVIVAL = virtualControllerNS::A;

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
	Planet field;
	Magnet magnet[gameNS::NUM_MAGNET];
	Text text;
	Text text2;

	//UIRecursion uiRecursion[gameNS::NUM_PLAYER];
	UIPlayTime uiPlayTime[gameNS::NUM_PLAYER];
	UIChingin uiChingin[gameNS::NUM_PLAYER];
	UICutMemoryLine uiCutMemoryLine[gameNS::NUM_PLAYER];
	UIRevival uiRevival[gameNS::NUM_PLAYER];
	UIScreenSplitLine uiScreenSplitLine;
	LineEffect lineEffect;		//���C���G�t�F�N�g

	Colony colony[gameNS::NUM_COLONY];
	Junk junk[JUNK_MAX];
	PointSprite pointSprite;
	InstancingBillboard plane;
	Object testObject;//��
	Object testCube;//��
	//�v���C���[
	Player *player[gameNS::NUM_PLAYER];
	//�v���C���[�N���X�֓���
	Map map;// ��

	std::vector<Wasuremono*> wasuremono;
	WasuremonoManager wasuremonoManager;
	ChinginManager chinginManager;
	HpEffect hpEffect[gameNS::NUM_PLAYER];
	TargetDisplayEffect target;
	UIPause uiPause;

	bool startCountFlag;
	bool endCountFlag;
	bool onUI = true;
	float frameTime = 0.0f;//�t���[���^�C���ۑ��ϐ�


	//�V�[���̃J���[����Z�l�����擾����N���X
	Lambert* lambert;

	//�V�[���̃J���[�����i�[����T�[�t�F�C�X
	LPDIRECT3DTEXTURE9 colorTexture = NULL;
	LPDIRECT3DSURFACE9 colorSurface = NULL;

	//�V�[����Z�l���i�[����T�[�t�F�C�X
	LPDIRECT3DTEXTURE9 zMapTexture = NULL;
	LPDIRECT3DSURFACE9 zMapSurface = NULL;

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

