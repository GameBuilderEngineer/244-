//-----------------------------------------------------------------------------
// �񕜃G�t�F�N�g�w�b�_�[ [FeelEffect.h]
// ����� �ђˏt�P
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "EffectManager.h"

static const int FEEL_EFFECT = 200;	// �����ɕ\�����邤���őÓ������Ȑ�

//--------------------
// �񕜃G�t�F�N�g�N���X
//--------------------
class FeelEffect :public EffectManager
{
private:
	InstancingEffect instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	EffectIns feelEffect[FEEL_EFFECT];			// �G�t�F�N�g�z��
	int numOfUse;							// �g�p���̐�
	D3DXVECTOR3* renderList;				// �C���X�^���V���O�`�悷��G�t�F�N�g�̍��W
	LPD3DXMESH sphere;						// �o�E���f�B���O�X�t�B�A�p���`���b�V��

public:
	virtual void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	virtual void update(float frameTime);
	virtual void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);

	// �񕜃G�t�F�N�g�𔭐�������
	void generateFeelEffect(int num, D3DXVECTOR3 positionToGenerate, D3DXVECTOR3 effectVec);
	bool feel;
};

