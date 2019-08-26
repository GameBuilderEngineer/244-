//===================================================================================================================================
//【GameMaster.cpp】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/07/31
// [更新日]2019/08/26
//===================================================================================================================================
#include "GameMaster.h"
using namespace gameMasterNS;

//===================================================================================================================================
//【コンストラクタ】
//===================================================================================================================================
GameMaster::GameMaster()
{
	ZeroMemory(this, sizeof(GameMaster));
}

//===================================================================================================================================
//【デストラクタ】
//===================================================================================================================================
GameMaster::~GameMaster()
{

}

//===================================================================================================================================
//【初期化】
//===================================================================================================================================
void GameMaster::initialize()
{
}

//===================================================================================================================================
//【更新】
//===================================================================================================================================
void GameMaster::update(float frameTime)
{
	//ゲーム開始カウントダウン
	gameStartCount(frameTime);
	if (!alreadyStart)return;
	
	//ゲームタイムの更新
	updateGameTime(frameTime);
	
	//ゲーム終了カウントダウン
	gameFinishCount(frameTime);

}

//===================================================================================================================================
//【ゲーム時間の更新】
//===================================================================================================================================
void GameMaster::updateGameTime(float frameTime)
{
	if (alreadyStart == false)return;
	gameTimer -= frameTime;
}

//===================================================================================================================================
//【ゲーム開始時のカウントダウンの更新】
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
		alreadyStart = true;	//ゲーム開始
	}

}
//===================================================================================================================================
//【ゲーム終了時のカウントダウンの更新】
//===================================================================================================================================
void GameMaster::gameFinishCount(float frameTime)
{
	if (gameTimer > COUNT_DOWN)return;
	if (alreadyFinish == false)
	{
		alreadyFinish = true;
		setCountDown();			//ゲーム終了カウントダウンのセット
	}

	countDownTimer += frameTime;
	if (countDownTimer > COUNT_INTERVAL)
	{
		countDownTimer = 0.0f;
		count--;
	}
}

//===================================================================================================================================
//【ゲームカウントダウンのセット】
//===================================================================================================================================
void GameMaster::setCountDown()
{
	count = COUNT_DOWN;
	countDownTimer = 0.0f;
}

//===================================================================================================================================
//【ゲーム開始処理】
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
//【setter】
//===================================================================================================================================
void GameMaster::setWage(int playerNo, int wage){ playerInformation[playerNo].wage = wage;}
void GameMaster::setPlayerCharacter(int playerNo,int playerType, int modelType) {
	if (playerNo >= playerNS::NUM_PLAYER || playerNo < 0)return;
	playerInformation[playerNo].playerType= playerType;
	playerInformation[playerNo].modelType = modelType;
}

//===================================================================================================================================
//【getter】
//===================================================================================================================================
//勝敗結果を取得
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
//プレイヤー情報の取得
playerTable* GameMaster::getPlayerInfomation(){	return playerInformation;}
//ゲーム制限時間の取得
float GameMaster::getGameTime() {return gameTimer;}
//ゲームが終了したかどうか
bool GameMaster::whetherGameOver(){	return gameTimer < 0;}
int GameMaster::getCount() { return count; }
bool GameMaster::whetherAlreadyStart() { return alreadyStart; }
bool GameMaster::displayStart() { return displayStartTimer >= 0.0f; }
bool GameMaster::displayFinish() { return displayFinishTimer >= 0.0f; }