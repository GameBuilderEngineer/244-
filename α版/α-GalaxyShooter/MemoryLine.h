#pragma once
#include "Base.h"
#include "MemoryPile.h"
#include "Player.h"
#include "InstancingBillboard.h"
#include <vector>

namespace memoryLineNS
{
	const float MINIMUM_DISTANCE = 2.0f;
	const float MAXIMUM_DISTANCE = 10.0f;
	const float LOST_TIME = 2.0f;
	const float THICKNESS = 3.0f; // ���C���̑���
}


class MemoryLine : public Base
{
	Line* line;							//�������[���C����`�悷������(���̂ł͂Ȃ�)
	InstancingBillboard billboard;		//�������[���C�����r���{�[�h�̓_�ŕ`�悷�����
	MemoryPile* joinTarget;				//�������[���C�����`�����錳�ɂȂ郁�����[�p�C���̃|�C���^���
	Player* joinPlayer;					//�������[���C���𐶐������v���C���[�ւ̃|�C���^���
	D3DXVECTOR3** pointList;			//�������[�p�C�����Ƃ̃������[���C�����`������`�悷��_�̈ʒu���X�g
	D3DXVECTOR3* renderList;			//�������[���C���S�̂̕`�惊�X�g�i�C���X�^���X�r���{�[�h���v����ʒu���X�g�͈�j
	bool initialized;					//�������t���O�i�������[�A�N�Z�X�G���[�h�~�j
	bool disconnected;					//�ؒf�t���O�i�ؒf�����ƁA���������ֈڍs����j
	float lostTime;						//���������p�^�C�}�[
	int pileNum;						//�������[�p�C���̍ő吔�i��A�N�e�B�u���܂ށj
	int* pointNum;						//�e�������[�p�C�����n�_�Ƃ��郁�����[���C����̓_�̐��̃��X�g
	int renderNum;						//�������[���C���S�̂̕`�搔
public:
	MemoryLine();
	~MemoryLine();

	//proccessing
	void initialize(LPDIRECT3DDEVICE9 device, MemoryPile* memoryPile, int num, Player* player, 
		LPD3DXEFFECT effect, LPDIRECT3DTEXTURE9 texture);
	void unInitialize();
	void render(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPosition);
	void update(LPDIRECT3DDEVICE9 device, float frameTime);

	//operation
	bool collision(D3DXVECTOR3 position, float radius);	//�Փˌ��m
	float calculationDistance(D3DXVECTOR3 point);		//(���Z)����_�ƃ��C���Ƃ̋�����߂�
	void setLine(LPDIRECT3DDEVICE9 device);				//(�X�V)�������[�p�C���̊Ԃ̃��C����ݒ肷��
	void lost(float frameTime);							//(�X�V)��������
	void disconnect();									//(�ؑ�)�ؒf����
	//setter
	//getter
};