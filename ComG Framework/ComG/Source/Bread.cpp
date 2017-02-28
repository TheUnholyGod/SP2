#include "Bread.h"
#include "ItemFactory.h"

Bread::Bread(Vector3 position) :Food(105,"Bread", "", "", CRAFTABLE, 50, 10)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(2);
	size.push_back(Vector3(10, 5, 10));

	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defRecipe[104] = 2; //Wheat
}


Bread::~Bread()
{
}

void Bread::Eat()
{
	
}