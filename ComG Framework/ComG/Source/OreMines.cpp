#include "OreMines.h"

OreMines::OreMines() : Building(110, "OreMines", "OBJ//Barn.obj", "", 100, RESOURCE, false) {} // Change the ID
OreMines::~OreMines(){}
int OreMines::get_Health(){ return health_; }