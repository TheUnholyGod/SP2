#ifndef _MENU_H
#define _MENU_H

#include "Utility.h"
#include "Application.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "LoadTGA.h"
#include "SceneManager.h"
#include "Camera3.h"
#include "GLFW\glfw3.h"
#include "GL\glew.h"

class Menu
{
	enum GEOMETRY_TYPE
	{
		//Pause Menu
		GEO_PAUSEMENU,
		GEO_OPTIONS,
		GEO_BACKTOGAME,
		GEO_BACKTOMAIN,

		//Options Menu
		GEO_OPTIONSMENU,
		GEO_MOUSE,
		GEO_VOLUME,
		GEO_BACK,

		//Crafting Menu
		GEO_CRAFTMENU,
		
		//Building Menu
		GEO_BUILDMENU,

		//Cursor
		GEO_CURSOR,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
	Menu();
	~Menu();

	void init();
	void update();
	void Render();
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	void RenderMesh(Mesh *mesh, bool enableLight);

	bool pause;

	int menuType;
	int pauseSelection;
	int optionSelection;
	int buildSelection;
	int craftSelection;
	int windowX;
	int windowY;

	double cursorX;
	double cursorY;

	std::clock_t start;
	float elapsedTime;

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh *meshList[NUM_GEOMETRY];
	MS modelStack, viewStack, projectionStack;
};

#endif