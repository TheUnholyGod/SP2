#include "Crafting.h"

Crafting::Crafting() : Building(303, "Crafting", "", 100, RESOURCE, false) {} // Change the ID
Crafting::~Crafting(){}
int Crafting::get_Health(){ return health_; }