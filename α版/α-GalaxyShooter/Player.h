#pragma once
#include "Object.h"
#include "BoundingSphere.h"
#include "MemoryPile.h"


namespace playerNS{
	const float SPEED = 30.0f;
	const float JUMP_FORCE = 200.0f;
	const float RECOVERY_TIME = 1.0f;
	const float GRAVITY_FORCE = 80.0f;
}

class Player : public Object
{
private:
	int hp;
	int maxHp;
	int sp;
	int maxSp;
	float recoveryTimer;

public:
	BoundingSphere bodyCollide;

	Player();
	~Player();

	void initialize(LPDIRECT3DDEVICE9 device, StaticMesh* _staticMesh, D3DXVECTOR3* _position);
	void update(float frameTime);
	void toonRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
	void move(D3DXVECTOR2 moveDirection, D3DXVECTOR3 cameraAxisX, D3DXVECTOR3 cameraAxisZ);
	void jump();
	void reset();

	void damgae(int value) { hp = max(hp - value, 0); }
	void recoveryHp(int value) { hp = min(hp + value, maxHp); }
	void lostSp(int value) { sp = max(sp - value,0); }
	void recoverySp(int value) { sp = min(sp + value, maxSp); }

	int getHp() { return hp; }
	int getMaxHp() { return maxHp; }
	int getSp() { return sp; }
	int getMaxSp() { return maxSp; }
};