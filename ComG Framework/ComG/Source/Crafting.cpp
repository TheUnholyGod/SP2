#include "Crafting.h"

Crafting::Crafting() : Building(111, "Crafting", "OBJ//Barn.obj", 100, RESOURCE, false) {} // Change the ID
Crafting::~Crafting(){}
int Crafting::get_Health(){ return health_; }