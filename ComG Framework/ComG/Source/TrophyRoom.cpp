#include "TrophyRoom.h"
#include "ItemFactory.h"

TrophyRoom::TrophyRoom(Vector3 position) : Building(102, "Trophy Room", "OBJ//TrophyRoom.obj", "Image//TrophyRoom_Texture.tga", 100, NORMAL, true)
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

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(201)] = 10; //Stone
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 10; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(203)] = 10; //Copper
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(204)] = 10; //Gold
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 10; //Wood
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(207)] = 10; //Biomass
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(210)] = 10; //Cloth
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(211)] = 10; //Circuit Board
}

TrophyRoom::~TrophyRoom(){}

int TrophyRoom::get_Health(){ return health_; }