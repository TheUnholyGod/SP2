#ifndef _ITEMFACTORY_H
#define _ITEMFACTORY_H

#include "Item.h"

class ItemFactory
{
private:
	static ItemFactory* ItemF_;
	ItemFactory();
public:
	~ItemFactory();
	static ItemFactory* getItemFactory();
	static Item* generateItem(int key);
	static Item* SpawnItem(int key, Vector3 position);
};

#endif