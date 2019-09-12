//-----------------------------------------------------------------------------
// ���X�����m�Ǘ�����[WasuremonoManager.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/9
//-----------------------------------------------------------------------------
#include "Base.h"
#include "WasuremonoManager.h"
#include "WasuremonoSeries.h"

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
}


//=============================================================================
// ����������
//=============================================================================
void WasuremonoManager::initialize(LPDIRECT3DDEVICE9 device,
	std::vector<Wasuremono*> *_wasuremono,
	StaticMeshLoader* staticMeshLoader,
	Planet* _field)
{
	table = new WasuremonoTable(staticMeshLoader);	// �e�[�u������
	Wasuremono::setTable(table);					// �e�[�u�������X�����m�ÓI�����o�ɐݒ�
	wasuremono = _wasuremono;
	wasuremono->reserve(WASUREMONO_MAX);			// ���X�����m�|�C���^vector�̃������̂ݐ�ɑ��₵�Ă����i�Ċm�ۖh�~�j
	ZeroMemory(typeCount, sizeof(int) * NUM_WASUREMONO);
	field = _field;
	this->device = device;
	timeCnt = 0.0f;

	//--------------------
	// ���X�����m��Ĕz��
	//--------------------
	// ���X�����m�^�C�v�̌���
	std::vector<int> type(INITIAL_PLACEMENT_NUMBER);
	for (size_t i = 0; i < type.size(); i++)
	{
		type[i] = decideType();
	}

	// ���X�����m�������W�̌���
  	std::vector<D3DXVECTOR3> position(INITIAL_PLACEMENT_NUMBER);
	for (size_t i = 0; i < position.size(); i++)
	{
		position[i] = positionRand(1.05f/*���a��1.0���Ƃ߂荞�݂̊֌W���������ʒu���΂�*/);
	}

	// ���X�����m����Đ���
	for (int i = 0; i < INITIAL_PLACEMENT_NUMBER; i++)
	{
		(*wasuremono)[i] = create(type[i], &position[i]);
	}
}


//=============================================================================
// �I������
//=============================================================================
void WasuremonoManager::uninitialize(void)
{
	SAFE_DELETE(table);	// �e�[�u���j��

	//----------------------
	// ���X�����m����Ĕj��
	//----------------------
	for (size_t i = 0; i < wasuremono->size(); i++)
	{
		delete (*wasuremono)[i];
	}
	std::vector<Wasuremono*> temp;	// �ꎞ�I�u�W�F�N�g�ƃX���b�v����
	(*wasuremono).swap(temp);		// �������A���P�[�^�ɖ߂�
}


//=============================================================================
// �X�V����
//=============================================================================
void WasuremonoManager::update(float frameTime)
{
	// �A�N�e�B�u�łȂ����X�����m��j��
	for (size_t i = 0; i < wasuremono->size(); i++)
	{
		if ((*wasuremono)[i]->getActive() == false)
		{
			destroy(i);
		}
	}

	// �ȉ��̍X�V�Ԋu�𒲐�
	timeCnt += frameTime;
	if (timeCnt < RESPAWN_SURBEY_INTERVAL) { return; }
	timeCnt = 0.0f;

	// �������X�|�[��
	autoRespawn();
}


//=============================================================================
// �������X�|�[������
//=============================================================================
void WasuremonoManager::autoRespawn(void)
{
	D3DXVECTOR3 newPosition;

	if (wasuremono->size() < (size_t)WASUREMONO_MAX)
	{
		newPosition = positionRand(1.5f);
		create(decideType(), &newPosition);
	}
}


//=============================================================================
// ���X�����m���P����
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

	typeCount[typeID]++;		// �^�C�v���Ƃ̃J�E���g�𑝂₷
	return wasuremono->back();
}


//=============================================================================
// ���X�����m���P�j��
//=============================================================================
void WasuremonoManager::destroy(int i)
{
	typeCount[(*wasuremono)[i]->getType()]--;	// �^�C�v���Ƃ̃J�E���g���炷
	delete (*wasuremono)[i];
	wasuremono->erase(wasuremono->begin() + i);
}


//=============================================================================
// �^�C�v�����߂�
//=============================================================================
int WasuremonoManager::decideType()
{
	int temp = rand() % 10000;
	float scale = temp / 100.0f;
	int ans = -1;	// �ԋp�l

	// ���X�����m�o���m�����L�[�l�Ɣ�r����͈͂Ƃ��Ĉ���
	// �L�[�l���͈͓��ɓ������Ƃ��̃��X�����m�Ɍ��肷��
	float sum = 0.0f;
	for (int i = 0; i < NUM_WASUREMONO; i++)
	{
		sum += table->getProbability(i);
		if (scale < sum)
		{
			ans = i;
			break;
		}
	}
	return ans;
}


//=============================================================================
// �����_���z�u
//=============================================================================
D3DXVECTOR3 WasuremonoManager::positionRand(float radiusRatio)
{
	// �����_���ɋɊp�ƕ��ʊp�����߂�
	float latitude = D3DXToRadian(rand() % 181);	// �Ɋp�i�ܓx�j
	float longitude = D3DXToRadian(rand() % 360);	// ���ʊp�i�o�x�j

	// �ɍ��W�𒼌����W�ɕϊ��������
	float x = sinf(latitude) * cosf(longitude);
	float y = sinf(latitude) * sinf(longitude);
	float z = cosf(latitude);

	// �f���Ƃ̋����𒲐�
	D3DXVECTOR3 setPos = D3DXVECTOR3(x, y, z);
	D3DXVec3Scale(&setPos, &setPos, field->getRadius() * radiusRatio);
	setPos += *field->getPosition();

	return setPos;
}


//=============================================================================
// �C���X�^���V���O�`��
//=============================================================================
void WasuremonoManager::instancingRender(LPDIRECT3DDEVICE9 device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR3 cameraPositon, LPD3DXEFFECT effect)
{
	int listAddCount[NUM_WASUREMONO] = { 0 };		// �e���X�g�̗v�f�J�E���^
	int representative[NUM_WASUREMONO] = { -1 };	// �e�N���X�̑�\�C���X�^���X�ԍ�

	// �e�N���X�̍��W���X�g
	D3DXVECTOR3* chewingGumList		= new D3DXVECTOR3[typeCount[CHEWING_GUM]];
	D3DXVECTOR3* electricFanList	= new D3DXVECTOR3[typeCount[ELECTRIC_FAN]];
	D3DXVECTOR3* jumpRopeList		= new D3DXVECTOR3[typeCount[JUMP_ROPE]];
	D3DXVECTOR3* televisionList		= new D3DXVECTOR3[typeCount[TELEVISION]];
	D3DXVECTOR3* kendamaList		= new D3DXVECTOR3[typeCount[KENDAMA]];
	D3DXVECTOR3* soccerBallList		= new D3DXVECTOR3[typeCount[SOCCER_BALL]];
	D3DXVECTOR3* christmasTreeList	= new D3DXVECTOR3[typeCount[CHRISTMAS_TREE]];
	D3DXVECTOR3* bicycleList		= new D3DXVECTOR3[typeCount[BICYCLE]];
	D3DXVECTOR3* dialPhoneList		= new D3DXVECTOR3[typeCount[DIAL_PHONE]];
	D3DXVECTOR3* stuffedBunnyList	= new D3DXVECTOR3[typeCount[STUFFED_BUNNY]];

	// ���W���X�g�𖄂߂�
	for (int i = 0; i < wasuremono->size(); i++)
	{
		switch ((*wasuremono)[i]->getType())
		{
		case CHEWING_GUM:
			chewingGumList[listAddCount[CHEWING_GUM]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[CHEWING_GUM] == 1)
			{
				representative[CHEWING_GUM] = i;
			}
			break;

		case ELECTRIC_FAN:
			electricFanList[listAddCount[ELECTRIC_FAN]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[ELECTRIC_FAN] == 1)
			{
				representative[ELECTRIC_FAN] = i;
			}
			break;

		case JUMP_ROPE:
			jumpRopeList[listAddCount[JUMP_ROPE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[JUMP_ROPE] == 1)
			{
				representative[JUMP_ROPE] = i;
			}
			break;

		case TELEVISION:
			televisionList[listAddCount[TELEVISION]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[TELEVISION] == 1)
			{
				representative[TELEVISION] = i;
			}
			break;

		case KENDAMA:
			kendamaList[listAddCount[KENDAMA]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[KENDAMA] == 1)
			{
				representative[KENDAMA] = i;
			}
			break;

		case SOCCER_BALL:
			soccerBallList[listAddCount[SOCCER_BALL]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[SOCCER_BALL] == 1)
			{
				representative[SOCCER_BALL] = i;
			}
			break;

		case CHRISTMAS_TREE:
			christmasTreeList[listAddCount[CHRISTMAS_TREE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[CHRISTMAS_TREE] == 1)
			{
				representative[CHRISTMAS_TREE] = i;
			}
			break;

		case BICYCLE:
			bicycleList[listAddCount[BICYCLE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[BICYCLE] == 1)
			{
				representative[BICYCLE] = i;
			}
			break;

		case DIAL_PHONE:
			dialPhoneList[listAddCount[DIAL_PHONE]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[DIAL_PHONE] == 1)
			{
				representative[DIAL_PHONE] = i;
			}
			break;

		case STUFFED_BUNNY:
			stuffedBunnyList[listAddCount[STUFFED_BUNNY]] = *(*wasuremono)[i]->getPosition();
			if (++listAddCount[STUFFED_BUNNY] == 1)
			{
				representative[STUFFED_BUNNY] = i;
			}
			break;
		}
	}

	// �C���X�^���V���O�`��ɍ��W���X�g��n��
	(*wasuremono)[representative[CHEWING_GUM]]->setNumOfRender(device, typeCount[CHEWING_GUM], chewingGumList);
	(*wasuremono)[representative[ELECTRIC_FAN]]->setNumOfRender(device, typeCount[ELECTRIC_FAN], electricFanList);
	(*wasuremono)[representative[JUMP_ROPE]]->setNumOfRender(device, typeCount[JUMP_ROPE], jumpRopeList);
	(*wasuremono)[representative[TELEVISION]]->setNumOfRender(device, typeCount[TELEVISION], televisionList);
	(*wasuremono)[representative[KENDAMA]]->setNumOfRender(device, typeCount[KENDAMA], kendamaList);
	(*wasuremono)[representative[SOCCER_BALL]]->setNumOfRender(device, typeCount[SOCCER_BALL], soccerBallList);
	(*wasuremono)[representative[CHRISTMAS_TREE]]->setNumOfRender(device, typeCount[CHRISTMAS_TREE], christmasTreeList);
	(*wasuremono)[representative[BICYCLE]]->setNumOfRender(device, typeCount[BICYCLE], bicycleList);
	(*wasuremono)[representative[DIAL_PHONE]]->setNumOfRender(device, typeCount[DIAL_PHONE], dialPhoneList);
	(*wasuremono)[representative[STUFFED_BUNNY]]->setNumOfRender(device, typeCount[STUFFED_BUNNY], stuffedBunnyList);

	// �C���X�^���V���O�`��
	(*wasuremono)[representative[CHEWING_GUM]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[ELECTRIC_FAN]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[JUMP_ROPE]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[TELEVISION]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[KENDAMA]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[SOCCER_BALL]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[CHRISTMAS_TREE]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[BICYCLE]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[DIAL_PHONE]]->multipleRender(device, view, projection, cameraPositon, effect);
	(*wasuremono)[representative[STUFFED_BUNNY]]->multipleRender(device, view, projection, cameraPositon, effect);

	// ���X�g���
	SAFE_DELETE_ARRAY(chewingGumList)
	SAFE_DELETE_ARRAY(electricFanList)
	SAFE_DELETE_ARRAY(jumpRopeList)
	SAFE_DELETE_ARRAY(televisionList)
	SAFE_DELETE_ARRAY(kendamaList)
	SAFE_DELETE_ARRAY(soccerBallList)
	SAFE_DELETE_ARRAY(christmasTreeList)
	SAFE_DELETE_ARRAY(bicycleList)
	SAFE_DELETE_ARRAY(dialPhoneList)
	SAFE_DELETE_ARRAY(stuffedBunnyList)
}