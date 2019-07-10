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
// �C���N���[�h��
// WasuremonoTable��Wasuremono, WasuremonoManager
// Wasuremono��WasuremonoManager

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace WasuremonoNS
{
	// ���X�|�[�����[�h
	enum RESPAWN_MODE
	{
		FEW_WASUREMONO		// ���X�����m�̏��Ȃ��ꏊ�Ƀ��X�|�[��
	};


	const static int INITIAL_PLACEMENT_NUMBER = 100;
}

#define SECOND(_s)	(_s * 60/*fps*/)



//*****************************************************************************
// �N���X��`
//*****************************************************************************
class WasuremonoManager
{
private:
	DWORD frameCnt;						// �t���[���J�E���g

	// ���X�����m�\�i���̂�`���M�����Q�Ɖ\�j
	WasuremonoTable* table;

	// ���X�����m�X���b�g�i�����������X�����m���Ǘ�����|�C���^vector�j
	std::vector<Wasuremono*> wasuremono;

	// �������A���S���Y��
	void setUpInitialType(int typeID[]);
	void setUpInitialPosition(D3DXVECTOR3 position[]);

	// ���X�|�[���֌W
	int respawnMode;					// ���X�|�[���̃��[�h
	bool surbeyRespawnCondition(void);	// ���X�|�[�������𒲂ׂ�
	void autoRespawn(void);				// �������X�|�[������

public:
	WasuremonoManager(void);
	~WasuremonoManager(void);
	void initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader);// ������
	void uninitialize(void);					// �I������
	void update(void);							// �X�V����
	Wasuremono* create(int typeID, D3DXVECTOR3 *position);// ���X�����m�𐶐�
	void destroy(int id);						// ���X�����m��j��
	void startWork(void);						// �Q�[���J�n���̃��X�����m��������
	void finishWork(void);						// �Q�[���I�����̃��X�����m��Ĕj��
};


