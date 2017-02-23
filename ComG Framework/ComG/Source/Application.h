#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsExit;
	static GLFWwindow* m_window;
	static const unsigned char Application::FPS; // FPS of this game
	static const unsigned int Application::frameTime; // time for each frame
	static StopWatch m_timer;
	static int saveno;
};

#endif