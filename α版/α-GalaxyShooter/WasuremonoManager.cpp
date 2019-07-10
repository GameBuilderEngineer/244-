//-----------------------------------------------------------------------------
// ���X�����m�Ǘ�����[WasuremonoManager.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/9
//-----------------------------------------------------------------------------
#include "Base.h"
#include "WasuremonoManager.h"
using namespace WasuremonoNS;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
WasuremonoManager::WasuremonoManager(void)
{
	table = NULL;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
WasuremonoManager::~WasuremonoManager(void)
{
	SAFE_DELETE(table);
}


//=============================================================================
// ����������
//=============================================================================
void WasuremonoManager::initialize(LPDIRECT3DDEVICE9 device, StaticMeshLoader* staticMeshLoader)
{
	if (table == NULL)
	{// ����̎��s�̏ꍇ
		table = new WasuremonoTable(staticMeshLoader);
		// �f�X�g���N�^�Ŕj���i�Q�[���V�[�������v���C����ꍇ�̏������Ȃǔj���s�v�ȃP�[�X��z��j

		Wasuremono::setDevice(device);
		Wasuremono::setTable(table);
	}

	frameCnt = 0;
	respawnMode = 0;
}


//=============================================================================
// �I������
//=============================================================================
void WasuremonoManager::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void WasuremonoManager::update(void)
{
	// �X�V�p�x�𒲐�
	if (frameCnt++ < SECOND(3)) { return; }
	frameCnt = 0;

	// �󋵂��擾�����X�|�[���𔻒f����
	if (surbeyRespawnCondition() == true)
	{
		autoRespawn();
	}
}


//=============================================================================
// ���X�|�[�������𒲂ׂ�
//=============================================================================
bool WasuremonoManager::surbeyRespawnCondition(void)
{
	// ���̏���
	if (wasuremono.size() < size_t(INITIAL_PLACEMENT_NUMBER * 0.8f))
	{
		respawnMode = FEW_WASUREMONO;
		return true;
	}

	return false;
}


//=============================================================================
// �������X�|�[������
//=============================================================================
void WasuremonoManager::autoRespawn(void)
{
	switch (respawnMode)
	{
	case FEW_WASUREMONO:
		break;

	default:
		break;
	}
}


//=============================================================================
// ���X�����m�𐶐�
//=============================================================================
Wasuremono* WasuremonoManager::create(int typeID, D3DXVECTOR3 *position)
{
	switch (typeID)
	{
		case CHEWING_GUM:
			wasuremono.push_back(new ChewingGum(typeID, position));
			break;

		case ELECTRIC_FAN:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case JUMP_ROPE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case TELEVISION:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case KENDAMA:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case SOCCER_BALL:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case CHRISTMAS_TREE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case BICYCLE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case DIAL_PHONE:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;

		case STUFFED_BUNNY:
			wasuremono.push_back(new Wasuremono(typeID, position));
			break;
		
		default:
			break;
	}
	return wasuremono.back();
}


//=============================================================================
// ���X�����m��j��
//=============================================================================
void WasuremonoManager::destroy(int id)
{
	delete wasuremono[id];
	wasuremono.erase(wasuremono.begin() + id);
}


//=============================================================================
// �Q�[���J�n���̃��X�����m��������
//=============================================================================
void WasuremonoManager::startWork(void)
{
	wasuremono.reserve(INITIAL_PLACEMENT_NUMBER);		// �|�C���^�m��

	int typeID[INITIAL_PLACEMENT_NUMBER];				// ��ސ���
	setUpInitialType(typeID);

	D3DXVECTOR3 position[INITIAL_PLACEMENT_NUMBER];		// ���W����
	setUpInitialPosition(position);

	for (int i = 0; i < INITIAL_PLACEMENT_NUMBER; i++)
	{
		wasuremono[i] = create(typeID[i], &position[i]);
	}
}


//=============================================================================
// �Q�[���I�����̃��X�����m��Ĕj��
//=============================================================================
void WasuremonoManager::finishWork(void)
{
	for (size_t i = 0; i < wasuremono.size(); i++)
	{
		delete wasuremono[i];
	}
	wasuremono.clear();
}


//=============================================================================
// �Q�[���X�^�[�g���Ƀ��X�����m�̃^�C�v�����߂�A���S���Y��
//=============================================================================
void WasuremonoManager::setUpInitialType(int typeID[])
{

}


//=============================================================================
// �Q�[���X�^�[�g���Ƀ��X�����m��z�u����A���S���Y��
//=============================================================================
void WasuremonoManager::setUpInitialPosition(D3DXVECTOR3 position[])
{
	
}