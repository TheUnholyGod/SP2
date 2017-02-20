#include "Barn.h"
#include "MyMath.h"

Barn::Barn() : Building(101, "Barn", "OBJ//Barn.obj", "Image//BarnInteriorUV(1).tga", 100, NORMAL, true)
{
	gameobjrenderer_ = new Renderer(Vector3(0 ,0, 5), Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(85, 50, 55));
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}
Barn::~Barn(){}

void Barn::update(double dt)
{

}

int Barn::get_Health(){ return health_; }