#include "AbstractScene.h"
using namespace SceneList;
AbstractScene::AbstractScene() {
	nextScene = NONE_SCENE;
	sceneName = "none";
	onChange = false;
}
AbstractScene::~AbstractScene() {

}