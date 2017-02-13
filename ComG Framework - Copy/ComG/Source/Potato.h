#ifndef _POTATO_H
#define _POTATO_H

#include "Food.h"
class Potato :
	public Food
{
public:
	Potato();
	~Potato();

	virtual void Eat();
};

#endif