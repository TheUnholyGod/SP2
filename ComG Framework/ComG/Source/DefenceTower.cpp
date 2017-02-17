#include "DefenceTower.h"

DefenceTower::DefenceTower() : Building(202, "Turret", "OBJ//Turret.obj", 100, DEFENCE, false) {} // Change the ID
DefenceTower::~DefenceTower(){}
int DefenceTower::get_Health(){ return health_; }
void DefenceTower::update(double dt)
{

}