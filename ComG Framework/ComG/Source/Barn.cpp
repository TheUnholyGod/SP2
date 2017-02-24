#include "Barn.h"
#include "MyMath.h"
#include "ItemFactory.h"

Barn::Barn(Vector3 position) : Building(101, "Barn", "OBJ//Barn(working).obj", "Image//barnInteriorUV.tga", 100, NORMAL, true)
{
	gameobjrenderer_ = new Renderer(position, Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(2);
	size.push_back(Vector3(55, 50, 85));

	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());

	defaultrecipe[ItemFactory::getItemFactory()->generateItem(202)] = 2; //Iron
	defaultrecipe[ItemFactory::getItemFactory()->generateItem(206)] = 20; //Wood
}
Barn::~Barn(){}

void Barn::update(double dt)
{

}

int Barn::get_Health(){ return health_; }