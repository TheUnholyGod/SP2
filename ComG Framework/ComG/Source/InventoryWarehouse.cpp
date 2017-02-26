#include "InventoryWarehouse.h"
#include "ItemFactory.h"

InventoryWarehouse::InventoryWarehouse(Vector3 position, Vector3 forward) : Building(103, "Inventory Shop", "OBJ//InventoryWarehouse.obj", "Image//InventoryWarehouse_Texture.tga", 100, NORMAL, true)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0)/*, forward*/);
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(20, 10, 11) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(201)] = 20; //Stone
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 5; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 15; //Wood
} 

InventoryWarehouse::~InventoryWarehouse(){}

int InventoryWarehouse::get_Health(){ return health_; }