#include "NPCHouse.h"
#include "ItemFactory.h"

NPCHouse::NPCHouse(Vector3 position) : Building(104, "NPC HDB", "OBJ//Barn.obj", "", 100, NORMAL, true)
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

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(201)] = 15; //Stone
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 5; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(203)] = 2; //Copper
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 10; //Wood
}

NPCHouse::~NPCHouse(){}

int NPCHouse::get_Health(){ return health_; }