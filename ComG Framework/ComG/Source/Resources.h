#ifndef _RESOURCES_H
#define _RESOURCES_H

#include "Item.h"
#include <string>

class Resources : public Item
{
public:
	Resources();
	~Resources();
private:
	int rarity;
	std::string type;
	//float weight;(optional)
};

#endif