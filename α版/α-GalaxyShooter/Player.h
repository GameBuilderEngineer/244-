//===================================================================================================================================
//�yPlayer.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/05/16
// [�X�V��]2019/08/04
//===================================================================================================================================
#pragma once
#include "Object.h"
#include "BoundingSphere.h"
#include "MemoryPile.h"
#include "MemoryLine.h"
#include "Recursion.h"
#include "Bullet.h"
#include "Input.h"
#include "Camera.h"
#include "ShockWave.h"


namespace playerNS{

	enum PLAYER_TYPE{
		PLAYER1,
		PLAYER2,
		TITLE_PLAYER,
		NUM_PLAYER
	};

	struct OperationKeyTable
	{
		BYTE front;
		BYTE back;
		BYTE right;
		BYTE left;
		BYTE reset;
		BYTE jump;
		BYTE cameraX;
		BYTE cameraY;
		BYTE provisional;
	};

	const OperationKeyTable KEY_TABLE_1P = {
		'W',		//FRONT
		'S',		//BACK
		'D',		//RIGHT
		'A',		//LEFT
		'R',		//RESET
		VK_SPACE,	//JUMP
		VK_F3,		//CameraAxisX
		VK_F4,		//CameraAxisY
		'G',		//Provisional
	};

	const OperationKeyTable KEY_TABLE_2P = {
		VK_UP,			//FRONT
		VK_DOWN,		//BACK
		VK_RIGHT,		//RIGHT
		VK_LEFT,		//LEFT
		'R',			//RESET
		VK_RETURN,		//JUMP
		VK_F5,			//CameraAxisX
		VK_F6,			//CameraAxisY
		'T',		//Provisional
	};
	const OperationKeyTable NON_CONTOROL = {
		VK_ESCAPE,		//FRONT
		VK_ESCAPE,		//BACK
		VK_ESCAPE,		//RIGHT
		VK_ESCAPE,		//LEFT
		VK_ESCAPE,		//RESET
		VK_ESCAPE,		//JUMP
		VK_ESCAPE,		//CameraAxisX
		VK_ESCAPE,		//CameraAxisY
	};

	const BYTE BUTTON_JUMP = virtualControllerNS::B;
	const BYTE BUTTON_BULLET = virtualControllerNS::R1;

	enum STATE {
		GROUND,
		DOWN,
		FALL,
		SKY,
		REVIVAL,
		STATE_NUM
	};

	const int NUM_BULLET = 30;				//�e�̐�
	const int NUM_MEMORY_PILE = 5;			//�������[�p�C���̐�
	const int AMOUNT_RECOVERY = 2;			//�񕜗�
	const float SPEED = 30.0f;				//���x
	const float JUMP_FORCE = 200.0f;		//�W�����v��
	const float GRAVITY_FORCE = 80.0f;		//�d��
	const float DIFFERENCE_FIELD = 1.0f;	//�t�B�[���h�␳����
	const float DOWN_TIME = 5.0f;			//�_�E������
	const float FALL_TIME = 0.5f;			//��������
	const float INVINCIBLE_TIME = 3.0f;		//���G����
	const float SKY_TIME = 10.0f;			//��󃂁[�h����
	const float INTERVAL_RECOVERY = 1.0f;	//�����񕜃C���^�[�o��
	const float INTERVAL_BULLET = 0.2f;		//�e�̔��˃C���^�[�o��
	const float CAMERA_SPEED = 2.5f;		//�e�̔��˃C���^�[�o��
	const float SKY_HEIGHT = 80.0f;			//��󃂁[�h�̍���


	//�v���C���[�̃X�^�[�g�|�W�V����
	const D3DXVECTOR3 START_POSITION[NUM_PLAYER] =
	{
		D3DXVECTOR3(100,0,0),
		D3DXVECTOR3(-100,0,0),
		D3DXVECTOR3(0,100,0)
	};

}

class Player : public Object
{
protected:
	LPDIRECT3DDEVICE9 device;
	TextureLoader* textureLoader;
	ShaderLoader* shaderLoader;

	//�X�e�[�^�X
	int type;											//�v���C���[�^�C�v
	int modelType;										//�L�����N�^�[���f���^�C�v
	int hp;												//�̗�
	int maxHp;											//�ő�̗�
	int sp;												//�폜�\��
	int maxSp;											//�폜�\��
	int wage;											//�`���M��
	Input* input;										//���̓N���X
	Camera* camera;										//�J�����ւ̃|�C���^
	playerNS::OperationKeyTable keyTable;				//����Key�e�[�u��

	int state;											//��ԕϐ�
	
	//�d�͏����ɗ��p
	LPD3DXMESH attractorMesh;							//�i���ݖ��g�p�j�d�́i���́j�������b�V��
	D3DXMATRIX* attractorMatrix;						//�i���ݖ��g�p�j�d�́i���́j�����I�u�W�F�N�g�}�g���b�N�X
	D3DXVECTOR3* attractorPosition;						//�d�́i���́j�����ʒu
	float attractorRadius;								//�d�́i���́j�����I�u�W�F�N�g���a


	//�^�C�}�[
	float recoveryTimer;								//�����񕜎���
	float invincibleTimer;								//���G����
	float skyTimer;										//��󃂁[�h��������
	float downTimer;									//�_�E���^�C�}�[[�̗͂��؂��or�������[���C����ؒf�����]
	float transitionTimer;								//�J�ڎ���
	float fallTimer;									//��������

	//����֌W
	float reverseValueXAxis;							//����X��
	float reverseValueYAxis;							//����Y��

	//�e�֌W
	int elementBullet;									//�e�A�N�Z�X�v�f��
	float intervalBullet;								//���e�Ԋu

	//�ڒn�֌W
	float difference;									//�t�B�[���h�␳����
	bool onGround;										//�ڒn����

	//��󃂁[�h�֌W
	float skyHeight;									//��󃂁[�h������

	//�������[�A�C�e���֌W
	MemoryPile memoryPile[playerNS::NUM_MEMORY_PILE];	//�������[�p�C��
	MemoryLine memoryLine;								//�������[���C��
	Recursion* recursion;								//���J�[�W����
	LPDIRECT3DTEXTURE9 recrusionTexture;				//���J�[�W�����p�e�N�X�`��
	int elementMemoryPile;								//�������[�p�C���v�f��
	bool onRecursion;									//���J�[�W���������t���O

	//�Ռ��g
	ShockWave* shockWave;								//�Ռ��g
	bool onShockWave;									//�Ռ��g�����t���O

	//�Փˏ��
	bool collidedOpponentMemoryLine;					//����̃������[���C���Ƃ̏Փ˃t���O

	//�A�N�V�����t���O
	bool disconnectOpponentMemoryLine;					//����̃������[���C���̐ؒf�A�N�V�������b�Z�[�W

public:
	BoundingSphere bodyCollide;							//���R���W����
	Bullet bullet[playerNS::NUM_BULLET];				//�e


	Player();
	~Player();

	//processing
	virtual void initialize(int playerType, int modelType, LPDIRECT3DDEVICE9 _device, StaticMeshLoader* staticMeshLoader, TextureLoader* textureLoader,ShaderLoader* shaderLoader);
	virtual void update(float frameTime);
	void toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon,
		LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void otherRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	//operation
	void configurationGravityWithRay(D3DXVECTOR3* attractorPosition, LPD3DXMESH attractorMesh, D3DXMATRIX* attractorMatrix);
	void configurationGravity(D3DXVECTOR3* attractorPosition,float _attractorRadius);
	void recorvery(float frameTime);
	void moveOperation();
	void move(D3DXVECTOR2 moveDirection, D3DXVECTOR3 cameraAxisX, D3DXVECTOR3 cameraAxisZ);
	void jump();
	void reset();
	void changeState(int _state);
	void ground();
	void fall();
	void down();
	void sky(); 
	void revival();
	void updateBullet(float frameTime);
	void controlCamera(float frameTime);
	void updateMemoryItem(float frameTime);
	void triggerShockWave();
	void deleteShockWave();
	void updateShockWave(float frameTime);
	void disconnectMemoryLine();

	//setter
	void setInput(Input* _input);
	void setCamera(Camera* _camera);
	void damgae(int value);
	void recoveryHp(int value);
	void lostSp(int value);
	void recoverySp(int value);
	void setCollidedMemoryLine(bool frag);

	//getter
	int getHp();
	int getMaxHp();
	int getSp();
	int getMaxSp();
	int getState();
	int getWage();
	bool whetherDown();
	bool whetherDeath();
	bool whetherInvincible(); 
	bool whetherSky();
	bool whetherFall();
	bool whetherGenerationRecursion();
	bool messageDisconnectOpponentMemoryLine();
	Recursion* getRecursion();
	MemoryLine* getMemoryLine();
};