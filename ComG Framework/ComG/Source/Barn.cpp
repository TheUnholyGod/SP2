#include "Barn.h"
#include "MyMath.h"

Barn::Barn() : Building(101, "Barn", "OBJ//Barn.obj", "Image//BarnInteriorUV.tga", 100, NORMAL, true)
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
	if (allAABB[0]->pointtoAABB(Player::getplayer()->getRenderer().getPosition()))
	{
		std::cout << "Collision detected" << std::endl;
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
	std::cout << "Building Position: " << this->gameobjrenderer_->getPosition() << std::endl;
	std::cout << "Max AABB: " << this->allAABB[0]->getAABBmax() << std::endl;
	std::cout << "Min AABB: " << this->allAABB[0]->getAABBmin() << std::endl;
	std::cout << "PLayer Position: " << Player::getplayer()->getRenderer().getPosition() << std::endl;
}

int Barn::get_Health(){ return health_; }