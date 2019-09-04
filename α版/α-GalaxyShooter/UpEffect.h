//-----------------------------------------------------------------------------
// �A�b�v�G�t�F�N�g�w�b�_�[ [UpEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int UP_EFFECT = 200;	// �����ɕ\�����邤���őÓ������Ȑ�

//--------------------
// �A�b�v�G�t�F�N�g�N���X
//--------------------
class UpEffect :public EffectManager
{
private:
	InstancingEffect instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	EffectIns upEffect[UP_EFFECT];			// �G�t�F�N�g�z��
	int numOfUse;							// �g�p���̐�
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��G�t�F�N�g�̍��W
	LPD3DXMESH sphere;						// �o�E���f�B���O�X�t�B�A�p���`���b�V��

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// �A�b�v�G�t�F�N�g�𔭐�������
	void generateUpEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
};

