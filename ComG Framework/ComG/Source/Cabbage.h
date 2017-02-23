#ifndef _CABBAGE_H
#define _CABBAGE_H

#include "Food.h"
class Cabbage :
	public Food
{
public:
	Cabbage(Vector3 = (0, 0, 0));
	~Cabbage();

	virtual void Eat();
};

#endif