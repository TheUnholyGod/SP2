#include "FastTravelRoom.h"
#include "ItemFactory.h"

FastTravelRoom::FastTravelRoom(Vector3 position) : Building(105, "Garage", "OBJ//Garage.obj", "Image//garage_Texture.tga", 100, NORMAL, true)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(7);
	size.push_back(Vector3(20, 10, 11) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 5; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 5; //Wood
}

FastTravelRoom::~FastTravelRoom(){}

int FastTravelRoom::get_Health(){ return health_; }