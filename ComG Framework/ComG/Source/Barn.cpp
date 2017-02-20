#include "Barn.h"
#include "MyMath.h"

Barn::Barn() : Building(101, "Barn", "OBJ//Barn.obj", "Image//BarnInteriorUV(1).tga", 100, NORMAL, true)
{
	gameobjrenderer_ = new Renderer(Vector3(0 ,0, 5), Vector3(1, 0, 0));
	size.push_back(Vector3(5, 5, 5));
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
} // Change the ID
Barn::~Barn(){}

void Barn::update(double dt)
{

}

int Barn::get_Health(){ return health_; }