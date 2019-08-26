//-----------------------------------------------------------------------------
// �C���X�^���V���O�G�t�F�N�g�w�b�_�[ [InstancingEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Player.h"
#include "Bullet.h"

static const int NUM_EFFECT = 100;	// �����ɕ\�����邤���őÓ������Ȑ�

//----------
// �G�t�F�N�g
//----------
class EffectIns	// 2�l����200���o��Ȃ�d�����Ǝv����Object���g���Ă��Ȃ�
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
	void addSpeed(D3DXVECTOR3 add) { speed += add; }
	void setUse(bool _use) { use = _use; }
	float time;

};
//--------------------
// �G�t�F�N�g�Ǘ��N���X
//--------------------
class EffectManager :public Base
{
private:
	InstancingEffect instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	EffectIns effectIns[NUM_EFFECT];		// �G�t�F�N�g�z��
	int numOfUse;							// �g�p���̐�
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��G�t�F�N�g�̍��W
	LPD3DXMESH sphere;						// �o�E���f�B���O�X�t�B�A�p���`���b�V��

	// �}�O�l�b�g�֌W�͍��͐G��Ȃ��i�������Ă��Ȃ��j
	//int type;
	//float amount;	//���C��
	//void reverseAmount();

public:
	void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	void update(float frameTime, Player* player);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// �G�t�F�N�g�𔭐�������
	void generateEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};

