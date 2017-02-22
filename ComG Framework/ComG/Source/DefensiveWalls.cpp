#include "DefensiveWalls.h"

DefensiveWalls::DefensiveWalls(Vector3 position) : Building(108, "DefensiveWalls", "OBJ//DefensiveWall.obj", "Image//DefensiveWall_Texture.tga", 100, DEFENCE, false)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(20, 10, 2) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}

DefensiveWalls::~DefensiveWalls(){}

int DefensiveWalls::get_Health(){ return health_; }