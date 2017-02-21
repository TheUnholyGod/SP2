#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
<<<<<<< HEAD
#define DEFAULT 6
=======
<<<<<<< HEAD
#define DEFAULT 1
=======
#define DEFAULT 4
>>>>>>> cc72d4c37c46ed0d056b38ca64ae0f2e2afa0486
>>>>>>> 5f6cb77a594889dde0f6e7b845a621cdb74db793

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