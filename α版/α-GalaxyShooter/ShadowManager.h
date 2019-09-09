//-----------------------------------------------------------------------------
// �e���� [ShadowManager.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/9/9
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include "InstancingBillboard.h"
#include "TextureLoader.h"

static const int INITIAL_NUM_SHADOW = 200;	// �|�C���^�z��v�f���̑Ó������ȏ����l

//----------
// �e�N���X
//----------
class Shadow
{
private:
	D3DXVECTOR3 *ownerPositionPointer;		// ������̍��W�̃|�C���^
	D3DXVECTOR3 position;					// �ʒu
	D3DXVECTOR3 scale;						// �X�P�[��
	float alpha;							// ���ߒl
	D3DXMATRIX matrixWorld;					// ���[���h���W

public:
	D3DXVECTOR3* getPosition() { return &position; }
	D3DXMATRIX* getMatrixWorld() { return &matrixWorld; }
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
};


//----------------------------
// �C���X�^���V���O�`��N���X
//----------------------------
class InstancingShadowRender :public InstancingBillboard
{
public:
	HRESULT initialize(LPDIRECT3DDEVICE9 device, LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon);
};


//--------------
// �e�Ǘ��N���X
//--------------
class ShadowManager :public Base
{
private:
	Shadow **shadow;							// �e�|�C���^�z��
	InstancingShadowRender instancingProcedure;	// �r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	D3DXVECTOR3* renderList;					// �C���X�^���V���O�`�悷��e�̍��W
	LPD3DXMESH sphere;							// �o�E���f�B���O�X�t�B�A�p���`���b�V��
	int shadowMax;								// �e�|�C���^�z��̗v�f��
	int numOfUse;								// �g�p��(�z��Ƀ|�C���^���Z�b�g����Ă���)��

	// Method
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 position, D3DXVECTOR3 targetPosition);// �e�̈ړ���ݒ�

public:
	void initialize(LPDIRECT3DDEVICE9 device, TextureLoader* _textureLoader, LPD3DXEFFECT effect);
	void uninitialize(void);
	void update(Sound* _sound, float frameTime);
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void generateShadow(int num, D3DXVECTOR3 setPosition, Player* target);	// �e�𔭐�������
};

