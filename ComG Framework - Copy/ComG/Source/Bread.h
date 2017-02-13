#ifndef _BREAD_H
#define _BREAD_H

#include "Food.h"
class Bread :
	public Food
{
public:
	Bread();
	~Bread();
	
	virtual void Eat();
};

#endif