#include "Inventory.h"

Inventory* Inventory::inventory;

Inventory::Inventory()
{

}

Inventory* Inventory::getinventory()
{
	if (!inventory)
	{
		inventory = new Inventory();
	}
	return inventory;
}

Inventory::~Inventory()
{

}

void Inventory::Additem(int key)
{
	Item* temp = new Item(*ItemFactory::getItemFactory()->generateItem(key));
	List.push_back(temp);
}

void Inventory::Removeitem(Item* item)
{
	Item* Remove = item;
	List.remove(Remove);
	delete Remove;
}
