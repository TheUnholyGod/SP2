#ifndef _POTATO_H
#define _POTATO_H

#include "Food.h"
class Potato :
	public Food
{
public:
	Potato(Vector3=(0, 0, 10));
	~Potato();

	virtual void Eat();
};

#endif