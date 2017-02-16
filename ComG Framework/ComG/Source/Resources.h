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
	std::string source_location_;
	//float weight;(optional)
public:
	Resources(int,std::string,std::string,RESOURCETYPE, int);
	~Resources();
};

#endif