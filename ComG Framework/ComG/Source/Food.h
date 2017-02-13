#ifndef _FOOD_H
#define _FOOD_H

#include "Item.h"

class Food : public Item
{
public:
	Food();
	~Food();
private:
	float nutrition;//Hunger Replenishment
	float shelf_life_;//Storage Time
};

#endif