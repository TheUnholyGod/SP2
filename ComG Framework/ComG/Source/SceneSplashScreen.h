#ifndef SCENE_SPLASH_SCREEN_H
#define SCENE_SPLASH_SCREEN_H

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
#include <ctime>

class SceneSplashScreen : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_PLAYER,
		GEO_AXES,
		GEO_TEXT,
		GEO_QUAD,
		GEO_SPLASHSCREEN1,
		GEO_SPLASHSCREEN2,/*
		//SkyBox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_SUN,
		GEO_LEFT1,
		GEO_RIGHT1,
		GEO_TOP1,
		GEO_BOTTOM1,
		GEO_FRONT1,
		GEO_BACK1,
		GEO_LEFT2,
		GEO_RIGHT2,
		GEO_TOP2,
		GEO_BOTTOM2,
		GEO_FRONT2,
		GEO_BACK2,
		*/
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
	/*enum ENEMYMESHLIST
	{
		GEO_MOLERAT,
		GEO_LIZARD,
		NUM_ENEMYGEOMETRY,
	};
*/
public:
	SceneSplashScreen();
	~SceneSplashScreen();

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
	Camera3 fp_camera;
	void RenderMesh(Mesh *mesh, bool enableLight);
	void DebugMode(double dt);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	Lighting light[1];
	std::clock_t start;
	int elapsed;
	bool change;
/*
	Mesh *enemyMeshList[NUM_ENEMYGEOMETRY];
	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	float LSPEED;
	void LoadSkybox();
	void RenderSkybox();
	double lightrotate, sunrotate;
	Mtx44 LightPos;
	int sunup;
	float suntimer;
	bool reset;

	std::list<Enemy*> BaseEnemy;
	std::list<Building*> BaseBuildings;
	void SpawnEnemy();
	void RenderEnemy();
	*/
};

#endif