#include "WaterWell.h"
#include "ItemFactory.h"

WaterWell::WaterWell(Vector3 position, Vector3 forward) : Building(112, "Water Well", "OBJ//WaterWell.obj", "Image//WaterWell_Texture.tga", 100, RESOURCE, false)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0)/*, forward*/);
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(10, 10, 10) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(201)] = 10; //Stone
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 5; //Wood
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(210)] = 5; //Cloth
}

WaterWell::~WaterWell(){}

int WaterWell::get_Health(){ return health_; }