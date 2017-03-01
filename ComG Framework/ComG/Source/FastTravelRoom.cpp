#include "FastTravelRoom.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Menu.h"

FastTravelRoom::FastTravelRoom(Vector3 position, Vector3 forward) : Building(105, "Garage", "OBJ//Garage.obj", "Image//garage_Texture.tga", 100, NORMAL, true)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0)/*, forward*/);
	gameobjrenderer_->setScaling(7);
	size.push_back(Vector3(19, 10, 9) * gameobjrenderer_->getScaling());
	AABB* fastTravelling = new AABB(Vector3(18, 18, 7) * gameobjrenderer_->getScaling(), (gameobjrenderer_->getPosition() + Vector3(0, 0, 50)));
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB.push_back(fastTravelling);
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 5; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 5; //Wood
}

FastTravelRoom::~FastTravelRoom(){}

int FastTravelRoom::get_Health(){ return health_; }

void FastTravelRoom::update(double dt)
{
<<<<<<< HEAD
	if (allAABB[1]->pointtoAABB(Player::getplayer()->getRenderer().getPosition(), GameObject::getRenderer().getForward()))
	{
		Menu::menuType = 5;
		Menu::tpZone = true;
	}
	else
	{
		Menu::tpZone = false;
	}
=======
>>>>>>> 9cc91eaf00a66be98b1e65622275e8541082eee7
}