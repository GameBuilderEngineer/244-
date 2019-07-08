//-----------------------------------------------------------------------------
// �`���M���f�[�^����[ChinginTable.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/7
//-----------------------------------------------------------------------------
#include "ChinginTable.h"
using namespace ChinginNS;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
ChinginTable::ChinginTable(void)
{
	data[0].id = 0;
	data[0].name = "�`���[�C���O�K��";
	data[0].amount = 5;

	data[1].id = 1;
	data[1].name = "��@";
	data[1].amount = 20;

	data[2].id = 2;
	data[2].name = "�Ȃ�Ƃ�";
	data[2].amount = 10;

	data[3].id = 3;
	data[3].name = "�e���r";
	data[3].amount = 50;

	data[4].id = 4;
	data[4].name = "�����";
	data[4].amount = 25;

	data[5].id = 5;
	data[5].name = "�T�b�J�[�{�[��";
	data[5].amount = 20;

	data[6].id = 6;
	data[6].name = "�N���X�}�X�c���[";
	data[6].amount = 75;

	data[7].id = 7;
	data[7].name = "���]��";
	data[7].amount = 50;

	data[8].id = 8;
	data[8].name = "���d�b";
	data[8].amount = 75;

	data[9].id = 9;
	data[9].name = "�E�T�M�̂ʂ������";
	data[9].amount = 200;

	data[10].id = 10;
	data[10].name = "�j���Q���i�ΐ푊��j";
	data[10].amount = 1000;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
ChinginTable::~ChinginTable(void)
{

}


//=============================================================================
// ���O���擾
//=============================================================================
std::string ChinginTable::getName(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			break;
		}
	}
	return out->name;
}


//=============================================================================
// ���z���擾
//=============================================================================
int ChinginTable::getAmount(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			break;
		}
	}
	return out->amount;
}

int ChinginTable::getAmount(std::string name)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->name == name)
		{
			break;
		}
	}
	return out->amount;
}


//=============================================================================
// ���z��������
//=============================================================================
void ChinginTable::addAmount(int &dest, int id)
{
	dest += getAmount(id);
}

void ChinginTable::addAmount(int &dest, std::string name)
{
	dest += getAmount(name);
}


//=============================================================================
// ���z������
//=============================================================================
void ChinginTable::subAmount(int &dest, int id)
{
	dest -= getAmount(id);
}

void ChinginTable::subAmount(int &dest, std::string name)
{
	dest -= getAmount(name);
}


//=============================================================================
// �v�f�̃A�h���X���擾
//=============================================================================
ChinginData* ChinginTable::find(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			return out;
		}
	}
	return NULL;
}

ChinginData* ChinginTable::find(std::string name)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->name == name)
		{
			return out;
		}
	}
	return NULL;
}

ChinginData* ChinginTable::find(int amount)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
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
ChinginData* ChinginTable::begin(void)
{
	return data;
}


//=============================================================================
// ���݂��邩����
//=============================================================================
bool ChinginTable::exists(int id)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->id == id)
		{
			return true;
		}
	}
	return false;
}

bool ChinginTable::exists(std::string name)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->name == name)
		{
			return true;
		}
	}
	return false;
}

bool ChinginTable::exists(int amount)
{
	ChinginData* out = data;
	for (int i = 0; i < NUM_CHINGIN; i++)
	{
		out++;
		if (out->amount == amount)
		{
			return true;
		}
	}
	return false;
}



