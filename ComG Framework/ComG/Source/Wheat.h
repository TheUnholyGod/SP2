#ifndef _WHEAT_H
#define _WHEAT_H

#include "Food.h"
class Wheat :
	public Food
{
public:
	Wheat(Vector3 = (0, 0, 0));
	~Wheat();

	virtual void Eat();
};

#endif