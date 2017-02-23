#include "Crafting.h"
#include "ItemFactory.h"

Crafting::Crafting(Vector3 position) : Building(111, "Crafting Shed", "OBJ//Shed.obj", "Image//ShedUV.tga", 100, RESOURCE, false)
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

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(201)] = 2; //Stone
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 2; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 2; //Wood
} 
Crafting::~Crafting(){}
int Crafting::get_Health(){ return health_; }