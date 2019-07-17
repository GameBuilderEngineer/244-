#pragma once
#include "Base.h"
#include "Camera.h"
#include "Input.h"
#include "Audio.h"
#include "Light.h"
#include "TextureLoader.h"
#include "StaticMeshLoader.h"
#include "ShaderLoader.h"
#include <string>

namespace SceneList
{
	enum {
		NONE_SCENE = -1,
		SPLASH,
		TITLE,
		TUTORIAL,
		OPERATION,
		CREDIT,
		SELECT_CHARACTER,
		GAME,
		RESULT,
	};
}

class AbstractScene :public Base
{
protected:
	//Data
	Input* input;
	Audio* audio;
	Camera* camera;
	Light* light;
	TextureLoader* textureLoader;
	StaticMeshLoader* staticMeshLoader;
	ShaderLoader* shaderLoader;
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
		Audio* _audio,
		TextureLoader* _textureLoader,
		StaticMeshLoader* _staticMeshLoader,
		ShaderLoader* _shaderLoader) = 0;		//初期化
	virtual void update(float frameTime) = 0;			//更新
	virtual void render(Direct3D9* direct3D9) = 0;		//描画
	virtual void collisions() = 0;						//衝突処理
	virtual void AI() = 0;								//AI処理
	virtual void uninitialize() = 0;					//終了処理

	void changeScene(int i) { onChange = true; nextScene = i; };
	bool checkChangeOrder() { return onChange; };
	int checkNextScene() { return nextScene; }
	std::string* getSceneName() { return &sceneName; }

};