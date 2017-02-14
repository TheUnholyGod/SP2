#ifndef _BUILDINGDATABASE_H
#define _BUILDINGDATABASE_H

#include <map>
#include "Source\Building.h"

class BuildingDataBase
{
public:
	typedef std::map<int, Building*> bdb;
private:
	bdb Buildingdatabase_;
	BuildingDataBase();
	static BuildingDataBase* Buildingdb_;
public:
	~BuildingDataBase();
	static BuildingDataBase* getBuildingDB();
	Building* getBuilding(int key);
	bdb& getDataBase();
};

#endif