#include "DefenceTower.h"

DefenceTower::DefenceTower() : Building("DefenceTower", 000, 100, DEFENCE, false) {} // Change the ID
DefenceTower::~DefenceTower(){}
int DefenceTower::get_Health(){ return health_; }