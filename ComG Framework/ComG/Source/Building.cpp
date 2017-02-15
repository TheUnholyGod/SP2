#include "Building.h"

Building::Building(int id, const std::string name, std::string source_, int health, BUILDINGFUNCTION function, bool enter) :
								GameObject(id,""), kName_(name), health_(health), FUNCTION(function), enter_(enter){}
Building::~Building(){}
int Building::get_Health(){ return health_; }