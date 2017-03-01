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

#include "BuildingDataBase.h"
#include "ItemDataBase.h"

#include "Building.h"
#include "BuildingFactory.h"
#include "GLFW\glfw3.h"
#include "GL\glew.h"
#include "Inventory.h"
#include <list>

#include "FastTravelRoom.h"
#include "TilledSoil.h"
#include "Player.h"

#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <map>

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
		GEO_CRAFTBUTTON,

		//Inventory Menu
		GEO_INVENTORYMENU,
		GEO_ITEMS,
		GEO_QUANTITY,
		GEO_IMAGE,
		GEO_POTATO,
		GEO_CARROT,
		GEO_CABBAGE,
		GEO_WHEAT,	
		GEO_STONE,
		GEO_IRON,
		GEO_COPPER,
		GEO_GOLD,
		GEO_WATER,
		GEO_WOOD,
		GEO_BIOMASS,
		GEO_ADHESIVES,
		GEO_METALSCRAPS,
		GEO_CLOTH,
		GEO_CIRCUITBOARDS,


		//Cursor
		GEO_CURSOR,

		//Misc
		GEO_TEXT,
		GEO_ARROW_L,
		GEO_ARROW_R,

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
	enum BUILDINGMESHLIST
	{
		GEO_BARN,
		GEO_TROPHYROOM,
		GEO_INVENTORYROOM,
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
	enum ITEMTYPE
	{
		ITEM_BREAD,
		ITEM_VEGETABLESTEW,
		ITEM_DRINKINGWATER,
		ITEM_CARROTJUICE,
		ITEM_SALAD,
		ITEM_GLOCK,
		ITEM_SCAR_H,
		ITEM_M200,
		ITEM_BOW,
		ITEM_FARMINGHOE,
		ITEM_KATANA,
		ITEM_KNIFE,
		NUM_ITEMTYPE,
	};

public:
	Menu();
	~Menu();

	void init();
	void update();
	void Render();
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	bool pause;	
	bool rendered;
	bool isMenu;

	int craft;
	int menuType;
	int pauseSelection;
	int optionSelection;
	int buildSelection;
	int craftSelection;
	int inventorySelection;
	int craftingSelection;
	int windowX;
	int windowY;
	int width;
	int height;

	double cursorX;
	double cursorY;

	typedef std::map<Item*, int> buildingrecipe;
	typedef std::map<int, int> itemrecipe;

	buildingrecipe::iterator bit;
	itemrecipe::iterator iit;

	buildingrecipe bRecipe;
	itemrecipe iRecipe;

	std::array<Mesh*, NUM_BUILDINGGEOMETRY> buildingMeshList;
	std::array<Mesh*, NUM_ITEMTYPE> itemMeshList;
	std::vector<std::string> buildingName;
	std::vector<std::string> foodName;
	std::vector<std::string> weaponName;
	std::vector<std::string> resourceName;
	std::vector<int> resourceQuantity;

	std::clock_t start;
	float elapsedTime;

	//Items
	std::string Itemname;
	int count;
	void checkItem(int key);
	float y1;

	const int buildingID;
	int itemID;

	int travelTo;
	bool tpZone;

	bool plantZone;

	//Inventory(building)
	bool check;
	bool checkbuild();
	std::map <int, int> Remove;
	void Removal();

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh *meshList[NUM_GEOMETRY];
	MS modelStack, viewStack, projectionStack;
};

#endif