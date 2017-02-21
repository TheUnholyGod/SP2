#include "WaterWell.h"

WaterWell::WaterWell() : Building(112, "WaterWell", "OBJ//WaterWell.obj", "Image//WaterWell_Texture.tga", 100, RESOURCE, false)
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

WaterWell::~WaterWell(){}

int WaterWell::get_Health(){ return health_; }