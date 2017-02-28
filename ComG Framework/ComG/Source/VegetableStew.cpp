#include "VegetableStew.h"



VegetableStew::VegetableStew(Vector3 position) :Food(106,"Vegetable Stew", "", "", CRAFTABLE, 100, 30)
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

	defRecipe[101] = 1; //Potato
	defRecipe[102] = 1; //Cabbage
	defRecipe[103] = 1; //Carrot
	defRecipe[206] = 1; //Wood
}


VegetableStew::~VegetableStew()
{
}

void VegetableStew::Eat()
{

}