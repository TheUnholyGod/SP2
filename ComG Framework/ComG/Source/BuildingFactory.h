#ifndef _BUILDINGFACTORY_H
#define _BUILDINGFACTORY_H

#include "Building.h"

class BuildingFactory
{
private:
	static BuildingFactory* BuildingF_;
	BuildingFactory();
public:
	~BuildingFactory();
	static BuildingFactory* getBuildingFactory();
	static Building* generateBuilding(int key, Vector3);
};

#endif