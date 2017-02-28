#ifndef _BREAD_H
#define _BREAD_H

#include "Food.h"
class Bread : public Food
{
public:
	Bread(Vector3 = (0, 0, 0));
	~Bread();
	
	virtual void Eat();
};

#endif