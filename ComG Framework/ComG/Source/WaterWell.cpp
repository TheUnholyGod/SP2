#include "WaterWell.h"

WaterWell::WaterWell() : Building("WaterWell", 000, 100, RESOURCE, false) {} // Change the ID
WaterWell::~WaterWell(){}
int WaterWell::get_Health(){ return health_; }