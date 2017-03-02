#ifndef SCENE_CITY_H
#define SCENE_CITY_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Camera4.h"
#include "Mesh.h"
#include "Menu.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include <list>
#include "Building.h"
#include "Enemy.h"
#include "Acrid_Plant.h"
#include "Projectile.h"
#include <vector>
#include <array>

class SceneCity : public Scene
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
		GEO_DRONE,
		GEO_ROGUEMECH,
		GEO_PATROLBOT,
		NUM_ENEMYGEOMETRY,
	};
	enum BUILDINGMESHLIST
	{
		GEO_GARAGE,
		GEO_CITYBUIULDING1,
		NUM_BUILDINGGEOMETRY,
	};
	enum PLAYER
	{
		GEO_HEALTHBAR,
		GEO_HEALTH,
		GEO_INTERACT,
		GEO_INTERACT_IMG,
		NUM_PLAYERGEOMETRY,
	};
	enum WEAPONMESHLIST
	{
		GEO_BOW,
		NUM_WEAPONGEOMETERY,
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
	enum LOOTMESHLIST
	{
		GEO_LPOTATO,
		GEO_LCABBAGE,
		GEO_LCARROT,
		GEO_LWHEAT,
		GEO_LBREAD,
		GEO_LVEGETABLESTEW,
		GEO_LPURIFIEDWATER,
		GEO_LCARROTJUICE,
		GEO_LSALAD,
		NUM_LOOTGEOMETERY,
	};
public:
	SceneCity();
	~SceneCity();

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
	std::array<Mesh*, NUM_SPRITES> spritesList;
	std::array<Mesh*, NUM_PLAYERGEOMETRY> playerMeshList;
	std::array<Mesh*, NUM_FOODGEOMETERY> foodMeshList;
	std::array<Mesh*, NUM_LOOTGEOMETERY> lootMeshList;

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack, viewStack, projectionStack;
	Vector3 forward, right, chardirection, camForward, camRight;
	Camera2 camera;
	Camera3 fp_camera;
	Menu pauseMenu;

	const int buildingID;
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
	double lightrotate, sunrotate;
	Mtx44 LightPos;
	int sunup;
	float suntimer;
	bool reset;
	Vector3 lighting;
	void LightUpdate(double dt);
	void LightReset(double dt);
	int Day;

	bool allbuildingcollision(GameObject*);

	std::vector<Enemy*> CityEnemy;
	void SpawnEnemy(double dt);
	void UpdateEnemy(double dt);
	void RenderEnemy();

	std::list<Building*> CityBuildings;
	void SpawnBuilding();
	void UpdateBuilding(double dt);
	void RenderBuilding();

	std::vector<Projectile*>CityProjectile;
	void SpawnProjectile(Vector3 position, Vector3 forward);
	void UpdateProjectiles(double dt);
	void RenderProjectile();

	std::vector<Item*> CityItems;
	const int ItemID;

	std::vector<Item*> CityLoots;
	std::map<Item*, int>CityLoots1;
	int LootID;
	Vector3 Lootpos;
	void SpawnLoot(int key);
	void RenderLoot();

	void RenderHealth();

	std::clock_t Pstart;
	float PTime;

	std::clock_t Bstart;
	float BTime;

	std::clock_t Estart;
	float ETime;

	std::clock_t t_random;
	float t_F_random;
};

#endif