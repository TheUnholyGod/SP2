#include "ItemFactory.h"
#include "ItemDataBase.h"

ItemFactory* ItemFactory::ItemF_;

ItemFactory::ItemFactory()
{

}

ItemFactory::~ItemFactory()
{
}

ItemFactory* ItemFactory::getItemFactory()
{
	if (!ItemF_)
	{
		ItemF_ = new ItemFactory;
	}
	return ItemF_;
}

Item* ItemFactory::generateItem(int key)
{
	Item* temp = new Item(*(ItemDataBase::getItemDB()->getItem(key)));
	return temp;
}