#include "DefenceTower.h"
#include "Camera3.h"

DefenceTower::DefenceTower() : Building(107, "Turret", "OBJ//Turret.obj", 100, DEFENCE, false) {}
DefenceTower::~DefenceTower(){}
int DefenceTower::get_Health(){ return health_; }
void DefenceTower::update(double dt)
{
	
	/*
	Vector3 turretPosition = GameObject::gameobjrenderer_->getPosition();
	Vector3 playerPosition = Camera3::getPosition();
	Vector3 turretForward = GameObject::gameobjrenderer_->getForward();
	if (turretForward != ())
		*/
}