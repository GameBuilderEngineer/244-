//-----------------------------------------------------------------------------
// ���X�����m�Ǘ�����[WasuremonoManager.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/9
//-----------------------------------------------------------------------------
#include "Base.h"
#include "WasuremonoManager.h"
#include "WasuremonoSeries.h"
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
void WasuremonoManager::initialize(LPDIRECT3DDEVICE9 device, std::vector<Wasuremono*> *wasuremono, StaticMeshLoader* staticMeshLoader, Planet*)
{
	if (table == NULL)
	{	// �C���X�^���X�������̂�
		table = new WasuremonoTable(staticMeshLoader);	// �e�[�u������
		Wasuremono::setTable(table);					// �e�[�u�������X�����m�ɐݒ�
		this->device = device;
	}

	this->wasuremono = wasuremono;
	wasuremono->reserve(WASUREMONO_MAX);	// vector�̃������̂ݐ�Ɋm��
	setUp();								// ���X�����m�����z��
	timeCnt = 0.0f;
	respawnMode = 0;
}


//=============================================================================
// �I������
//=============================================================================
void WasuremonoManager::uninitialize(void)
{
	clear();// ���X�����m��Ĕj��
}


//=============================================================================
// �X�V����
//=============================================================================
void WasuremonoManager::update(float frameTime)
{
	// �X�V�Ԋu�𒲐�
	timeCnt += frameTime;
	if (timeCnt < RESPAWN_SURBEY_INTERVAL) { return; }
	timeCnt = 0.0f;

	// ��\���̃��X�����m�����
	for (int i = 0; i < wasuremono->size(); i++)
	{
		if ((*wasuremono)[i]->getActive() == false)
		{
			SAFE_DELETE((*wasuremono)[i])
			wasuremono->erase(wasuremono->begin() + i);
		}
	}

	// �����ɓ��Ă͂܂�΃��X�|�[��
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
	// ��
	if (wasuremono->size() < size_t(INITIAL_PLACEMENT_NUMBER * 0.8f))
	{
		respawnMode = RANDOM;
		return true;
	}
	return false;
}


//=============================================================================
// �������X�|�[������
//=============================================================================
void WasuremonoManager::autoRespawn(void)
{
	D3DXVECTOR3 newPosition;

	switch (respawnMode)
	{
	case RANDOM:
		positionRand(newPosition);
		create(rand() % NUM_WASUREMONO, &newPosition);
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
			wasuremono->emplace_back(new ChewingGum(device, typeID, position));
			break;

		case ELECTRIC_FAN:
			wasuremono->emplace_back(new ElectricFan(device, typeID, position));
			break;

		case JUMP_ROPE:
			wasuremono->emplace_back(new JumpRope(device, typeID, position));
			break;

		case TELEVISION:
			wasuremono->emplace_back(new Television(device, typeID, position));
			break;

		case KENDAMA:
			wasuremono->emplace_back(new Kendama(device, typeID, position));
			break;

		case SOCCER_BALL:
			wasuremono->emplace_back(new SoccerBall(device, typeID, position));
			break;

		case CHRISTMAS_TREE:
			wasuremono->emplace_back(new ChristmasTree(device, typeID, position));
			break;

		case BICYCLE:
			wasuremono->emplace_back(new Bicycle(device, typeID, position));
			break;

		case DIAL_PHONE:
			wasuremono->emplace_back(new DialPhone(device, typeID, position));
			break;

		case STUFFED_BUNNY:
			wasuremono->emplace_back(new StuffedBunny(device, typeID, position));
			break;
		
		default:
			break;
	}

	return wasuremono->back();
}


//=============================================================================
// ���X�����m��j��
//=============================================================================
void WasuremonoManager::destroy(int id)
{
	delete (*wasuremono)[id];
	wasuremono->erase(wasuremono->begin() + id);
}


//=============================================================================
// ���X�����m�����z��
//=============================================================================
void WasuremonoManager::setUp(void)
{
	std::vector<int> type(INITIAL_PLACEMENT_NUMBER);
	setUpInitialType(type);

	std::vector<D3DXVECTOR3> position(INITIAL_PLACEMENT_NUMBER);
	setUpInitialPosition(position);

	for (int i = 0; i < INITIAL_PLACEMENT_NUMBER; i++)
	{
		(*wasuremono)[i] = create(type[i], &position[i]);
	}
}


//=============================================================================
// ���X�����m��Ĕj��
//=============================================================================
void WasuremonoManager::clear(void)
{
	for (size_t i = 0; i < wasuremono->size(); i++)
	{
		delete (*wasuremono)[i];
	}
	(*wasuremono).clear();
}


//=============================================================================
// �Q�[���X�^�[�g���Ƀ��X�����m�̃^�C�v�����߂�A���S���Y��
//=============================================================================
void WasuremonoManager::setUpInitialType(std::vector<int> &type)
{
	for (int i = 0; i < type.size(); i++)
	{
		type[i] = rand() % NUM_WASUREMONO;	// ��
	}
}


//=============================================================================
// �Q�[���X�^�[�g���Ƀ��X�����m��z�u����A���S���Y��
//=============================================================================
void WasuremonoManager::setUpInitialPosition(std::vector<D3DXVECTOR3> &position)
{
	for (int i = 0; i < position.size(); i++)
	{
		positionRand(position[i]);	// ��
	}
}

//=============================================================================
// �����_���z�u
//=============================================================================
D3DXVECTOR3 WasuremonoManager::positionRand(D3DXVECTOR3 &out)
{
	// ��
	float x = (float)(rand() % 100);
	if (rand() % 2) x = -x;
	float y = (float)(rand() % 100);
	if (rand() % 2) y = -y;
	float z = (float)(rand() % 100);
	if (rand() % 2) z = -z;
	D3DXVECTOR3 setPos = D3DXVECTOR3(x, y, z);
	D3DXVec3Normalize(&setPos, &setPos);
	setPos.x *= 200.0f;
	setPos.y *= 200.0f;
	setPos.z *= 200.0f;
	
	out = setPos;
	return setPos;
}

