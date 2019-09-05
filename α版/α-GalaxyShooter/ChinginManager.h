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

static const int INITIAL_NUM_CHINGIN = 300;	// �|�C���^�z��v�f���̑Ó������ȏ����l

//----------
// �`���M��
//----------
class Chingin	// �d���Ǝv����Object���g���Ă��Ȃ�
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
	Player* target;				// �^�[�Q�b�g�v���C���[

public:
	D3DXVECTOR3* getPosition() { return &position; }
	D3DXVECTOR3* getSpeed() { return &speed; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	BoundingSphere* getCollider() { return &bodyCollide; }
	Player* getTarget(void) { return target; }

	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setTarget(Player* _target) { target = _target; }
};


//--------------------
// �`���M���Ǘ��N���X
//--------------------
class ChinginManager :public Base
{
private:
	Chingin **chingin;						// �`���M���|�C���^�z��
	InstancingChingin instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��`���M���̍��W
	LPD3DXMESH sphere;						// �o�E���f�B���O�X�t�B�A�p���`���b�V��
	int chinginMax;							// �`���M���|�C���^�z��̗v�f��
	int numOfUse;							// �g�p��(�z��Ƀ|�C���^���Z�b�g����Ă���)��

	// �}�O�l�b�g�֌W�͍��͐G��Ȃ��i�������Ă��Ȃ��j
	//int type;
	//float amount;	//���C��
	//void reverseAmount();

	// Method
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition);// �`���M���̈ړ���ݒ�

public:
	void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	void uninitialize(void);
	void update(Sound* _sound, float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void generateChingin(int num, D3DXVECTOR3 setPosition, Player* target);	// �`���M���𔭐�������
};

