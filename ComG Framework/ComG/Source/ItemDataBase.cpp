#include "ItemDataBase.h"
#include "Potato.h"
#include "Carrot.h"
#include "Cabbage.h"
#include "Wheat.h"
#include "Bread.h"
#include "CarrotJuice.h"
#include "DrinkingWater.h"
#include "Salad.h"
#include "VegetableStew.h"
#include "Stone.h"
#include "Iron.h"
#include "Copper.h"
#include "Gold.h"
#include "Water.h"
#include "Wood.h"
#include "Biomass.h"
#include "Adhesives.h"
#include "MetalScraps.h"
#include "Cloth.h"
#include "CircuitBoards.h"

ItemDataBase* ItemDataBase::itemdb_;

ItemDataBase::ItemDataBase()
{
	Item* temp = new Potato;
	itemdatabase_[temp->getID()] = new Potato;
	delete temp;
	temp = new Carrot;
	itemdatabase_[temp->getID()] = new Carrot;
	delete temp;
	temp = new Cabbage;
	itemdatabase_[temp->getID()] = new Cabbage;
	delete temp;
	temp = new Wheat;
	itemdatabase_[temp->getID()] = new Wheat;
	delete temp;
	temp = new Bread;
	itemdatabase_[temp->getID()] = new Bread;
	delete temp;
	temp = new VegetableStew;
	itemdatabase_[temp->getID()] = new VegetableStew;
	delete temp;
	temp = new DrinkingWater;
	itemdatabase_[temp->getID()] = new DrinkingWater;
	delete temp;
	temp = new CarrotJuice;
	itemdatabase_[temp->getID()] = new CarrotJuice;
	delete temp;
	temp = new Salad;
	itemdatabase_[temp->getID()] = new Salad;
	delete temp;
	temp = new Stone;
	itemdatabase_[temp->getID()] = new Stone;
	delete temp;
	temp = new Iron;
	itemdatabase_[temp->getID()] = new Iron;
	delete temp;
	temp = new Copper;
	itemdatabase_[temp->getID()] = new Copper;
	delete temp;
	temp = new Gold;
	itemdatabase_[temp->getID()] = new Gold;
	delete temp;
	temp = new Water;
	itemdatabase_[temp->getID()] = new Water;
	delete temp;
	temp = new Wood;
	itemdatabase_[temp->getID()] = new Wood;
	delete temp;
	temp = new Biomass;
	itemdatabase_[temp->getID()] = new Biomass;
	delete temp;
	temp = new Adhesives;
	itemdatabase_[temp->getID()] = new Adhesives;
	delete temp;
	temp = new MetalScraps;
	itemdatabase_[temp->getID()] = new MetalScraps;
	delete temp;
	temp = new Cloth;
	itemdatabase_[temp->getID()] = new Cloth;
	delete temp;
	temp = new CircuitBoards;
	itemdatabase_[temp->getID()] = new CircuitBoards;
	delete temp;
}

ItemDataBase::~ItemDataBase()
{
}

ItemDataBase* ItemDataBase::getItemDB()
{
	if (!itemdb_)
	{
		itemdb_ = new ItemDataBase();
	}
	return itemdb_;
}

Item* ItemDataBase::getItem(int key)
{
	return itemdatabase_[key];
}

ItemDataBase::idb& ItemDataBase::getDataBase()
{
	return itemdatabase_;
}