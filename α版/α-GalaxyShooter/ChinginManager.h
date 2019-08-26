//-----------------------------------------------------------------------------
// �`���M������ [Chingin.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/8/1
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingChingin.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Player.h"
#include "Sound.h"

static const int NUM_CHINGIN = 100;	// �����ɕ\�����邤���őÓ������Ȑ�

//----------
// �`���M��
//----------
class Chingin	// 2�l����200���o��Ȃ�d�����Ǝv����Object���g���Ă��Ȃ�
{
private:
	D3DXVECTOR3 position;		// �ʒu
	D3DXVECTOR3 scale;			// �X�P�[��
	float radius;				// �Փ˔��a
	float alpha;				// ���ߒl
	D3DXVECTOR3 speed;			// ���x
	D3DXVECTOR3 acceleration;	// �����x
	D3DXVECTOR3 gravity;		// �d��
	D3DXMATRIX matrixWorld;		// ���[���h���W
	BoundingSphere bodyCollide;	// �o�E���f�B���O�X�t�B�A
	bool use;					// �g�p����

public:
	D3DXVECTOR3* getPosition() { return &position; }
	D3DXVECTOR3* getSpeed() { return &speed; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	BoundingSphere* getCollider() { return &bodyCollide; }
	bool getUse() { return use; }

	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setUse(bool _use) { use = _use; }
};


//--------------------
// �`���M���Ǘ��N���X
//--------------------
class ChinginManager :public Base
{
private:
	InstancingChingin instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	Chingin chingin[NUM_CHINGIN];			// �`���M���z��
	int numOfUse;							// �g�p���̐�
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��`���M���̍��W
	LPD3DXMESH sphere;						// �o�E���f�B���O�X�t�B�A�p���`���b�V��
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition);// �ړ����x

	// �}�O�l�b�g�֌W�͍��͐G��Ȃ��i�������Ă��Ȃ��j
	//int type;
	//float amount;	//���C��
	//void reverseAmount();

public:
	void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	void update(Sound* _sound, float frameTime, Player* player);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// �`���M���𔭐�������
	void generateChingin(int num, D3DXVECTOR3 positionToGenerate);
};

