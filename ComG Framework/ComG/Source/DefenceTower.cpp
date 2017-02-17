#include "DefenceTower.h"
#include "Camera3.h"

DefenceTower::DefenceTower() : Building(107, "Turret", "OBJ//Turret.obj", "", 100, DEFENCE, false) {}
DefenceTower::~DefenceTower(){}
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