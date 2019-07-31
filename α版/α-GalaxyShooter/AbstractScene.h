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
#include <string>

namespace SceneList
{
	enum {
		NONE_SCENE = -1,
		SPLASH,
		TITLE,
		SELECT,
		TUTORIAL,
		OPERATION,
		CREDIT,
		GAME,
		RESULT,
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
	TextManager* textManager;
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
		TextManager* _textManager) = 0;		//‰Šú‰»
	virtual void update(float frameTime) = 0;			//XV
	virtual void render(Direct3D9* direct3D9) = 0;		//•`‰æ
	virtual void collisions() = 0;						//Õ“Ëˆ—
	virtual void AI() = 0;								//AIˆ—
	virtual void uninitialize() = 0;					//I—¹ˆ—

	void changeScene(int i) { onChange = true; nextScene = i; };
	bool checkChangeOrder() { return onChange; };
	int checkNextScene() { return nextScene; }
	std::string* getSceneName() { return &sceneName; }

};