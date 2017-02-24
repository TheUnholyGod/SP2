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
	
	bool openinventory;
public:
	std::map<int, int> inv;
	std::map<std::string, int> inv1;
	std::list<std::string> List;
	int quantity;
	std::list<std::string> name;
	static Inventory *getinventory();
	void Additem(int key);
	void Removeitem(Item* item, int key);

	void setupdate();
	void Update(double dt);
	bool getopeninventory();
	std::string getitemname();
	int getsize();
	~Inventory();
	
protected:
	std::string itemname_;
	const std::string getName() { return itemname_; }
};

#endif