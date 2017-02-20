#include "Barn.h"

Barn::Barn() : Building(101, "Barn", "OBJ//Barn.obj", "Image//BarnInteriorUV(1).tga", 100, NORMAL, true)
{
	//size.push_back(Vector3(1, 1, 1));;
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
} // Change the ID
Barn::~Barn(){}

void Barn::update(double dt)
{
	//if (allAABB[1]->AABBtoAABB(*Player::getplayer()->getAABB()))
	//{
	//	std::cout << "Collision detected" << std::endl;
	//}
}

int Barn::get_Health(){ return health_; }