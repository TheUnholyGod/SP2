#ifndef _VEGETABLESTEW_H
#define _VEGETABLESTEW_H

#include "Food.h"
class VegetableStew :
	public Food
{
public:
	VegetableStew(Vector3 = (0, 0, 0));
	~VegetableStew();

	virtual void Eat();
};

#endif