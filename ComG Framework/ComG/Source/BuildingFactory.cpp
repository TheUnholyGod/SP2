#include "BuildingFactory.h"
#include "BuildingDataBase.h"
#include "Barn.h"
#include "DefenceTower.h"
#include "DefensiveWalls.h"
#include "FastTravelRoom.h"
#include "InventoryWarehouse.h"
#include "NPCHouse.h"
#include "OreMines.h"
#include "Crafting.h"
#include "PowerGenerator.h"
#include "TilledSoil.h"
#include "TrophyRoom.h"
#include "WaterWell.h"

BuildingFactory* BuildingFactory::BuildingF_;

BuildingFactory::BuildingFactory()
{
}


BuildingFactory::~BuildingFactory()
{
}

BuildingFactory* BuildingFactory::getBuildingFactory()
{
	if (!BuildingF_)
	{
		BuildingF_ = new BuildingFactory;
	}
	return BuildingF_;
}

Building* BuildingFactory::generateBuilding(int key)
{
	Building* temp = nullptr;
	std::vector<int> tempID(BuildingDataBase::getBuildingDB()->getIDList());
	if (key == tempID[0])
		temp = new Barn;
<<<<<<< HEAD
	if (key == tempID[1])
		temp = new DefenceTower;
	if (key == tempID[2])
		temp = new Crafting;
	if (key == tempID[3])
		temp = new DefensiveWalls;
	if (key == tempID[4])
		temp = new FastTravelRoom;
	if (key == tempID[5])
		temp = new InventoryWarehouse;
	if (key == tempID[6])
		temp = new NPCHouse;
	if (key == tempID[7])
		temp = new OreMines;
	if (key == tempID[8])
		temp = new PowerGenerator;
	if (key == tempID[9])
		temp = new TilledSoil;
	if (key == tempID[10])
		temp = new TrophyRoom;
	if (key == tempID[11])
=======
	else if (key == tempID[1])
		temp = new TrophyRoom;
	else if (key == tempID[2])
		temp = new InventoryWarehouse;
	else if (key == tempID[3])
		temp = new NPCHouse;
	else if (key == tempID[4])
		temp = new FastTravelRoom;
	else if (key == tempID[5])
		temp = new PowerGenerator;
	else if (key == tempID[6])
		temp = new DefenceTower;
	else if (key == tempID[7])
		temp = new DefensiveWalls;
	else if (key == tempID[8])
		temp = new TilledSoil;
	else if (key == tempID[9])
		temp = new OreMines;
	else if (key == tempID[10])
		temp = new Crafting;
	else if (key == tempID[11])
>>>>>>> e463784e665d33d905bb6fe301a67a66d37a2a8a
		temp = new WaterWell;
	return temp;
}