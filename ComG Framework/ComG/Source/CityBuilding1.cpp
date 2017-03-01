#include "CityBuilding1.h"
#include "ItemFactory.h"
#include "Player.h"
#include "Randomizer.h"

CityBuilding1::CityBuilding1(Vector3 position, Vector3 forward) : Building(114, "Building1", "OBJ//building.obj", "Image//building.tga", 100, NORMAL, true)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0)/*, forward*/);
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(22, 10, 11) * gameobjrenderer_->getScaling());
	size.push_back(Vector3(66, 30, 33) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(201)] = 15; //Stone
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 5; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(203)] = 2; //Copper
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 10; //Wood
	moved = false;
}

CityBuilding1::~CityBuilding1(){}

int CityBuilding1::get_Health(){ return health_; }

void CityBuilding1::update(double dt)
{
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	allAABB[1]->setMinMax(gameobjrenderer_->getPosition());
	if (getAABB(1)->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), Vector3(1, 0, 0)) && !moved)
	{
		int operator_ = 1 - (Randomizer::generate_range(1, 2));
		Vector3 new_pos = getRenderer().getPosition() + (operator_ * Vector3(10, 0, 10));
		if (!(getAABB(1)->pointtoAABB(new_pos, Vector3(1, 0, 0))))
		{
			getRenderer().setPosition(new_pos);
			moved = true;
		}
	}
}