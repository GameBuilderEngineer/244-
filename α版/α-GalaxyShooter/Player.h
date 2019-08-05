//===================================================================================================================================
//【Player.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/04
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
		DEFAULT,
		DOWN,
		SKY,
		REVIVAL,
		STATE_NUM
	};

	const int NUM_BULLET = 30;				//弾の数
	const int NUM_MEMORY_PILE = 5;			//メモリーパイルの数
	const int AMOUNT_RECOVERY = 2;			//回復料
	const float SPEED = 30.0f;				//速度
	const float JUMP_FORCE = 200.0f;		//ジャンプ力
	const float GRAVITY_FORCE = 80.0f;		//重力
	const float DIFFERENCE_FIELD = 1.0f;	//フィールド補正差分
	const float DOWN_TIME = 5.0f;			//ダウン時間
	const float INVINCIBLE_TIME = 3.0f;		//無敵時間
	const float SKY_TIME = 10.0f;			//上空モード時間
	const float INTERVAL_RECOVERY = 1.0f;	//自動回復インターバル
	const float INTERVAL_BULLET = 0.2f;		//弾の発射インターバル
	const float CAMERA_SPEED = 2.5f;		//弾の発射インターバル

	//プレイヤーのスタートポジション
	const D3DXVECTOR3 START_POSITION[NUM_PLAYER] =
	{
		D3DXVECTOR3(100,0,0),
		D3DXVECTOR3(-100,0,0),
		D3DXVECTOR3(0,100,0)
	};

}

class Player : public Object
{
private:
	LPDIRECT3DDEVICE9 device;
	TextureLoader* textureLoader;
	ShaderLoader* shaderLoader;

	//ステータス
	int type;											//プレイヤータイプ
	int hp;												//体力
	int maxHp;											//最大体力
	int sp;												//削除予定
	int maxSp;											//削除予定
	int wage;											//チンギン
	Input* input;										//入力クラス
	Camera* camera;										//カメラへのポインタ
	playerNS::OperationKeyTable keyTable;				//操作Keyテーブル

	int state;											//状態変数
	
	//重力処理に利用
	LPD3DXMESH attractorMesh;							//（現在未使用）重力（引力）発生メッシュ
	D3DXMATRIX* attractorMatrix;						//（現在未使用）重力（引力）発生オブジェクトマトリックス
	D3DXVECTOR3* attractorPosition;						//重力（引力）発生位置
	float attractorRadius;								//重力（引力）発生オブジェクト半径


	//タイマー
	float recoveryTimer;								//自動回復時間
	float invincibleTimer;								//無敵時間
	float skyTimer;										//上空モード制限時間
	float downTimer;									//ダウンタイマー[体力が切れるorメモリーラインを切断される]

	//操作関係
	float reverseValueXAxis;							//操作X軸
	float reverseValueYAxis;							//操作Y軸

	//弾関係
	int elementBullet;									//弾アクセス要素数
	float intervalBullet;								//発弾間隔

	//接地関係
	float difference;									//フィールド補正差分
	bool onGround;										//接地判定

	//メモリーアイテム関係
	MemoryPile memoryPile[playerNS::NUM_MEMORY_PILE];	//メモリーパイル
	MemoryLine memoryLine;								//メモリーライン
	Recursion* recursion;								//リカージョン
	LPDIRECT3DTEXTURE9 recrusionTexture;				//リカージョン用テクスチャ
	int elementMemoryPile;								//メモリーパイル要素数
	bool onRecursion;									//リカージョン生成フラグ

public:
	BoundingSphere bodyCollide;	//球コリジョン
	Bullet bullet[playerNS::NUM_BULLET];				//弾

	Player();
	~Player();

	//processing
	virtual void initialize(int playerType,LPDIRECT3DDEVICE9 _device, StaticMeshLoader* staticMeshLoader, TextureLoader* textureLoader,ShaderLoader* shaderLoader);
	virtual void update(float frameTime);
	void toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon,
		LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	
	//operation
	void configurationGravityWithRay(D3DXVECTOR3* attractorPosition, LPD3DXMESH attractorMesh, D3DXMATRIX* attractorMatrix);
	void configurationGravity(D3DXVECTOR3* attractorPosition,float _attractorRadius);
	void recorvery(float frameTime);
	void moveOperation();
	void move(D3DXVECTOR2 moveDirection, D3DXVECTOR3 cameraAxisX, D3DXVECTOR3 cameraAxisZ);
	void jump();
	void reset();
	void changeState(int _state);
	void down();
	void sky(); 
	void revival();
	void updateBullet(float frameTime);
	void controlCamera(float frameTime);
	void updateMemoryItem(float frameTime);


	//setter
	void setInput(Input* _input);
	void setCamera(Camera* _camera);
	void damgae(int value);
	void recoveryHp(int value);
	void lostSp(int value);
	void recoverySp(int value);

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
};