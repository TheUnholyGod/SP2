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
}

void Inventory::Removeitem(Item* item)
{
	Item* Remove = item;
	//List.remove(Remove);
	//inv.erase(Remove);
	delete Remove;
}

void Inventory::setupdate()
{
	openinventory = !openinventory;
}

void Inventory::Update(double dt)
{
	std::cout << "List: " << List.size() << std::endl;
	std::cout << "Map: " << inv.size() << std::endl;
	std::cout << itemname_ << " added" << std::endl;
	for (std::map<int, int>::iterator i = inv.begin(); i != inv.end(); i++)
	{
		std::cout << i->first << "=> " << i->second << std::endl;
	}
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