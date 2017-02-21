#include "TrophyRoom.h"

TrophyRoom::TrophyRoom() : Building(102, "TrophyRoom", "OBJ//Barn.obj", "", 100, NORMAL, true) 
{
	gameobjrenderer_ = new Renderer(Vector3(0, 0, 5), Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(20, 10, 11) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}

TrophyRoom::~TrophyRoom(){}

int TrophyRoom::get_Health(){ return health_; }