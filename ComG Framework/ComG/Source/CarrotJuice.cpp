#include "CarrotJuice.h"



CarrotJuice::CarrotJuice(Vector3 position) :Food(108, "Carrot Juice", "", "", CRAFTABLE, 20, 10)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(2);
	size.push_back(Vector3(5, 5, 5));

	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defRecipe[103] = 1; //Carrot
}


CarrotJuice::~CarrotJuice()
{
}

void CarrotJuice::Eat()
{
	
}
