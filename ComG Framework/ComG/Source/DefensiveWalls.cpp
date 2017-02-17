#include "DefensiveWalls.h"

DefensiveWalls::DefensiveWalls() : Building( 108, "DefensiveWalls", "OBJ//Barn.obj", 100, DEFENCE, false) {} // Change the ID
DefensiveWalls::~DefensiveWalls(){}
int DefensiveWalls::get_Health(){ return health_; }