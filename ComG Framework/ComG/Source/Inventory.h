#ifndef _INVENTORY_H
#define _INVENTORY_H

#include "Application.h"
#include "ItemFactory.h"
#include <string>
#include <list>

class Inventory
{
private:
	Inventory();
	static Inventory *inventory;
	std::list<Item*> List;
	bool openinventory;
public:
	static Inventory *getinventory();
	void Additem(int key);
	void Removeitem(Item* item);
	void setupdate();
	void Update(double dt);
	bool getopeninventory();
	~Inventory();
protected:
	std::string itemname_;
};

#endif

/*TO Do:
-pick up(additem())
-move in inventory(Update())
-render(render())
*/