#include "WaterWell.h"

WaterWell::WaterWell() : Building(112, "WaterWell", "OBJ//Barn.obj", "", 100, RESOURCE, false) {} // Change the ID
WaterWell::~WaterWell(){}
int WaterWell::get_Health(){ return health_; }