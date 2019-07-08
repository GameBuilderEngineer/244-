//-----------------------------------------------------------------------------
// �`���M���f�[�^����[ChinginTable.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/7
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include <string>

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace ChinginNS
{
	const static int NUM_CHINGIN = 5;
}


//*****************************************************************************
// �N���X��`
//*****************************************************************************
struct ChinginData
{
	int id;							// �`���M���̌ŗL�ԍ�
	std::string name;				// �`���M���̖��O
	int amount;						// �`���M�����z
};

class ChinginTable
{
private:
	ChinginData data[NUM_CHINGIN];	// �e�[�u���{��

public:
	ChinginTable(void);
	~ChinginTable(void);
	// ���O���擾
	std::string getName(int id);
	// ���z���擾
	int getAmount(int id);
	int getAmount(std::string name);
	// ���z��������
	void addAmount(int &dest, int id);
	void addAmount(int &dest, std::string name);
	// ���z������
	void subAmount(int &dest, int id);
	void subAmount(int &dest, std::string name);
	// �v�f�̃A�h���X�擾
	ChinginData* find(int id);
	ChinginData* find(std::string name);
	ChinginData* find(int amount);
	ChinginData* begin(void);
	// ���݂��邩�����@true�c�c���݂���/false�c�c���݂��Ȃ�
	bool exists(int id);
	bool exists(std::string name);
	bool exists(int amount);
};


