//-----------------------------------------------------------------------------
// �ӎv���菈�� [DecisionMaking.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#pragma once
#include "KnowledgeSourceBase.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class DecisionMaking:public KnowledgeSourceBase {
private:

public:
	// Method
	DecisionMaking(void);
	~DecisionMaking(void);
	void initialize(void) override;		// ����������
	void uninitialize(void) override;	// �I������
	void update(void) override;			// �X�V����
};