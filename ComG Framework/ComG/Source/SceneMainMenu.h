#ifndef SCENE_MAIN_MENU_H
#define SCENE_MAIN_MENU_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include <list>
#include "Building.h"
#include "Enemy.h"
#include "Lighting.h"
#include <vector>
#include "GLFW\glfw3.h"
#include "GL\glew.h"

class SceneMainMenu : public Scene
{
	enum GEOMETRY_TYPE
	{
		//Main Menu
		GEO_MAINMENU,
		GEO_PLAY,
		GEO_OPTIONS,
		GEO_EXIT,

		//Options Menu
		GEO_OPTIONSMENU,
		GEO_VOLUME,
		GEO_BACK,

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
		//add these enum in UNIFORM_TYPE before U_TOTAL
		//add these enum in UNIFORM_TYPE before U_TOTAL
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};

public:
	SceneMainMenu();
	~SceneMainMenu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
<<<<<<< HEAD
	int windowX;
	int windowY;

=======
<<<<<<< HEAD
	double cursorX; 
	double cursorY;

	int windowXpos;
	int windowYpos;
=======
<<<<<<< HEAD
	int windowX;
	int windowY;

=======
	int windowX; 
	int windowY;
>>>>>>> 3f299e67d480f3cd5ed7b9aa38053ed825073194
>>>>>>> 77bad397532de5879b74ee4aafd5daecd8881810

>>>>>>> c1d20e19e515a9b3f2efcd70a60349c6da2f0e7c
	bool options;

	int play;
	int optionHighlight;
	bool back;

	std::clock_t start;
	float elapsedTime;

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack, viewStack, projectionStack;
	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	Camera3 fp_camera;
	void RenderMesh(Mesh *mesh, bool enableLight);
	void DebugMode(double dt);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
};

#endif