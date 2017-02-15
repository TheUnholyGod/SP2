#include "DefensiveWalls.h"

DefensiveWalls::DefensiveWalls() : Building( 203, "DefensiveWalls", "", 100, DEFENCE, false) {} // Change the ID
DefensiveWalls::~DefensiveWalls(){}
int DefensiveWalls::get_Health(){ return health_; }