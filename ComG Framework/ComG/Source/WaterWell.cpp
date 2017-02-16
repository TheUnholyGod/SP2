#include "WaterWell.h"

WaterWell::WaterWell() : Building(304, "WaterWell", "", 100, RESOURCE, false) {} // Change the ID
WaterWell::~WaterWell(){}
int WaterWell::get_Health(){ return health_; }