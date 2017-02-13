#include "ItemDataBase.h"
#include <list>

ItemDataBase* ItemDataBase::itemdb_;

ItemDataBase::ItemDataBase()
{

}

ItemDataBase::~ItemDataBase()
{
}

ItemDataBase* ItemDataBase::getItemDB()
{
	if (!itemdb_)
	{
		itemdb_ = new ItemDataBase();
	}
	return itemdb_;
}

Item* ItemDataBase::getItem(int key)
{
	return itemdatabase_[key];
}