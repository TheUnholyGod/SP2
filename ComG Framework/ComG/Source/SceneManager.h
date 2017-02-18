#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
#define DEFAULT 3

#include <map>
#include "Scene.h"

class SceneManager
{
private:
	std::map<int, Scene*> SceneDataBase;
	static int prevScene;
	static SceneManager* scenemanager;
	SceneManager();
public:
	static int currScene;
	~SceneManager();
	void init(int key);
	void exit(int key);
	static void changeScene(int key);
	static SceneManager* getSceneManger();
	int getPrevScene();
	void update();
};

#endif