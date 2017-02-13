#ifndef _WHEAT_H
#define _WHEAT_H

#include "Food.h"
class Wheat :
	public Food
{
public:
	Wheat();
	~Wheat();

	virtual void Eat();
};

#endif