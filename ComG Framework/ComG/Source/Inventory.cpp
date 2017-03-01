#include "Inventory.h"

Inventory* Inventory::inventory;

Inventory::Inventory()
{
	openinventory = false;
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
	inv.erase(inv.begin(), inv.end());
	List.erase(List.begin(), List.end());
}

void Inventory::Additem(int key)
{
	
	if (inv[key])
		inv[key]++;
	else
	{
		Item* temp = new Item(*ItemFactory::getItemFactory()->generateItem(key));
		itemname_ = temp->getName();
		inv[key] = 1;
	}
}

void Inventory::Removeitem(Item* item, int key)
{
	if (inv[key])
	{
		if(inv[key]>1)
		inv[key]--;
		
		else
		{
			Item* Remove = item;
			delete Remove;
		}
	}
	else
	{
		std::cout << "No such item in inventory" << std::endl;
	}
}

void Inventory::setupdate()
{
	openinventory = !openinventory;
}

void Inventory::Update(double dt)
{
	std::cout << "Type: " << inv.size() << std::endl;
	for (std::map<int, int>::iterator i = inv.begin(); i != inv.end(); i++)
	{
		std::cout << i->first << "=> " << i->second << std::endl;
	}
}

bool Inventory::getopeninventory()
{
	return openinventory;
}

std::string Inventory::getitemname()
{
	return itemname_;
}

int Inventory::getsize()
{
	return List.size();
}

