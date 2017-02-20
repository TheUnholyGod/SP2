#ifndef _INVENTORY_H
#define _INVENTORY_H

#include "ItemFactory.h"
#include <string>
#include <list>

class Inventory
{
private:
	Inventory();
	static Inventory *inventory;
	std::list<Item*> List;
public:
	static Inventory *getinventory();
	void Additem(int key);
	void Removeitem(Item* item);
	void Update();
	void Render();
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