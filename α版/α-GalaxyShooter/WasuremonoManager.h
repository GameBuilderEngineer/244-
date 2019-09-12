//-----------------------------------------------------------------------------
// ���X�����m�Ǘ�����[WasuremonoManager.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/9
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include "StaticMeshLoader.h"
#include "WasuremonoTable.h"
#include "Wasuremono.h" 
#include "Planet.h"
using namespace WasuremonoNS;

// �C���N���[�h��
// WasuremonoTable��Wasuremono, WasuremonoSeries, WasuremonoManager
// Wasuremono��WasuremonoSeries, WasuremonoManager
// WasuremonoSeries��WasuremonoManager

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace WasuremonoNS
{
	const static int WASUREMONO_MAX = 160;				// ���X�����m�ő吔	
	const static int INITIAL_PLACEMENT_NUMBER = 120;		// ���X�����m�����z����
	const static float RESPAWN_SURBEY_INTERVAL = 1.5f;	// ���X�����m���X�|�[���Ԋu(�b)
}


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class WasuremonoManager
{
private:
	// Data
	WasuremonoTable* table;					// ���X�����m�\�i���̂�`���M�����Q�Ɖ\�j
	std::vector<Wasuremono*>* wasuremono;	// ���X�����m
	int typeCount[NUM_WASUREMONO];			// ���X�����m���Ƃ̐��i�C���X�^���V���O�`��Ŏg���j
	Planet* field;							// �t�B�[���h
	LPDIRECT3DDEVICE9 device;				// �f�o�C�X
	float timeCnt;							// ���ԃJ�E���g


	// �������X�|�[������
	void autoRespawn(void);
	// �����_���z�u
	D3DXVECTOR3 positionRand(float radiusRatio);
	// �^�C�v�����߂�
	int decideType(void);

public:
	WasuremonoManager(void);
	~WasuremonoManager(void);							
	void initialize(LPDIRECT3DDEVICE9 device, std::vector<Wasuremono*> *_wasuremono, StaticMeshLoader* staticMeshLoader, Planet* _field);
	void uninitialize(void);
	void update(float frameTime);

	// ���X�����m���P����
	Wasuremono* create(int typeID, D3DXVECTOR3 *position);
	// ���X�����m���P�j��
	void destroy(int i);
	// �C���X�^���V���O�`��
	void instancingRender(LPDIRECT3DDEVICE9 device,
		D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon, LPD3DXEFFECT effect);
};


