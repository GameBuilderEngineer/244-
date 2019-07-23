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

// �C���N���[�h��
// WasuremonoTable��Wasuremono, WasuremonoSeries, WasuremonoManager
// Wasuremono��WasuremonoSeries, WasuremonoManager
// WasuremonoSeries��WasuremonoManager

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace WasuremonoNS
{
	// ���X�|�[�����[�h
	enum RESPAWN_MODE
	{
		RANDOM		// �����_��
	};

	const static int WASUREMONO_MAX = 200;
	const static int INITIAL_PLACEMENT_NUMBER = 100;
	const static float RESPAWN_SURBEY_INTERVAL = 3.0f;
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
	float timeCnt;							// ���ԃJ�E���g
	int respawnMode;						// ���X�|�[���̃��[�h
	LPDIRECT3DDEVICE9 device;				// �f�o�C�X
	Planet *field;							// �t�B�[���h���
		
	// �^�C�v������
	void setUpInitialType(std::vector<int> &type);
	// ���W������
	void setUpInitialPosition(std::vector<D3DXVECTOR3> &position);
	// ���X�|�[�������𒲂ׂ�
	bool surbeyRespawnCondition(void);
	// �������X�|�[������
	void autoRespawn(void);
	// �����_���z�u
	D3DXVECTOR3 positionRand(D3DXVECTOR3 &out);


public:
	WasuremonoManager(void);
	~WasuremonoManager(void);							
	void initialize(LPDIRECT3DDEVICE9 device, std::vector<Wasuremono*> *wasuremono, StaticMeshLoader* staticMeshLoader, Planet*);
	void uninitialize(void);
	void update(float frameTime);

	// ���X�����m�𐶐�
	Wasuremono* create(int typeID, D3DXVECTOR3 *position);
	// ���X�����m��j��
	void destroy(int id);
	// ���X�����m�����z��
	void setUp(void);
	// ���X�����m��Ĕj��
	void clear(void);
};


