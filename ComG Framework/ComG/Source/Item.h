#ifndef _ITEM_H
#define _ITEM_H

#include "GameObject.h"
#include <string>

class Item : public GameObject
{
protected:
	const std::string kname_;
public:
	Item(int,std::string);
	~Item();
};

#endif