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

Building* BuildingFactory::generateBuilding(int key, Vector3 position)
{
	Building* temp = nullptr;
	std::vector<int> tempID(BuildingDataBase::getBuildingDB()->getIDList());
	if (key == tempID[0])
		temp = new Barn(position);
	if (key == tempID[1])
		temp = new DefenceTower(position);
	if (key == tempID[2])
		temp = new Crafting(position);
	if (key == tempID[3])
		temp = new DefensiveWalls(position);
	if (key == tempID[4])
		temp = new FastTravelRoom(position);
	if (key == tempID[5])
		temp = new InventoryWarehouse(position);
	if (key == tempID[6])
		temp = new NPCHouse(position);
	if (key == tempID[7])
		temp = new OreMines(position);
	if (key == tempID[8])
		temp = new PowerGenerator(position);
	if (key == tempID[9])
		temp = new TilledSoil(position);
	if (key == tempID[10])
		temp = new TrophyRoom(position);
	if (key == tempID[11])
		temp = new WaterWell(position);
	return temp;
}