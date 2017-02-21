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
	std::vector<int> IDlist;
public:
	~ItemDataBase();
	static ItemDataBase* getItemDB();
	Item* getItem(int key);
	idb& getDataBase();	
	std::vector<int> getIDList() { return IDlist; }
};

#endif