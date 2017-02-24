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
		List.push_back(temp->getName());
		inv[key] = 1;
	}
	/*Item* temp = new Item(*ItemFactory::getItemFactory()->generateItem(key));
	std::string name = temp->getName();
	if (inv1[name])
		inv1[name]++;
	else
	{
		inv1[name] = 1;
	}*/
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
			List.remove(item->getName());

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
	//std::cout << "List: " << List.size() << std::endl;
	std::cout << "Map: " << inv1.size() << std::endl;
	std::cout << itemname_ << " added" << std::endl;
	for (std::map<int, int>::iterator i = inv.begin(); i != inv.end(); i++)
	{
		std::cout << i->first << "=> " << i->second << std::endl;
	}
	/*for (std::map<std::string, int>::iterator i = inv1.begin(); i != inv1.end(); i++)
	{
		std::cout << i->first << "=> " << i->second << std::endl;
	}*/
}

bool Inventory::getopeninventory()
{
	bool open;
	open = openinventory;
	return open;
}

std::string Inventory::getitemname()
{
	std::string name;
	name = itemname_;
	return name;
}

int Inventory::getsize()
{
	int size;
	size = List.size();
	return size;
}

