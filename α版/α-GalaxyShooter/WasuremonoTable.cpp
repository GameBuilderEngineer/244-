//-----------------------------------------------------------------------------
// ���X�����m�f�[�^�[�x�[�X[WasuremonoTable.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/7
//-----------------------------------------------------------------------------
#include "WasuremonoTable.h"
using namespace WasuremonoNS;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
WasuremonoTable::WasuremonoTable(StaticMeshLoader* staticMeshLoader)
{
	this->staticMeshLoader = staticMeshLoader;

	// �e�[�u���̍\�z
	data[CHEWING_GUM].typeID = CHEWING_GUM;
	data[CHEWING_GUM].name = "�`���[�C���O�K��";
	data[CHEWING_GUM].amount = 5;
	data[CHEWING_GUM].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);
	data[ELECTRIC_FAN].typeID = ELECTRIC_FAN;

	data[ELECTRIC_FAN].name = "��@";
	data[ELECTRIC_FAN].amount = 20;
	data[ELECTRIC_FAN].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[JUMP_ROPE].typeID = JUMP_ROPE;
	data[JUMP_ROPE].name = "�Ȃ�Ƃ�";
	data[JUMP_ROPE].amount = 10;
	data[JUMP_ROPE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[TELEVISION].typeID = TELEVISION;
	data[TELEVISION].name = "�e���r";
	data[TELEVISION].amount = 50;
	data[TELEVISION].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[KENDAMA].typeID = KENDAMA;
	data[KENDAMA].name = "�����";
	data[KENDAMA].amount = 25;
	data[KENDAMA].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[SOCCER_BALL].typeID = SOCCER_BALL;
	data[SOCCER_BALL].name = "�T�b�J�[�{�[��";
	data[SOCCER_BALL].amount = 20;
	data[SOCCER_BALL].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[CHRISTMAS_TREE].typeID = CHRISTMAS_TREE;
	data[CHRISTMAS_TREE].name = "�N���X�}�X�c���[";
	data[CHRISTMAS_TREE].amount = 75;
	data[CHRISTMAS_TREE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[BICYCLE].typeID = BICYCLE;
	data[BICYCLE].name = "���]��";
	data[BICYCLE].amount = 50;
	data[BICYCLE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[DIAL_PHONE].typeID = DIAL_PHONE;
	data[DIAL_PHONE].name = "���d�b";
	data[DIAL_PHONE].amount = 75;
	data[DIAL_PHONE].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[STUFFED_BUNNY].typeID = STUFFED_BUNNY;
	data[STUFFED_BUNNY].name = "�E�T�M�̂ʂ������";
	data[STUFFED_BUNNY].amount = 200;
	data[STUFFED_BUNNY].staticMesh = &(staticMeshLoader->staticMesh[staticMeshNS::BULLET]);

	data[HUMAN].typeID = HUMAN;
	data[HUMAN].name = "�j���Q���i�ΐ푊��j";
	data[HUMAN].amount = 1000;
	data[HUMAN].staticMesh = NULL;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
WasuremonoTable::~WasuremonoTable(void)
{

}


//=============================================================================
// �v�f�̃A�h���X���擾
//=============================================================================
WasuremonoData* WasuremonoTable::find(int typeID)
{
	if (typeID < NUM_WASUREMONO)
	{
		return &data[typeID];
	}
	return NULL;
}

WasuremonoData* WasuremonoTable::find(std::string name)
{
	WasuremonoData* out = data;
	for (int i = 0; i < NUM_WASUREMONO; i++)
	{
		out++;
		if (out->name == name)
		{
			return out;
		}
	}
	return NULL;
}

WasuremonoData* WasuremonoTable::find(int amount)
{
	WasuremonoData* out = data;
	for (int i = 0; i < NUM_WASUREMONO; i++)
	{
		out++;
		if (out->amount == amount)
		{
			return out;
		}
	}
	return NULL;
}

// �擪�v�f���擾
WasuremonoData* WasuremonoTable::begin(void)
{
	return data;
}


//=============================================================================
// ���݂��邩����
//=============================================================================
bool WasuremonoTable::exists(int typeID)
{
	if (typeID < NUM_WASUREMONO) return true;
	else return false;
}

bool WasuremonoTable::exists(std::string name)
{
	WasuremonoData *p = find(name);
	if (p != NULL)
	{
		return 	true;
	}
	return false;
}

bool WasuremonoTable::exists(int amount)
{
	WasuremonoData *p = find(amount);
	if (p != NULL)
	{
		return 	true;
	}
	return false;
}

//=============================================================================
// ���O���擾
//=============================================================================
std::string WasuremonoTable::getName(int typeID)
{
	if (typeID < NUM_WASUREMONO)
	{
		return data[typeID].name;
	}
	return "�s����ID����";
}


//=============================================================================
// ���z���擾
//=============================================================================
int WasuremonoTable::getAmount(int typeID)
{
	if (typeID < NUM_WASUREMONO)
	{
		return data[typeID].amount;
	}
	return -1;
}

int WasuremonoTable::getAmount(std::string name)
{
	WasuremonoData *p = find(name);
	if (p != NULL)
	{
		return 	p->amount;
	}
	return -1;
}


//=============================================================================
// ���z��������
//=============================================================================
void WasuremonoTable::addAmount(int &dest, int typeID)
{
	dest += getAmount(typeID);
}

void WasuremonoTable::addAmount(int &dest, std::string name)
{
	dest += getAmount(name);
}


//=============================================================================
// ���z������
//=============================================================================
void WasuremonoTable::subAmount(int &dest, int typeID)
{
	dest -= getAmount(typeID);
}

void WasuremonoTable::subAmount(int &dest, std::string name)
{
	dest -= getAmount(name);
}

