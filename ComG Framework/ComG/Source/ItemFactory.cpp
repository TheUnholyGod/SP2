#include "ItemFactory.h"
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
#include "Projectile.h"

ItemFactory* ItemFactory::ItemF_;

ItemFactory::ItemFactory()
{

}

ItemFactory::~ItemFactory()
{
}

ItemFactory* ItemFactory::getItemFactory()
{
	if (!ItemF_)
	{
		ItemF_ = new ItemFactory;
	}
	return ItemF_;
}

Item* ItemFactory::generateItem(int key)
{
	Item* temp = nullptr;
	std::vector<int> tempID(ItemDataBase::getItemDB()->getIDList());
	if (key == tempID[0])
		temp = new Potato;
	else if (key == tempID[1])
		temp = new Carrot;
	else if (key == tempID[2])
		temp = new Cabbage;
	else if (key == tempID[3])
		temp = new Wheat;
	else if (key == tempID[4])
		temp = new Bread;
	else if (key == tempID[5])
		temp = new VegetableStew;
	else if (key == tempID[6])
		temp = new DrinkingWater;
	else if (key == tempID[7])
		temp = new CarrotJuice;
	else if (key == tempID[8])
		temp = new Salad;
	else if (key == tempID[9])
		temp = new Stone;
	else if (key == tempID[10])
		temp = new Iron;
	else if (key == tempID[11])
		temp = new Copper;
	else if (key == tempID[12])
		temp = new Gold;
	else if (key == tempID[13])
		temp = new Water;
	else if (key == tempID[14])
		temp = new Wood;
	else if (key == tempID[15])
		temp = new Biomass;
	else if (key == tempID[16])
		temp = new Adhesives;
	else if (key == tempID[17])
		temp = new MetalScraps;
	else if (key == tempID[18])
		temp = new Cloth;
	else if (key == tempID[19])
		temp = new CircuitBoards;
	else if (key == tempID[20])
		temp = new Compound_Bow;
	else if (key == tempID[21])
		temp = new Projectile;
	return temp;
}