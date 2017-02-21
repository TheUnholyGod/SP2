#include "DefenceTower.h"
#include "Camera3.h"

DefenceTower::DefenceTower() : Building(107, "Turret", "OBJ//Turret.obj", "Image//Turret_Texture.tga", 100, DEFENCE, false) 
{
	gameobjrenderer_ = new Renderer(Vector3(0, 0, 5), Vector3(1, 0, 0));
	gameobjrenderer_->setScaling(5);
	size.push_back(Vector3(20, 10, 11) * gameobjrenderer_->getScaling());
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
	allAABB[0]->setMinMax(gameobjrenderer_->getPosition());
}

DefenceTower::~DefenceTower()
{

}

int DefenceTower::get_Health(){ return health_; }

void DefenceTower::update(double dt)
{
	GameObject::gameobjrenderer_->setPosition(Vector3(10,0,0));
	Vector3 turretPosition = GameObject::gameobjrenderer_->getPosition();
	Vector3 playerPosition = Camera3::getPosition();
	/*
	Vector3 turretForward = GameObject::gameobjrenderer_->getForward();
	if (turretForward != ())
		*/
	Vector3 newForward = playerPosition - turretPosition;
	GameObject::gameobjrenderer_->setForward(Vector3(newForward.Normalize().x, 0, newForward.Normalize().z) );
}