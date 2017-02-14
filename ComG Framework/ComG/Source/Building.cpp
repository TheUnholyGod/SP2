#include "Building.h"

Building::Building(const std::string name, const int id, int health, BUILDINGFUNCTION function, bool enter) :
								GameObject(id), kName_(name), health_(health), FUNCTION(function), enter_(enter){}
Building::~Building(){}
int Building::get_Health(){ return health_; }