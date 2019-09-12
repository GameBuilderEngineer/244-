//===================================================================================================================================
//【AbstractScene.h】
// [作成者]HAL東京GP12A332 11 菅野 樹
// [作成日]2019/05/16
// [更新日]2019/08/04
//===================================================================================================================================
#pragma once
#include "Base.h"
#include "Camera.h"
#include "Input.h"
#include "Light.h"
#include "Sound.h"
#include "TextureLoader.h"
#include "StaticMeshLoader.h"
#include "ShaderLoader.h"
#include "TextManager.h"
#include "GameMaster.h"
#include "AnimationLoader.h"
#include <string>

namespace SceneList
{
	enum {
		NONE_SCENE = -1,
		RESULT,
		SPLASH,
		TITLE,
		SELECT,
		TUTORIAL,
		OPERATION,
		CREDIT,
		GAME,
	};
}

class AbstractScene :public Base
{
protected:
	//Data
	Direct3D9* direct3D9;
	Input* input;
	Sound* sound;
	Camera* camera;
	Light* light;
	TextureLoader* textureLoader;
	StaticMeshLoader* staticMeshLoader;
	ShaderLoader* shaderLoader;
	AnimationLoader* animationLoader;
	TextManager* textManager;
	GameMaster* gameMaster;
	float sceneTimer;
	bool onChange;
	int nextScene;
	std::string sceneName;
public:
	//Method
	AbstractScene();
	virtual ~AbstractScene();
	virtual void initialize(
		Direct3D9* _direct3D9,
		Input* _input,
		Sound* _sound,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader,
		TextManager* _textManager) = 0;		//初期化
	virtual void update(float frameTime) = 0;			//更新
	virtual void render(Direct3D9* direct3D9) = 0;		//描画
	virtual void collisions() = 0;						//衝突処理
	virtual void AI() = 0;								//AI処理
	virtual void uninitialize() = 0;					//終了処理

	//シーン切替関係関数
	void changeScene(int i) { onChange = true; nextScene = i; };
	bool checkChangeOrder() { return onChange; };
	int checkNextScene() { return nextScene; }
	std::string* getSceneName() { return &sceneName; }
	void copyGameMaster(GameMaster* destination);
	void setGameMaster(GameMaster* resorce);
	void setAnimationLoader(AnimationLoader* animationLoader);
};