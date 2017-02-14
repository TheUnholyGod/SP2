#include "DefensiveWalls.h"

DefensiveWalls::DefensiveWalls() : Building("DefensiveWalls", 203, 100, DEFENCE, false) {} // Change the ID
DefensiveWalls::~DefensiveWalls(){}
int DefensiveWalls::get_Health(){ return health_; }