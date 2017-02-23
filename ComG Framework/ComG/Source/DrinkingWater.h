#ifndef _DRINKINGWATER_H
#define _DRINKINGWATER_H

#include "Food.h"
class DrinkingWater :
	public Food
{
public:
	DrinkingWater(Vector3 = (0, 0, 0));
	~DrinkingWater();

	virtual void Eat();
};

#endif