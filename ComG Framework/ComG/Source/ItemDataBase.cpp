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
#include "Compound_Bow.h"
#include "Glock_17C.h"
#include "M200_CheyTac_Intervention.h"
#include "Scar-H.h"
#include "Farming_Hoe.h"
#include "Katana_Sword.h"
#include "Kitchen_Knife.h"
#include "Projectile.h"

ItemDataBase* ItemDataBase::itemdb_;

ItemDataBase::ItemDataBase()
{
	Item* temp = new Potato;
	itemdatabase_[temp->getID()] = new Potato;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Cabbage;
	itemdatabase_[temp->getID()] = new Cabbage;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Carrot;
	itemdatabase_[temp->getID()] = new Carrot;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Wheat;
	itemdatabase_[temp->getID()] = new Wheat;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Bread;
	itemdatabase_[temp->getID()] = new Bread;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new VegetableStew;
	itemdatabase_[temp->getID()] = new VegetableStew;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new DrinkingWater;
	itemdatabase_[temp->getID()] = new DrinkingWater;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new CarrotJuice;
	itemdatabase_[temp->getID()] = new CarrotJuice;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Salad;
	itemdatabase_[temp->getID()] = new Salad;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Stone;
	itemdatabase_[temp->getID()] = new Stone;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Iron;
	itemdatabase_[temp->getID()] = new Iron;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Copper;
	itemdatabase_[temp->getID()] = new Copper;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Gold;
	itemdatabase_[temp->getID()] = new Gold;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Water;
	itemdatabase_[temp->getID()] = new Water;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Wood;
	itemdatabase_[temp->getID()] = new Wood;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Biomass;
	itemdatabase_[temp->getID()] = new Biomass;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Adhesives;
	itemdatabase_[temp->getID()] = new Adhesives;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new MetalScraps;
	itemdatabase_[temp->getID()] = new MetalScraps;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Cloth;
	itemdatabase_[temp->getID()] = new Cloth;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new CircuitBoards;
	itemdatabase_[temp->getID()] = new CircuitBoards;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Kitchen_Knife;
	itemdatabase_[temp->getID()] = new Kitchen_Knife;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Katana_Sword;
	itemdatabase_[temp->getID()] = new Katana_Sword;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Farming_Hoe;
	itemdatabase_[temp->getID()] = new Farming_Hoe;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Glock_17C;
	itemdatabase_[temp->getID()] = new Glock_17C;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Scar_H;
	itemdatabase_[temp->getID()] = new Scar_H;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new M200_CheyTac_Intervention;
	itemdatabase_[temp->getID()] = new M200_CheyTac_Intervention;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Compound_Bow;
	itemdatabase_[temp->getID()] = new Compound_Bow;
	IDlist.push_back(temp->getID());
	delete temp;
	temp = new Projectile;
	itemdatabase_[temp->getID()] = new Projectile;
	IDlist.push_back(temp->getID());
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