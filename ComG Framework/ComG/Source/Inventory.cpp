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

void Inventory::Removeitem(int item, int key)
{
	if (inv[item])
	{
		if(inv[item]>key)
		inv[item]-=key;
		
		else
		{
			inv[item] = 0;
			inv.erase(item);
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
	return inv.size();
}

void Inventory::reset()
{
	if (inv.size())
	{
		inv.erase(inv.begin(), inv.end());
	}
}