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
		NUM_WASUREMONO,		// ���X�����m��ނ̐�

		// �l�ԁi�ΐ푊��j�̓e�[�u����Ƀf�[�^�̂ݑ��݂���
		// �e�[�u����ȊO�Ń��X�����m�Ƃ��Ă͐����Ȃ�
		HUMAN = NUM_WASUREMONO,

		NUM_TABLE_ELEMENT	// ���X�����m�e�[�u���̗v�f��
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
	StaticMeshLoader* staticMeshLoader;						// ���b�V�����[�_�[
	WasuremonoData data[WasuremonoNS::NUM_TABLE_ELEMENT];	// �e�[�u���{��

public:
	WasuremonoTable(StaticMeshLoader* p);
	~WasuremonoTable(void);

	// �v�f�̃A�h���X�擾
	WasuremonoData* find(int typeID);
	WasuremonoData* find(std::string name);
	WasuremonoData* begin(void);
	// ���݂��邩�����@true�c�c���݂���/false�c�c���݂��Ȃ�
	bool exists(int typeID);
	bool exists(std::string name);
	// ���O���擾
	std::string getName(int typeID);
	// ���z���擾
	int getAmount(int typeID);
	int getAmount(std::string name);
	// ���b�V�������擾
	StaticMesh* getStaticMesh(int typeID);
	StaticMesh* getStaticMesh(std::string name);
	// ���z��������
	void addAmount(int &dest, int typeID);
	void addAmount(int &dest, std::string name);
	// ���z������
	void subAmount(int &dest, int typeID);
	void subAmount(int &dest, std::string name);

	// ���b�V�����[�_�[���Z�b�g
	void setStaticMeshLoader(StaticMeshLoader* staticMeshLoader) { this->staticMeshLoader = staticMeshLoader; }
};


