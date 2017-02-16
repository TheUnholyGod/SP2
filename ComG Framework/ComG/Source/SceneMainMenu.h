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

class SceneMainMenu : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_QUAD,
		GEO_BUTTON1,
		GEO_BUTTON2,
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
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack, viewStack, projectionStack;
	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	Camera3 fp_camera;
	Lighting light[1];
	void RenderMesh(Mesh *mesh, bool enableLight);
	float LSPEED;
	void LoadSkybox();
	void RenderSkybox();
	void DebugMode(double dt);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	double lightrotate, sunrotate;
	Mtx44 LightPos;

	int sunup;
	float suntimer;
	bool reset;

	std::list<Enemy*> BaseEnemy;
	std::list<Building*> BaseBuildings;
	void SpawnEnemy();
	void RenderEnemy();
};

#endif