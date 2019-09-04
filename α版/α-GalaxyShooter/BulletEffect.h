//-----------------------------------------------------------------------------
// �e�G�t�F�N�g�w�b�_�[ [BulletEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Bullet.h"
#include "EffectManager.h"

static const int BULLET_EFFECT = 100;			// �����ɕ\�����邤���őÓ������Ȑ�
static const float BULLET_EFFECT_TIME = 0.04;	// �G�t�F�N�g��������

//--------------------
// �e�G�t�F�N�g�N���X
//--------------------
class BulletEffect :public EffectManager
{
private:
	InstancingEffect instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	EffectIns bulletEffect[BULLET_EFFECT];	// �G�t�F�N�g�z��
	EffectIns bulletSmokeEffect[BULLET_EFFECT];	// �G�t�F�N�g�z��
	int numOfUse;							// �g�p���̐�
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��G�t�F�N�g�̍��W
	LPD3DXMESH sphere;						// �o�E���f�B���O�X�t�B�A�p���`���b�V��

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// �e�G�t�F�N�g�𔭐�������
	void generateBulletEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};

