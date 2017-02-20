#ifndef _BUILDINGDATABASE_H
#define _BUILDINGDATABASE_H

#include "Building.h"
#include <map>
#include <vector>

class BuildingDataBase
{
public:
	typedef std::map<int, Building*> bdb;
private:
	bdb Buildingdatabase_;
	BuildingDataBase();
	static BuildingDataBase* Buildingdb_;
	std::vector<int> IDlist;
public:
	~BuildingDataBase();
	static BuildingDataBase* getBuildingDB();
	Building* getBuilding(int key);
	bdb& getDataBase();
	std::vector<int> getIDList() { return IDlist; }
};

#endif