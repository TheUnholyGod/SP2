#include "BuildingFactory.h"
#include "BuildingDataBase.h"

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
	Building* temp = BuildingDataBase::getBuildingDB()->getBuilding(key);
	return temp;
}