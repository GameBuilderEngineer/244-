//============================================================================================================================================
// Document
//============================================================================================================================================
// EffectDew.h
// HAL���� GP-12A-332 09 �T���v��
// 2019/08/30
//============================================================================================================================================
#pragma once
#include "Base.h"
#include "InstancingEffect.h"
#include "TextureLoader.h"
#include "BoundingSphere.h"
#include "Player.h"
#include "EffectManager.h"
//============================================================================================================================================
// NameSpace
// ���O���
//============================================================================================================================================
namespace effectDewNS
{
	const int EFFECT_MAX = (100);	//	�����`�搔
}
//============================================================================================================================================
// Class
// �N���X
//============================================================================================================================================
class EffectDew
{
private:
	BoundingSphere bodyCollide;	//	�o�E���f�B���O�X�t�B�A
	D3DXMATRIX matrixWorld;		//	���[���h���W
	D3DXVECTOR3 position;		//	�ʒu
	D3DXVECTOR3 scale;			//	�X�P�[��
	D3DXVECTOR3 speed;			//	���x
	D3DXVECTOR3 acceleration;	//	�����x
	D3DXVECTOR3 gravity;		//	�d��
	float collisionRadius;		//	�Փ˔��a
	float alpha;				//	�A���t�@�l
	bool existenceFlag;			//	���݃t���O
public:
	D3DXVECTOR3* getPosition(void) { return &position; }
	D3DXVECTOR3* getSpeed(void) { return &speed; }
	D3DXMATRIX* getMatrixWorld(void) { return &matrixWorld; }
	BoundingSphere* getCollider(void) { return &bodyCollide; }
	bool getExistenceFlag(void) { return existenceFlag; }
	void setPosition(D3DXVECTOR3 _position) { position = _position; }
	void setSpeed(D3DXVECTOR3 _speed) { speed = _speed; }
	void setExistenceFlag(bool _flag) { existenceFlag = _flag; }
};

class EffectDewManager :public Base
{
private:
	InstancingEffect instancingProcedure;										//	�r���{�[�h�̃C���X�^���V���O�`�揈���N���X
	EffectDew effectDew[effectDewNS::EFFECT_MAX];								//	�G�t�F�N�g�z��
	int existence;																//	�g�p���̐�
	D3DXVECTOR3* renderList;													//	�C���X�^���V���O�`�悷��G�t�F�N�g�̍��W
	LPD3DXMESH sphere;															//	�o�E���f�B���O�X�t�B�A�p���`���b�V��
	D3DXVECTOR3 moveSpeed(D3DXVECTOR3 _position, D3DXVECTOR3 _targetPosition);	// �ړ����x
public:
	void initialize(LPDIRECT3DDEVICE9 _device, TextureLoader* _textureLoader, LPD3DXEFFECT _effect);
	void update(float _frameTime, Player* _player);
	void render(LPDIRECT3DDEVICE9 _device, D3DXMATRIX _view, D3DXMATRIX _projection, D3DXVECTOR3 _cameraPosition);
	void generateEffect(int _index, D3DXVECTOR3 _positionToGenerate);
};