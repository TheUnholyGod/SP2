#ifndef _RESOURCES_H
#define _RESOURCES_H

#include "Item.h"
#include <string>

class Resources : public Item
{
protected:
	enum RESOURCETYPE
	{
		MINING,
		NATURE,
		LOOT,
	};
	const RESOURCETYPE kTYPE_;
	const int krarity_;
	//float weight;(optional)
public:
	Resources(std::string, RESOURCETYPE, int);
	~Resources();
};

#endif