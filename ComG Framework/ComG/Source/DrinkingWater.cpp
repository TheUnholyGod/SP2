#include "DrinkingWater.h"



DrinkingWater::DrinkingWater(Vector3 position) :Food(107,"Drinking Water", "", "", CRAFTABLE, 5, 50)
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

	defRecipe[205] = 2; //Water
	defRecipe[210] = 1;//Cloth
}


DrinkingWater::~DrinkingWater()
{
}

void DrinkingWater::Eat()
{

}