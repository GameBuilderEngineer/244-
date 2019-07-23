//-----------------------------------------------------------------------------
// �L���u���b�N�{�[�h���� [BlackBoardMemory.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "BlackBoardBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class MemoryBB : public BlackBoardBase {
private:
	// Data
	enum {
		INDEX,
		NUM_DATA
	};



public:
	// Method
	MemoryBB(void);
	~MemoryBB(void);
	void initialize(void) override;				// ����������
	void uninitialize(void) override;			// �I������
	bool getAccessPermission(int tag) override;	// ���W���[���ɃA�N�Z�X����Ԃ�
};