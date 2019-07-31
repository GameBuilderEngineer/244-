#pragma once
#include "Object.h"
#include "BoundingSphere.h"
//#include "MemoryPile.h"
//#include "MemoryLine.h"
//#include "Recursion.h"
#include "Bullet.h"

namespace playerNS{
	const float SPEED = 30.0f;
	const float JUMP_FORCE = 200.0f;
	const float RECOVERY_TIME = 1.0f;
	const float GRAVITY_FORCE = 80.0f;

	enum PLAYER_TYPE{
		PLAYER1,
		PLAYER2,
		NUM_PLAYER
	};

	enum STATE {
		DEFAULT,
		DOWN,
		SKY,
		STATE_NUM
	};

	const float DOWN_TIME = 3.0f;
	const float SKY_TIME = 10.0f;
	
	const int NUM_BULLET = 30;				//弾の数
	const float INTERVAL_TIME_BULLET = 0.2f;//弾の発射インターバル
	const int NUM_MEMORY_PILE = 5;			//メモリーパイルの数

	//プレイヤーのスタートポジション
	const D3DXVECTOR3 START_POSITION[NUM_PLAYER] =
	{
		D3DXVECTOR3(0,100,0),
		D3DXVECTOR3(0,-100,0)
	};
}

class Player : public Object
{
private:
	int type;
	//ステータス
	int hp;
	int maxHp;
	int sp;
	int maxSp;
	int wage;								//チンギン

	int state;								//状態変数

	float recoveryTimer;					//自動回復時間
	float invincibleTimer;					//無敵時間
	float skyTimer;							//上空モード制限時間
	float downTimer;						//ダウンタイマー[体力が切れるorメモリーラインを切断される]

	Bullet bullet[playerNS::NUM_BULLET];	//弾


public:
	BoundingSphere bodyCollide;	//球コリジョン

	Player();
	~Player();

	//processing
	virtual void initialize(int playerType,LPDIRECT3DDEVICE9 device,StaticMesh* _staticMesh);
	virtual void initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position);
	virtual void update(float frameTime);
	void toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon,
		LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 textureShade, LPDIRECT3DTEXTURE9 textureLine);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	
	//operation
	void move(D3DXVECTOR2 moveDirection, D3DXVECTOR3 cameraAxisX, D3DXVECTOR3 cameraAxisZ);
	void jump();
	void reset();
	void changeState(int _state);
	void down();
	void sky();

	//setter
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

};