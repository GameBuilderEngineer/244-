#pragma once
#include "Base.h"
#include "Camera.h"
#include "Input.h"
#include "Light.h"
#include "TextureLoader.h"
#include "StaticMeshLoader.h"
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
	Camera* camera;
	Light* light;
	TextureLoader* textureLoader;
	StaticMeshLoader* staticMeshLoader;
	float sceneTimer;
	bool onChange;
	int nextScene;
	std::string sceneName;
public:
	//Method
	AbstractScene();
	virtual ~AbstractScene();
	virtual void initialize(Direct3D9* direct3D9,Input* input,TextureLoader* textureLoader,StaticMeshLoader* staticMeshLoader) = 0;		//‰Šú‰»
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