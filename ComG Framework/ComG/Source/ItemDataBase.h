#ifndef _ITEMDATABASE_H
#define _ITEMDATABASE_H

#include "Item.h"
#include <map>

class ItemDataBase
{
public:
	typedef std::map<int, Item*> idb;
private:
	idb itemdatabase_;
	ItemDataBase();
	static ItemDataBase* itemdb_;
public:
	~ItemDataBase();
	static ItemDataBase* getItemDB();
	Item* getItem(int key);
	idb& getDataBase();
};

#endif