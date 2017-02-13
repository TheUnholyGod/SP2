#include "ItemDataBase.h"

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