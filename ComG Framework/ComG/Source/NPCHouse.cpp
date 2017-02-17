#include "NPCHouse.h"

NPCHouse::NPCHouse() : Building(104, "NPCHouse", "OBJ//Barn.obj",  100, NORMAL, true) {} // Change the ID
NPCHouse::~NPCHouse(){}
int NPCHouse::get_Health(){ return health_; }