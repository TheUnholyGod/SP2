#ifndef _CARROT_H
#define _CARROT_H

#include "Food.h"
class Carrot :
	public Food
{
public:
	Carrot(Vector3=(2, 0, 15));
	~Carrot();

	virtual void Eat();
};

#endif