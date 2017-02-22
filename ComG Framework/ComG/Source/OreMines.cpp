#include "OreMines.h"

OreMines::OreMines(Vector3 position) : Building(110, "OreMines", "OBJ//Barn.obj", "", 100, RESOURCE, false)
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

OreMines::~OreMines(){}

int OreMines::get_Health(){ return health_; }