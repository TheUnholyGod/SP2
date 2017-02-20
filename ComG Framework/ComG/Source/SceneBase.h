#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Camera4.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include <list>
#include "Building.h"
#include "Enemy.h"
#include <vector>
#include <array>

class SceneBase : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_PLAYER,
		GEO_AXES,
		GEO_TEXT,
		GEO_QUAD,
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
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		//add these enum in UNIFORM_TYPE before U_TOTAL
		//add these enum in UNIFORM_TYPE before U_TOTAL
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
	enum ENEMYMESHLIST
	{
		GEO_MOLERAT,
		GEO_LIZARD,
		NUM_ENEMYGEOMETRY,
	};
	enum BUILDINGMESHLIST
	{
		GEO_BARN,
		GEO_TROPHYROOM,
		GEO_INVENTORYWAREHOUSE,
		GEO_NPCHOUSE,
		GEO_FASTTRAVELPORTAL,
		GEO_POWERGENERATOR,
		GEO_DEFENCETOWER,
		GEO_DEFENCEWALLS,
		GEO_TILLEDSOIL,
		GEO_OREMINES,
		GEO_CRAFTING,
		GEO_WATERWELL,
		NUM_BUILDINGGEOMETRY,
	};

	enum WEAPONMESHLIST
	{
		GEO_BOW,
		NUM_WEAPONGEOMETERY,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	std::array<Mesh*, NUM_GEOMETRY> meshList;
	std::array<Mesh*, NUM_ENEMYGEOMETRY> enemyMeshList;
	std::array<Mesh*, NUM_WEAPONGEOMETERY> weaponmesh;
	std::array<Mesh*, NUM_BUILDINGGEOMETRY> buildingMeshList;

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack, viewStack, projectionStack;
	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	
	Camera4 fp_camera;
	void RenderMesh(Mesh *mesh, bool enableLight);
	float LSPEED;
	void LoadSkybox();
	void RenderSkybox();
	void DebugMode(double dt);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	
	//Light
	Light light[1];
	double lightrotate,sunrotate;
	Mtx44 LightPos;
	int sunup;
	float suntimer;
	bool reset;
	Vector3 lighting;
	void LightUpdate(double dt);
	void LightReset(double dt);
	int Day;

	bool allbuildingcollision( GameObject* );

	std::list<Enemy*> BaseEnemy;
	std::list<Building*> BaseBuildings;

	void SpawnEnemy(double dt);
	void RenderEnemy();

	void SpawnBuilding(double dt);
	void RenderBuilding();
};

#endif