#ifndef _ITEMFACTORY_H
#define _ITEMFACTORY_H

#include "Source\Item.h"

class ItemFactory
{
private:
	static ItemFactory* ItemF_;
	ItemFactory();
public:
	~ItemFactory();
	static ItemFactory* getItemFactory();
	static Item* generateItem(int key);
};

#endif