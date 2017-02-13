#ifndef _ITEM_H
#define _ITEM_H

#include <string>

class Item
{
protected:
	const std::string kname_;
public:
	Item(std::string);
	~Item();
};

#endif