#ifndef SCENE_TEST_H
#define SCENE_TEST_H

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
#include "Projectile.h" 
#include "Menu.h"
#include <vector>
#include <array>

class SceneTest : public Scene
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

		GEO_CURSOR,

		GEO_PAUSEMENU,
		GEO_OPTIONSMENU,

		GEO_OPTIONS,
		GEO_BACKTOGAME,
		GEO_BACKTOMAIN,

		GEO_MOUSE,
		GEO_VOLUME,

		GEO_SCAR_BODY,
		GEO_SCAR_BOLT,
		GEO_SCAR_CHARGING,
		GEO_SCAR_CASING,

		NUM_GEOMETRY,
	};
	enum SPRITES
	{
		GEO_BUILDUI,
		GEO_BARNSPRITE,
		GEO_TROPHYROOMSPRITE,
		GEO_INVENTORYROOMSPRITE,
		GEO_NPCHOUSESPRITE,
		GEO_FASTTRAVELPORTALSPRITE,
		NUM_SPRITES,
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

	enum PROJECTILEMESHLIST
	{
		GEO_ARROW,
		NUM_PROJECTILEGEOMETERY,
	};

	enum FOODMESHLIST
	{
		GEO_POTATO,
		GEO_CABBAGE,
		GEO_CARROT,
		GEO_WHEAT,
		GEO_BREAD,
		GEO_VEGETABLESTEW,
		GEO_PURIFIEDWATER,
		GEO_CARROTJUICE,
		GEO_SALAD,
		NUM_FOODGEOMETERY,
	};

public:
	SceneTest();
	~SceneTest();

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
	std::array<Mesh*, NUM_PROJECTILEGEOMETERY> projectileMeshList;
	std::array<Mesh*, NUM_FOODGEOMETERY> foodMeshList;
	std::array<Mesh*, NUM_SPRITES> spritesList;

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack, viewStack, projectionStack;
	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	Camera3 fp_camera;

	const int buildingID;
	void RenderMesh(Mesh *mesh, bool enableLight);
	float LSPEED;
	void LoadSkybox();
	void RenderSkybox();
	void DebugMode(double dt);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);

	bool buildBuilding;
	void buildBuildingUpdate(double dt);

	//Light
	Light light[1];
	double lightrotate, sunrotate;
	Mtx44 LightPos;
	int sunup;
	float suntimer;
	bool reset;
	Vector3 lighting;
	void LightUpdate(double dt);
	void LightReset(double dt);
	int Day;

	std::vector<Enemy*> BaseEnemy;
	void SpawnEnemy(double dt);
	void UpdateEnemy(double dt);
	void RenderEnemy();

	std::list<Building*> BaseBuildings;
	void SpawnBuilding();
	void UpdateBuilding(double dt);
	void RenderBuilding();

	std::vector<Projectile*>BaseProjectile;
	void SpawnProjectile();
	void UpdateProjectiles(double dt);
	void RenderProjectile();

	std::vector<Item*> BaseItems;
	const int ItemID;
	void SpawnItems(double dt);
	void RenderItems();

	Menu pauseMenu;
	int windowX;
	int windowY;

	double cursorX;
	double cursorY;

	int windowXpos;
	int windowYpos;

	bool pause;
	bool options;
	int pauseHighlight;
	int optionHighlight;

	std::clock_t start;
	float elapsedTime;

	std::clock_t Istart;
	float ITime;
};

#endif