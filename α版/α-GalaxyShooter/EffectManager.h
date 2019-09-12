//-----------------------------------------------------------------------------
// �C���X�^���V���O�G�t�F�N�g�w�b�_�[ [InstancingEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Bullet.h"

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
	D3DXVECTOR3* getScale() { return &scale; }
	D3DXVECTOR3* getSpeed() { return &speed; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	BoundingSphere* getCollider() { return &bodyCollide; }
	bool getUse() { return use; }

	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setScale(D3DXVECTOR3 _scale) { speed = _scale; }
	void addSpeed(D3DXVECTOR3 add) { speed += add; }
	void setUse(bool _use) { use = _use; }
	float time;

};
//--------------------
// �G�t�F�N�g�Ǘ��N���X
//--------------------
class EffectManager :public Base
{
protected:
	InstancingEffect instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	int numOfUse;							// �g�p���̐�
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��G�t�F�N�g�̍��W
	LPD3DXMESH sphere;						// �o�E���f�B���O�X�t�B�A�p���`���b�V��
public:
	~EffectManager();
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
};

