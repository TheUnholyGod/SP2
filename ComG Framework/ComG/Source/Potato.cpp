#include "Potato.h"

Potato::Potato() :Food(101,"Potato", "OBJ\\Potato.obj", "", FARMABLE, 15, 5)
{
	gameobjrenderer_ = new Renderer(Vector3(0, 0, 10), Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(2);
	size.push_back(Vector3(5, 5, 5));

	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}


Potato::~Potato()
{
}

void Potato::Eat()
{

}