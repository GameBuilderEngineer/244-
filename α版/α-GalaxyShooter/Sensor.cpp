//-----------------------------------------------------------------------------
// �Z���T�[���� [Sensor.h]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/15
//-----------------------------------------------------------------------------
#include "Sensor.h"
#include "BlackBoardRecognition.h"
#include <memory>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Sensor::Sensor(void)
{

}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
Sensor::~Sensor(void)
{

}


//=============================================================================
// ����������
//=============================================================================
void Sensor::initialize(void)
{
	KnowledgeSourceBase::initialize();
}


//=============================================================================
// �I������
//=============================================================================
void Sensor::uninitialize(void)
{

}


//=============================================================================
// �X�V����
//=============================================================================
void Sensor::update(void)
{
	// �H����
	const float& test1 = read<float>(BB::ENVIRONMENT_RECOGNITION, Page::DISTANCE_TO_XXXXXXX4_CRISP_DATA);
	float test2 = copy<float>(BB::ENVIRONMENT_RECOGNITION, Page::DISTANCE_TO_XXXXXXX3_FUZZY_DATA);

	write(BB::ENVIRONMENT_RECOGNITION, Page::DISTANCE_TO_OPPONENT_FUZZY_DATA, test2);

	//// for�ŉ񂵂���
	//const float* test[NUM_DISTANCE_CRISP_DATA];
	//for (int i = 0; i < NUM_DISTANCE_CRISP_DATA; i++)
	//{
	//	test[i] = read<float>(ENVIRONMENT_RECOGNITION, DISTANCE_TO_OPPONENT_CRISP_DATA);
	//}
	
}
