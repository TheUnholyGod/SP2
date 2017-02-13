#ifndef _FOOD_H
#define _FOOD_H

#include "Item.h"
#include <string>

class Food : public Item
{
protected:
	enum FOODTYPE
	{
		FARMABLES,
		CRAFTABLES,
	}TYPE;

	float nutrition_;//Hunger Replenishment
	float shelf_life_;//Storage Time
public:
	Food(std::string, FOODTYPE, float nutri, float life);
	~Food();

};

#endif