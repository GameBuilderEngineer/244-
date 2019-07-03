#include "AbstractScene.h"
using namespace SceneList;
AbstractScene::AbstractScene() {
	nextScene = NONE_SCENE;
	sceneName = "none";
	sceneTimer = 0.0f;
	onChange = false;
}
AbstractScene::~AbstractScene() {

}