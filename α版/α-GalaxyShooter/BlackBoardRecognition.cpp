//-----------------------------------------------------------------------------
// ���F���u���b�N�{�[�h���� [BlackBoardRecognition.cpp]
// Author�FGP12A332 32 �����a�P
// �쐬���F2019/6/19
//-----------------------------------------------------------------------------
#include "BlackBoardRecognition.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
RecognitionBB::RecognitionBB(Player* _opponentPlayer): opponentPlayer(_opponentPlayer)
{
	// No Process
}


//=============================================================================
// ����������
//=============================================================================
void RecognitionBB::initialize(void)
{
	memoryBB = NULL;
	// opponentPlayer = �R���X�g���N�^�Őݒ��
	myPosition = NULL;
	inAir = false;
	distanceBetweenPlayers = 0.0f;
	D3DXVECTOR3 lineCutCoord = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isDestinationDecided = false;

	isOpponentNear = false;
	isOpponentOffensive = false;
	isBulletNear = false;
	isChinginLow = false;

	ZeroMemory(recursionRecognition, sizeof(RecursionRecognition) * NUM_RECURSION_RECOGNITION);
	recursionPolicy = RECURSION_PERSONALITY::LARGEST_WEIGHT;// �����J�[�W�����̕��j��ݒ�
	isStartRecursion = false;
	ZeroMemory(&runningRecursion, sizeof(RecursionRecognition));
	isRecursionRunnning = false;
}