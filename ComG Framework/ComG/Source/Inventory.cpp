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
	Item* temp = new Item(*ItemFactory::getItemFactory()->generateItem(key));
	List.push_back(temp);
	std::stringstream ss;
	ss << temp->getName();
	itemname_ = ss.str();
	name.push_back(itemname_);
}

void Inventory::Removeitem(Item* item)
{
	Item* Remove = item;
	List.remove(Remove);
	delete Remove;
}

void Inventory::setupdate()
{
	openinventory = !openinventory;
}

void Inventory::Update(double dt)
{
	std::cout << "List: " << List.size() << std::endl;
	std::cout << itemname_ << " added" << std::endl;
	for (std::list<std::string>::iterator i = name.begin(); i != name.end(); i++)
	{
		std::cout << *i << std::endl;
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