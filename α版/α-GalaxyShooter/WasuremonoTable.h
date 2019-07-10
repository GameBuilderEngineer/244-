//-----------------------------------------------------------------------------
// ���X�����m�f�[�^�x�[�X[WasuremonoTable.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/7/7
//-----------------------------------------------------------------------------
#pragma once
#include "Base.h"
#include <string>
#include "StaticMeshLoader.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace WasuremonoNS
{
	// ���X�����m�̎��
	enum WASUREMONO_TYPE
	{
		CHEWING_GUM,		// �`���[�C���O�K��
		ELECTRIC_FAN,		// ��@
		JUMP_ROPE,			// �꒵��
		TELEVISION,			// �e���r
		KENDAMA,			// ���񂾂�
		SOCCER_BALL,		// �T�b�J�[�{�[��
		CHRISTMAS_TREE,		// �N���X�}�X�c���[
		BICYCLE,			// ���]��
		DIAL_PHONE,			// ���d�b
		STUFFED_BUNNY,		// �������̂ʂ������
		HUMAN,				// �l�ԁi�ΐ푊��j

		NUM_WASUREMONO,		// ���X�����m��ނ̐�
	};
}


//*****************************************************************************
// �N���X��`
//*****************************************************************************
struct WasuremonoData
{
	int typeID;				// ���X�����m�̌ŗL�ԍ�
	std::string name;		// ���X�����m�̖��O
	int amount;				// ���X�����m�̃`���M��
	StaticMesh* staticMesh;	// ���b�V�����
};

class WasuremonoTable
{
private:
	StaticMeshLoader* staticMeshLoader;
	WasuremonoData data[WasuremonoNS::NUM_WASUREMONO];	// �e�[�u���{��

public:
	WasuremonoTable(StaticMeshLoader* staticMeshLoader);
	~WasuremonoTable(void);

	// �v�f�̃A�h���X�擾
	WasuremonoData* find(int id);
	WasuremonoData* find(std::string name);
	WasuremonoData* find(int amount);
	WasuremonoData* begin(void);
	// ���݂��邩�����@true�c�c���݂���/false�c�c���݂��Ȃ�
	bool exists(int id);
	bool exists(std::string name);
	bool exists(int amount);
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

	// ���̑��A�N�Z�T
	void setStaticMeshLoader(StaticMeshLoader* staticMeshLoader) { this->staticMeshLoader = staticMeshLoader; }
	StaticMesh* getStaticMesh(int id) { return data[id].staticMesh; }
};


