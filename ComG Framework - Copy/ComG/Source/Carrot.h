#ifndef _CARROT_H
#define _CARROT_H

#include "Food.h"
class Carrot :
	public Food
{
public:
	Carrot();
	~Carrot();

	virtual void Eat();
};

#endif