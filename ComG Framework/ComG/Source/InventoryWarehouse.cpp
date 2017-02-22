#include "InventoryWarehouse.h"

<<<<<<< HEAD
InventoryWarehouse::InventoryWarehouse() : Building(103, "InventoryRoom", "OBJ//InventoryWarehouse.obj", "Image//InventoryWarehouse_Texture.tga", 100, NORMAL, true) 
=======
InventoryWarehouse::InventoryWarehouse(Vector3 position) : Building(103, "InventoryWarehouse", "OBJ//InventoryWarehouse.obj", "Image//InventoryWarehouse_Texture.tga", 100, NORMAL, true)
>>>>>>> f8055a930c079c2d9b415cabe98dc97aeb384e4f
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(20, 10, 11) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
} 

InventoryWarehouse::~InventoryWarehouse(){}

int InventoryWarehouse::get_Health(){ return health_; }