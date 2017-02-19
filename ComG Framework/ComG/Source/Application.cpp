#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "Scene.h"
#include "SceneManager.h"
#include "ItemDataBase.h"
#include "EnemyDataBase.h"
#include <iostream>

const unsigned char Application::FPS = 60; // FPS of this game
const unsigned int Application::frameTime = 1000 / FPS; // time for each frame
GLFWwindow* Application::m_window = NULL;
StopWatch Application::m_timer;
bool Application::IsExit;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	//Create a window and create its OpenGL context
	Application::m_window = glfwCreateWindow(800, 600, "Computer Graphics", NULL, NULL);

	//If the window couldn't be created
	if (!Application::m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(Application::m_window);

	//Sets the key callback
	//glfwSetKeyCallback(Application::m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	glfwSetWindowSizeCallback(Application::m_window, resize_callback);
	SceneManager::getSceneManger()->init(DEFAULT);
	ItemDataBase::getItemDB();
	EnemyDataBase::getEnemyDB();
	srand(time(NULL));
}

void Application::Run()
{
	//Main Loop

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(Application::m_window) && !IsExit)
	{
		SceneManager::getSceneManger()->update();
	} //Check if the ESC key had been pressed or if the window had been closed
	SceneManager::getSceneManger()->exit(SceneManager::currScene);
	delete SceneManager::getSceneManger();

}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(Application::m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
