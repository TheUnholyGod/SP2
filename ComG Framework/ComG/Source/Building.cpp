#include "Building.h"
#include "Collision.h"

Building::Building(int id, const std::string name, std::string source_, int health, BUILDINGFUNCTION function, bool enter) :
								GameObject(id,""), kName_(name), health_(health), FUNCTION(function), enter_(enter)
{
	for (auto &i : size)
	{
		AABB* temp = new AABB(i, gameobjrenderer_->getPosition());
		allAABB.push_back(temp);
	}
}
Building::~Building(){}
int Building::get_Health(){ return health_; }