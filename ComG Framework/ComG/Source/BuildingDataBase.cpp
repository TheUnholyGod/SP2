#include "BuildingDataBase.h"
#include "Barn.h"
#include "DefenceTower.h"
#include "Crafting.h"
#include "DefensiveWalls.h"
#include "FastTravelRoom.h"
#include "InventoryWarehouse.h"
#include "NPCHouse.h"
#include "OreMines.h"
#include "PowerGenerator.h"
#include "TilledSoil.h"
#include "TrophyRoom.h"
#include "WaterWell.h"

BuildingDataBase* BuildingDataBase::Buildingdb_;

BuildingDataBase::BuildingDataBase()
{
	Building* temp = new Barn;
	Buildingdatabase_[temp->getID()] = new Barn;
	delete temp;
	temp = new DefenceTower;
	Buildingdatabase_[temp->getID()] = new DefenceTower;
	delete temp;
	temp = new Crafting;
	Buildingdatabase_[temp->getID()] = new Crafting;
	delete temp;
	temp = new DefensiveWalls;
	Buildingdatabase_[temp->getID()] = new DefensiveWalls;
	delete temp;
	temp = new FastTravelRoom;
	Buildingdatabase_[temp->getID()] = new FastTravelRoom;
	delete temp;
	temp = new InventoryWarehouse;
	Buildingdatabase_[temp->getID()] = new InventoryWarehouse;
	delete temp;
	temp = new NPCHouse;
	Buildingdatabase_[temp->getID()] = new NPCHouse;
	delete temp;
	temp = new OreMines;
	Buildingdatabase_[temp->getID()] = new OreMines;
	delete temp;
	temp = new PowerGenerator;
	Buildingdatabase_[temp->getID()] = new PowerGenerator;
	delete temp;
	temp = new TilledSoil;
	Buildingdatabase_[temp->getID()] = new TilledSoil;
	delete temp;
	temp = new TrophyRoom;
	Buildingdatabase_[temp->getID()] = new TrophyRoom;
	delete temp;
	temp = new WaterWell;
	Buildingdatabase_[temp->getID()] = new WaterWell;
	delete temp;
}


BuildingDataBase::~BuildingDataBase()
{
	Buildingdatabase_.erase(Buildingdatabase_.begin(), Buildingdatabase_.end());
}

BuildingDataBase* BuildingDataBase::getBuildingDB()
{
	if (!Buildingdb_)
	{
		Buildingdb_ = new BuildingDataBase;
	}
	return Buildingdb_;
}

Building* BuildingDataBase::getBuilding(int key)
{
	return Buildingdatabase_[key];
}

BuildingDataBase::bdb& BuildingDataBase::getDataBase()
{
	return Buildingdatabase_;
}
