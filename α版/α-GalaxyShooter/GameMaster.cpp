//===================================================================================================================================
//�yGameMaster.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/07/31
// [�X�V��]2019/08/26
//===================================================================================================================================
#include "GameMaster.h"
using namespace gameMasterNS;

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
GameMaster::GameMaster()
{
	ZeroMemory(this, sizeof(GameMaster));
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
GameMaster::~GameMaster()
{

}

//===================================================================================================================================
//�y�������z
//===================================================================================================================================
void GameMaster::initialize()
{
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
void GameMaster::update(float frameTime)
{
	//�Q�[���J�n�J�E���g�_�E��
	gameStartCount(frameTime);
	if (!alreadyStart)return;
	
	//�Q�[���^�C���̍X�V
	updateGameTime(frameTime);
	
	//�Q�[���I���J�E���g�_�E��
	gameFinishCount(frameTime);

}

//===================================================================================================================================
//�y�Q�[�����Ԃ̍X�V�z
//===================================================================================================================================
void GameMaster::updateGameTime(float frameTime)
{
	if (alreadyStart == false)return;
	gameTimer -= frameTime;
}

//===================================================================================================================================
//�y�Q�[���J�n���̃J�E���g�_�E���̍X�V�z
//===================================================================================================================================
void GameMaster::gameStartCount(float frameTime)
{
	if (alreadyStart)return;
	countDownTimer += frameTime;
	if (countDownTimer > COUNT_INTERVAL)
	{
		countDownTimer = 0.0f;
		count--;
	}

	if (count == 0)
	{
		alreadyStart = true;	//�Q�[���J�n
	}

}
//===================================================================================================================================
//�y�Q�[���I�����̃J�E���g�_�E���̍X�V�z
//===================================================================================================================================
void GameMaster::gameFinishCount(float frameTime)
{
	if (gameTimer > COUNT_DOWN)return;
	if (alreadyFinish == false)
	{
		alreadyFinish = true;
		setCountDown();			//�Q�[���I���J�E���g�_�E���̃Z�b�g
	}

	countDownTimer += frameTime;
	if (countDownTimer > COUNT_INTERVAL)
	{
		countDownTimer = 0.0f;
		count--;
	}
}

//===================================================================================================================================
//�y�Q�[���J�E���g�_�E���̃Z�b�g�z
//===================================================================================================================================
void GameMaster::setCountDown()
{
	count = COUNT_DOWN;
	countDownTimer = 0.0f;
}

//===================================================================================================================================
//�y�Q�[���J�n�����z
//===================================================================================================================================
void GameMaster::gameStart()
{
	alreadyStart		= false;
	alreadyFinish		= false;
	gameTimer			= GAME_TIME;
	displayStartTimer	= DISPLAY_START_TIME;
	displayFinishTimer	= DISPLAY_FINISH_TIME;
	setCountDown();
}

//===================================================================================================================================
//�ysetter�z
//===================================================================================================================================
void GameMaster::setWage(int playerNo, int wage){ playerInformation[playerNo].wage = wage;}
void GameMaster::setPlayerCharacter(int playerNo,int playerType, int modelType) {
	if (playerNo >= playerNS::NUM_PLAYER || playerNo < 0)return;
	playerInformation[playerNo].playerType= playerType;
	playerInformation[playerNo].modelType = modelType;
}

//===================================================================================================================================
//�ygetter�z
//===================================================================================================================================
//���s���ʂ��擾
int GameMaster::getResult() {
	int result = DRAW;
	if (playerInformation[playerNS::PLAYER1].wage > playerInformation[playerNS::PLAYER2].wage)
	{
		result = WIN_1P;
	}
	else
	{
		result = WIN_2P;
	}
	return DRAW;
}
//�v���C���[���̎擾
playerTable* GameMaster::getPlayerInfomation(){	return playerInformation;}
//�Q�[���������Ԃ̎擾
float GameMaster::getGameTime() {return gameTimer;}
//�Q�[�����I���������ǂ���
bool GameMaster::whetherGameOver(){	return gameTimer < 0;}
int GameMaster::getCount() { return count; }
bool GameMaster::whetherAlreadyStart() { return alreadyStart; }
bool GameMaster::displayStart() { return displayStartTimer >= 0.0f; }
bool GameMaster::displayFinish() { return displayFinishTimer >= 0.0f; }