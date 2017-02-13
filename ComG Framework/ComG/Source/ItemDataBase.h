#ifndef _ITEMDATABASE_H
#define _ITEMDATABASE_H

#include "Item.h"
#include <map>

class ItemDataBase
{
private:
	std::map<int, Item*> itemdatabase_;
	ItemDataBase();
	static ItemDataBase* itemdb_;
public:
	~ItemDataBase();
	static ItemDataBase* getItemDB();
};

#endif