//===================================================================================================================================
//【Player.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/22
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
#include "Sound.h"


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
		BYTE revival;
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
		VK_SPACE,	//Revival
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
		'T',			//Provisional
		VK_SPACE,		//Revival
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
		VK_ESCAPE,		//Provisional
		VK_ESCAPE,		//Revival
	};

	const BYTE BUTTON_JUMP = virtualControllerNS::B;
	const BYTE BUTTON_BULLET = virtualControllerNS::R1;
	const BYTE BUTTON_CUT = virtualControllerNS::X;
	const BYTE BUTTON_REVIVAL = virtualControllerNS::A;

	enum STATE {
		GROUND,
		DOWN,
		FALL,
		SKY,
		REVIVAL,
		STATE_NUM
	};

	const int NUM_BULLET				= 30;		//弾の数
	const int NUM_MEMORY_PILE			= 5;		//メモリーパイルの数
	const int AMOUNT_RECOVERY			= 2;		//回復量
	const int MAX_HP					= 100;		//ＨＰ最大値
	const int MAX_REVIVAL_POINT			= 1000;		//復活ポイント最大値
	const int INCREASE_REVIVAL_POINT	= 50;		//復活ポイント増加値
	const int DECREASE_REVIVAL_POINT	= 3;		//復活ポイント増加値
	const float SPEED					= 30.0f;	//速度
	const float DASH_MAGNIFICATION		= 2.0f;		//ダッシュ倍率
	const float JUMP_FORCE				= 30.0f;	//ジャンプ力
	const float GRAVITY_FORCE			= 9.8f*7.0;	//重力
	const float DIFFERENCE_FIELD		= 0.2f;		//フィールド補正差分
	const float DECREASE_REVIVAL_TIME	= 0.1f;		//復活ポイント減少時間
	const float FALL_TIME				= 0.5f;		//落下時間
	const float INVINCIBLE_TIME			= 3.0f;		//無敵時間
	const float SKY_TIME				= 10.0f;	//上空モード時間
	const float INTERVAL_RECOVERY		= 1.0f;		//自動回復インターバル
	const float INTERVAL_BULLET			= 0.2f;		//弾の発射インターバル
	const float CAMERA_SPEED			= 2.0f;		//カメラの速さ
	const float SKY_HEIGHT				= 80.0f;	//上空モードの高さ
	const float RECURSION_TIME			= 3.0f;		//リカージョンの生存時間

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
protected:
	LPDIRECT3DDEVICE9 device;
	TextureLoader* textureLoader;
	ShaderLoader* shaderLoader;
	Input* input;										//入力クラス
	Sound* sound;										//サウンドクラス

	//ステータス
	int type;											//プレイヤータイプ
	int modelType;										//キャラクターモデルタイプ
	int hp;												//体力
	int revivalPoint;									//復活ポイント
	int wage;											//チンギン
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
	float decreaseRevivalTimer;							//復活ポイント減少タイマー
	float transitionTimer;								//遷移時間
	float fallTimer;									//落下時間

	//操作関係
	float reverseValueXAxis;							//操作X軸
	float reverseValueYAxis;							//操作Y軸
	bool onJump;										//ジャンプフラグ
	//弾関係
	int elementBullet;									//弾アクセス要素数
	float intervalBullet;								//発弾間隔

	//接地関係
	float difference;									//フィールド補正差分
	bool onGround;										//接地判定

	//上空モード関係
	float skyHeight;									//上空モード時高さ

	//メモリーアイテム関係
	MemoryPile memoryPile[playerNS::NUM_MEMORY_PILE];	//メモリーパイル
	MemoryLine memoryLine;								//メモリーライン
	MemoryLine starLine;								//星形メモリーライン
	Recursion* recursion;								//リカージョン
	LPDIRECT3DTEXTURE9 recrusionTexture;				//リカージョン用テクスチャ
	int elementMemoryPile;								//メモリーパイル要素数
	bool onRecursion;									//リカージョン生成フラグ
	float recursionTimer;								//リカージョン生存時間

	//衝撃波
	ShockWave* shockWave;								//衝撃波
	bool onShockWave;									//衝撃波生成フラグ
	bool canShockWave;									//衝撃波使用可能フラグ

	//衝突情報
	bool collidedOpponentMemoryLine;					//相手のメモリーラインとの衝突フラグ

	//アクションフラグ
	bool disconnectOpponentMemoryLine;					//相手のメモリーラインの切断アクションメッセージ

public:
	BoundingSphere bodyCollide;							//球コリジョン
	Bullet bullet[playerNS::NUM_BULLET];				//弾


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
	void changeGround();
	void changeFall();
	void changeDown();
	void changeSky(); 
	void changeRevival();
	void updateGround(float frameTime, bool onJump);
	void updateFall(float frameTime);
	void updateDown(float frameTime);
	void updateSky(float frameTime);
	void updateRevival(float frameTime);
	void updateBullet(float frameTime);
	void controlCamera(float frameTime);
	void updateMemoryItem(float frameTime);
	void deleteMemoryItem();
	void triggerShockWave();
	void deleteShockWave();
	void updateShockWave(float frameTime);
	void disconnectMemoryLine();

	//setter
	void setInput(Input* _input);
	void setCamera(Camera* _camera);
	void setSound(Sound* _sound);
	void damgae(int value);
	void recoveryHp(int value);
	void setCollidedMemoryLine(bool frag);

	//getter
	int getHp();
	int getRevivalPoint();
	int getState();
	int getWage();
	bool whetherDown();
	bool whetherRevival();
	bool whetherDeath();
	bool whetherInvincible(); 
	bool whetherSky();
	bool whetherFall();
	bool whetherGenerationRecursion();
	bool whetherCollidedOpponentMemoryLine();
	bool messageDisconnectOpponentMemoryLine();
	Recursion* getRecursion();
	MemoryLine* getMemoryLine();
};