//-----------------------------------------------------------------------------
// センサー処理 [Sensor.h]
// Author：GP12A332 32 中込和輝
// 作成日：2019/6/15
//-----------------------------------------------------------------------------
#include "Sensor.h"
#include "BlackBoardRecognition.h"
#include <memory>

//=============================================================================
// コンストラクタ
//=============================================================================
Sensor::Sensor(void)
{

}


//=============================================================================
// デストラクタ
//=============================================================================
Sensor::~Sensor(void)
{

}


//=============================================================================
// 初期化処理
//=============================================================================
void Sensor::initialize(void)
{
	KnowledgeSourceBase::initialize();
}


//=============================================================================
// 終了処理
//=============================================================================
void Sensor::uninitialize(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void Sensor::update(void)
{
	// 工事中
	const float& test1 = read<float>(BB::ENVIRONMENT_RECOGNITION, Page::DISTANCE_TO_XXXXXXX4_CRISP_DATA);
	float test2 = copy<float>(BB::ENVIRONMENT_RECOGNITION, Page::DISTANCE_TO_XXXXXXX3_FUZZY_DATA);

	write(BB::ENVIRONMENT_RECOGNITION, Page::DISTANCE_TO_OPPONENT_FUZZY_DATA, test2);

	//// forで回したい
	//const float* test[NUM_DISTANCE_CRISP_DATA];
	//for (int i = 0; i < NUM_DISTANCE_CRISP_DATA; i++)
	//{
	//	test[i] = read<float>(ENVIRONMENT_RECOGNITION, DISTANCE_TO_OPPONENT_CRISP_DATA);
	//}
	
}
