#ifndef _INVENTORY_H
#define _INVENTORY_H

#include "Application.h"
#include "ItemFactory.h"
#include <string>
#include <list>
#include <sstream>
#include <map>
#include <utility>

class Inventory
{
private:
	Inventory();
	static Inventory *inventory;
	std::map<int, int> inv;
	std::list<std::string> List;
	int quantity;
	std::list<std::string> name;
	bool openinventory;
public:
	static Inventory *getinventory();
	void Additem(int key);
	void Removeitem(Item* item, int key);

	void setupdate();
	void Update(double dt);
	bool getopeninventory();
	std::string getitemname();
	int getsize();
	~Inventory();
	std::map<int, int> getInventoryContents() { return inv; }
	void reset();
protected:
	std::string itemname_;
	const std::string getName() { return itemname_; }
};

#endif