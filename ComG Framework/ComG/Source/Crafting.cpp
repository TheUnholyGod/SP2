#include "Crafting.h"

Crafting::Crafting() : Building("Crafting", 303, 100, RESOURCE, false) {} // Change the ID
Crafting::~Crafting(){}
int Crafting::get_Health(){ return health_; }