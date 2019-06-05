#pragma once
#include "Base.h"
#include "Camera.h"
#include <string>


namespace SceneList
{
	enum {
		NONE_SCENE = -1,
		OPENING,
		TITLE,
		SELECT_CHARACTER,
		RESULT,
	};
}

class AbstractScene :public Celement
{
protected:
	//Data
	Camera* camera;
	bool onChange;
	int nextScene;
	std::string sceneName;
public:
	//Method
	AbstractScene();
	virtual ~AbstractScene();
	virtual void initialize(Direct3D9* direct3D9) = 0;							//������
	virtual void update() = 0;								//�X�V
	virtual void render(Direct3D9* direct3D9) = 0;			//�`��
	virtual void collisions() = 0;							//�Փˏ���
	virtual void AI() = 0;									//AI����
	virtual void uninitialize() = 0;						//�I������

	void changeScene(int i) { onChange = true; nextScene = i; };
	bool checkChangeOrder() { return onChange; };
	int checkNextScene() { return nextScene; }
	std::string* getSceneName() { return &sceneName; }
};