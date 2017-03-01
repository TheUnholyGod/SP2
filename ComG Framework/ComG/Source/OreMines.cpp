#include "OreMines.h"
#include "Player.h"
#include "ItemFactory.h"

OreMines::OreMines(Vector3 position, Vector3 forward) : Building(110, "Ore Mines", "OBJ//Barn.obj", "", 100, RESOURCE, false)
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
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 5; //Wood
} 

OreMines::~OreMines(){}

int OreMines::get_Health(){ return health_; }

void OreMines::update(double dt)
{
	if (allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), GameObject::getRenderer().getForward()))
	{
		cancollect = true;
	}
	else
	{
		cancollect = false;
	}
}