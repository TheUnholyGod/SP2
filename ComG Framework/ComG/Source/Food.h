#ifndef _FOOD_H
#define _FOOD_H

#include "Item.h"

class Food : public Item
{
protected:
	enum FOODTYPE
	{
		FARMABLE,
		CRAFTABLE,
	}TYPE;
	float nutrition_;//Hunger Replenishment
	float shelf_life_;//Storage Time
public:
	Food(int,std::string,FOODTYPE,float,float);
	~Food();

	virtual void Eat()=0;
};

#endif