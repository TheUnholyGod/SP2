#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneSplashScreen.h"
#include "SceneTest.h"
#include "SceneCity.h"
#include "SceneMainMenu.h"
#include "Application.h"
#include "SceneWildLife.h"
#include "SceneCity.h"
#include "SceneGameOver.h"

SceneManager* SceneManager::scenemanager;
int SceneManager::prevScene = DEFAULT;
int SceneManager::currScene = DEFAULT;

SceneManager::SceneManager()
{
	prevScene = DEFAULT;
	SceneDataBase[1] = new SceneSplashScreen();
	SceneDataBase[2] = new SceneMainMenu();
	SceneDataBase[3] = new SceneLoading();
	SceneDataBase[4] = new SceneTest();
	SceneDataBase[5] = new SceneWildLife();
	SceneDataBase[6] = new SceneCity();
	SceneDataBase[7] = new SceneGameOver();
}

SceneManager::~SceneManager()
{
	SceneDataBase.erase(SceneDataBase.begin(), SceneDataBase.end());
}

void SceneManager::init(int key)
{
	SceneDataBase[key]->Init();
}

void SceneManager::exit(int key)
{
	SceneDataBase[key]->Exit();
}

void SceneManager::changeScene(int key)
{
	scenemanager->exit(scenemanager->prevScene);
	scenemanager->init(key);
	scenemanager->prevScene = key;
}

SceneManager* SceneManager::getSceneManger()
{
	if (!scenemanager)
	{
		scenemanager = new SceneManager;
	}
	return scenemanager;
}

int SceneManager::getPrevScene()
{
	return prevScene;
}

void SceneManager::update()
{
	scenemanager->SceneDataBase[currScene]->Update(Application::m_timer.getElapsedTime());
	if (prevScene != currScene)
	{
		scenemanager->changeScene(3);
		scenemanager->SceneDataBase[3]->Render();
		//Swap buffers
		glfwSwapBuffers(Application::m_window);
		scenemanager->changeScene(currScene);
	}
	scenemanager->SceneDataBase[currScene]->Render();
	//Swap buffers
	glfwSwapBuffers(Application::m_window);
	//Get and organize events, like keyboard and mouse input, window resizing, etc...
	glfwPollEvents();
	Application::m_timer.waitUntil(Application::frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   
}